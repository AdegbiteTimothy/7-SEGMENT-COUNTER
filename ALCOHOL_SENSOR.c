/*
 * File:   ALCOHOL_SENSOR.c
 * Author: TIMOTHY
 *
 * Created on June 29, 2018, 7:20 PM
 * PIC16F877A
 */
#include <xc.h>
#define _XTAL_FREQ 20000000      // Tell the compiler that we are using 20MHz
#include <LCDLIBRARY1.h>
//CONFIG1
#pragma config FOSC =   HS   // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE =  OFF   // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON   // Power-up Timer Enable bit (PWRT disabled)
//#pragma config MCLR  = OFF   // RELAY/MCLR/VPP Pin Function Select bit (RELAY/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON   // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP =  OFF    // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD =  OFF    // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP =   OFF 
//#pragma config IESO = OFF 
//#pragma config FCMEN = OFF 
//#pragma config DEBUG = OFF
//CONFIG2
//#pragma config BOR4V = BOR40V
//#pragma config WRT = OFF
unsigned int ALCOHOLLEVEL ;
unsigned int THRESHOLD ;
//double ALCOHOLLEVEL1 = 45.6 ;
//unsigned int ALCOHOLLEVEL2  = 65123;
//char check[] = "56ECTRONICS" ;
/*
const unsigned short Custom_Char5x8[] = {
  0xe,0x1b,0x11,0x11,0x11,0x11,0x1F,0x1F, // Code for CGRAM memory space 1
  0xe,0X1b,0x11,0x1f,0x1f,0x1f,0x1f,0x1f, // Code for CGRAM memory space 2
  0xe,0X1b,0x11,0x11,0x11,0x1f,0x1f,0x1f, // Code for CGRAM memory space 3
  0xe,0X1b,0x11,0x11,0x1f,0x1f,0x1f,0x1f, // Code for CGRAM memory space 4
  0xe,0X1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f, // Code for CGRAM memory space 5
  0x00,0X01,0x02,0x03,0x04,0x05,0x06,0x07, // Code for CGRAM memory space 6
  0b00000,0b00000,0b01010,0b10101,0b10001,0b01110,0b00100,0b00000, // Code for CGRAM memory space 7
  0b11111,0b11111,0b10101,0b11011,0b11011,0b11111,0b10001,0b11111  // Code for CGRAM memory space 8
};
*/
int scanvalue;
int numberpressed1 = 0;
int numberpressed2 = 0;
int numberpressed3 = 0;
int numberpressed4 = 0;
int numberpressed5 = 0;
int passwordcorrect;
int passwordcorrect1;
int ENTER;

int resetnumberpressed1 = 1;
int resetnumberpressed2 = 2;
int resetnumberpressed3 = 3;
int resetnumberpressed4 = 4;
int resetnumberpressed5=  5;
int resetpasswordcorrect = 0;
int resetALCOHOLLEVEL1 = 0;
int resetALCOHOLLEVEL2 = 0;
char i;
char j; 




void DISPLAYPARAMETERS()
{
 CURSOR(FIRSTROW,0);
 LCDWRITE("CODE") ;
 NUMDISP(resetALCOHOLLEVEL1);
 NUMDISP(resetnumberpressed1);
 NUMDISP(resetnumberpressed5);
 NUMDISP(resetnumberpressed3);
 NUMDISP(resetnumberpressed4);
 NUMDISP(resetnumberpressed2);
 NUMDISP(resetALCOHOLLEVEL2);
return ;
}

int scan()
            {
           scanvalue  =  100 ;
           while(scanvalue == 100)
           {
          //////////////////////////////////////////////////////
         ADCON0bits.CHS = 0;
         __delay_ms(10);
         ADCON0bits.GO_DONE = 1;
         while(ADCON0bits.GO_DONE);
         ALCOHOLLEVEL = (ADRESL + (ADRESH * 256)) / 10.23 ;
         CURSOR(FIRSTROW,0),NUMDISP(ALCOHOLLEVEL) ,LCDWRITE("% - ") , LCDWRITE("HIGH        "); //LCDWRITE(" ") ; 
        //////////////////////////////////////////////////////////////////////////////////////////////// 
           while(RC3)
           {
               CURSOR(FIRSTROW,0);
               LCDWRITE("CODE") ;
               NUMDISP(resetALCOHOLLEVEL1);
               NUMDISP(resetnumberpressed1);
               NUMDISP(resetnumberpressed5);
               NUMDISP(resetnumberpressed3);
               NUMDISP(resetnumberpressed4);
               NUMDISP(resetnumberpressed2);
               NUMDISP(resetALCOHOLLEVEL2);
           }
          /////////////////////////////////////////////////////////////////////////////////////////////////////
             PORTB = 0B11101111;
             __delay_ms(100);
            if(PORTBbits.RB0 == 0)
            {
               __delay_ms(100);
               while(PORTBbits.RB0 == 0);
               __delay_ms(100);
               scanvalue = 7;
               return scanvalue;
            }
            
            else if(PORTBbits.RB1 == 0)
            {
               __delay_ms(100);
               while(PORTBbits.RB1 == 0);
               __delay_ms(100);
               scanvalue = 4;
               return scanvalue;
            }
            
            else if(PORTBbits.RB2 == 0)
            {
               __delay_ms(100);
               while(PORTBbits.RB2 == 0);
               __delay_ms(100);
               scanvalue = 1;
               return scanvalue;
            }
            
            else if(PORTBbits.RB3 == 0)
            {
               __delay_ms(100);
               while(PORTBbits.RB3 == 0);
               __delay_ms(100);
               scanvalue = 'A';
               return scanvalue;
            }
               
            
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /
            
                          PORTB = 0B11011111;
                        __delay_ms(100);
                        if(PORTBbits.RB0 == 0)
                        {
                          __delay_ms(100);
                           while(PORTBbits.RB0 == 0);
                           __delay_ms(100);
                           scanvalue = 8;
                           return scanvalue;
                        }

                        if(PORTBbits.RB1 == 0)
                        {
                           __delay_ms(100);
                           while(PORTBbits.RB1 == 0);
                           __delay_ms(100);
                           scanvalue = 5;
                           return scanvalue;
                        }

                        if(PORTBbits.RB2 == 0)
                        {
                           __delay_ms(100);
                           while(PORTBbits.RB2 == 0);
                           __delay_ms(100);
                           scanvalue = 2;
                           return scanvalue;
                        }

                         if(PORTBbits.RB3 == 0)
                        {
                           __delay_ms(100);
                           while(PORTBbits.RB3 == 0);
                           __delay_ms(100);
                           scanvalue = 0;
                           return scanvalue;
                        }
            
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////  
                                PORTB = 0B10111111;
                                __delay_ms(100);
                                if(PORTBbits.RB0 == 0)
                                {
                                   __delay_ms(100);
                                   while(PORTBbits.RB0 == 0);
                                   __delay_ms(100);
                                   scanvalue = 9;
                                   return scanvalue;
                                }

                                if(PORTBbits.RB1 == 0)
                                {
                                   __delay_ms(100);
                                   while(PORTBbits.RB1 == 0);
                                   __delay_ms(100);
                                   scanvalue = 6;
                                   return scanvalue;
                                }

                                if(PORTBbits.RB2 == 0)
                                {
                                   __delay_ms(100);
                                   while(PORTBbits.RB2 == 0);
                                   __delay_ms(100);
                                   scanvalue = 3;
                                   return scanvalue;
                                }

                                 if(PORTBbits.RB3 == 0)
                                {
                                   __delay_ms(100);
                                   while(PORTBbits.RB3 == 0);
                                   __delay_ms(100);
                                   scanvalue = 'B';
                                   return scanvalue;
                                }
                                
   //////////////////////////////////////////////////////////////////////////////////////////////////////                             
                                PORTB = 0B01111111;
                                __delay_ms(100);
                                if(PORTBbits.RB0 == 0)
                                {
                                   __delay_ms(100);
                                   while(PORTBbits.RB0 == 0);
                                   __delay_ms(100);
                                   scanvalue = 'C';
                                   return scanvalue;
                                }

                                if(PORTBbits.RB1 == 0)
                                {
                                   __delay_ms(100);
                                   while(PORTBbits.RB1 == 0);
                                   __delay_ms(100);
                                   scanvalue = 'D';
                                   return scanvalue;
                                }

                                if(PORTBbits.RB2 == 0)
                                {
                                   __delay_ms(100);
                                   while(PORTBbits.RB2 == 0);
                                   __delay_ms(100);
                                   scanvalue = 'E';
                                   return scanvalue;
                                }

                                 if(PORTBbits.RB3 == 0)
                                {
                                   __delay_ms(100);
                                   while(PORTBbits.RB3 == 0);
                                   __delay_ms(100);
                                   scanvalue = 'F';
                                   return scanvalue;
                                }
            }
            
         }
   

void passwordroutine()
{
    numberpressed1 =numberpressed2=numberpressed3=numberpressed4=numberpressed5 = passwordcorrect = ENTER = 0;
    CURSOR(SECONDROW,0);
     LCDWRITE("          ");
            
     numberpressed1 = scan();
     CURSOR(SECONDROW,0);
     LCDWRITE("*");
     //NUMDISP(numberpressed1);
     
     numberpressed2 = scan();
     CURSOR(SECONDROW,1);
     LCDWRITE("*");
     //NUMDISP(numberpressed2);
     
    
     numberpressed3 = scan();
     CURSOR(SECONDROW,2);
     LCDWRITE("*");
     //NUMDISP(numberpressed3);
     
    
     numberpressed4 = scan();
     CURSOR(SECONDROW,3);
     LCDWRITE("*");
     //NUMDISP(numberpressed4);
     
    
     numberpressed5 = scan();
     CURSOR(SECONDROW,4);
     LCDWRITE("*");
     //NUMDISP(numberpressed5);
     
     ENTER = scan();
     CURSOR(SECONDROW,5);
     LCDWRITE("*");
     //NUMDISP(ENTER);
     
     
     if(ENTER == 65 )
     {
          if(numberpressed1 == resetnumberpressed1)
            {
                 if(numberpressed2 == resetnumberpressed2)
                 {
                     if(numberpressed3 == resetnumberpressed3)
                     {
                          if(numberpressed4 == resetnumberpressed4)
                          {
                             if(numberpressed5 ==resetnumberpressed5) 
                             {
                                 passwordcorrect = 1;
                             }
                                 
                          }
                         
                     }
                 }
                
            }
            else
            {
                passwordcorrect = 0;
            }
    }
     
     return ;
}

void PRESETALCOHOLLEVEL()
{
    int reset;
    if(passwordcorrect == 1)
    {
        CURSOR(SECONDROW,0);
        LCDWRITE("OPTIONS 1,2,3");
        reset = scan() ;
        switch(reset)
        {
            
            case 1 : passwordcorrect1 = 1 ;
                     break ; 
            case 2 :  CURSOR(SECONDROW,0);
                      LCDWRITE("E-THRESHOLD :   ");
                      resetALCOHOLLEVEL1 = scan() ;
                      CURSOR(SECONDROW,13);  ////
                      NUMDISP(resetALCOHOLLEVEL1);
                      resetALCOHOLLEVEL2 = scan() ;
                      CURSOR(SECONDROW,14);   ////
                      NUMDISP(resetALCOHOLLEVEL2);
                      THRESHOLD = ((resetALCOHOLLEVEL1*10) + resetALCOHOLLEVEL2  );
                      __delay_ms(1000);
                      
                      break ;
            case 3 :  CURSOR(SECONDROW,0);
                      LCDWRITE("P-RESET:         ");
                         resetnumberpressed1 = scan();
                         CURSOR(SECONDROW,9);
                      NUMDISP(resetnumberpressed1);
                         resetnumberpressed2 = scan();
                         CURSOR(SECONDROW,10);
                      NUMDISP(resetnumberpressed2);
                         resetnumberpressed3 = scan();
                         CURSOR(SECONDROW,11);
                      NUMDISP(resetnumberpressed3);
                         resetnumberpressed4 = scan();
                         CURSOR(SECONDROW,12);
                      NUMDISP(resetnumberpressed4);
                         resetnumberpressed5 = scan();
                         CURSOR(SECONDROW,13);
                      NUMDISP(resetnumberpressed5);
                      CURSOR(SECONDROW,0);
                      LCDWRITE("R-SUCESSFUL     ");
                      __delay_ms(1000);
                         break ;
            default :   CURSOR(SECONDROW,0);
                        LCDWRITE("W-OPTION") ;
                        __delay_ms(1000);
           // return ;
        }
        passwordcorrect = 0;
    }

    return ;
    
}



int main (void)
{
 resetnumberpressed1 = eeprom_read (0xE9);
 resetnumberpressed2 = eeprom_read (0xEA);
 resetnumberpressed3 = eeprom_read (0xEB);
 resetnumberpressed4 = eeprom_read (0xEC);
 resetnumberpressed5 = eeprom_read (0xED);
 resetALCOHOLLEVEL1 = eeprom_read  (0xEE);
 resetALCOHOLLEVEL2 = eeprom_read  (0xEF);
 THRESHOLD = ((resetALCOHOLLEVEL1*10) + resetALCOHOLLEVEL2  );
TRISA = 0B00000001;    
TRISB = 0B00001111;
TRISC = 0B00001000;
TRISD = 0;
TRISE = 0;
PORTA = 0;    
PORTB = 0;
PORTC = 0;
PORTD = 0;
PORTE = 0;
ADCON1=0B10001110; 
ADCON0=0B11000001; 
 passwordcorrect = 0;
config();
 
////////////////////////////////////////////////////////////////////
/*
  Lcd_Cmd(0x04);   // Set CGRAM Address
  Lcd_Cmd(0x00);   // .. set CGRAM Address
  for (i = 0; i <= 63 ; i++)
  Lcd_Print_Char(Custom_Char5x8[i]);
  Lcd_Cmd(0);      // Return to Home
  Lcd_Cmd(2);      // .. return to Home
 
  */
//CURSOR(FIRSTROW,1) , LCDWRITE("ALCOHOL-LEVEL");
//CURSOR(SECONDROW,3), LCDWRITE("DETECTOR");
//__delay_ms(4000) ; 
//CURSOR(SECONDROW,3),LCDWRITE("          ") ;
//DISPLAYPARAMETERS();
//__delay_ms(4000) ;
CLRDISP();
 do
 { 
     eeprom_write(0xE9, resetnumberpressed1);
     eeprom_write(0xEA, resetnumberpressed2);
     eeprom_write(0xEB, resetnumberpressed3);
     eeprom_write(0xEC, resetnumberpressed4);
     eeprom_write(0xED, resetnumberpressed5);
     eeprom_write(0xEE, resetALCOHOLLEVEL1);
     eeprom_write(0xEF, resetALCOHOLLEVEL2);
   
     if(resetnumberpressed1 >= 100)
     {
        resetnumberpressed1 = 1;
        resetnumberpressed2 = 2;
        resetnumberpressed3 = 3;
        resetnumberpressed4 = 4;
        resetnumberpressed5=  5;
        resetALCOHOLLEVEL1 = 4;
        resetALCOHOLLEVEL2 = 4;
     }
    
     
     while(RC3)
     DISPLAYPARAMETERS();
         
     
   ADCON0bits.CHS = 0;
   __delay_ms(10);
   ADCON0bits.GO_DONE = 1;
   while(ADCON0bits.GO_DONE);
   ALCOHOLLEVEL = (ADRESL + (ADRESH * 256)) / 10.23 ;
   CURSOR(FIRSTROW,0),NUMDISP(ALCOHOLLEVEL) ,LCDWRITE("% - ") ; //LCDWRITE(" ") ; 
   if(ALCOHOLLEVEL > THRESHOLD )
   {
    RC4 = 0 , RC5 = 1  ,passwordcorrect1 = 0, LCDWRITE("HIGH        ");   
      while( passwordcorrect1 != 1)
      {
         passwordroutine();
         PRESETALCOHOLLEVEL() ;
      
         if( passwordcorrect1 == 1)
         {
          CURSOR(SECONDROW,0);
          LCDWRITE("CORRECT        ");
          __delay_ms(1000);
          RC0 = 1 , RC1 = 0 ;
          CLRDISP();
         }
       else
       {
          CURSOR(SECONDROW,0);
          LCDWRITE("WRONG-P        ");
          __delay_ms(1000);
       }
     }
   }
   else
   {
       RC4 = 1 , RC5 =  0 ;
       LCDWRITE("LOW         "); 
      
   }
   
            
    /*
    CURSOR(FIRSTROW,1);
    Lcd_Print_Char(0); // Display Custom Character 0
    Lcd_Print_Char(1); // Display Custom Character 1
    Lcd_Print_Char(2); // Display Custom Character 2
    Lcd_Print_Char(3); // Display Custom Character 3
    Lcd_Print_Char(4); // Display Custom Character 4
    Lcd_Print_Char(5); // Display Custom Character 5
    Lcd_Print_Char(6); // Display Custom Character 6
    Lcd_Print_Char(7); // Display Custom Character 7
    LCDWRITE("ALCOHOL-LEVEL");
    
    //Print predefined special character//
    CURSOR(SECONDROW,1);
    Lcd_Print_Char(0b11100000); //binary value of alpha from data-sheet
    __delay_ms(1000);
     */
  } 
  while(1);
    return;
}
