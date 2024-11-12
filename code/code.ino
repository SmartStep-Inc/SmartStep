#include <HardwareSerial.h>   // Include the HardwareSerial library

HardwareSerial SerialLidar(1);  // Define hardware serial for LiDAR, using UART1

int dist;                      // Distance measurements of LiDAR
int strength;                  // Signal strength of LiDAR
int check;                     // Checksum value
int i;
int uart[9];                   // Data array for LiDAR
const int HEADER = 0x59;       // Frame header of the data package

void setup() {
  Serial.begin(9600);           // Start the serial monitor at 9600 baud
  SerialLidar.begin(115200, SERIAL_8N1, 22, 21); // Start LiDAR serial at 115200 baud on pins 22 (RX) and 21 (TX)
}

void loop() {
  if (SerialLidar.available()) {    // Check if LiDAR serial has data
    if (SerialLidar.read() == HEADER) {  // Look for header byte
      uart[0] = HEADER;
      if (SerialLidar.read() == HEADER) {  // Look for second header byte
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {      // Read remaining data into uart array
          uart[i] = SerialLidar.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)) {  // Verify checksum
          dist = uart[2] + uart[3] * 256;  // Calculate distance
          strength = uart[4] + uart[5] * 256; // Calculate signal strength

          // Send distance to the Serial Monitor
          Serial.println(dist);

          // Trigger sound command based on distance
          if (dist < 100 && dist > 10) {
            Serial.println("PLAY_SOUND");  // Send "PLAY_SOUND" command over Serial
          } else if (dist < 10) {
            Serial.println("BLOCKED");
          } else {
            Serial.println("STOP_SOUND");  // Send "STOP_SOUND" command if not in range
          }

          delay(500);

        }
      }
    }
  }
}
