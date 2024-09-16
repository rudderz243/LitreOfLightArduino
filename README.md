# ESP8266 Litre of Light Controller

This code implements a web server on an ESP8266 microcontroller to control a "Litre of Light" system. The system uses a daylight sensor to determine ambient light levels and automatically turns on an LED light when it's dark. It also provides a web interface for manual control and configuration.

## Features

- Automatic light control based on ambient light levels.
- Adjustable light sensitivity (Low, Medium, High).
- Manual light control (On/Off).
- Web interface for control and monitoring.
- Status reporting (Mode, Sensitivity, Light level).

## Hardware Requirements

- ESP8266 microcontroller (e.g., NodeMCU, Wemos D1 Mini)
- Daylight sensor (analog)
- LED light
- Resistors (for LED and sensor)
- Breadboard and jumper wires

## Installation

1. Install the ESP8266 board support package in your Arduino IDE.
2. Install the following libraries:
    - ESP8266WiFi
    - ESP8266WebServer
3. Connect the hardware components as shown in the wiring diagram.
4. Update the following constants in the code:
    - `APSSID`: SSID of the ESP8266 access point
    - `APPSK`: Password of the ESP8266 access point
5. Upload the code to your ESP8266.

## Usage

1. Power on the ESP8266. It will create a Wi-Fi access point with the SSID and password specified in the code.
2. Connect your smartphone or computer to the ESP8266's Wi-Fi network.
3. Open a web browser and navigate to the ESP8266's IP address (printed in the serial monitor).
4. The web interface provides the following controls:
    - **Light On/Off:** Manually turn the light on or off.
    - **Automatic Mode:** Enable or disable automatic light control.
    - **Sensitivity:** Adjust the light sensitivity (Low, Medium, High).
    - **Status:** Display the current mode, sensitivity, and light level.

## API Endpoints

The following API endpoints are available for controlling the system programmatically:

- `/LightOn`: Turn the light on.
- `/LightOff`: Turn the light off.
- `/AutomaticMode`: Enable automatic mode.
- `/Low`: Set sensitivity to Low.
- `/Medium`: Set sensitivity to Medium.
- `/High`: Set sensitivity to High.
- `/Status`: Get the current status (Mode, Sensitivity, Light level).

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvement, please open an issue or submit a pull request.