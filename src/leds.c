#include "leds.h"

#define LEDS_ALL_OFF    0x0000
#define LEDS_ALL_ON     0xFFFF
#define LED_OFFSET      1
#define LSB             1

static uint16_t * direccion;
static LedError_t registrarError;

uint16_t LedToMask(uint8_t led) {
    if (led > 16)
    {
        registrarError();   
        return -1;
    }
    return (LSB << (led - LED_OFFSET));
}

void Leds_Create(uint16_t *puerto, LedError_t handler) {
    registrarError = handler;
    direccion = puerto;
    *direccion = LEDS_ALL_OFF;
}

void Led_On(uint8_t led) {
    *direccion |= LedToMask(led);
}

void Led_Off(uint8_t led) {
    *direccion &= ~LedToMask(led);
}

void Leds_On(void) {
    *direccion = LEDS_ALL_ON;
}

void Leds_Off(void){
    *direccion = LEDS_ALL_OFF;
}

char Led_Status(uint8_t led){
    return((*direccion & LedToMask(led)) && LedToMask(led));
}
