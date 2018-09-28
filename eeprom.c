/*
 * File:   eeprom.c
 * Author: TIMOTHY
 *
 * Created on May 14, 2017, 10:50 AM
 */

//LED MULTIPLEXING.
#include <xc.h>
#include <string.h>
#include <stdbool.h>

// Configuration bits
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)2
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
//#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF 

#define _XTAL_FREQ 16000000      // Tell the compiler that we are useing 16MHz

int count1=0 , count11=0 , count2 =0, count3 =0, count4 =0 ,countindex = 0;

/*
void increment1()
{
    if (count1>9)
           {
               count1 = 0;
               count2++;
               if(count2>9)
               {
                   count2 =  0;
                   count3++;
                    if(count3>9)
                    {
                        count3 =  0;
                        count4++;
                           if(count4>9)
                           {
                           count4 =  0;

                    }
               }
                       
           }
       }
}
*/
void increment()
{
    count1 =  count11%10;
    count2 = (count11/10)%10;
    count3=  (count11/100)%10;
    count4 =  count11 / 1000;
}

char getdisp(int count)
{
    switch(count)
    {
          case 0: return(0b00111111);
          case 1: return(0b00000110);
          case 2: return(0b01011011);
          case 3: return(0b01001111);
          case 4: return(0b01100110);
          case 5: return(0b01101101);
          case 6: return(0b01111100);
          case 7: return(0b00000111);
          case 8: return(0b01111111);
          case 9: return(0b01100111);
          default: return(0b00111111);
    }
   
}

void BCDDISP()
{
     
    //  PORTB=0;
       PORTC=0B11110111;
       PORTB = getdisp(count1);
       __delay_us(1000);
       
       
        // PORTB=0;
       PORTC=0B11111011;
       PORTB = getdisp(count2);
       __delay_us(1000);
    
       
    //  PORTB=0;
       PORTC=0B11111101;
       PORTB = getdisp(count3);
       __delay_us(1000);
       
       
     //  PORTB=0;
       PORTC=0B11111110;
       PORTB = getdisp(count4);
       __delay_us(1000);
       
       
}


int main(void)
{
    TRISA=0B00000000;
    TRISB=0B00000000;
    TRISC=0B00000000;
    TRISD=0B00001111;
    TRISE=0B00000000;
    PORTA=0;
    PORTB=0;
    PORTC=0;
    PORTD=0;
    PORTE=0;
    ADCON1=7;
    ADCON0=0;
    count11 = eeprom_read (0xE9);    // Reading the value from address 0xE5
    
   
    
   while(1) 
    {
          
    eeprom_write(0xE9, count11);     // Writing value count11 to EEPROM address 0xE5     
    
       if(RD0)
       {
           __delay_ms(500);
           while(RD0);
           __delay_ms(500);
           count11++;
           
       }
       
       if(RD1)
       {
           __delay_ms(500);
           while(RD1);
           __delay_ms(500);
             if(count11 == 0)
                count11 = 1;
           count11 = count11 * 2;
       }
       
       if(RD2)
       {
           __delay_ms(500);
           while(RD2);
           __delay_ms(500);
             if(count11 == 0)
                 count11 = 1;
           count11 = count11 * 10;
       }
       
       if(RD3)
       {
           __delay_ms(500);
           while(RD3);
           __delay_ms(500);
             if(count11 == 0)
                 count11 = 1;
           count11 = count11 / 10;
       }

       if(count11 >= 9999)
               count11 = 0;
       
      increment();
      BCDDISP();
   }
       
       
}


 