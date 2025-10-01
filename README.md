# ChildCare AI Guardian

An edge-AI wearable tailored for pediatric care and nursery monitoring. Tracks continuous skin temperature, electrodermal activity (GSR), and pulse rate to detect fevers, dehydration spikes, and emotional distress or crying episodes before they escalate.

## Sensor Architecture

- **Contactless Skin Thermometry**: MLX90614 infrared thermopile sensor prevents skin irritation.
- **Electrodermal Response (GSR)**: Measures autonomic nervous system sweat gland activation.
- **Adaptive Vitals Fusion**: Machine learning heuristic correlates elevated pulse with skin conductance changes to differentiate active play from distress.

## Pinout Table

| Sensor | Interface | Pins | Description |
| --- | --- | --- | --- |
| MLX90614 | I2C | GPIO 21 (SDA), 22 (SCL) | Medical IR Temperature |
| GSR Sensor | Analog | GPIO 34 (ADC1) | Skin Conductance |
| Pulse Sensor | Analog | GPIO 35 (ADC1) | Optical Heart Rate |
