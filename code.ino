#include <SoftwareSerial.h>   // Include the SoftwareSerial library

SoftwareSerial Serial1(2, 3);  // Define software serial for LiDAR (pins 2, 3)

int dist;                      // Distance measurements of LiDAR
int strength;                  // Signal strength of LiDAR
int check;                     // Checksum value
int i;
int uart[9];                   // Data array for LiDAR
const int HEADER = 0x59;       // Frame header of the data package

void setup() {
  Serial.begin(9600);           // Start the serial monitor at 9600 baud
  Serial1.begin(115200);        // Start the LiDAR serial at 115200 baud
}

void loop() {
  if (Serial1.available()) {    // Check if LiDAR serial has data
    if (Serial1.read() == HEADER) {  // Look for header byte
      uart[0] = HEADER;
      if (Serial1.read() == HEADER) {  // Look for second header byte
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {      // Read remaining data into uart array
          uart[i] = Serial1.read();
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
          } else if (dist == -1 || dist < -1) {
            Serial.println("STOP_SOUND");  // Send "STOP_SOUND" command if not in range
          } else {
            Serial.println("STOP_SOUND");  // Send "STOP_SOUND" command if not in range
          }

          delay(500);

        }
      }
    }
  }
}
