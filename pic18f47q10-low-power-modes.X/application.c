/**
 * **********************************************************
 *  include files
 * **********************************************************
 **/
#include "mcc_generated_files/system/system.h"
#include "application.h"
#include "stdio.h"

/**
 * **********************************************************
 *  Macros definitions
 * **********************************************************
 **/

#define ONE_SEC                            (1000)

#define MAX_EEPROM_OPERATION_CNT           (30)

#define DOZEMODE_EEPROM_ADDRESS            (0X0200)
#define ACTIVEMODE_EEPROM_ADDRESS          (0X0010)

#define CLK_RATIO_1_8_IN_DOZE_MODE         (0X02)
#define CLK_RATIO_1_32_IN_DOZE_MODE        (0X04)

/**
 * **********************************************************
 *  File local variables
 * **********************************************************
 **/




//string to display on terminal window as soon as MCU is loaded with firmware
const uint8_t  applicationStartedText[]       ="  Application started     MCU is in Active mode\n";

//strings to display on terminal window, when MCU enters powerdown modes by switch press
const  uint8_t eepromOperationStartedText[]   = "\tEEPROM  Operation started .....Inprogress...wait....";
const  uint8_t eepromOperationCompletedText[] = "....Completed\n\n";
const  uint8_t dozeModeText_1_8[]             = "\tEntered DozeMode (1:8)\n\n";
const  uint8_t dozeModeText_1_32[]            = "\tEntered DozeMode (1:32)\n\n";
const  uint8_t idleModeText[]                 = "\tEntered IdleMode\n\n";
const  uint8_t sleepModeText[]                = "\tEntered SleepMode\n\n";
const  uint8_t wakeUpText[]                   = "\tEntered ActiveMode (Wakeup)\n\n";

//instructions to the user is displayed on terminal window to press switch inorder to enter into powerdown modes

const uint8_t dummyString[]={0};
const uint8_t pressSwitchText[]= "Press Switch-";
const uint8_t toEnterText[]    = "To Enter";
const uint8_t toPerformText[]  = "To Perform";
const uint8_t toExitText[]     = "To Exit";
const uint8_t EEPROM_OpActiveModeInsText[]   = "EEPROM Operation in Activemode\n";
const uint8_t dozeModeInsTextToEnter_1_8[]   = "Dozemode (1:8)\n";
const uint8_t EEPROM_OpDozeModeInsText_1_8[] = "EEPROM Operation in Dozemode (1:8)\n";
const uint8_t dozeModeInsTextToExit_1_8[]    = "Dozemode and Enter Activemode\n";
const uint8_t dozeModeInsTextToEnter_1_32[]  = "Dozemode (1:32)\n";
const uint8_t EEPROM_OpDozeModeInsText_1_32[]= "EEPROM Operation in Dozemode (1:32)\n";
const uint8_t dozeModeInsTextToExit_1_32[]   = "Dozemode and Enter Activemode\n";
const uint8_t idleModeInsTextToEnter[]       = "Idlemode\n";
const uint8_t idleModeInsTextToExit[]        = "Idlemode and Enter Active mode\n";
const uint8_t sleepModeInsTextToEnter[]      = "Sleepmode\n";
const uint8_t sleepModeInsTextToExit[]       = "Sleepmode and Enter Active mode\n";

//enum typedef for key press status
typedef enum 
{
    KEY_NO_ACTION,
    KEY_PRESSED,
    KEY_RELEASED,
}buttonState_t;

static buttonState_t buttonState = KEY_NO_ACTION;


typedef enum
{
    DUMMY_TEXT,
    EEPROM_OP_ACTIVE_MODE_INS_TXT,
    DOZEMODE_INS_TXT_TO_ENTER_1_8,
    EEPROM_OP_DOZE_MODE_INS_TXT_1_8,
    DOZEMODE_INS_TXT_TO_EXIT_1_8, 
    DOZEMODE_INS_TXT_TO_ENTER_1_32,
    EEPROM_OP_DOZE_MODE_INS_TXT_1_32,
    DOZEMODE_INS_TXT_TO_EXIT_1_32,
    IDLEMODE_INS_TXT_TO_ENTER,       
    IDLEMODE_INS_TXT_TO_EXIT,  
    SLEEPMODE_INS_TXT_TO_ENTER,       
    SLEEPMODE_INS_TXT_TO_EXIT,          
    
} pressSwitchInstruction_t;

const  uint8_t *displayStrings[]=
{
    dummyString,
    EEPROM_OpActiveModeInsText,
    dozeModeInsTextToEnter_1_8,
    EEPROM_OpDozeModeInsText_1_8,
    dozeModeInsTextToExit_1_8,
    dozeModeInsTextToEnter_1_32,
    EEPROM_OpDozeModeInsText_1_32,
    dozeModeInsTextToExit_1_32,
    idleModeInsTextToEnter,
    idleModeInsTextToExit,
    sleepModeInsTextToEnter,
    sleepModeInsTextToExit
};

typedef enum
{
    APP_INIT,
    PRESS_SW_TO_START_EEPROM_OP_IN_ACTIVE_MODE,
    WAIT_FOR_SWITCH_PRESS,
    EEPROM_OPERATION_ACTIVE_MODE,
    ACTIVATE_DOZE_MODE_1_8,
    EEPROM_OPERATION_DOZE_MODE_1_8,
    WAKE_DOZE_MODE_1_8,
    ACTIVATE_DOZE_MODE_1_32,
    EEPROM_OPERATION_DOZE_MODE_1_32,
    WAKE_DOZE_MODE_1_32,
    ACTIVATE_IDLE_MODE,
    WAKE_IDLE_MODE,
    ACTIVATE_SLEEP_MODE,
    WAKE_SLEEP_MODE,
} appState_t;
 
static appState_t appTaskCurrState = APP_INIT;
static appState_t appTaskPrevState;



/**
 * **********************************************************
 *  static function's declaration
 * **********************************************************
 **/

static void EnableSwitchPress(void);
static void DisableSwitchPress(void);
static void SendButtonPressInstruction( pressSwitchInstruction_t displayStringsIndex,const uint8_t *actionText);
static void LEDBlink(void);
static void MemoryOperation(const uint16_t address, const uint8_t *data);
static void SendStringWakeup(void);
static void ActivateDozeMode(uint8_t reg);
static void DisableDozeMode(void);
static void ActivateIdleMode(void);
static void DisableIdleMode(void);
static void ActivateSleepMode(void);


/**
 * **********************************************************
 *  global function's definition
 * **********************************************************
 **/




/**
  @Param
  none
  @Returns
   none
  @Description
  function to enable the button press interrupt,to detect button press and enter into the powerdown modes
 **/
void EnableSwitchPress(void) 
{
     // Enable Interrupt-on-Change Enable bit in Peripheral Interrupt Enable Register 0
    PIE0bits.IOCIE = 1;   
     //Enable interrupt on change for group IOCBP register - positive
    IOCBPbits.IOCBP0 = 1;
     // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
     // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();   
   
}
/**
  @Param
  none
  @Returns
   none
  @Description
  function to disable the button press interrupt,and not to detect button press during EEPROM Operation and
 before displaying next instruction to press switch inorder to enter into powerdown modes.
 **/
void DisableSwitchPress(void) 
{
    // Disable Interrupt-on-Change Enable bit in Peripheral Interrupt Enable Register 0
    PIE0bits.IOCIE = 0;
    //Disable interrupt on change for group IOCBP register - positive
    IOCBPbits.IOCBP0 = 0;
    // Disable the Global Interrupts
    INTERRUPT_GlobalInterruptDisable();
    // Disable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptDisable();
}


/**
  @Param
  none
  @Returns
   none
  @Description
  function to send an instruction to the user to press switch for the following instances:
     *To enter into the powerdown modes
     *To wakeup from the powerdown modes
     *To perform EEPROM Operation in Active and Dozemode 
 **/
void SendButtonPressInstruction( pressSwitchInstruction_t displayStringsIndex, const uint8_t* actionText) 
{  
    printf ("%d. %s %s %s", displayStringsIndex,pressSwitchText,actionText,displayStrings[displayStringsIndex]);
}


/**
   @Param
   none
   @Returns
    none
   @Description
   function to turn LED ON for one SEC and turn OFF
 **/
void LEDBlink(void) 
{
    LED_ON();
    __delay_ms(ONE_SEC);
    LED_OFF();
}

/**
   @Param
   address-EEPROM address
   data-EEPROM data
   @Returns
    none
   @Description
   Performs EEPROM Write and Read operation in Active mode and Doze mode by switch press
 **/
void MemoryOperation(const uint16_t address, const uint8_t *data) 
{   
    uint8_t tempData;
    uint8_t eepromOperationCount = 0;
    int j = 0;
    while (eepromOperationCount < MAX_EEPROM_OPERATION_CNT ) 
    {
        for (j = 0; *(data + j) != '\0'; j++) 
        {
            //EEPROM Write operation to the memory
            NVM_UnlockKeySet(UNLOCK_KEY_WORD_BYTE_WRITE);
            EEPROM_Write(address, *(data + j));
            //EEPROM Read operation 
            tempData = EEPROM_Read(address);
            //sending the data through EUSART2 peripheral
            NVM_UnlockKeyClear();
            if (eepromOperationCount==1) 
            {
                 EUSART2_Write(tempData);
            }

        }
        eepromOperationCount++;
    }
    printf("%s",eepromOperationCompletedText);
}  
   



/**
   @Param
    none
   @Returns
    none
   @Description
   function to transmit wakeup text after waking up from the power down modes and
   LED turns ON for 0.6 milli secs and turns OFF to indicate the MCU is waked up from powerdown modes 
 *
 **/
void SendStringWakeup(void)
{
    printf("%s",wakeUpText);
    //delay is given to avoid the text display on terminal window back-to-back continously 
    __delay_ms(ONE_SEC);
    LEDBlink();
}


/**
   @Param
   reg is used as a nibble
   @Returns
    none
   @Description
   function to activate Doze mode with Doze ratio 1:8 and 1:32 using reg varaible, by switch press
 **/
void ActivateDozeMode(uint8_t reg) 
{

    //Register to select the CPU Doze ratio
    CPUDOZE = reg & 0x0F;
    //Doze mode enable bit
    CPUDOZEbits.DOZEN = 1;
    if (reg == 0x02) 
    {
        //Send Dozemode entered text on terminal window
        printf("%s",dozeModeText_1_8);
    }
    else 
    {

        printf("%s",dozeModeText_1_32);
    }
    //Recover on Interrupt enable bit
    CPUDOZEbits.ROI = 1;
}
/**
  @Param
  none
  @Returns
   none
  @Description
  function to disable Doze mode and enter into Activemode
 **/
void DisableDozeMode(void)
{
  //Disable Doze Enable bit in CPUDOZE Register
  CPUDOZEbits.DOZEN = 0;  
}

/**
   @Param
    none
   @Returns
    none
   @Description
   function to activate Idle mode by switch press
 **/
void ActivateIdleMode(void) 
{
    //Send string Idle Mode on terminal window
    printf("%s",idleModeText);
    //delay is given to avoid the text display on terminal window back-to-back continously 
     __delay_ms(ONE_SEC);
    //Displays the next instruction to the user on terminal window
    SendButtonPressInstruction( IDLEMODE_INS_TXT_TO_EXIT,toExitText);
    //Enable Switch press to detect button press interrupt
    EnableSwitchPress();
    //Idle mode enable bit
    CPUDOZEbits.IDLEN = 1;
    SLEEP();
}
/**
  @Param
  none
  @Returns
   none
  @Description
  function to disable Idle mode and to enter Activemode
 **/
void DisableIdleMode(void)
{
    //Disable Idle Enable bit in CPUDOZE Register
      CPUDOZEbits.IDLEN = 0;
  
}

/**
   @Param
    none
   @Returns
    none
   @Description
   function to activate Sleep mode by Switch press
 **/
void ActivateSleepMode(void) 
{
    //Send string Sleep mode on terminal window 
   printf("%s",sleepModeText);
     //delay is given to avoid the text display on terminal window back-to-back continously 
     __delay_ms(ONE_SEC);
    //Displays the next instruction to the user on terminal window
    SendButtonPressInstruction(SLEEPMODE_INS_TXT_TO_EXIT,toExitText);
    //Enable Switch press to detect switch press interrupt
    EnableSwitchPress();
    //Sleep mode enable bit
    CPUDOZEbits.IDLEN = 0;
    Sleep();
}




/**
 @Param
  none
 @Returns
  none
 @Description
 ApplicationTask().
 @brief
 * SendString()-To print powerdown mode Enter/Wakeup/EEPROM Operation text on terminal window 
 * SendButtonPressInstruction()-To print next instruction,press switch to Enter/Wakeup/EEPROM Operation 
                                   to the user on terminal window
 * DisableSwitchPress()-After entering into powerdown mode,disables switchpress interrupt until next 
                      instruction to the user is displayed on terminal window. 
 * EnableSwitchPress()-Enable switch press interrupt to detect switch press.
 * ActivateDozeMode()-function to activate Doze mode by switch press and displays Dozemode entered text.
 * ActivateIdleMode()-function to activate Idle mode by switch press and displays Idlemode entered text.
 * ActivateSleepMode()-function to activate Sleep mode by switch press and displays Sleepmode entered text
 * SendStringWakeup()-Sends wakeup text after waking up from the power down mode by switch press and 
                                                    LED turns ON for 0.6 milli seconds and OFF .   
 * DisableDozeMode()-function to come out of the Dozemode .
 * DisableIdleMode()-function to come out of the Idlemode.  
 * MemoryOperation()-Performs Memory Write and Read operation.                    
 **/
void ApplicationTask(void)
{
    
    // ButtonDriver(); //.. in this appplication button state is beiing updated inside the ISR
    // MemoryWRDriver(); // .. in this application this operation is depends upon application functionality
    switch (appTaskCurrState)
    {
        case APP_INIT:
            printf("%s",applicationStartedText);
            appTaskCurrState = PRESS_SW_TO_START_EEPROM_OP_IN_ACTIVE_MODE;
            break;
        case PRESS_SW_TO_START_EEPROM_OP_IN_ACTIVE_MODE:
            SendButtonPressInstruction( EEPROM_OP_ACTIVE_MODE_INS_TXT,toPerformText);
            appTaskPrevState = WAIT_FOR_SWITCH_PRESS;
            appTaskCurrState =  appTaskPrevState;
            break;
        case WAIT_FOR_SWITCH_PRESS:
            //check for button press and update current state
            if (buttonState == KEY_PRESSED) 
            {
                appTaskCurrState =  appTaskPrevState + 1;
                 buttonState = KEY_RELEASED;
            }
            break;
        case EEPROM_OPERATION_ACTIVE_MODE:
            DisableSwitchPress();
            MemoryOperation(ACTIVEMODE_EEPROM_ADDRESS, eepromOperationStartedText);
            SendButtonPressInstruction(DOZEMODE_INS_TXT_TO_ENTER_1_8,toEnterText);
            EnableSwitchPress();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case ACTIVATE_DOZE_MODE_1_8:
            DisableSwitchPress();
            ActivateDozeMode(CLK_RATIO_1_8_IN_DOZE_MODE);
            SendButtonPressInstruction(EEPROM_OP_DOZE_MODE_INS_TXT_1_8,toPerformText);
            EnableSwitchPress();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case EEPROM_OPERATION_DOZE_MODE_1_8:
            DisableSwitchPress();
            MemoryOperation(DOZEMODE_EEPROM_ADDRESS, eepromOperationStartedText);
            SendButtonPressInstruction(DOZEMODE_INS_TXT_TO_EXIT_1_8,toExitText);
            EnableSwitchPress();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case WAKE_DOZE_MODE_1_8:
            DisableSwitchPress();
            DisableDozeMode();
            SendStringWakeup();
            SendButtonPressInstruction(DOZEMODE_INS_TXT_TO_ENTER_1_32,toEnterText);
            EnableSwitchPress();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case ACTIVATE_DOZE_MODE_1_32:
            DisableSwitchPress();
            ActivateDozeMode(CLK_RATIO_1_32_IN_DOZE_MODE);
            SendButtonPressInstruction(EEPROM_OP_DOZE_MODE_INS_TXT_1_32,toPerformText);
            EnableSwitchPress();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case EEPROM_OPERATION_DOZE_MODE_1_32:
             DisableSwitchPress();
            MemoryOperation(DOZEMODE_EEPROM_ADDRESS, eepromOperationStartedText);
            SendButtonPressInstruction(DOZEMODE_INS_TXT_TO_EXIT_1_32,toExitText);
            EnableSwitchPress();
             appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case WAKE_DOZE_MODE_1_32:
            DisableSwitchPress();
            DisableDozeMode();
            SendStringWakeup();
            SendButtonPressInstruction( IDLEMODE_INS_TXT_TO_ENTER,toEnterText);
            EnableSwitchPress();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case ACTIVATE_IDLE_MODE:
            DisableSwitchPress();
            ActivateIdleMode();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case WAKE_IDLE_MODE:
            DisableSwitchPress();
            DisableIdleMode();
            SendStringWakeup();
            SendButtonPressInstruction(SLEEPMODE_INS_TXT_TO_ENTER,toEnterText);
            EnableSwitchPress();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case ACTIVATE_SLEEP_MODE:
            DisableSwitchPress();
            ActivateSleepMode();
            EnableSwitchPress();
            appTaskPrevState = appTaskCurrState;
            appTaskCurrState = WAIT_FOR_SWITCH_PRESS;
            break;
        case WAKE_SLEEP_MODE:
            DisableSwitchPress();
            SendStringWakeup();
            EnableSwitchPress();
            appTaskPrevState= PRESS_SW_TO_START_EEPROM_OP_IN_ACTIVE_MODE;
            appTaskCurrState = PRESS_SW_TO_START_EEPROM_OP_IN_ACTIVE_MODE;
            break;
        default:
            break;
    }
}
/**
  @Param
   none
  @Returns
   none
  @Description
  Interrupt on Change(IOC) Call back function at run time to detect switch press. 
 **/
void UserInterruptHandler(void) 
{
    //to detect the key press
    buttonState = KEY_PRESSED;
}
