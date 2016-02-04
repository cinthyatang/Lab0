/*
 * Cinthya Tang
 * ECE 372
 * Lab0 Part 3
 */


#include <xc.h>
#include "switch.h"
#define INPUT 1
#define ENABLED 1 

void initSW1(){
    TRISDbits.TRISD6 = INPUT;           // Configure switch as input
    CNCONDbits.ON = 1;                  // Enable overall interrupt
    CNENDbits.CNIED6 = ENABLED;         // Enable pin CN
    CNPUDbits.CNPUD6 = ENABLED;         // Enable pull-up resistor
    IFS1bits.CNDIF = 0;                 // Put down the flag
    IPC8bits.CNIP = 7;                  // Configure interrupt priority
    IEC1bits.CNDIE = ENABLED;           // Enable interrupt for D pins
}