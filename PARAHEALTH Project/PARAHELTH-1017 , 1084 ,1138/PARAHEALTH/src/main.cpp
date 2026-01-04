#define BLYNK_TEMPLATE_ID "TMPL6d0FXh4ic"
#define BLYNK_TEMPLATE_NAME "PARAHEALTH"
#define BLYNK_AUTH_TOKEN "rtyJP2NAXaFCw4Pbzmp8gCZxs-SnAKGY"
#include <Wire.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "MAX30100_PulseOximeter.h"
#include <DHT.h>

char ssid[] = "AA";
char pass[] = "123qwerty";

#define MAX30100_SDA 21
#define MAX30100_SCL 22
#define DHT11_PIN 5      
#define LM35_PIN 34      
#define BUZZER_PIN 23    

#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);

PulseOximeter pox;
float heartRate = 0;
uint8_t spO2 = 0;
bool blynkConnected = false;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

float bodyTemp = 0.0;
float roomTemp = 0.0;
float humidity = 0.0;
uint32_t lastSensorUpdate = 0;
bool manualLog = false;
bool resetAlarm = false;

bool alarmActive = false;
String alarmMessage = "";
uint32_t alarmStartTime = 0;
const uint32_t ALARM_TIMEOUT = 30000;

const float MIN_HR = 40.0;
const float MAX_HR = 180.0;
const float MIN_SPO2 = 90.0;
const float MIN_TEMP = 36.0;
const float MAX_TEMP = 39.0;

void sensorTask(void *parameter) {
  Serial.println("MAX30100 task started on Core " + String(xPortGetCoreID()));
  
  Wire.begin(MAX30100_SDA, MAX30100_SCL);
  
  if (!pox.begin()) {
    Serial.println("MAX30100 init failed!");
    while(1);
  }
  
  pox.setIRLedCurrent(MAX30100_LED_CURR_50MA);
  
  for(;;) {
    pox.update();
    
    portENTER_CRITICAL(&mux);
    float hr = pox.getHeartRate();
    uint8_t spo2Val = pox.getSpO2();
    
    if (hr > 0) heartRate = hr;
    if (spo2Val > 0) spO2 = spo2Val;
    portEXIT_CRITICAL(&mux);
    
    delay(1);
  }
}

void buzzerOn() {
  digitalWrite(BUZZER_PIN, HIGH);
  alarmActive = true;
  alarmStartTime = millis();
}

void buzzerOff() {
  digitalWrite(BUZZER_PIN, LOW);
  alarmActive = false;
  alarmMessage = "";
}

void beepPattern(int beeps) {
  for(int i = 0; i < beeps; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

void checkAlarmConditions(float hr, float spo2, float temp) {
  if (hr <= 0 || spo2 <= 0 || temp <= 0) return;
  
  String newAlarmMessage = "";
  
  if (hr < MIN_HR) {
    newAlarmMessage = "LOW Heart Rate: " + String(hr, 0) + " BPM";
  } else if (hr > MAX_HR) {
    newAlarmMessage = "HIGH Heart Rate: " + String(hr, 0) + " BPM";
  }
  else if (spo2 < MIN_SPO2) {
    newAlarmMessage = "LOW SpO2: " + String(spo2) + "%";
  }
  else if (temp < MIN_TEMP) {
    newAlarmMessage = "LOW Temperature: " + String(temp, 1) + "°C";
  } else if (temp > MAX_TEMP) {
    newAlarmMessage = "HIGH Temperature: " + String(temp, 1) + "°C";
  }
  
  if (newAlarmMessage.length() > 0) {
    if (!alarmActive || alarmMessage != newAlarmMessage) {
      alarmMessage = newAlarmMessage;
      buzzerOn();
      beepPattern(5);
      
      if (blynkConnected) {
        Blynk.virtualWrite(V10, "!!! " + alarmMessage);
        Blynk.logEvent("health_alert", alarmMessage);
      }
      
      Serial.println("ALARM: " + alarmMessage);
    }
  } else if (alarmActive) {
    buzzerOff();
    if (blynkConnected) {
      Blynk.virtualWrite(V10, "All parameters normal");
    }
    Serial.println("Alarm cleared - all parameters normal");
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("\n=== PARAHEALTH MONITOR WITH ALARM ===");
 
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.println("... buzzer...");
  beepPattern(2);
  delay(500);
  
  xTaskCreatePinnedToCore(
    sensorTask,
    "SensorTask",
    10000,
    NULL,
    1,
    NULL,
    1
  );
  
  delay(100);
  
  dht.begin();
  delay(1000);
  
  analogReadResolution(12);
  analogSetPinAttenuation(LM35_PIN, ADC_11db); 
  
  pinMode(LM35_PIN, INPUT);
  
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  WiFi.setSleep(false);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n WiFi Connected!");
    
    Blynk.config(BLYNK_AUTH_TOKEN);
    if (Blynk.connect(3000)) {
      blynkConnected = true;
      Serial.println(" Blynk Connected!");
      Blynk.virtualWrite(V10, "System Online - Waiting for readings...");
    }
  }
  
  Serial.println("\n=== SENSOR READINGS ===");
  Serial.println("Time\tHR\tSpO2\tBody°C\tRoom°C\tHumid%\tAlarm");
  Serial.println("------------------------------------------------------------");
}

void readDHT11() {
  static uint8_t dhtFailCount = 0;
  
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  if (isnan(temp) || isnan(hum)) {
    dhtFailCount++;
    if (dhtFailCount > 3) {
      Serial.println("DHT11 read error");
      dhtFailCount = 0;
    }
    return;
  }
  
  dhtFailCount = 0;
  
  if (temp >= 0 && temp <= 50) roomTemp = temp;
  if (hum >= 0 && hum <= 100) humidity = hum;
}

float readLM35() {
  // Take 5 quick readings
  int samples = 5;
  long sum = 0;
  
  for(int i = 0; i < samples; i++) {
    sum += analogRead(LM35_PIN);
    delay(2);
  }
  
  float avgADC = (float)sum / samples;
  
  
  float temperature = avgADC * 0.08057;
  
  return temperature;
}

void loop() {
  if (blynkConnected) {
    Blynk.run();
  }
  
  if (alarmActive && (millis() - alarmStartTime > ALARM_TIMEOUT)) {
    buzzerOff();
    if (blynkConnected) {
      Blynk.virtualWrite(V10, " Alarm timeout - check patient");
    }
  }
  
  if (millis() - lastSensorUpdate > 2000) {
    readDHT11();
    bodyTemp = readLM35();
    
    float currentHR, currentSpO2;
    portENTER_CRITICAL(&mux);
    currentHR = heartRate;
    currentSpO2 = spO2;
    portEXIT_CRITICAL(&mux);
    
    checkAlarmConditions(currentHR, currentSpO2, bodyTemp);
    
    if (blynkConnected) {
      if (currentHR > 0 && currentHR < 200) Blynk.virtualWrite(V0, currentHR);
      if (currentSpO2 > 0 && currentSpO2 <= 100) Blynk.virtualWrite(V1, currentSpO2);
      if (bodyTemp > 15 && bodyTemp < 50) Blynk.virtualWrite(V2, bodyTemp);
      if (roomTemp > 0 && roomTemp < 50) Blynk.virtualWrite(V3, roomTemp);
      if (humidity > 0 && humidity <= 100) Blynk.virtualWrite(V4, humidity);
    }
    
    Serial.print(millis()/1000);
    Serial.print("s\t");
    Serial.print(currentHR > 0 ? String(currentHR, 0) : "--");
    Serial.print("\t");
    Serial.print(currentSpO2 > 0 ? String(currentSpO2) : "--");
    Serial.print("\t");
    Serial.print(bodyTemp > 0 ? String(bodyTemp, 1) : "--");
    Serial.print("\t");
    Serial.print(roomTemp > 0 ? String(roomTemp, 1) : "--");
    Serial.print("\t");
    Serial.print(humidity > 0 ? String(humidity, 0) : "--");
    Serial.print("\t");
    
    if (alarmActive) {
      Serial.print("!!!");
    } else if (currentHR > 0 && currentSpO2 > 0 && bodyTemp > 0) {
      Serial.print("--");
    } else {
      Serial.print("__");
    }
    Serial.println();
    
    lastSensorUpdate = millis();
  }
  
  delay(10);
}

BLYNK_WRITE(V5) {
  manualLog = param.asInt();
  if (manualLog && blynkConnected) {
    Blynk.virtualWrite(V10, "Manual log saved");
    Serial.println("Manual log triggered");
    manualLog = false;
    Blynk.virtualWrite(V5, 0);
  }
}

BLYNK_WRITE(V11) {
  resetAlarm = param.asInt();
  if (resetAlarm && blynkConnected) {
    buzzerOff();
    Blynk.virtualWrite(V10, "Alarm manually reset");
    Serial.println("Alarm manually reset");
    resetAlarm = false;
    Blynk.virtualWrite(V11, 0);
  }
}