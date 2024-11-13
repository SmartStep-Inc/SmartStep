<h1>SmartStep</h1>
<h3>SmartStep is an innovative smart shoe designed to assist visually impaired individuals in navigating their surroundings. Powered by an ESP32 microcontroller and equipped with a LiDAR sensor, this smart shoe detects obstacles in real-time and provides auditory feedback via a web server. The LiDAR sensor continuously scans for objects, while the ESP32 processes the data to assess proximity, ensuring safe and intuitive navigation. SmartStep enhances spatial awareness, promoting independence and mobility.</h3>

**Features**
<br>
**Real-time obstacle detection**: Detects objects within 10-250 cm.
<br>
**Auditory feedback**: Sends commands (PLAY_SOUND, BLOCKED, STOP_SOUND) to a web server, which provides the user with audio cues based on distance.
<br>
**Compact and efficient**: Designed for easy integration into footwear, making it a discreet and practical aid.
<br>
<br>
**System Overview**
<br>
**Microcontroller**: ESP32
<br>
**Sensor**: LiDAR for accurate distance measurement
<br>
**Feedback System**: Web server plays sounds based on distance to objects
<br>
<br>
PLAY_SOUND: Object detected within 10-250 cm.
BLOCKED: Object is very close (less than 10 cm).
STOP_SOUND: No object nearby.
<br>
<br>
**How It Works**
<br>
Setup: The ESP32 connects to Wi-Fi and starts a web server.
<br>
Web Server: Serves a simple HTML page displaying the current command (PLAY_SOUND, BLOCKED, or STOP_SOUND).
<br>
Proximity Commands: The ESP32 interprets LiDAR data and sends appropriate commands to the web server for real-time auditory feedback.
<br>
<br>
**Installation**
<br>
<br>
Upload the code to the ESP32 and connect at 115200 Baud Rate.
<br>
Change code accordingly from your wifi hotspot SSID and Password.
<br>
Connect the ESP32 to the Power Source and place it in the shoe.
<br>
**Ready to Use!**
