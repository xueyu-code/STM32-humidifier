#ifndef __OLED_H
#define __OLED_H



void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowChinese(uint8_t Line, uint8_t Column, char Char);//ÏÔÊ¾Ò»¸öºº×Ö
void OLED_ShowSentence(uint8_t Line, uint8_t Column, char *Char);//ÏÔÊ¾×Ö·û´®£¨°üº¬ºº×Ö£©
void my_oled_display1(void);
void my_oled_disply_yuzhi(void);
void my_oled_display_mode(void);
void my_oled_Alarm(void);
#endif
