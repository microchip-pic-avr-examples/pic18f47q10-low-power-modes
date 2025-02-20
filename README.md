[![MCHP](images/microchip.png)](https://www.microchip.com)

# Low Power Modes in PIC® Microcontrollers
# Introduction
 PIC Microcontroller Units (MCU)s feature various Power-Down modes that help to reduce average power consumption through effective management of CPU operations, clock signals, and peripherals. The Power-Down modes typically comprise of Doze, Idle, Sleep and Deep sleep modes. The PIC18-Q10 family of MCUs have three Power-Down modes - Doze, Idle and Sleep. This example demonstrates how to achieve low power consumption by using these modes.    

 # Useful Links
- [TB3144: Doze, Idle and PMD Features of 8-Bit PIC® Microcontrollers](https://www.microchip.com/DS90003144)
- [Low Power Modes on PIC® Microcontrollers - YouTube](https://youtu.be/4QdOuG0TZic)
- [PIC18-Q10 Product Family Page](https://www.microchip.com/design-centers/8-bit/pic-mcus/device-selection/pic18f-q10-product-family)
- [PIC18F47Q10 Data Sheet](https://www.microchip.com/DS40002043)
- [PIC18F47Q10 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=pic18f47q10)

# Power-Down Modes 
This section briefly discusses each of the Power-Down mode available on PIC18-Q10 devices.

## Doze Mode
 In Doze mode, CPU and memory operations are affected, but the peripheral clocks continue to run. Doze mode allows power saving by reducing CPU clock instruction cycles, while leaving the peripheral clock unchanged. In Doze mode, the CPU executes only one instruction cycle out of every N-cycles as defined by the DOZE [2:0] bits in the `CPUDOZE` register. For example, if DOZE [2:0] = 001, the instruction cycle ratio is 1:4. The CPU and memory execute for one instruction cycle and then lay idle for three instruction cycles. During the unused cycles, the peripherals continue to operate at the system clock speed.

Steps to enter Doze mode:
1. CPUDOZEbits.DOZEN = 1;        // Doze enable bit (DOZEN) must be set to enter the Doze mode
2. CPUDOZEbits.DOZE = dozeRatio; //Select the ratio of CPU clock instruction cycle to Peripheral clock instruction cycle in DOZE register
3. CPUDOZEbits.ROI = 1; //Set the Recover-On-Interrupt bit to come out of the Doze mode when the interrupt occurs

## Idle Mode
 In Idle mode, CPU and Memory operations are halted, but the peripheral clocks continue to run. Device is put into Idle mode by executing the `SLEEP` instruction when the Idle enable bit is set.

## Sleep Mode 
Sleep mode turns off the system clock. The CPU and all peripherals requiring the system clock will cease operation. The contents of the memory and registers are maintained in Sleep mode. The device is put into Sleep mode by executing the `SLEEP` instruction when the Idle enable bit is clear.

# Clocks
This section discusses the System clock, CPU clock, and Peripheral clock (Refer to Table 1).

## System Clock
 The System clock, designated as FOSC, is the main clock which can be supplied from external oscillators, quartz crystal resonators, ceramic resonators, or Resistor-Capacitor (RC) circuits. Additionally, the system clock source can be supplied from one of two internal oscillators. The Oscillator module can be configured to select one of the clock sources.

## CPU Clock
 The instruction clock, or CPU clock, is derived from the system clock,or FOSC, through a divider to deliver an instruction clock of FOSC/4 (1/4 the oscillator speed). This is done to allow the fetch and execute pipeline in the architecture to execute one assembly instruction per instruction clock cycle (except for branches and goto's which execute in two). The CPU clock is supplied to the CPU and memory to perform CPU and memory operations in the application.

## Peripheral Clock
 Each peripheral on the device will have its own clock options which usually include FOSC, FOSC/4, the internal low-frequency oscillator (LFINTOSC), and the output of other peripherals. Refer to the device data sheet for the specifics of each peripheral. 

![clock_details](images/clock_details.jpg)

*Table 1: Clock details in Power Down modes*

## Peripheral Module Disable

The Peripheral Module Disable (PMD) feature provides the ability to disable a peripheral by stopping all clock sources supplied to that module. A peripheral can be disabled by setting the corresponding peripheral disable bit in the PMDx register.  All the peripherals are enabled by default. To reduce overall power consumption, the user can disable unused modules/peripherals. Refer to the device data sheet for more details about the PMD register

# Demo Description

![block_diagram](images/block_diagram.jpg)

Figure 1. Block diagram of application demo  

  In this demo:
* The PIC18F47Q10 Curiosity Nano and Power debugger boards from Microchip are used to demonstrate Power-Down modes configuration and to measure MCU power consumption.
* The on-board mechanical switch (SW0) of the PIC18F47Q10 Curiosity Nano board is used to invoke Power-Down modes or to wake up the MCU from Power-Down modes which happens sequentially at each switch press event.
* The MCU operating mode (i.e. Active mode/Doze mode/Idle mode/Sleep mode) information is transmitted to the terminal window of the Data Visualizer tool, through the virtual COM port of the Curiosity Nano board.
* The Power Debugger board measures the power consumption of the PIC18F47Q10 MCU and displays the measurement using MPLAB Data visualizer.
* The on-board LED (LED0) is used as an indication while the MCU wakes up from any of the Power-Down modes and enters the Active mode.
* On start-up, the MCU operates in Active mode. When SW0 is pressed, the MCU performs EEPROM write and read operations. While this is happening, the power consumption of the device can be viewed in Data Visualizer. 
* When SW0 is pressed again, the MCU enters Doze mode and performs the EEPROM operation. In this mode, the CPU operates at reduced clock instruction cycles compared to the Active mode. The MCU remains in Doze mode until SW0 is pressed again, after which the MCU will wake up from Doze mode and enter Active mode. LED0 will then turn on to indicate the MCU is in Active mode.
* When SW0 is pressed again, the MCU will enter Idle mode. The MCU will remain in Idle mode until SW0 is pressed and the MCU switches to Active mode. LED0 will turn on to indicate the device is in Active mode 
* When SW0 is pressed again, the MCU enters Sleep mode. The MCU continues in Sleep mode until a switch press event is detected. Upon a switch press event, the MCU wakes up from the Sleep mode and enters Active mode. LED0 will be on to indicate the device is in Active mode. 

# Hardware Used
**[PIC18F47Q10 Curiosity Nano board](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)**

With full program and debug capabilities, the PIC18F47Q10 Curiosity Nano evaluation kit offers complete support for the new design. With the award-winning MPLAB X integrated development platform and MPLAB Code Configurator (MCC), the kit provides access to the Intelligent analog and Core Independent Peripherals on the PIC18F47Q10. Figure 2 shows the PIC18F47Q10 Curiosity Nano board. For more details refer to the [PIC18F47Q10 Curiosity Nano Hardware User Guide](https://www.microchip.com/DS40002103)

![curiosity_nano](images/curiosity_nano.jpg)

Figure 2. PIC18F47Q10 Curiosity Nano Board

**[Power Debugger](https://www.microchip.com/developmenttools/ProductDetails/atpowerdebugger)**    

Power Debugger is a powerful development tool used for debugging and programming AVR and SAM MCUs. The power debugger contains two channels for measuring power consumption, one channel is used for High-precision low-current measurement, while the second channel is used for Low-precision high-current measurement. In this example, Power Debugger with Channel A (High precision low-current measurement) is used in order to measure current consumption of the PIC18F47Q10 MCU and to transmit the measured data to Data Visualizer. For more details refer to the [Power Debugger User Guide](https://www.microchip.com/42696). Figure 3 shows the Power debugger.

![power_debugger](images/power_debugger.jpg)

Figure 3. Power Debugger

**Note:** In Curiosity Nano board, on-board level shifters will draw a current of 20 μA. To know the power consumption of PIC18F47Q10 MCU in each power down modes, subtract 20 μA from actual power consumption.

# Software Tools:
Microchip’s free MPLAB X IDE, compiler and MPLAB Code Configurator (MCC) graphical code generator are used throughout the firmware development. Following are the tool versions used for this demo application:
* [MPLAB® X IDE v6.20](https://www.microchip.com/mplab/mplab-x-ide)
* [XC8 Compiler v3.00](https://www.microchip.com/mplab/compilers)
* [MPLAB® Code Configurator (MCC) v5.7.1](https://www.microchip.com/mplab/mplab-code-configurator)
* [Microchip PIC18F-Q Series Device Support 1.26.442](https://packs.download.microchip.com/)

**Note:** For running the demo, the installed tool versions must be same or later. This example is not tested with previous versions.

**MPLAB Data Visualizer**

 MPLAB Data Visualizer is a plugin available in MPLAB X used to process and visualize data. Data Visualizer can receive data from various sources such as the Embedded Debugger Data Gateway Interface (DGI) and COM ports. Data Visualizer is made up of several modules such as Graph, Terminal, Power debugging, Custom dashboard, etc. In this example, Data Visualizer is used to plot power consumption data received from the Power Debugger. The terminal window is used to display serial data transmitted by the PIC18F47Q10 MCU to indicate the current Power-Down mode. 

# Demo
## Peripherals Configuration Using MCC

**Clock Control**

- Clock Source: HFINTOSC
- HF Internal Clock: 1_MHz
- Clock Divider: 1

**Configuration Bits**

- Fail-Safe Clock Monitor Enable: Disabled
- External Oscillator Mode Selection: Oscillator not enabled
- Brown-out Reset Enable: Brown-out Reset disabled
- WDT Operating Mode: WDT Disabled

**UART**

- UART PLIB Selector: EUSART2
- Requested Baudrate: 9600
- Data Size: 8
- Flow Control Mode: None
- Redirect Printf to UART: Enabled

**NVM**

- Generate Flash APIs: Enabled 
- Generate EEPROM APIs: Enabled

**Pins**

| Pin Name | Module  | Function | Direction | Custom Name | Weak Pullup |
| -------- | ------- | -------- | --------- | ----------- | ----------- | 
|   RD0    | EUSART2 |   TX2    |   output  |    IO_RD0   |     No      |
|   RB0    | Pins    |   GPIO   |   input   |    IO_RB0   |     Yes     |
|   RE2    | Pins    |   GPIO   |   input   |    IO_RE2   |     Yes     | 
|   RE0    | Pins    |   GPIO   |   output  |    LED      |     No      |

# Hardware Setup
There are two methods for Hardware connection.

### First Method:
1. Short the pins RE2 and RB0 using the jumper
2. Cut the Target Power strap on PIC18F47Q10 Curiosity Nano board to measure the power consumption of the MCU (refer to PIC18F47Q10 Curiosity Nano Hardware User Guide)
3. Set up the hardware connections as shown in figure 4:
   - Short the Variable Supply voltage pin to the Channel A input pin of the Power Debugger
   - Since the Target Power strap is cut, power to the target MCU is suspended from the USB. Power debugger is used as a source to supply power to the Curiosity Nano board. Connect the Channel A output of power debugger to the VTG pin of Curiosity Nano board, which supplies power of 3.3V.

![connection_1](images/connection_1.jpg)

Figure 4. Current Measurement Using Power Debugger Hardware Connections


4. Power debugger has an on-board voltage supply which can provide up to 1.6V to 5.5V from the USB DEBUG connector. To supply 3.3V to the PIC18F47Q10 MCU follow the steps below:
    - In the **Data Visualizer tab**, select Power Debugger CMSIS-DAP
    - Enable power interface by opening **Power Settings**. Enter 3300 in the Output Voltage in mV box.
    - Click anywhere outside the Power settings pop-up to save the settings

![power_configuration](images/power_configuration.jpg)

Figure 5. Power Configuration Window

### Second Method:
1. Short the pins RE2 and RB0 using the jumper.
2. Cut the Power Target strap on PIC18F47Q10 Curiosity Nano board and solder two wires on that VTG strap.
3. Connect the two soldered wires to the Channel A of the power debugger in series to measure current as shown in Figure 6.

![connection_2](images/connection_2.jpg)

Figure 6. Current Measurement Using the Power Debugger Hardware Connection

4. Set up the hardware, as shown in figure 6.

**Note:** Steps from 5 to 10 are the same for the two methods of hardware connection

5. Power the Curiosity Nano board from the PC by connecting a micro USB cable between the PC USB port and the micro USB port of the Curiosity Nano board.

6. Similarly, power the Power Debugger board from the PC by connecting a micro USB cable between the PC USB port and the micro USB port (named as DEBUG) of the Power Debugger board.

7. The Curiosity Nano board will appear as a Mass Storage Device after connecting to the PC.

8. Program the MCU by clicking “Make and Program Device” icon on MPLAB X IDE.


### Steps to Plot Power in Data Visualizer
1. Open Data Visualizer by clicking the Data Visualizer icon in MPLAB X.
2. Under the **Data Visualizer** tab, click on the connections on the left side of the pane.
3. Expand the option "Power Debugger CMSIS-DAP".
4. Click the play button next to "Power". 

![data_visualizer](images/data_visualizer.jpg)

Figure 7. Start Data Visualizer and Start Plotting Power

### Steps to open the Terminal Window in Data Visualizer
1. In the Data Visualizer window, click "Connections".
2. Expand the option "PIC18F47Q10 Curiosity Nano".
3. Mouse over the COM port listed under "PIC18F47Q10 Curiosity Nano".
4. Click the terminal icon.

![terminal](images/terminal.jpg)

Figure 8. Open the Terminal Window in Data Visualizer

# Demo Operation

The following figures show the average current consumption of the Curiosity Nano board in different Power-Down modes of MCU. The power consumption values discussed in this document are analyzed with the hardware setup previously mentioned.

**Active Mode:**
- After power up, the MCU enters the Active mode
- Before each switch press, instructions are mentioned to the user on the terminal window.  E.g.: Press Switch- To perform EEPROM operations in Active mode.
- When the Curiosity Nano board is loaded with the firmware, the following waveform (Refer to Fig. 9) is observed and instructions are provided on the terminal window to the user for further operations
- Observe the average current consumption of the MCU in Active mode is 255 uA

![power_analysis_active_1](images/power_analysis_active_1.jpg)

Figure 9: Current Consumption in Active Mode

**Active Mode – EEPROM Operations**
- Press Switch (SW0) to perform EEPROM operations in Active mode and the user needs to wait until the “Completed” text is displayed on the terminal window, which indicates EEPROM operations are completed
- Notice that the average current consumption during EEPROM operations in Active mode is 916.8 μA  (Refer to Fig. 10).

![power_analysis_active_eeprom](images/power_analysis_active_eeprom.jpg)

Figure 10. EEPROM Operations in Active Mode

- Observe the “Completed” text and the next instructions for the user are displayed on the terminal window (Refer to Fig. 11).

![power_analysis_active_2](images/power_analysis_active_2.jpg)

Figure 11. Current Consumption and the Terminal Window in Active Mode

**Doze Mode (Doze ratio=1:8)**
* Press Switch (SW0) to enter Doze mode with Doze ratio 1:8 and see that the text "Entered Doze mode 1:8" is displayed on the terminal window after the switch press and wait for the next instruction to be displayed on terminal window.
* Observe that the average current consumption in Doze mode with ratio 1:8 is 228 μA (Refer to Fig. 12).

![power_analysis_doze8_1](images/power_analysis_doze8_1.jpg)

Figure 12. Current Consumption and the Terminal Window in Doze Mode With 1:8 Doze Ratio

**Doze Mode (Doze ratio=1:8) – EEPROM Operations**
- Press Switch (SW0) to perform EEPROM operations in Doze mode with doze ratio 1:8.
- During the EEPROM operations, the user needs to wait to see the text “Completed” on the terminal window, which indicates that the EEPROM operations are completed and within this time the the Switch press is not detected. The CPU and memory operate at only one instruction cycle out of the eight, i.e. with reduced frequency (125 kHz) compared to the frequency used in Active mode, and the rest of the peripherals operate at the system clock speed of 1MHz.
- Observe the current plot during EEPROM operations (Refer to Fig. 13) 
- Once the EEPROM operations are completed, the user needs to wait for furhter instructions to be displayed on terminal window 

![power_analysis_doze8_eeprom](images/power_analysis_doze8_eeprom.jpg)

Figure 13. EEPROM Operations in Doze Mode With 1:8 Doze Ratio

- Press Switch (SW0) to wake up from Doze mode with ratio 1:8 and to enter Active mode and notice the text “Entered Active mode (Wakeup)” is displayed on the terminal window.
- Observe that the current consumption in Active mode is 255 μA and wait until the next instruction is displayed on the terminal window (Refer to Fig. 14).

![power_analysis_doze8_2](images/power_analysis_doze8_2.jpg)

Figure 14. Current Consumption and the Terminal Window in Doze Mode With 1:8 Doze Ratio

**Doze Mode (Doze ratio=1:32)**
- Press Switch (SW0) to enter Doze mode with Doze ratio 1:32 and observe the text "Entered Doze mode 1:32" is displayed on the terminal window after the switch press and wait for the next instruction to be displayed on the terminal window.
- Observe that the current consumption in Doze mode with ratio 1:32 is 225 μA (Refer to Fig. 15).

![power_analysis_doze32_1](images/power_analysis_doze32_1.jpg)

Figure 15. Current Consumption and the Terminal Window in Doze Mode With 1:32 Doze Ratio

**Doze mode (Doze ratio=1:32) – EEPROM Operations**
- Press Switch (SW0) to perform EEPROM operations in Doze mode with Doze ratio 1:32.
- During EEPROM operations, the user needs to wait to observe the text “Completed” on the terminal window, which indicates EEPROM operations are complete and within this time the Switch press is not detected. The CPU and memory operate at only one instruction cycle out of 32 i.e. with reduced frequency (31.2 kHz) compared to the frequency used in Doze mode with ratio 1:8 and rest of the peripherals operates at the system clock speed of 1MHz.
- Observe the current consumption plot during EEPROM operations which is less than the current consumption in Doze mode with ratio 1:8.
- Once the EEPROM operations are completed, user needs to wait for the next instruction to be displayed on terminal window (Refer to Fig. 16).

![power_analysis_doze32_eeprom](images/power_analysis_doze32_eeprom.jpg)

Figure 16. EEPROM Operations in Doze Mode With Doze Ratio 1:32

* Press Switch (SW0) to wake up from the Doze mode with ratio 1:32 and to enter Active mode and observe the text “Entered Active mode (Wakeup)” is displayed on terminal window.
* Observe the current consumption in Active mode and wait until next the instruction is displayed on the terminal window (Refer to Fig. 17).

![power_analysis_doze32_2](images/power_analysis_doze32_2.jpg)

Figure 17. Current Consumption and the Terminal Window in Doze Mode With Doze Ratio 1:32

**Idle Mode**
- Press Switch (SW0) to enter Idle mode, see the text “Entered IdleMode” is displayed on the terminal window and see the average current consumption in Idle mode
- Wait for the next instruction to be displayed on terminal window (Refer to Fig. 18).

![power_analysis_idle](images/power_analysis_idle.jpg)

Figure 18. Current Consumption in Idle Mode

- Press Switch (SW0) to wake up from the Idle mode and enter Active mode (Refer to Fig. 19).

![power_analysis_active_after_idle](images/power_analysis_active_after_idle.jpg)

Figure 19. Current Consumption and the Terminal Window in Active Mode After Waking From Idle Mode

**Sleep Mode**
- Press Switch (SW0) to enter the Sleep mode, see the text displayed on terminal window and notice the average low current consumption. In sleep mode, the MCU consumes the least current power (Refer to Fig. 20).

![power_analysis_sleep](images/power_analysis_sleep.jpg)

Figure 20. Current Consumption and the Terminal window in Sleep Mode

- Press Switch (SW0) to wake up from Sleep Mode and enter Active mode.  After waking up from the sleep mode, MCU starts displaying the first instruction to the user.

# Conclusion
This example demonstrates the configuration of various Power-Down modes available in PIC18-Q10 MCUs. As demonstrated in the example, EEPROM read and write operations take more current in Active mode as compared to Doze mode. In Doze mode, current consumption depends upon the doze ratio selected. In PIC18-Q10 MCUs, Sleep mode is the lowest current mode where the MCU power consumption is minimum, as clock is disabled to CPU and all the other peripherals.
