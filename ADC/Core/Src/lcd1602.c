#include "lcd1602.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "string.h"

static void LCD_SendCommand(uint8_t cmd);
static void LCD_SendData(uint8_t data);
static void LCD_SendNibble(uint8_t nibble);
static void LCD_Delay(uint32_t delay);

// Khởi tạo LCD1602
void LCD_Init(void) {
    HAL_Delay(50); // Đợi LCD khởi động
    LCD_SendNibble(0x03);
    LCD_Delay(5);
    LCD_SendNibble(0x03);
    LCD_Delay(1);
    LCD_SendNibble(0x03);
    LCD_SendNibble(0x02); // Chuyển sang chế độ 4-bit

    // Thiết lập chế độ hoạt động
    LCD_SendCommand(0x28); // Giao tiếp 4-bit, 2 dòng, 5x8 điểm
    LCD_SendCommand(0x08); // Tắt màn hình
    LCD_SendCommand(0x01); // Xóa màn hình
    LCD_SendCommand(0x06); // Tăng địa chỉ DDRAM sau mỗi lần ghi, không dịch màn hình
    LCD_SendCommand(0x0C); // Bật màn hình, tắt con trỏ
}

// Xóa toàn bộ màn hình
void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

// Đặt con trỏ tại vị trí hàng `row` và cột `col`
void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? 0x80 : 0xC0; // DDRAM của hàng 0 bắt đầu tại 0x80, hàng 1 tại 0xC0
    address += col;
    LCD_SendCommand(address);
}

// Hiển thị chuỗi ký tự lên LCD
void LCD_Print(char* string) {
    while (*string) {
        LCD_SendData((uint8_t)(*string));
        string++;
    }
}

// Gửi lệnh điều khiển đến LCD
static void LCD_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_RS_Port, LCD_RS_Pin, GPIO_PIN_RESET); // RS = 0
    LCD_SendNibble(cmd >> 4); // Gửi 4 bit cao
    LCD_SendNibble(cmd & 0x0F); // Gửi 4 bit thấp
}

// Gửi dữ liệu đến LCD
static void LCD_SendData(uint8_t data) {
    HAL_GPIO_WritePin(LCD_RS_Port, LCD_RS_Pin, GPIO_PIN_SET); // RS = 1
    LCD_SendNibble(data >> 4); // Gửi 4 bit cao
    LCD_SendNibble(data & 0x0F); // Gửi 4 bit thấp
}

// Gửi 4 bit dữ liệu/command đến LCD
static void LCD_SendNibble(uint8_t nibble) {
    HAL_GPIO_WritePin(LCD_D4_Port, LCD_D4_Pin, (nibble >> 0) & 0x01);
    HAL_GPIO_WritePin(LCD_D5_Port, LCD_D5_Pin, (nibble >> 1) & 0x01);
    HAL_GPIO_WritePin(LCD_D6_Port, LCD_D6_Pin, (nibble >> 2) & 0x01);
    HAL_GPIO_WritePin(LCD_D7_Port, LCD_D7_Pin, (nibble >> 3) & 0x01);

    HAL_GPIO_WritePin(LCD_E_Port, LCD_E_Pin, GPIO_PIN_SET); // E = 1
    LCD_Delay(1);
    HAL_GPIO_WritePin(LCD_E_Port, LCD_E_Pin, GPIO_PIN_RESET); // E = 0
    LCD_Delay(1);
}

// Hàm trễ
static void LCD_Delay(uint32_t delay) {
    HAL_Delay(delay);
}
