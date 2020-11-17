#include  <stdint.h>

typedef void (*LedError_t) (void);

void Leds_Create(uint16_t *puerto, LedError_t handler);

void Led_On(uint8_t led);

void Led_Off(uint8_t led);

void Leds_On(void);

void Leds_Off(void);

char Led_Status(uint8_t led);