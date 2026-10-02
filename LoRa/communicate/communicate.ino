#include <HardwareSerial.h>

#define PIN_RX2 16  // ESP32 RX2 -> E32 TXD
#define PIN_TX2 17  // ESP32 TX2 -> E32 RXD

HardwareSerial LoRaSerial(2); // Hardware UART2

void setup() {
  // USB Serial Monitor connection to PC
  Serial.begin(115200);
  delay(1000);

  // Hardware Serial connection to LoRa module (9600 baud default)
  LoRaSerial.begin(9600, SERIAL_8N1, PIN_RX2, PIN_TX2);

  Serial.println("==========================================");
  Serial.println("  E32 LoRa 2-Way Transceiver Ready!       ");
  Serial.println("  Type a message and press Enter to send. ");
  Serial.println("==========================================");
}

void loop() {
  // 1. TRANSMIT: Check if user typed anything into the Serial Monitor
  if (Serial.available() > 0) {
    String outboundMessage = Serial.readStringUntil('\n');
    outboundMessage.trim(); // Clean up trailing whitespace/newlines

    if (outboundMessage.length() > 0) {
      // Send the string over LoRa UART with a newline delimiter
      LoRaSerial.println(outboundMessage);
      
      // Echo what was sent on local monitor
      Serial.print("[Me]: ");
      Serial.println(outboundMessage);
    }
  }

  // 2. RECEIVE: Check if data arrived wirelessly from the other LoRa module
  if (LoRaSerial.available() > 0) {
    String inboundMessage = LoRaSerial.readStringUntil('\n');
    inboundMessage.trim();

    if (inboundMessage.length() > 0) {
      // Display received wireless message
      Serial.print("[Peer]: ");
      Serial.println(inboundMessage);
    }
  }
}
