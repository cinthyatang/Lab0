/* 
 * File:   led.c
 * Author: Cinthya Tang
 *
 * Created on February 2, 2016, 3:15 PM
 */

#include <xc.h>
#include "led.h"
#define OUTPUT 0
#define ON 1
#define OFF 0

void initLEDs(){
    //TODO: Initialize LEDs
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
    
}

void turnOnLED(int led){
    //TODO: You may choose to write this function
    // as a matter of convenience
    if(led == 1){
        LATDbits.LATD0 = ON;
        LATDbits.LATD1 = OFF;
        LATDbits.LATD2 = OFF;
    }
    else if(led == 2){
        LATDbits.LATD0 = OFF;
        LATDbits.LATD1 = ON;
        LATDbits.LATD2 = OFF;        
    }
    else{
        LATDbits.LATD0 = OFF;
        LATDbits.LATD1 = OFF;
        LATDbits.LATD2 = ON;
    }
    
    
}