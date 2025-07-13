// 🔥 Smart Plant System Code (Fully Updated)

#define BLYNK_TEMPLATE_ID "TMPL3GNAX5iTd"
#define BLYNK_TEMPLATE_NAME "Smart Plant"
#define BLYNK_AUTH_TOKEN "yPnAsLtlugH0b6LDdXZ_ricupMqYaZZh"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "";     
char pass[] = "";     

// Pin Definitions
#define RELAY_PIN D1
#define DHTPIN D4
#define PIR_PIN D2
#define SOIL_MOISTURE_PIN A0

// DHT Sensor setup
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Control variables
bool pir_enabled = false;
bool pump_manual_control = false;
bool pump_auto_running = false;
unsigned long pumpStartTime = 0;
const unsigned long pumpDuration = 5000; // 5 seconds

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Pump OFF initially

  pinMode(PIR_PIN, INPUT);
  
  dht.begin();
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

// BLYNK_WRITE for PIR Switch (V6)
BLYNK_WRITE(V6)
{
  pir_enabled = param.asInt();
  if (pir_enabled) {
    Serial.println("PIR Sensor Enabled");
  } else {
    Serial.println("PIR Sensor Disabled");
  }
}

// BLYNK_WRITE for Pump Switch (V12)
BLYNK_WRITE(V12)
{
  int buttonState = param.asInt();
  if (buttonState == 1) {
    pump_manual_control = true;
    pump_auto_running = false;
    digitalWrite(RELAY_PIN, LOW); // Turn ON pump
    Serial.println("Pump ON via Manual Blynk Switch");
  } else {
    pump_manual_control = false;
    pump_auto_running = false;
    digitalWrite(RELAY_PIN, HIGH); // Turn OFF pump
    Serial.println("Pump OFF via Manual Blynk Switch");
  }
}

// Function to read sensors and handle auto watering
void sendSensorData()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int soilMoistureRaw = analogRead(SOIL_MOISTURE_PIN);
  int soilMoisturePercent = map(soilMoistureRaw, 1023, 400, 0, 100);
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print readings
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.print("°C  ");
  Serial.print("Soil Moisture Raw: ");
  Serial.print(soilMoistureRaw);
  Serial.print("  Soil Moisture %: ");
  Serial.println(soilMoisturePercent);

  // Send to Blynk App
  Blynk.virtualWrite(V0, t);      // Temperature
  Blynk.virtualWrite(V1, h);      // Humidity
  Blynk.virtualWrite(V3, soilMoisturePercent); // Soil Moisture %

  // 🌱 Auto Watering Logic
  if (soilMoisturePercent < 30 && !pump_manual_control && !pump_auto_running) {
    Serial.println("Soil moisture low! Starting pump automatically...");
    
    digitalWrite(RELAY_PIN, LOW);         // Turn ON pump
    Blynk.virtualWrite(V12, 1);            // Update manual switch ON
    Blynk.logEvent("pumping", String("Auto watering started! Soil moisture was ") + soilMoisturePercent + "%");

    pump_auto_running = true;
    pumpStartTime = millis();
  }
}

// Function to check PIR sensor
void checkPIR()
{
  if (pir_enabled) {
    int motionDetected = digitalRead(PIR_PIN);
    if (motionDetected == HIGH) {
      Serial.println("Motion Detected near Plants! 🌱🚶‍♂️");
      Blynk.logEvent("motion_detected", "Motion detected near your plants!");
      delay(2000); // Small delay to prevent spamming
    }
  }
}

void loop()
{
  Blynk.run();

  // Send sensor data every 5 seconds
  static unsigned long lastSensorRead = 0;
  if (millis() - lastSensorRead > 5000) {
    sendSensorData();
    lastSensorRead = millis();
  }

  checkPIR();

  // Auto-pump timing management
  if (pump_auto_running && (millis() - pumpStartTime >= pumpDuration)) {
    if (!pump_manual_control) {
      digitalWrite(RELAY_PIN, HIGH); // Turn OFF pump
      Blynk.virtualWrite(V12, 0);    // Update manual switch OFF
      Serial.println("Auto watering finished.");
    }
    pump_auto_running = false;
  }
}
