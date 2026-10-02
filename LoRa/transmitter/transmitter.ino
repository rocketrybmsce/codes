#include <HardwareSerial.h>

#define PIN_RX2 16  // ESP32 RX2 -> E32 TXD
#define PIN_TX2 17  // ESP32 TX2 -> E32 RXD

HardwareSerial LoRaSerial(2); // Use UART2

int countdown = 10;

void setup() {
  Serial.begin(115200);
  
  // Wait for serial monitor to open
  delay(1000);

  // Initialize UART2 for LoRa (Default E32 baud rate is 9600)
  LoRaSerial.begin(9600, SERIAL_8N1, PIN_RX2, PIN_TX2);
  
  Serial.println("E32 LoRa Transmitter Ready (M0 & M1 tied to GND)!");
}

void loop() {
  String message = "Countdown: " + String(countdown);
  
  // Transmit data over UART
  LoRaSerial.println(message);
  Serial.println("Sent: " + message);

  // Decrement countdown
  countdown--;
  if (countdown < 0) {
    countdown = 10;
  }

  delay(2000); // Send every 2 seconds
}
