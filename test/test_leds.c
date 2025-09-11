/**
* iniciar el driver y revisar que todos los leds esten apagados
* prender un led y verificar que no cambia el resto
* prender un led y apagarlo cualquiera
* prender mas de un led, apagar uno y verificar que el resto siguen sin cambio
* tratar de prender leds fuera de rango y comprobar que se genera un error
* tratar de apagar leds fuera de rango y comprobar que se genera un error
* prender todos los leds
* apagar todos los leds
* consultar el estado de un led encendido y comprobar que es correcto
* consultar el estado de un led apagado y comprobar que es correcto
* prender un led mas de una vez y verificar que sigue prendido
* apagar un led mas de una vez y verificar que sigue apagado
* prender algunos leds, despues prender todos y comprobar que todos los leds quedan prendidos
* apagar algunos leds, despues apagar todos y copmprobar que todos los leds quedan apagados
**/

#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

static uint16_t puerto_virtual;

void setUp(void) {
    LedsInitDriver(&puerto_virtual);
}

void tearDown(void) {

}

// iniciar el driver y revisar que todos los leds esten apagados
void test_al_iniciar_todos_los_leds_estan_apagados(void) {
    uint16_t puerto_virtual = 0xFFFF;   // como tiene el mismo nombre que la variable global puerto_virtual, la funció la usa sobre la global

    LedsInitDriver(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// prender un led y verificar que no cambia el resto
void test_prender_un_led_y_verificar_que_no_cambia_el_resto(void) {
    LedsTurnOn(3);
    // TEST_ASSERT_BIT_HIGH(puerto_virtual, 2);         // Solo verifica si el led 2 esta encendido
    TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_virtual);    // Verifica si SOLO el led 2 esta encendido
}

// prender un led y apagarlo cualquiera
void test_prender_un_led_cualquiera_y_apagarlo(void) {
    LedsTurnOn(5);
    LedsTurnOff(5);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// prender mas de un led, apagar uno y verificar que el resto siguen sin cambio
void test_prender_mas_de_un_led_apagar_uno_y_verificar_que_el_resto_sigue_sin_cambios(void) {
    LedsTurnOn(3);
    LedsTurnOn(5);
    LedsTurnOff(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, puerto_virtual);
}

// tratar de prender leds fuera de rango y comprobar que se genera un error
void test_tratar_de_prender_leds_fuera_de_rango_y_comprobar_que_se_genera_un_error(void) {
    //RegistrarMensaje_Expect(ALERTA, "LedsTurnOn", 0, "El led no es valido");
    //RegistrarMensaje_IgnoreArg_linea();

    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOn(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
    
    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOn(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

    // Verifico limite inferior y superior de turnon y turnoff
    // Se recomeindan pruebas cortas -> una para prender y otra para apagar
}

// tratar de apagar leds fuera de rango y comprobar que se genera un error
void test_tratar_de_apagar_leds_fuera_de_rango_y_comprobar_que_se_genera_un_error(void) {
    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOff(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
    
    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOff(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// prender todos los leds
void test_prender_todos_los_leds(void){
    LedsTurnOffAll();
    LedsTurnOnAll();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);
}

// apagar todos los leds
void test_apagar_todos_los_leds(void){
    LedsTurnOnAll();
    LedsTurnOffAll();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// consultar el estado de un led encendido y comprobar que es correcto
void test_consultar_estado_de_led_encendido_y_comprobar_que_es_correcto(void){
    LedsTurnOff(7);                                                 // Apago el led con función que ya esta probada
    LedsTurnOn(7);                                                  // Prendo un LED conocido
    TEST_ASSERT_TRUE(LedsIsOn(7));                                  // Consulto su estado que debe estar encendido (true)
    TEST_ASSERT_BIT_HIGH(7-1, puerto_virtual);
}

// consultar el estado de un led apagado y comprobar que es correcto
void test_consultar_estado_de_led_apagado_y_comprobar_que_es_correcto(void){
    LedsTurnOn(5);                                                  // Enciendo el led con función que ya esta probada
    LedsTurnOff(5);                                                 // Apago el led con la función que quiero testear
    TEST_ASSERT_TRUE(LedsIsOff(5));                                 // Consulto su estado que debe estar apagado (true)
    TEST_ASSERT_BIT_LOW(5-1, puerto_virtual);
}

// prender un led mas de una vez y verificar que sigue prendido
void test_prender_un_led_mas_de_una_vez_y_verificar_que_sigue_prendido(void){
    LedsTurnOff(4);                         // inicia apagado
    LedsTurnOn(4);                          // prendo primera vez
    LedsTurnOn(4);                          // prendo segunda vez
    TEST_ASSERT_TRUE(LedsIsOn(4));          // debe seguir prendido
    TEST_ASSERT_BIT_HIGH(4-1, puerto_virtual);
}

// apagar un led mas de una vez y verificar que sigue apagado
void test_apagar_un_led_mas_de_una_vez_y_verificar_que_sigue_apagado(void){
    LedsTurnOn(6);                           // inicia encendido
    LedsTurnOff(6);                          // apago primera vez
    LedsTurnOff(6);                          // apago segunda vez
    TEST_ASSERT_TRUE(LedsIsOff(6));          // debe seguir apagado
    TEST_ASSERT_BIT_LOW(6-1, puerto_virtual);
}

// prender algunos leds, despues prender todos y comprobar que todos los leds quedan prendidos
void test_prender_algunos_luego_prender_todos_y_quedan_todos_prendidos(void) {
    LedsTurnOffAll();

    LedsTurnOn(2);
    LedsTurnOn(7);
    LedsTurnOn(12);

    LedsTurnOnAll();

    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);
}

// apagar algunos leds, despues apagar todos y copmprobar que todos los leds quedan apagados
void test_apagar_algunos_luego_apagar_todos_y_quedan_todos_apagados(void) {
    LedsTurnOnAll();

    LedsTurnOff(3);
    LedsTurnOff(9);
    LedsTurnOff(15);

    LedsTurnOffAll();

    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}