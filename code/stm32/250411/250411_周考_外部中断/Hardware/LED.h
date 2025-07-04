#ifndef _LED_H
#define _LED_H

void LED_Init(void);
void LED1_On(void);
void LED1_Off(void);
void LED1_Turn(void);

void LED2_On(void);
void LED2_Off(void);
void LED2_Turn(void);

void LED3_On(void);
void LED3_Off(void);
void LED3_Turn(void);

void LED_Positive_ms(uint16_t ms);
void LED_negative_ms(uint16_t ms);

#endif
