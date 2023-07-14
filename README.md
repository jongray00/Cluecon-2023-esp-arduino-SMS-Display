# SMS Display with ESP32, I2C Display, and SignalWire

This project allows you to receive SMS messages and display them on an I2C LCD display using an ESP32 board. The messages are received through a Python server and forwarded to the ESP32 via serial communication.

## Prerequisites

- ESP32 board (e.g., NodeMCU 32S)
- I2C LCD display (compatible with the LiquidCrystal_I2C library)
- SignalWire account for receiving SMS messages
- Ngrok for exposing the Python server to the internet

## Wiring the ESP32 to the I2C Display

1. Connect the VCC pin of the display to the 5V pin of the ESP32.
2. Connect the GND pin of the display to the GND pin of the ESP32.
3. Connect the SDA pin of the display to the SDA pin of the ESP32.
4. Connect the SCL pin of the display to the SCL pin of the ESP32.

## Setting Up Arduino Environment

1. Install the Arduino IDE.
2. Install the ESP32 board support for the Arduino IDE.
3. Install the LiquidCrystal_I2C library in the Arduino IDE.
4. Connect the ESP32 board to your computer via USB.
5. Open the Arduino IDE and select the ESP32 board (NodeMCU 32S) from the board manager.
6. Open the provided Arduino code in the IDE.
7. Modify the code to set up your Wi-Fi credentials in the `setup()` function.
8. Upload the code to the ESP32 board.

## Setting Up Python Environment

1. Install Python on your computer.
2. Install the required Python libraries by running `pip install pyserial`.
3. Copy and paste the provided Python script into a new file.
4. Replace the serial port value in the `ser` variable with the correct port for your ESP32.
5. Save the Python file.

## Exposing Python Server with Ngrok

1. Install Ngrok on your computer.
2. Open a terminal or command prompt and navigate to the directory where Ngrok is installed.
3. Run the command `ngrok http 3000` to start the Ngrok tunnel.
4. Note the Ngrok URL provided in the terminal, as it will be used later.

## Updating Arduino Code with Ngrok URL

1. Open the Arduino code in the Arduino IDE.
2. Replace `"09c22beaaef0.ngrok.app"` with your Ngrok URL in the `loop()` function.
3. Upload the updated code to the ESP32 board.

## Configuring SignalWire Webhook

1. Sign up for a SignalWire account.
2. Purchase a phone number.
3. Go to the Edit Phone Number section.
4. Set the Ngrok URL and specific route, as the "incoming message webhook" within the SignalWire dashboard.

## Testing

1. Power on the ESP32 board.

2. Verify that the I2C LCD display shows "SMS Display" initially.
3. Send an SMS message to the phone number associated with your SignalWire account.
4. The received message should appear on the I2C LCD display and in the Arduino IDE's serial monitor.


Congratulations! You have successfully set up the SMS display project using an ESP32, I2C LCD display, Python server, and SignalWire.

![IMG_2616](https://github.com/jongray00/Cluecon-2023-esp-arduino-SMS-Display/assets/78746011/3b0fd473-38a8-4c89-a699-c3594ed6e3ad)
<img width="324" alt="Screen Shot 2023-07-13 at 5 13 54 PM" src="https://github.com/jongray00/Cluecon-2023-esp-arduino-SMS-Display/assets/78746011/0831ddbc-50b4-4863-a96d-88d3e2f213ac">

