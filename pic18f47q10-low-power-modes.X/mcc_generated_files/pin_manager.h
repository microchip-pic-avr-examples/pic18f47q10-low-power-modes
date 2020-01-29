/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78
        Device            :  PIC18F47Q10
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RB0 aliases
#define IO_RB0_TRIS                 TRISBbits.TRISB0
#define IO_RB0_LAT                  LATBbits.LATB0
#define IO_RB0_PORT                 PORTBbits.RB0
#define IO_RB0_WPU                  WPUBbits.WPUB0
#define IO_RB0_OD                   ODCONBbits.ODCB0
#define IO_RB0_ANS                  ANSELBbits.ANSELB0
#define IO_RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define IO_RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define IO_RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define IO_RB0_GetValue()           PORTBbits.RB0
#define IO_RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define IO_RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define IO_RB0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define IO_RB0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define IO_RB0_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define IO_RB0_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define IO_RB0_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define IO_RB0_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RD0 procedures
#define RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define RD0_GetValue()              PORTDbits.RD0
#define RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define RD0_SetPullup()             do { WPUDbits.WPUD0 = 1; } while(0)
#define RD0_ResetPullup()           do { WPUDbits.WPUD0 = 0; } while(0)
#define RD0_SetAnalogMode()         do { ANSELDbits.ANSELD0 = 1; } while(0)
#define RD0_SetDigitalMode()        do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set LED aliases
#define LED_TRIS                 TRISEbits.TRISE0
#define LED_LAT                  LATEbits.LATE0
#define LED_PORT                 PORTEbits.RE0
#define LED_WPU                  WPUEbits.WPUE0
#define LED_OD                   ODCONEbits.ODCE0
#define LED_ANS                  ANSELEbits.ANSELE0
#define LED_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED_GetValue()           PORTEbits.RE0
#define LED_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LED_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set IO_RE2 aliases
#define IO_RE2_TRIS                 TRISEbits.TRISE2
#define IO_RE2_LAT                  LATEbits.LATE2
#define IO_RE2_PORT                 PORTEbits.RE2
#define IO_RE2_WPU                  WPUEbits.WPUE2
#define IO_RE2_OD                   ODCONEbits.ODCE2
#define IO_RE2_ANS                  ANSELEbits.ANSELE2
#define IO_RE2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define IO_RE2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define IO_RE2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define IO_RE2_GetValue()           PORTEbits.RE2
#define IO_RE2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define IO_RE2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define IO_RE2_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define IO_RE2_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define IO_RE2_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define IO_RE2_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define IO_RE2_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define IO_RE2_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF0 pin functionality
 * @Example
    IOCBF0_ISR();
 */
void IOCBF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF0_SetInterruptHandler() method.
    This handler is called every time the IOCBF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF0_SetInterruptHandler(IOCBF0_InterruptHandler);

*/
extern void (*IOCBF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF0_SetInterruptHandler() method.
    This handler is called every time the IOCBF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF0_SetInterruptHandler(IOCBF0_DefaultInterruptHandler);

*/
void IOCBF0_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/