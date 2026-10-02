#include <HardwareSerial.h>

#define PIN_RX2 16  // ESP32 RX2 -> E32 TXD
#define PIN_TX2 17  // ESP32 TX2 -> E32 RXD

HardwareSerial LoRaSerial(2); // Use UART2

void setup() {
  Serial.begin(115200);
  delay(1000);

  LoRaSerial.begin(9600, SERIAL_8N1, PIN_RX2, PIN_TX2);
  
  Serial.println("E32 LoRa Receiver Listening (M0 & M1 tied to GND)...");
}

void loop() {
  if (LoRaSerial.available() > 0) {
    String receivedData = LoRaSerial.readStringUntil('\n');
    
    if (receivedData.length() > 0) {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }
  }
}
