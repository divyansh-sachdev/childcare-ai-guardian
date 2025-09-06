#ifndef STRESS_MODEL_H
#define STRESS_MODEL_H

#include <Arduino.h>

struct ChildState {
    float skinConductance;
    float bodyTemp;
    int   heartRate;
    bool  isStressed;
    bool  hasFever;
};

inline ChildState evaluateVitals(int gsrRaw, float tempC, int bpm) {
    ChildState state;
    state.skinConductance = (4095.0f - gsrRaw) / 40.95f; // 0-100%
    state.bodyTemp = tempC;
    state.heartRate = bpm;
    
    state.hasFever = (tempC >= 38.0f);
    // Elevated GSR coupled with tachycardia indicates distress/pain
    state.isStressed = (state.skinConductance > 65.0f && bpm > 115);
    
    return state;
}

#endif
