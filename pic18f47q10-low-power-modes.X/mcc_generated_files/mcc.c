/**
  @Generated PIC10 / PIC12 / PIC16 / PIC18 MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78
        Device            :  PIC18F47Q10
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above or later
        MPLAB             :  MPLAB X 5.20
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

#include "mcc.h"


void SYSTEM_Initialize(void)
{
    INTERRUPT_Initialize();
    PMD_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    EUSART2_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 1_MHz; 
    OSCFRQ = 0x00;
    // TUN 0; 
    OSCTUNE = 0x00;
}

void PMD_Initialize(void)
{
    // CLKRMD CLKR enabled; SYSCMD SYSCLK enabled; SCANMD SCANNER disabled; FVRMD FVR disabled; IOCMD IOC enabled; CRCMD CRC disabled; HLVDMD HLVD disabled; NVMMD NVM enabled; 
    PMD0 = 0x78;
    // TMR0MD TMR0 disabled; TMR1MD TMR1 disabled; TMR4MD TMR4 disabled; TMR5MD TMR5 disabled; TMR2MD TMR2 disabled; TMR3MD TMR3 disabled; TMR6MD TMR6 disabled; 
    PMD1 = 0x7F;
    // ZCDMD ZCD disabled; DACMD DAC disabled; CMP1MD CMP1 disabled; ADCMD ADC disabled; CMP2MD CMP2 disabled; 
    PMD2 = 0x67;
    // CCP2MD CCP2 disabled; CLC5MD CLC5 disabled; CCP1MD CCP1 disabled; CLC6MD CLC6 disabled; PWM4MD PWM4 disabled; PWM3MD PWM3 disabled; CLC7MD CLC7 disabled; CLC8MD CLC8 disabled; 
    PMD3 = 0xFF;
    // CWG1MD CWG1 disabled; UART2MD EUSART2 enabled; MSSP1MD MSSP1 disabled; UART1MD EUSART enabled; MSSP2MD MSSP2 disabled; 
    PMD4 = 0x31;
    // DSMMD DSM disabled; CLC3MD CLC3 disabled; CLC4MD CLC4 disabled; CLC1MD CLC1 disabled; CLC2MD CLC2 disabled; 
    PMD5 = 0xF1;
}


/**
 End of File
*/
