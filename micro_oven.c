#include <xc.h>
#include "clcd.h"
#include "micro_oven.h"
#include "matrix_keypad.h"


unsigned char min, sec;
unsigned int temp;
extern  unsigned char screen_flag;
extern  unsigned char reset_flag;
unsigned char pre_heat ;

void display_power_screen(void )
{
    for(unsigned char i = 0; i< 16; i++)
    {
        clcd_putch(BAR, LINE1(i)); // 0 1 2 3 .... 15
        __delay_ms(100);
    }
    clcd_print("Powering ON", LINE2(3));
    clcd_print("Microwave Oven", LINE3(2));
    for(unsigned char i = 0; i< 16; i++)
    {
        clcd_putch(BAR, LINE4(i)); // 0 1 2 3 .... 15
        __delay_ms(100);
    }
    __delay_ms(1000);
}

 void display_modes(void)
 {
      clcd_print("1. Micro", LINE1(3));
      clcd_print("2. Grill", LINE2(3));
      clcd_print("3. Convection", LINE3(3));
      clcd_print("4. Start", LINE4(3));
     
 }
 void set_time(unsigned char key, unsigned char reset_flag )
 {
     static unsigned char blink_pos = 0; //0 sec field, 1 min field
     static unsigned char key_count = 0;
     static unsigned char delay, display_blank;
     if(reset_flag == RESET_FLAG  )
     {
         sec = 0;
         min = 0;
         key = 0;
         key_count = 0;
         blink_pos = 0;
     }
     
     //print the format
     clcd_print("SET TIME (MM:SS)", LINE1(0));
     clcd_print("TIME:", LINE2(0));
     clcd_putch(':', LINE2(7));
     
     clcd_print("*:CLEAR #:ENTER", LINE4(0));
     
     // read the time from the keypad , set time
     // key = * # 0 1 2 3 4 5 6 7 8 9  and all  released
     if(key != '*' && key != '#' && key != ALL_RELEASED ) // 0 1 2 3 4 5 6 7 8 9 
     {
         key_count++; // <= 2 sec, >2 min
         if(key_count <= 3) // 2 times we are seconds
         {
             sec = sec * 10 + key;
             blink_pos = 0; // update blink position  to sec
         }
         else  if(key_count <= 5)// more than 2 times we are reading min
         {
          min = min * 10 + key;
          blink_pos = 1;
         }
         
     }
     //* clear time
     else if (key == '*')
     {
        if(blink_pos == 0)  
        {
            sec = 0;
            key_count = 0;       
        }
        else if(blink_pos ==1)
        {
            min = 0;
            key_count = 2;
        }
    }
     //# start cooking with time set display the time
     else if(key == '#')
     {
         clear_screen();
         // turn ON FAN RC2 = 1
         FAN = ON;
         // turn O TIME
         TMR2ON = 1;
         // change the screen to display time
         screen_flag = DISPLAY_TIME;
     }
      if(delay++ == 10)
     {
      delay = 0;
      display_blank = !display_blank; // 1   , 0  , 1  , 0  ,  1
     }
       
     // display min and sec , blink sec field editable field
     if(display_blank)
     {
         if(blink_pos == 0)
         {
             clcd_putch(' ', LINE2(8));
             clcd_putch(' ', LINE2(9));
         }
         else
         {
             clcd_putch(' ', LINE2(5));
             clcd_putch(' ', LINE2(6));
         }
     }
     else
     {
         clcd_putch( sec / 10 + '0', LINE2(8));  // 30  30/10  3 +'0' -> '3' , 30 % 10 -> 0 + -> '0'
         clcd_putch( sec % 10 + '0', LINE2(9));
         
         clcd_putch( min / 10 + '0', LINE2(5));
         clcd_putch( min % 10 + '0', LINE2(6));
         
         
     }    
 }
 
 void set_temp( unsigned char key , unsigned char reset_flag)
 {
     
     static unsigned char key_count = 0;
     static unsigned char delay, display_blank ;
     if(reset_flag == RESET_FLAG  )
     {
         temp = 0;
         key = 0;
         key_count = 0;
        
     }
     if(delay++ == 5)
     {
      delay = 0;
      display_blank = !display_blank; // 1   , 0  , 1  , 0  ,  1
     }
     
     //print the format
     clcd_print("SET Temp <*c>", LINE1(0));
     clcd_print("TEMP", LINE2(0));
     clcd_print("*:CLEAR #:ENTER", LINE4(0));
     
     // read the temperature
          if(key != '*' && key != '#' && key != ALL_RELEASED ) // 0 1 2 3 4 5 6 7 8 9 
     {
         key_count++; // 
         if(key_count <= 4) // 3 times we are  reading temperature
         {
             temp = temp * 10 + key; // 1 * 10 // 10 * 10 -> 100 + 2 -> 102           
         }
         
     }
     //* clear time
     else if (key == '*')
     {
         temp = 0;
         key_count = 0;
     }
     //# start cooking with time set display the time
     else if(key == '#')
     {
         clear_screen();
         pre_heat = 60;
         // turn on the timer
         TMR2ON = 1;
        // display pre heating along with time left
         clcd_print("pre-Heating", LINE1(3));
         clcd_print("Time Rem:", LINE3(0));
         clcd_putch('s', LINE3(12));
         while(pre_heat)
         {
             clcd_putch( pre_heat / 100 + '0', LINE3(9)); // 300 -> 300/100 30 10 +'0' -> '3' , 30 % 10 -> 0 +'0' -> '0'
        clcd_putch( (pre_heat / 10) % 10 + '0', LINE3(10));
        clcd_putch((pre_heat % 10) + '0', LINE3(11));
         }
         TMR2ON = 0;
         clear_screen();
         screen_flag = MICRO_MODE;
         reset_flag = RESET_FLAG;
         
         // implement pre heating screen 
     }
        
     if(display_blank) // blink the temperature
     {
       clcd_putch(' ', LINE2(7));
       clcd_putch(' ', LINE2(8));
       clcd_putch(' ', LINE2(9));  
     }
     else
     {
                                                 
        clcd_putch( temp / 100 + '0', LINE2(7)); // 300 -> 300/100 30 10 +'0' -> '3' , 30 % 10 -> 0 +'0' -> '0'
        clcd_putch( (temp / 10) % 10 + '0', LINE2(8));
        clcd_putch((temp % 10) + '0', LINE2(9));

     }     
 }    
     
 
void display_time(void)
{
  clcd_print("TIME = ", LINE1(1));
  clcd_putch( min / 10 + '0', LINE1(9));
  clcd_putch( min % 10 + '0', LINE1(10));   
  clcd_putch(':', LINE1(11));
  clcd_putch( sec / 10 + '0', LINE1(12));  // 30  30/10  3 +'0' -> '3' , 30 % 10 -> 0 + -> '0'
  clcd_putch( sec % 10 + '0', LINE1(13));
  clcd_print("4.START/RESUME", LINE2(2));
  clcd_print("5.PAUSE", LINE3(2));
  clcd_print("6.STOP", LINE4(2));
         
  if(min == 0 && sec == 0)
  {
      clear_screen();
      TMR2ON =0;
      FAN= 0;
      clcd_print("TIME UP!!!", LINE2(4));
      clcd_print("Enjoy your meal", LINE3(0));
      
      
      __delay_ms(2000);
      clear_screen();
      screen_flag = MENU_SCREEN;
  }
}
void heat_food(void)
{
    sec = 30;
    min = 0;
    TMR2ON = 1;
    FAN = 1;
    screen_flag = DISPLAY_TIME;
}
 