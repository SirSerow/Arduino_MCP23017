# Upgraded Cable Tester with MCP Multiplexers

## Overview
This upgraded version of the cable tester leverages multiplexers **(MCP23X17)** to provide enhanced control over testing multiple cable lines individually from both ends of the connector. Designed for DB-37 cables, this improved tester delivers precise diagnostics and robust quality assurance for industrial applications.

## Background
**Where These Cables Are Used:**
- **Industrial Automation & Control:** DB-37 connectors are commonly deployed in advanced control panels, process controllers, and automation systems.
- **Instrumentation & Data Acquisition:** High-density connectors like the DB-37 are used in systems where reliable, multi-channel connectivity is crucial.
- **Critical Systems:** In environments where cable integrity is paramount, such as in safety and process control systems, ensuring every connection is fault-free is essential.

**Why Testing Is Important:**
- **Enhanced Quality Assurance:** Testing each channel individually ensures that even intermittent or minor faults are detected early.
- **Minimized Downtime:** Reliable testing prevents faulty cables from being installed in mission-critical applications, reducing the risk of system failures.
- **Improved Troubleshooting:** Detailed per-channel diagnostics help quickly identify and address specific issues, streamlining maintenance.

## Project Description
The upgraded tester incorporates MCP multiplexers to efficiently manage a large number of channels (up to 37) with the following features:
1. **Initialization:**  
   - Multiple MCP23X17 I2C devices are set up to handle both output and input channels.
   - The system initializes the LCD, push buttons, buzzer, and reset circuitry.

2. **User Interface:**  
   - **Start Button:** Initiates the testing sequence.
   - **Next Button:** Allows cycling through channels to monitor or re-test in case of a fault.
   - **LCD Display:** Provides real-time status updates and error messages.
   - **Buzzer:** Issues audible alerts when a channel fails the test.

3. **Channel Testing:**  
   - **Multiplexer Control:** The system uses MCP multiplexers to switch between cable lines, activating one channel at a time.
   - **Signal Verification:** Each activated channel is monitored via the corresponding input MCP, ensuring proper electrical connectivity.
   - **Error Reporting:** When a channel fails, the tester produces a beep and displays the specific channel number on the LCD.

4. **Reset and Repeat:**  
   - A dedicated reset function ensures that all MCP devices are properly restarted before beginning a new test cycle.

## Hardware Components
- **Arduino Board:** Acts as the central controller running the test firmware.
- **Adafruit MCP23X17 Multiplexers:** Six MCP23X17 devices are used (three for outputs and three for inputs) to manage testing across multiple channels.
- **LCD Display (16x2, I2C):** Displays test instructions, progress, and error messages.
- **Push Buttons:**
  - **Start Button:** To commence the testing sequence.
  - **Next Button:** To navigate through channels, especially when a fault is detected.
- **Buzzer:** Provides audible alerts for failed channels.
- **Reset Circuitry:** Ensures proper initialization of the MCP devices.

## Circuit Schematic
The upgraded PCB design schematics are located in the [Schematic folder](./Schematic/). These documents illustrate the integration of the MCP23X17 multiplexers with the Arduino board and other components.

## Software
The firmware for this tester is written in Arduino C++ and utilizes the following libraries:
- **Adafruit_MCP23X17:** Manages communication with the MCP multiplexers.
- **LiquidCrystal_I2C:** Interfaces with the 16x2 LCD display.
- **Wire:** Facilitates I2C communication between the Arduino and MCP devices.

### Key Firmware Functions
- **Multiplexer Initialization:**  
  Configures each MCP23X17 device as either input or output as required.
- **Channel Testing Routine:**  
  Iterates over channels (1 to 37), using the multiplexers to activate and read signals from each cable line.
- **User Feedback:**  
  Provides both visual feedback on the LCD and audible alerts via the buzzer if a channel does not pass the test.
- **Reset Functions:**  
  Ensures the MCP devices are properly reset between tests for consistent performance.

For the complete firmware code, refer to the `main.ino` file in this repository.

## Installation and Usage
1. **Hardware Assembly:**  
   Assemble the upgraded tester according to the PCB schematic provided in the *Schematic* folder.
2. **Firmware Upload:**  
   Use the Arduino IDE to compile and upload the firmware to your Arduino board.
3. **Testing Procedure:**  
   - Connect the DB-37 cable to the tester.
   - Press the **Start Button** to begin the test sequence.
   - Observe the LCD for real-time status updates and channel-specific error messages.
   - If a channel fails, an audible alert will prompt you to use the **Next Button** to review the faulty channel.
   - Use the reset functionality as needed to clear errors and restart the testing process.

## License
This project is open source and available under the MIT License. Contributions and modifications are welcome.

## Acknowledgements
Special thanks to the Adafruit team for the MCP23X17 library and the Arduino community for their ongoing support and resources.
