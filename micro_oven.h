/* 
 * File:   micro_oven.h
 * Author: praveen
 *
 * Created on 8 January, 2026, 12:37 PM
 */

#ifndef MICRO_OVEN_H
#define	MICRO_OVEN_H

#define FAN                   RC2
#define FAN_DDR               TRISC2

#define ON                    1
#define OFF                   0

#define POWER_SCREEN          0X10
#define MENU_SCREEN           0X20
#define MICRO_MODE            0X30
#define GRILL_MODE            0X40
#define CONVECTION_MODE       0X50
#define START_MODE            0X60
#define DISPLAY_TIME          0x70

#define PAUSE                 0x80
#define STOP                  0x90


#define RESET_FLAG            0x31
#define RESET_NOTHING         0xff

void display_power_screen(void );
void display_modes(void);
void set_time(unsigned char key, unsigned char reset_flag );
void set_temp( unsigned char key , unsigned char reset_flag);
void display_time(void);
void heat_food(void);


#endif	/* MICRO_OVEN_H */

