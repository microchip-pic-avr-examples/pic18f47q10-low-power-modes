/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.1.1
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

void (*IO_RB0_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x0;
    LATD = 0x0;
    LATE = 0x0;
    /**
    ODx registers
    */
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;
    ODCOND = 0x0;
    ODCONE = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0xFF;
    TRISD = 0xFE;
    TRISE = 0x6;

    /**
    ANSELx registers
    */
    ANSELA = 0xFF;
    ANSELB = 0xFE;
    ANSELC = 0xFF;
    ANSELD = 0xFE;
    ANSELE = 0x2;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0x1;
    WPUC = 0x0;
    WPUD = 0x0;
    WPUE = 0x4;


    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x7;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0xF;

   /**
    RxyI2C | RxyFEAT registers   
    */
    /**
    PPS registers
    */
    RD0PPS = 0x0B;  //RD0->EUSART2:TX2;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCBP = 0x1;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x0;
    IOCCF = 0x0;
    IOCEP = 0x0;
    IOCEN = 0x0;
    IOCEF = 0x0;

    IO_RB0_SetInterruptHandler(IO_RB0_DefaultInterruptHandler);

    // Enable PIE0bits.IOCIE interrupt 
    PIE0bits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin IO_RB0
    if(IOCBFbits.IOCBF0 == 1)
    {
        IO_RB0_ISR();  
    }
}
   
/**
   IO_RB0 Interrupt Service Routine
*/
void IO_RB0_ISR(void) {

    // Add custom IO_RB0 code

    // Call the interrupt handler for the callback registered at runtime
    if(IO_RB0_InterruptHandler)
    {
        IO_RB0_InterruptHandler();
    }
    IOCBFbits.IOCBF0 = 0;
}

/**
  Allows selecting an interrupt handler for IO_RB0 at application runtime
*/
void IO_RB0_SetInterruptHandler(void (* InterruptHandler)(void)){
    IO_RB0_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IO_RB0
*/
void IO_RB0_DefaultInterruptHandler(void){
    // add your IO_RB0 interrupt custom code
    // or set custom function using IO_RB0_SetInterruptHandler()
}
/**
 End of File
*/