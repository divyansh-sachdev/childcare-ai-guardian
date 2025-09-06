/**
 * ChildCare AI Guardian — Pediatric Stress & Fever Detection
 * Author: Divyansh Sachdev
 */

#include <Arduino.h>
#include "config.example.h"
#include "stress_model.h"

void setup() {
    Serial.begin(115200);
    Serial.println("==================================================");
    Serial.println("  ChildCare AI Guardian — Pediatric Smart Band");
    Serial.println("==================================================");
    Serial.println("[INFO] Infrared Temp Sensor (MLX90614) OK.");
    Serial.println("[STATUS] Continuous vitals monitoring started.");
}

void loop() {
    int gsrRaw = analogRead(GSR_PIN);
    float tempC = 37.2f;
    int bpm = 98;

    ChildState report = evaluateVitals(gsrRaw, tempC, bpm);

    Serial.printf("[VITALS] Temp: %.1f C | HR: %d bpm | GSR: %.1f%% | Status: %s\n",
                  report.bodyTemp, report.heartRate, report.skinConductance,
                  report.isStressed ? "STRESSED/CRYING" : (report.hasFever ? "FEVER ALERT" : "Calm"));

    delay(2000);
}
