# ECSE3038 Lab 5 - API Client with ESP32 and LCD

## Purpose of the Code
This project was developed as part of the ECSE3038 Lab 5 assignment to familiarize students with an API using an ESP32 microcontroller. The goal is to have the ESP32 connect to Wi-Fi, make an HTTPS GET request to a specified API endpoint, parse the JSON response, and display the resulting messages on a 16x2 I2C LCD.

## Expected Behavior and Function Descriptions

### Overall Workflow:
1. **Initialization (`setup()`):**
   - **Wi-Fi Connection:** The ESP32 initializes its Wi-Fi module and connects to the specified network.
   - **LCD Setup:** The LCD is initialized and its backlight is turned on.
   - **Serial Monitor Setup:** The Serial Monitor is started at a baud rate of 115200.
   - **Status Display:** A message is displayed on the LCD to indicate the current connection status.

2. **Main Loop (`loop()`):**
   - **GET Request:** Once Wi-Fi is connected, the ESP32 creates a secure client (using `WiFiClientSecure`), and an HTTP GET request is made to the API endpoint `/message`. An `api-key` header is added to the request.
   - **Response Handling:** The API response is received and printed to the Serial Monitor.
   - **JSON Parsing:** The code uses ArduinoJson to parse the JSON response, extracting `line_1` and `line_2`.
   - **LCD Update:** The extracted messages are then displayed on the LCD.
   

### Function Summaries:
- **`setup()`**  
  Initializes Serial communication, I2C (for the LCD), the LCD itself, and connects to the Wi-Fi network. It displays connection status messages on the LCD.
  
- **`loop()`**  
  Checks if Wi-Fi is connected. If so, it creates a secure client, makes an HTTPS GET request to the API endpoint, parses the JSON response, and updates the LCD with the messages from the response. Debug messages are printed via Serial.

- **`WiFiClientSecure`**  
  Used to establish a secure HTTPS connection; `client.setInsecure()` is called for development purposes to bypass SSL certificate verification.

- **`HTTPClient`**  
  Manages the HTTP operations, sending the GET request and receiving the response.

- **`deserializeJson()`**  
  Parses the JSON payload from the API response and extracts `line_1` and `line_2`.

- **`lcd.print()` & `lcd.setCursor()`**  
  Functions from the LiquidCrystal_I2C library used to control the LCD display and show the messages.
