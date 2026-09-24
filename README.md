<div align="center">

# ChildCare AI Guardian

**Paediatric wearable fusing IR thermometry, electrodermal activity and pulse into a distress signal**

![Domain](https://img.shields.io/badge/Domain-Multi--Sensor_Fusion-00F3FF?style=for-the-badge) ![Platform](https://img.shields.io/badge/Platform-ESP32_Edge-9D00FF?style=for-the-badge) ![Sensors](https://img.shields.io/badge/Sensors-3_Channel_Fusion-0066FF?style=for-the-badge)

![ESP32](https://img.shields.io/badge/ESP32-0D1117?style=flat-square&logo=espressif&logoColor=white) ![Arduino](https://img.shields.io/badge/Arduino-0D1117?style=flat-square&logo=arduino&logoColor=white) ![C++](https://img.shields.io/badge/C++-0D1117?style=flat-square&logo=cplusplus&logoColor=white) ![MLX90614](https://img.shields.io/badge/MLX90614-0D1117?style=flat-square) ![GSR](https://img.shields.io/badge/GSR-0D1117?style=flat-square) ![PPG](https://img.shields.io/badge/PPG-0D1117?style=flat-square)

</div>

---

## Overview

A wearable for nursery and paediatric monitoring that reads three physiological channels at once —
contactless skin temperature, electrodermal activity, and pulse rate — and fuses them into a single
state assessment covering fever and distress.

The fusion step is the point. Any one channel on its own is noisy and ambiguous: a raised heart rate
could be a child running around, and elevated skin conductance could be a warm room. Requiring
*both* to be elevated simultaneously is what separates genuine distress from ordinary active play.

## Domain &amp; Techniques

| Layer | Implementation |
| :--- | :--- |
| **Contactless Thermometry** | MLX90614 IR thermopile reads skin temperature without contact, avoiding irritation on sensitive skin |
| **Electrodermal Activity** | GSR channel normalised from raw 12-bit ADC into a 0&ndash;100% conductance scale |
| **Pulse** | Optical PPG sensor on a second ADC channel |
| **Fusion Rule** | Distress requires conductance &gt; 65% <em>and</em> pulse &gt; 115 BPM together — the conjunction is what rejects the active-play false positive |
| **Fever Detection** | Independent threshold on skin temperature at 38&nbsp;&deg;C, evaluated separately from the distress path |

## Pipeline

```
MLX90614 (IR temp) ---------------------> [ >= 38.0 C ] --> fever flag

GSR ---> normalise to 0-100% --+
                               |--> [ conductance > 65%  AND  BPM > 115 ] --> distress flag
Pulse sensor ---> BPM ---------+
```

## Pinout

| Sensor | Interface | Pins | Description |
| --- | --- | --- | --- |
| MLX90614 | I2C | GPIO 21 (SDA), 22 (SCL) | Medical IR Temperature |
| GSR Sensor | Analog | GPIO 34 (ADC1) | Skin Conductance |
| Pulse Sensor | Analog | GPIO 35 (ADC1) | Optical Heart Rate |

## Repository Layout

| Path | Purpose |
| :--- | :--- |
| `ChildCareGuardian.ino` | Main firmware — sensor polling and alert dispatch |
| `stress_model.h` | `evaluateVitals()` — normalisation and the fever / distress decision rules |
| `config.example.h` | Thresholds — copy to `config.h` |

## Project Status

**Implemented:** three-channel acquisition, conductance normalisation, and a deterministic rule-based
fusion model for fever and distress.

**Roadmap:** the decision boundary is currently hand-tuned rather than learned. The natural next step
is to log labelled sessions (calm / active / distressed) and fit a small decision tree or logistic
model over the same three features — a change that would replace the fixed thresholds with a
per-child adaptive boundary without altering the sensor stack.

> Research prototype. Not a certified medical device.

---

<div align="center">
  <sub>
    Part of the <b>AI + Robotics</b> engineering portfolio of
    <a href="https://github.com/divyansh-sachdev">Divyansh Sachdev</a><br>
    90+ national &amp; international competition wins &middot; IIT / NIT / IIIT podiums
  </sub>
</div>
