
#include "stm32f10x.h"


// Note: CPU_CLK / BAUD_RATE must fit within 16-bits
#define  CPU_CLK  72000000
#define  BAUD_RATE  115200

// Values for the 2-bit pairs for MODE found in the CRL/CRH register:
#define  GPIO_MODE_INPUT            0x0
#define  GPIO_MODE_OUTPUT_MAX_2MHZ  0x2

#define  GPIO_CNF_AF_PUSH_PULL      0x2
#define  GPIO_CNF_PULL_UP_OR_DOWN   0x2 // Set the bit corresponding to the port in the DR to 1 to choose UP rather than DOWN

#define  PIN9_MODE_POS   4 // bit position 4 is bit0 of the MODE9 setting
#define  PIN9_CNF_POS    6
#define  PIN10_MODE_POS  8
#define  PIN10_CNF_POS  10


void init_serial()
{
  // Enable USART1:
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  // Set the baud rate:
  USART1->BRR = CPU_CLK / BAUD_RATE;
  // Enable the USART for both transmission and reception:
  USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;

  // I guess these might mean enable pull up for RX and set TX as hard-driven output
  // AFOUT_10 probably mean b10, i.e. function 2, which is AF output, push-pull
  //gpio_usart1_tx_mode(GPIO_AFOUT_10);
  //gpio_usart1_rx_mode(GPIO_HIGHZ_INPUT);

  // TX is pin 9 on port A (PA 9)
  // RX is pin 10 on port A (PA 10)
  // Mask out any current values for the MODE and CNF values for pins 9 and 10
  GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9 | GPIO_CRH_MODE10 | GPIO_CRH_CNF10)) |
              (GPIO_MODE_OUTPUT_MAX_2MHZ << PIN9_MODE_POS) |
              (GPIO_CNF_AF_PUSH_PULL << PIN9_CNF_POS) |
              (GPIO_MODE_INPUT << PIN10_MODE_POS) |
              (GPIO_CNF_PULL_UP_OR_DOWN << PIN10_CNF_POS)
              ;
  // Enable the pull-up for PA 10 (RX):
  GPIOA->BSRR = GPIO_BSRR_BS10;
}


void send_char( char ch)
{
  // Wait until DR is ready for the next frame:
  while ( 0 == (USART1->SR & USART_SR_TXE) );
  //while (!(USART1->SR & USART_SR_TXE));
  // Send the next frame:
  USART1->DR = ch;
}


void send_text( char const *text)
{
  char  ch;

  while ( (ch = *text) != '\0')
  {
    send_char( ch);
    text += 1;
  }
}


char hex_digit( u8 digit)
{
  return (digit <= 9) ? ('0' + digit) : ('a' + (digit - 10));
}


void send_u32_as_hex( u32 value)
{
  u8  p;
  s8  os;
  for ( os = 8*sizeof(u32) - 4, p = 0;  0 <= os;  os -= 4, ++ p )
  {
    send_char( hex_digit( value >> os & 0xf) );
  }
}

