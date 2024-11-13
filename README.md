**SmartStep**
SmartStep is an innovative smart shoe designed to assist visually impaired individuals in navigating their surroundings. Powered by an ESP32 microcontroller and equipped with a LiDAR sensor, this smart shoe detects obstacles in real-time and provides auditory feedback via a web server. The LiDAR sensor continuously scans for objects, while the ESP32 processes the data to assess proximity, ensuring safe and intuitive navigation. SmartStep enhances spatial awareness, promoting independence and mobility.

**Features**
**Real-time obstacle detection**: Detects objects within 10-250 cm.
**Auditory feedback**: Sends commands (PLAY_SOUND, BLOCKED, STOP_SOUND) to a web server, which provides the user with audio cues based on distance.
**Compact and efficient**: Designed for easy integration into footwear, making it a discreet and practical aid.

**System Overview**
**Microcontroller**: ESP32
**Sensor**: LiDAR for accurate distance measurement
**Feedback System**: Web server plays sounds based on distance to objects

PLAY_SOUND: Object detected within 10-250 cm.
BLOCKED: Object is very close (less than 10 cm).
STOP_SOUND: No object nearby.

**How It Works**
Setup: The ESP32 connects to Wi-Fi and starts a web server.
Web Server: Serves a simple HTML page displaying the current command (PLAY_SOUND, BLOCKED, or STOP_SOUND).
Proximity Commands: The ESP32 interprets LiDAR data and sends appropriate commands to the web server for real-time auditory feedback.
Installation
Upload the code to the ESP32.
Connect to the ESP32's IP address in a browser on the same Wi-Fi network to access the web-based auditory feedback.
