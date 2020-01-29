#  Introduction
 The term " power down mode” refers to a condition in which a Microcontroller Unit (MCU) enters a low-power mode. The power down modes helps to reduce average power consumption of the MCU through effective management of CPU operations, clock signal to CPU and peripherals. The power down modes in PIC family of MCU’s typically comprises of Doze, Idle, Sleep and Deep sleep modes. The PIC18 Q10 family of MCU’s have three power down modes and they are Doze, Idle and Sleep mode. This example demonstrates configuration of Doze, Idle and Sleep power down modes in PIC18F47Q10 MCU, to achieve low power consumption.         
# 	Power down modes -Theory
This section briefly discusses each of the power down mode available in PIC18 Q10 family.

**Doze mode:** In Doze mode CPU and memory operations are affected, but the peripheral clocks continue to run. Doze mode allows power saving by reducing CPU clock instruction cycle compared to the active mode, while leaving the peripherals clock unchanged. In Doze mode CPU executes only one instruction cycle out of every N-cycles as defined by the DOZE [2:0] bits in CPUDOZE register. For example, if DOZE [2:0] = 001, the instruction cycle ratio is 1:4. The CPU and memory execute for one instruction cycle and then lay idle for three instruction cycles. During the unused cycles, the peripherals continue to operate at the system clock speed.
Steps to enter the Doze mode:
1. CPUDOZEbits.DOZEN    = 1; //Doze enable bit (DOZEN) must be set, to enter the Doze mode.
2. CPUDOZEbits.DOZE[2:0]= 0bxxx; //Select the ratio of CPU clock instruction cycle to Peripheral             clock instruction cycle in DOZE register.
3. CPUDOZEbits.ROI          = 1; //Set the Recover-On-Interrupt bit to come out of the Doze mode, when              interrupt occurs.

**Idle mode:** In Idle mode CPU and Memory operations are halted, but the peripheral clocks continue to run. Device is put into the Idle mode by executing **SLEEP** instruction, when Idle enable bit (IDLEN=1) is set.

**Sleep mode:** Sleep mode turns OFF the system clock. The CPU and all peripherals requiring the system clock will cease operation. The contents of the memory and registers are maintained in the sleep mode. Device is put into the Sleep mode by executing **SLEEP** instruction, when Idle enable bit (IDEN=0) is clear.

# Clocks
This section discusses about System clock, CPU clock and Peripheral cock (Refer Table 1).

**System Clock:** System clock designated as FOSC is the main clock which can be supplied from external oscillators, quartz crystal resonators, ceramic resonators and Resistor-Capacitor (RC) circuits. In addition, the system clock source can be supplied from one of two internal oscillators. Oscillator module can be configured to select one of the clock sources.

**CPU Clock:** The instruction clock or CPU clock is derived from the system clock or FOSC through a divider to deliver an instruction clock of FOSC/4 (1/4 the oscillator speed). This is done to allow the fetch and execute pipeline in the architecture to execute one assembly instruction per instruction clock cycle (except for branches and goto's which execute in two). CPU clock is supplied to the CPU and memory to perform CPU and memory Operations in the application.

**Peripheral Clock:** Clock to different peripherals can be selected from various options such as FOSC i.e. the system clock, FOSC/4 (instruction clock or CPU clock), output of other peripherals, LFINTOSC, MFINTOSC, HFINTOSC or Timer overflow events etc.

![](https://i.imgur.com/TO5wWYw.jpg)

  **Table 1 : Clock details in Power Down modes**

### Peripheral Module Disable:
The Peripheral Module Disable (PMD) provides the ability to disable a peripheral module by stopping all clock sources supplied to that module. A peripheral can be disabled by setting the corresponding peripheral disable bit in the PMDx register.  All the peripherals are enabled by default. To reduce overall power consumption, the user can disable unused modules/Peripherals. Refer to the device data sheet for more details about the PMD register

# Demo Description

![](https://i.imgur.com/eQTtz4s.jpg)

**Figure 1: Block diagram of application demo**   

  In this demo,
*    PIC18F47Q10 Curiosity Nano and Power debugger boards from Microchip are used to demonstrate power down modes configuration and to measure MCU power consumption.
*    The on-board mechanical switch (SW0) of PIC18F47Q10 Curiosity Nano board is used to invoke power down modes or to wake up the MCU from power down modes which happens sequentially at each switch press event.
*    The MCU operating mode (i.e. Active mode/Doze mode/Idle mode/Sleep mode) information is transmitted to the terminal window of Data visualizer tool, through virtual COM port of the Curiosity nano board.
*    The power debugger board measures the power consumption of the PIC18F47Q10 MCU and transmit it to the power analysis window of Data visualizer tool.
*    The onboard LED(LED0) is used as an indication while the MCU wakes up from any of the power down modes and enters the active mode.
*    Active mode: After power up, by default MCU operates in Active mode. To a switch press event the MCU performs EEPROM write and read operations. The power consumption of Curiosity Nano board in Active mode, can be viewed on power analysis window of the Data visualizer tool.
*   Doze mode: The MCU enters Doze mode to a switch press event and performs the EEPROM operation. In this mode CPU operates at reduced clock instruction cycles compared to the active mode. The MCU continue to be in Doze mode until a switch press event is detected. Upon a switch press event, the MCU wake up from Doze mode and enter Active mode. Then after the on-board LED turns ON indicating the MCU is in active mode.
*  	Idle mode: The MCU enters Idle mode to a switch press event. The MCU continue to be in Idle mode until a switch press event is detected. Upon a switch press event, the MCU wake up from the Idle mode and enter active mode. Then after the on-board LED turns ON indicating the MCU is in active mode.
*  Sleep mode: The MCU enters Sleep mode to a switch press event. The MCU continue to be in Sleep mode until a switch press event is detected. Upon a switch press event, the MCU wake up from the Sleep mode and enter active mode. Then after the on-board LED turns ON indicating the MCU is in active mode.

# Hardware used
### PIC18F47Q10 Curiosity nano board:
With full program and debug capabilities, the PIC18F47Q10 Curiosity Nano evaluation kit offers complete support for the new design. With the award-winning MPLAB X integrated development platform and MPLAB Code Configurator (MCC), the kit provides access to the Intelligent analog and Core Independent Peripherals on the PIC18F47Q10. Figure 2 shows PIC18F47Q10 Curiosity Nano board.For more details refer to the [PIC18F47Q10 Curiosity Nano Hardware user guide](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F47Q10-Curiosity-Nano-Hardware-User-Guide.pdf)

 ![](https://i.imgur.com/yvGS1Bp.jpg)

**Figure 2: PIC18F47Q10 Curiosity Nano board**

###  Power Debugger:    
Power debugger is a powerful development tool used for debugging and programming the AVR and SAM MCUs. The power debugger contains two channels for measuring power consumption, one channel is used for High-precision low-current measurement, while the second channel is used for Low-precision high-current measurement. In this example Power Debugger with Channel A (High precision low-current measurement) is used in order to measure current consumption of the PIC18F47Q10 MCU and to transmit the measured data to Power Analysis window of data visualizer tool. For more details refer to the [Power Debugger user guide](http://ww1.microchip.com/downloads/en/DeviceDoc/Power-Debugger_UserGuide.pdf). Figure 3 shows the Power debugger.

![](https://i.imgur.com/trDnua5.jpg)

**Figure 3: Power Debugger**

**Note: In Curiosity Nano board, on-board level shifters will draw a current of 20 μA. To know the power consumption of PIC18F47Q10 MCU in each power down modes, minus 20 μA from actual power consumption.**

# Software Tools:
Microchip’s free MPLAB X IDE, compiler and MPLAB Code Configurator (MCC) graphical code generator are used throughout the firmware development. Following are the tool versions used for this demo application:
* MPLAB X IDE v5.30
* XC8 Compiler v2.10
* MPLAB Code Configurator (MCC v3.85.1)
* Standalone Data Visualizer 2.20.674

**Note: For running the demo, the installed tool versions should be same or later. This example is not tested with previous versions.**

### Data Visualizer:
 The Data Visualizer is a software tool used to process and visualize data. The Data Visualizer can receive data from various sources such as the Embedded Debugger Data Gateway Interface (DGI) and COM ports. Data Visualizer is made up of several modules such as Graph, Oscilloscope, Terminal, Power debugging, Custom dashboard etc. In this example Standalone data visualizer tool is used to receive power consumption data from the Curiosity Nano board, and display it on Power analysis window .The terminal window is used to display the operating modes of the PIC18F47Q10 MCU(i.e. Active mode/Doze mode/Idle mode/Sleep mode). For more details on Data Visualizer tool refer to the [Data Visualizer user guide](http://ww1.microchip.com/downloads/en/DeviceDoc/40001903B.pdf).

#  Demo realization
## Peripherals Configuration using MCC
### System Configuration
The system configuration window of MCC is used for MCU oscillator, PLL, Watchdog timer and low voltage programming configuration. Internal oscillator of 1MHz frequency with clock divider 1 is used as a system clock and the Watchdog timer is disabled in this example. Figure 4 shows the system configuration settings used in this example.

![](https://i.imgur.com/cmTYkxk.jpg)

**Figure 4: System Configuration**

### EUSART2 Configuration
In this demo EUSART2 is used to transmit data on the terminal window to display the device mode of operation (i.e. active/doze/idle/sleep). Figure 5 shows the EUSART2 module configuration settings.
Configurations to be done on EUSART2 peripheral:
* Check the Enable EUSART checkbox.
* Check the Enable Transmit checkbox.
* Set the Baud Rate to 9600.
* Check the Redirect STDIO to USART.

![](https://i.imgur.com/WBsP0pA.jpg)

**Figure 5: EUSART2 Configuration**



### Pin Module
The I/O pin mapping of the PIC18F47Q10 MCU for EUSART2 interface and Curiosity Nano on board LED is shown in the figure 6.
Configurations to be done:
* Select pin RD0 as an EUSART2 TX pin.
* Configure pin RE0 as output to connect to LED0.
* Configure pin RE2 as input. The RE2 pin is connected to Switch and external interrupt feature is not available on pin RE2, so pin RB0 with IOC (Interrupt on Change) is used for detecting switch press event.
* Set pin RB0 IOC (Interrupt on Change) to positive.

![](https://i.imgur.com/9V3lVDx.jpg)

**Figure 6: Pin manager configuration**

![](https://i.imgur.com/Fdhpadi.jpg)

**Figure 7: Pin module configuration**

### Memory Configuration
In the peripherals section of MCC, click on Memory. Flash memory read/write routines are automatically included. Check the Add DataEE Routines to include EEPROM memory write/read routines which are required for this example.

 ![](https://i.imgur.com/O2kLe9m.jpg)

 **Figure 8:Memory module configuration**

# 	 Hardware Setup
There are two methods for Hardware connection.

### First Method:
1.	Short the pins RE2 and RB0 using the jumper.
2.	Cut the VTG strap on PIC18F47Q10 Curiosity nano board to measure the power consumption of the MCU (refer Figure 9).

![](https://i.imgur.com/quROXme.jpg)

**Figure 9:Cut VTG strap on Curiosity Nano Board**

3.	Setup the hardware connections as shown in figure 10:
* 	Short the Variable Supply voltage pin to the Channel A input pin of power debugger
* 	Since VTG strap is cut, power to the target MCU is suspended from USB. Power debugger is used as a source, to supply power to the Curiosity Nano Board. Connect Channel A output of power debugger to the VTG pin of Curiosity nano board, which supplies power of 3.3V.

![](https://i.imgur.com/6RTHswm.jpg)

**Figure 10: Current measurement using power debugger hardware connections**

![](https://i.imgur.com/NY95EdQ.jpg)

**Figure 11: Hardware setup**

4.	Power debugger has an on-board voltage supply which can provide up to 1.6V to 5.5V from the USB DEBUG connector. To supply 3.3V to the PIC18F47Q10 MCU follow the steps below:
* In the Data Visualizer window, select **Power Debugger Data Gateway** in DGI control panel.
* Enable power interface in DGI control panel and open Power Configuration window by clicking on **Setting** icon. Uncheck **Enable B channel** which disables Channel B, so that Channel A can be used.
* Check the **Enable Voltage Output** and by varying the **Voltage Output** slider, set voltage to 3.3V.
* Click on **OK** button.

![](https://i.imgur.com/sxVRnC2.jpg)

**Figure 12: Power Configuration window**

### Second Method:
1.	Short the pins RE2 and RB0 using the jumper.
2.	Cut the VTG strap on PIC18F47Q10 Curiosity nano board and solder two wires on that VTG strap
3.	Connect the two soldered wires to the Channel A of the power debugger in series to measure current as shown in figure 13.


![](https://i.imgur.com/56dKdha.jpg)

**Figure 13:Current measurement using power debugger hardware connections**

4.  Setup the hardware, as shown in figure 14.

![](https://i.imgur.com/HPSe3vH.jpg)

**Figure 14:Hardware setup**

**(Steps from 5 to 10 are same for the two methods of hardware connection)**

5. Power the Curiosity nano board from PC machine, by connecting micro USB cable between PC USB port and micro USB port of the Curiosity nano board.

6. Similarly, power the Power debugger board from PC machine, by connecting micro USB cable between PC USB port and micro USB port (named as DEBUG) of the power debugger board.

7. The Curiosity Nano board should appear as a Mass Storage Device after connecting to the PC.

8. Program the MCU by clicking “Make and Program Device” icon on MPLAB XPRESS IDE as shown in figure 15.

![](https://i.imgur.com/HowCk6M.jpg)

**Figure 15:Programming the device**

9.  IDE generates the .hex file, save the file in local PC.
10.  Drag the .hex from the downloads section and drop the file on to the Curiosity drive. This should program the device.


**Follow the steps listed below, to open Power Analysis and Terminal window in Data Visualizer.**
### Steps to open the Power Analysis window in Data Visualizer
**Open the standalone Data Visualizer tool.**
1.  In the Data Visualizer window, click on the **Configuration tab**.
2.	In the **Modules section**, expand **External connection option** and then double click on **Data Gateway Interface (DGI).**
3.  Select the **Power Debugger Data Gateway** in DGI Control Panel.
4.  Click on the **Connect** button.
5.  Enable the **Power** Interface in DGI Control Panel, to allow the measured power data being sent from Power Debugger Data Gateway to the DGI Control Panel.
6.  In the **Modules** section, expand **Visualization** option and then double click on **Power Debugging**, **Power Analysis** window will be opened.
7. In Power Analysis window, expand **Control Panel** and drag the Channel A current source from DGI Control Panel and drop it into Channel A current sink in Power Analysis window.
8.	Start receiving the power data by clicking **Start** button.

![](https://i.imgur.com/COBgVqn.jpg)

**Figure 16:Start Data visualizer and open Power analysis window**



### Steps to open Terminal window in Data Visualizer:
**Open the standalone Data Visualizer tool.**
1.	In the Data Visualizer window, click on the **Configuration tab**.
2.	In the **Modules section**, expand **External connection** option and then double click on Serial Port.
3.	Select the **Curiosity Virtual Com Port** in Serial Port Control Panel.
4.	Set the Baud rate to 9600.
5.	Check the **“Open Terminal”** option.
6.	Click on the **Connect** button.

![](https://i.imgur.com/RXXt0uk.jpg)

**Figure 17:Open terminal window in Data visualizer**


# Demo Operation
Instant and Window Average current consumption Explanation:

![](https://i.imgur.com/auQBxsZ.jpg)

**Figure 18:Power Analysis window for Instant and Window Average**

**Instant Current Consumption:**
Figure 18 shows the instant current consumption of MCU at time T1 is 545.3 μA.

**Window Average:**
 Window Average is the average current consumption of the samples over the period. Figure 14 shows the window average current consumption of MCU is 250.8 μA.

**Following figures show the average current consumption of the Curiosity nano board in different power down modes of MCU.**

**The intend of demonstration is to showcase the configuration and functionality of MCU power down modes and the power consumption values discussed in this document are observed with mentioned Hardware setup as shown in figure 14.**

**Active mode:**
* After power up the MCU, enters the Active mode.
* Before each switch press, instructions are mentioned to the user on terminal window.  E.g.  Press Switch- To perform EEPROM Operation in Active mode.
* When the Curiosity Nano board is loaded with the firmware, following waveform (Refer Fig 19) is observed and instructions are provided on terminal window to the user for further operations.
* Observe the average current consumption of the MCU in Active mode is 243.7 μA.
* Refer Window average current and don’t refer instant current.

![](https://i.imgur.com/HHPnxsd.jpg)

**Figure 19:Power Analysis and Terminal window in Active Mode**


**Active mode –EEPROM Operation**
* Press Switch (SW0) to perform EEPROM Operation in Active mode and user needs to wait until the “Completed” text is displayed on terminal window, which indicates EEPROM Operation is completed.
* Observe the average current consumption during EEPROM Operation in Active mode is 916.8 μA  (Refer Fig 20).

![](https://i.imgur.com/3pC8WOS.jpg)

**Figure 20:Open terminal window in Data visualizer**

* Observe the “Completed” text and next instruction to the user is displayed on terminal window (Refer Fig 21).

![](https://i.imgur.com/kaM3vUc.jpg)

**Figure 21:Power Analysis and Terminal window in Active Mode**

**Doze mode (Doze ratio=1:8)**
* Press Switch (SW0) to enter Doze mode with Doze ratio 1:8 and observe the text” Entered Doze mode 1:8” is displayed on terminal window after switch press and wait for the next instruction to be displayed on terminal window.
* Observe the average current consumption in Doze mode with ratio 1:8 is 217.5 μA (Refer Fig 22).

![](https://i.imgur.com/cD9JDuY.jpg)

**Figure 22:Power Analysis and Terminal window in Doze mode with 1:8 doze ratio**

**Doze mode (Doze ratio=1:8) – EEPROM Operation**
* Press Switch (SW0) to perform EEPROM Operation in Doze mode with Doze ratio 1:8.
* During EEPROM Operation , user needs  to wait to observe the text “Completed” on terminal window, which indicates EEPROM Operation is completed and within this time Switch press is not detected .The CPU and memory operate at only one instruction cycle out of the eight i.e. with reduced frequency (125kHz) compare to the frequency  used in the Active mode and rest of the peripherals operates at the system clock speed i.e. 1MHz frequency.
* Observe the average current consumption during EEPROM Operation is 745.1 μA.
* Once the EEPROM Operation is completed, user needs to wait for the next instruction to be displayed on terminal window (Refer Fig 23).

![](https://i.imgur.com/9gVH3yR.jpg)

**Figure 23:EEPROM Operation in Doze mode with 1:8 doze ratio**

* Press Switch (SW0) to wake up from the Doze mode with ratio 1:8 and to enter Active mode and observe the text “Entered Active mode (Wakeup)” is displayed on terminal window.
* Observe the current consumption in Active mode is 243.7 μA and wait until next instruction is displayed on terminal window (Refer Fig 24).

![](https://i.imgur.com/VAhAdLW.jpg)

**Figure 24:Power Analysis and Terminal window in Doze mode with 1:8 doze ratio**

**Doze mode (Doze ratio=1:32)**
* Press Switch (SW0) to enter Doze mode with Doze ratio 1:32 and observe the text” Entered Doze mode 1:32” is displayed on terminal window after switch press and wait for the next instruction to be displayed on terminal window.
* Observe the average current consumption in Doze mode with ratio 1:32 is 214.8 μA (Refer Fig 25).

![](https://i.imgur.com/HlN367w.jpg)

**Figure 25:Power Analysis and Terminal window in Doze mode with Doze ratio 1:32**

**Doze mode (Doze ratio=1:32) –EEPROM Operation**
* Press Switch (SW0) to perform EEPROM Operation in Doze mode with Doze ratio 1:32.
* During EEPROM Operation , user needs  to wait  to observe the text “Completed” on terminal window, which indicates EEPROM Operation is completed and within this time Switch press is not detected .The CPU and memory operate at only one instruction cycle out of 32  i.e. with reduced  frequency (31.2kHz) compared to the frequency used in the Doze mode with ratio 1:8 and rest of the peripherals operates at the system clock speed i.e. 1MHz frequency.
* Observe the average current consumption during EEPROM Operation is 513.6 μA which is less than the current consumption in Doze mode with ratio 1:8.
* Once the EEPROM Operation is completed, user needs to wait for the next instruction to be displayed on terminal window (Refer Fig 26).

![](https://i.imgur.com/xHJlUrD.jpg)

**Figure 26:EEPROM operation in Doze mode with Doze ratio 1:32**

* Press Switch (SW0) to wake up from the Doze mode with ratio 1:32 and to enter Active mode and observe the text “Entered Active mode (Wakeup)” is displayed on terminal window.
* Observe the average current consumption in Active mode is 243.7 μA and wait until next instruction is displayed on terminal window (Refer Fig 27).

![](https://i.imgur.com/0Nvb4Aa.jpg)

**Figure 27:Power Analysis and Terminal window in Doze mode with Doze ratio 1:32**

**Idle Mode**
* Press Switch (SW0) to enter Idle mode, observe the text “Entered IdleMode” is displayed on Terminal window and observe the average current consumption in Idle mode is 212.9 μA on Power Analysis window.
* Wait for the next instruction to be displayed on terminal window (Refer Fig 28).

![](https://i.imgur.com/okV4KYg.jpg)

**Figure 28:Power Analysis and Terminal window in Idle mode**

* Press Switch (SW0) to wake up from the Idle mode and enter Active mode (Refer Fig 29).

![](https://i.imgur.com/81Gypq3.jpg)

**Figure 29:Power Analysis and Terminal window in Active mode after waking from the Idle mode**

**Sleep Mode**
* Press Switch (SW0) to enter the Sleep mode, observe the text displayed on Terminal window and observe the average low current consumption 589.4 nA on Power Analysis window. In the sleep mode MCU consumes lowest current (Refer Fig 30).

![](https://i.imgur.com/R0yYrp5.jpg)

**Figure 30:Power Analysis and Terminal window in Sleep mode**

* Press Switch (SW0) to wake up from Sleep Mode and enter Active mode.  After waking up from the Sleep mode, MCU starts displaying the first instruction to the user (Refer Fig 31).

![](https://i.imgur.com/mTbYRsK.jpg)

**Figure 31:Power Analysis and Terminal window in Active mode after waking from the Sleep mode**

# Conclusion
This example demonstrates the configuration of various power down modes available in PIC18 Q10 MCUs. As demonstrated in the example, EEPROM Write and Read operations takes more current in Active mode as compared to Doze mode. In Doze mode current consumption depends upon the doze ratio selected. In PIC18 Q10 MCUs, Sleep mode is the lowest current mode where the MCU power consumption is minimum, as clock is disabled to CPU and all the other peripherals.
