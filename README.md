# Threshold Detector

**Threshold Detector** is an Arduino-Python-based system designed to monitor and analyze real-time noise levels in classrooms or other environments. It detects noise fluctuations, classifies them into thresholds (e.g., Silent, Low, Medium, High), and provides useful insights about noise trends. The system helps track engagement and identify patterns in classroom behavior over time.

---

## Features

- **Real-Time Noise Monitoring**: Reads noise fluctuation data from an Arduino board via a sound sensor and visualizes it dynamically.
- **Threshold Classification**: Categorizes noise levels into predefined thresholds—Silent, Low, Medium, and High.
- **Data Logging**: Stores timestamped noise fluctuation data in a CSV file for analysis and future reference.
- **Data Analysis**: Provides insights such as the percentage of time the environment remained silent.
- **Interactive Interface**: Offers a Pygame GUI for starting data collection and viewing analysis results.

---

## Requirements

### Hardware
- **Arduino Board** (e.g., Arduino Uno)
- **Sound Sensor** (e.g., KY-037 or similar)
- USB cable for connecting the Arduino to a computer

### Software
- Python 3.x
- Arduino IDE
- Required Python Libraries:
  - `pygame`
  - `serial`
  - `matplotlib`

---

## Installation

1. Clone this repository or download the source code:
   ```bash
   git clone https://github.com/your-repo/threshold-detector.git
   cd threshold-detector
   ```

2. Install the required Python libraries:
   ```bash
   pip install pygame pyserial matplotlib
   ```  
3. Upload the Arduino code for reading sound sensor data to your Arduino board using the Arduino IDE.

---

## Usage

1. Connect the Arduino to your computer via USB.

2. Ensure the correct serial port (COM3, ttyUSB0, etc.) is set in the Python code.

3. Run the Python script:

```bash
python threshold_detector.py
```

4. Use the GUI:

- Start Data Collection: Begin collecting and visualizing noise data in real time.
- Show Data Analysis: View insights like the percentage of silence during the session.


---

## File Structure
- include/ : contains the readme files for headers
- lib/ : The libraries in the project for Arduino
- src/: Contains the source code file (Upload that to the Arduino.)
- test/ : Used as a test folder (Only for testing code)
- Monitor.py : Main Python script for the project.
- noise_data.csv: CSV file to log noise fluctuation data.
- README.md: Documentation for the project.

--- 

## How It Works
1. Data Collection: The Arduino reads noise fluctuation data and sends it to the Python application via the serial port.
2. Real-Time Visualization: Noise levels are plotted dynamically using Matplotlib.
3. Thresholds:
    - Silent: Below 40 fluctuations
    - Low: Between 40–70 fluctuations
    - Medium: Between 70–90 fluctuations
    - High: Above 90 fluctuations

4. Data Analysis: Calculates the percentage of silence in the recorded session and displays it in the GUI.

---

## Possible Future Enhancements

- Noise Trend Analysis: Add advanced visualizations for long-term data trends.
- Notification System: Include alerts when noise exceeds a threshold.
- Cloud Integration: Upload data to a server for centralized monitoring and reporting.

---

## Contributions

Contributions are welcome! Feel free to open issues or submit pull requests for improvements.

---

## License

This project is licensed under the MIT License. See the LICENSE file for details.

---