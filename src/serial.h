
#ifndef __SERIAL_H
#define __SERIAL_H


#include "stm32f10x.h"


extern
void init_serial()
;

extern
void send_char( char ch)
;

extern
void send_text( char const *text)
;

extern
char hex_digit( u8 digit)
;

extern
void send_u32_as_hex( u32 value)
;


#endif

