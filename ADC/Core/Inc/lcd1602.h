#ifndef LCD1602_H
#define LCD1602_H

#include "stm32f1xx_hal.h" // Thay đổi phù hợp với MCU bạn đang sử dụng

// Định nghĩa các chân LCD (thay đổi tùy theo cách kết nối của bạn)
#define LCD_RS_Pin GPIO_PIN_0 // RS
#define LCD_RS_Port GPIOB
#define LCD_E_Pin GPIO_PIN_1  // Enable
#define LCD_E_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_2 // Data 4
#define LCD_D4_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_3 // Data 5
#define LCD_D5_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_4 // Data 6
#define LCD_D6_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_5 // Data 7
#define LCD_D7_Port GPIOB

// Các hàm điều khiển LCD
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char* string);

#endif // LCD1602_H
