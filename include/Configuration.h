#ifndef CATBOXBOX_INCLUDE_CONFIGURATION_H_
#define CATBOXBOX_INCLUDE_CONFIGURATION_H_


// Uncomment to enable debug output via Serial console.
#define DEBUG_MODE


///// Catbox.cpp /////
// Input
#define PIN_BTN_RESET_TIMER     12
#define PIN_DIP_EXTRA_SWITCH    7
// Output
#define PIN_BUZZER              10
// PWM Output
#define PIN_LED_GRN             11
#define PIN_LED_YLW             9
#define PIN_LED_RED             6
// 74HC165 I/O
#define PIN_74HC165_DATA        2 // IC-PIN-9, "SO" Serial-Output
#define PIN_74HC165_CLK         4 // IC-PIN-2, Clock
#define PIN_74HC165_LATCH       3 // IC-PIN-1, Shift / Load
// TODO : Define interrupt pins to be used...
//  Nano's interrupts: 2, 3


///// Buzzer.h /////
#define BUZZER_FREQ_HZ_MIN      -500
#define BUZZER_FREQ_HZ_MAX      2300


#endif //CATBOXBOX_INCLUDE_CONFIGURATION_H_
