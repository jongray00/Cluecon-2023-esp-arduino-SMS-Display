#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

// ENSURE THAT THE ADDRESS OF THE DISPLAY, AND THE DIMENSIONS OF DISPLAY ARE CORRECT
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Adjust the I2C address and LCD dimensions if needed

String sender;         // Variable to store the sender's number
String messageBody;    // Variable to store the message body

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino is ready");
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMS Display");

  // Connect to WiFi
  WiFi.begin("NETWORK-NAME", "NETWORK-PASSWORD");  // Replace with your WiFi credentials

  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void webhookHandler() {
  // Update the LCD display with the incoming SMS information
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(sender);
  lcd.setCursor(0, 1);
  lcd.print(messageBody);

  // Print the received data to the Serial Monitor
  Serial.print("Received data from webserver - ");
  Serial.print("From: ");
  Serial.print(sender);
  Serial.print(", Body: ");
  Serial.println(messageBody);
}

void processReceivedData(const String& data) {
  if (data.startsWith("From:")) {
    sender = data.substring(6);
    sender.trim();
  } else if (data.startsWith("Message:")) {
    messageBody = data.substring(9);
    messageBody.trim();
  }
}

void loop() {
  WiFiClient client;
  lcd.clear();
  lcd.setCursor(0, 0);
  // Check if the Arduino received any data from the webserver
  while (Serial.available()) {
    char c = Serial.read();
    // Process the received data here
    Serial.print("Received data from webserver: ");
    Serial.println(c);
    lcd.print(c);
    if (c == '\n') {
      processReceivedData(sender);
      processReceivedData(messageBody);
      webhookHandler();
    }
  }

  // Check if there is any data available from the Serial Monitor
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Received data from Serial Monitor: ");
    Serial.println(data);
  }
// ENTER IN YOUR HOST IN THE FORMAT BELOW
  if (client.connect("09c22beaaef0.ngrok.app", 3000)) {
    client.println("GET /sms-webhook HTTP/1.1");
    client.println("Host: 09c22beaaef0.ngrok.app");
    client.println("Connection: close");
    client.println();
    while (client.connected() && !client.available()) {}
    while (client.connected() || client.available()) {
      char c = client.read();
      // Process the received data here
      if (c == '\n') {
        if (client.read() == '\r') {
          if (client.read() == '\n') {
            String line = client.readStringUntil('\r');
            processReceivedData(line);
          }
        }
      }
    }
    webhookHandler();
    client.stop();
  }
  delay(5000);  // Adjust the delay according to your requirements
}
