# Wireless motor control through Arduino ESP32 module

This folder contains two projects demonstrating first wireless communication between a system and an ESP32 microcontroller using the TCP/IP protocol, and the second using that communication to for a closed feedback loop motor control system

TCP/IP was chosen for its speed and simplicity, and using websocket made the implementation simpler still.

# Requirements

## Microcontroller 

Any development board for the ESP32 is suitable, though pin connections will vary and will need to be changed accordingly in the arduino code. A HiLetgo ESP-WROOM-32 board was specifically used in this project, chosen for its low cost and ease of availability.

## Motor and Driver

A 5V DC 28BYJ-48 stepper motor with a ULN2003 driver are used with this project. They were chosen for their low cost and ease of use. The code and system can be adapted for use with any other

## Position sensor

A potentiometer was going to be used to provide the feedback loop with an accurate position reading though this portion of the project was never implemented. For this reason, an optional function in the ClosedFeedbackMotorControl portion of the project is included that imitates the behavior of a potentiometer.

# Instructions

## Setting Up Arduino IDE

To program our Arduino ESP32 board, we used the arduino IDE version 1.8.19. Instructions for installing this can be found online

After installing this version of the IDE, ensure you have the ESP32 board installed. Once again, guides to do this can be found online.

Finally, open the Library Manager in the IDE and install the WebSockets libary.

## Uploading code to the Arduino

Each of the 3 demo folders contain 2 files, one being the computer-side .py file, and the other being the arduino-side .ino file. We reccomend beginning with the communication_demo, as it is the simplest and does not require anything to be connected to the arduino board.

Open the esp_control.ino file in the Arduino IDE, and replace the strings in lines 4 and 5 with your networks SSID and PASSWORD

```ino 
const char* ssid = "<SSID_OF_NETWORD>";
const char* password = "<PASSWORD_OF_NETWORK>";
```

You are now ready to upload your code to the ESP32 board.

## Connecting Hardware to the Board

Connect the motor and potentiometer to the ardino board using the corresponding pin connections.

## Establishing Communication between the Computer and Board

When the ESP32 connects to your network, it will be assigned a local IP, which your computer will need to know in order to communicate. 

As soon as the arduino sketch has finished uploading, open the serial monitor, which will on; confirm a wifi connection, and two; give you the IP address of your ESP32

Once you have the IP, open the esp_com.py file, and edit line 5, replacing <IP_OF_ESP32> with the IP given to the ESP32

```python
ws_server_address = "ws://<IP_OF_ESP32>:81"
```

Finally, ensure your computer is connected to the same network as the ESP32, run the python code in a terminal, and the program should now work!