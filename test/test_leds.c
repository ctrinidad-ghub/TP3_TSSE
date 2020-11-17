#include "unity.h"
#include "leds.h"

uint16_t ledsVirtuales;
char error_inf = 0;

void registrarError(void) {
    error_inf = 1;
}

void setUp(void) {
    Leds_Create(&ledsVirtuales, registrarError);
}

void tearDown(void) {
}

// Despues de la inicializacion todos los LEDSs deben quedar apagados
void test_LedsOffAfterCreate(void) {
    uint16_t ledsVirtuales = 0xFFFF;
    Leds_Create(&ledsVirtuales, registrarError);
    TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}

// Se puede prender un LED individual
void test_PrenderLedIndividual(void) {
    Led_On(10);
    TEST_ASSERT_EQUAL_HEX16(1 << 9, ledsVirtuales);
}

// Se puede apagar un LED individual
void test_ApagarLedIndividual(void) {
    Led_On(10);
    Led_Off(10);
    TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}

// Se pueden prender y apagar multiples LEDs
void test_PrenderApagarMultiplesLeds(void) {
    Led_On(3);
    Led_On(4);
    Led_Off(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 3, ledsVirtuales);
}

// Se pueden prender todos los LEDs de una vez
void test_PrenderTodosLosLeds(void) {
    Leds_On();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}

// Se pueden apagar todos los LEDs de una vez
void test_ApagarTodosLosLeds(void) {
    Leds_On();
    Leds_Off();
    TEST_ASSERT_EQUAL_HEX16(0x0, ledsVirtuales);
}

// Se puede consultar el estado de un LED prendido
void test_ConsultarEstadoLedPrendido(void) {
    char led_status;

    Led_On(6);
    Led_On(7);
    led_status = Led_Status(6);

    TEST_ASSERT_TRUE(led_status);
}

// Se puede consultar el estado de un LED apagado
void test_ConsultarEstadoLedApagado(void) {
    char led_status;

    Led_On(7);
    led_status = Led_Status(6);

    TEST_ASSERT_FALSE(led_status);
}

// Revisar limites de los parametros - Led 1 - Prendido
void test_LimiteLed1Prender(void) {
    Led_On(1);
    TEST_ASSERT_EQUAL_HEX16(1, ledsVirtuales);
}

// Revisar limites de los parametros - Led 1 - Apagado
void test_LimiteLed1Apagar(void) {
    Led_On(1);
    Led_Off(1);
    TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}

// Revisar limites de los parametros - Led 16 - Prendido
void test_LimiteLed16Prender(void) {
    Led_On(16);
    TEST_ASSERT_EQUAL_HEX16(1 << 15, ledsVirtuales);
}

// Revisar limites de los parametros - Led 16 - Apagado
void test_LimiteLed16Apagar(void) {
    Led_On(16);
    Led_Off(16);
    TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}

// Revisar parametros fuero de lo limites
void test_PrenderLedInvalido(void) {
    Led_On(17);
    TEST_ASSERT(error_inf);
}