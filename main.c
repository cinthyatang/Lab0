/*
 Cinthya Tang
 ECE 372
 Lab0 Part 2
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "switch.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define UP 1
#define DOWN 0

typedef enum stateTypeEnum{ 
            LED1, LED2, LED3, debouncePress, debounceRelease, wait
} stateType;

volatile stateType state = LED1;
volatile stateType nextState = LED2;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.
    initSW1();
    initLEDs();
    initTimer1();
    initTimer2();
    turnOnLED(1);
    
    while(1){
        switch (state) {
        case LED1:
            turnOnLED(1);
            break;
        case LED2:
            turnOnLED(2);
            break;	
        case LED3:
            turnOnLED(3);	
            break;
        case debouncePress:
            delayMs(10);
            state = wait;
            break;
        case wait:
            break;
        case debounceRelease:
            delayMs(10);
            state = nextState;
            break;
        default:
            break;
        }
    }
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed
//CN ISR
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
	IFS1bits.CNDIF = 0;
	unsigned Button = PORTDbits.RD6;
	if (Button == DOWN) {
		TMR1 = 0;
        T1CONbits.ON = 1;
        //FORWARD
		switch(state) {
            case LED1:
                nextState = LED2;
                break;
            case LED2:
                nextState = LED3;
                break;
            case LED3:
                nextState = LED1;
                break;
		}
        state = debouncePress;
	}

	else if (Button == UP) {
        state = debounceRelease;
	}
}

//Timer ISR
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() {
	IFS0bits.T1IF = 0;
	T1CONbits.ON = 0;
	//BACKWARDS
	switch (nextState) {
        case LED1:
            nextState = LED2;
            break;
        case LED2:
            nextState = LED3;
            break;
        case LED3:
            nextState = LED1;
            break;
	}
}
