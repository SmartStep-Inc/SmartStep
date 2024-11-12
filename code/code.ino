#include <HardwareSerial.h>   // Include the HardwareSerial library

int dist;                      // Distance measurements of LiDAR
int strength;                  // Signal strength of LiDAR
int check;                     // Checksum value
int i;
int uart[9];                   // Data array for LiDAR
const int HEADER = 0x59;       // Frame header of the data package

void setup() {
  Serial.begin(115200);           // Start the serial for LiDAR at 115200 baud on RX0 (GPIO 3) and TX0 (GPIO 1)
  Serial2.begin(9600);            // Start the serial monitor at 9600 baud
}

void loop() {
  if (Serial.available()) {             // Check if LiDAR serial has data
    if (Serial.read() == HEADER) {      // Look for header byte
      uart[0] = HEADER;
      if (Serial.read() == HEADER) {    // Look for second header byte
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {       // Read remaining data into uart array
          while (!Serial.available());  // Wait for each byte
          uart[i] = Serial.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)) {  // Verify checksum
          dist = uart[2] + uart[3] * 256;  // Calculate distance
          strength = uart[4] + uart[5] * 256; // Calculate signal strength

          // Send distance to the Serial Monitor
          Serial2.println(dist);

          // Trigger sound command based on distance
          if (dist < 100 && dist > 10) {
            Serial2.println("PLAY_SOUND");  // Send "PLAY_SOUND" command over Serial2
          } else if (dist < 10) {
            Serial2.println("BLOCKED");
          } else {
            Serial2.println("STOP_SOUND");  // Send "STOP_SOUND" command if not in range
          }

          delay(500);

        }
      }
    }
  }
}
