
#ifndef APPLICATION_H
#define	APPLICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

   
 /**
 * **********************************************************
 *  Macros definitions
 * **********************************************************
 **/   
#define LED_ON()                                 LED_SetLow()
#define LED_OFF()                                LED_SetHigh()
  
/**
 @Param
  none
 @Returns
  none
 @Description
 ApplicationTask().
 **/
void ApplicationTask(void);

/**
  @Param
   none
  @Returns
   none
  @Description
  Interrupt on Change(IOC) Call back function at run time to detect switch press. 
 **/
void UserInterruptHandler(void);

 
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

