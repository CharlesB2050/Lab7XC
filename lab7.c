/*
 * File:   lab7.c
 * Author: Carlos
 *
 * Created on 6 de abril de 2022, 03:03 PM
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



#include <xc.h>
#include <stdio.h>
#include <stdint.h>

#define _XTAL_FREQ 2000000
#define BOTON1 PORTBbits.RB0
#define BOTON2 PORTBbits.RB1
void __interrupt() isr (void){
    
    if(INTCONbits.RBIF){        // Fue interrupci n del PORTB?
        if (!BOTON1){
            PORTA++;
            INTCONbits.RBIF = 0;    // Limpiamos bandera de interrupci n?
        }
        if (!BOTON2){
            PORTA--;
            INTCONbits.RBIF = 0;    // Limpiamos bandera de interrupci n?
        }
    }
    if (INTCONbits.T0IF){
            PORTC++;
            INTCONbits.T0IF = 0;
            TMR0 = 59;
        
    }
    return;
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    TRISA = 0;
    TRISC = 0; 
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    
    PORTA = 0;
    PORTC = 0; 
    
    OPTION_REGbits.nRBPU = 0;
    
   //Timer0 Registers Prescaler= 256 - TMR0 Preset = 59 - Freq = 9.91 Hz - Period = 0.100864 seconds
    OPTION_REGbits.T0CS = 0;  // bit 5  TMR0 Clock Source Select bit...0 = Internal Clock (CLKO) 1 = Transition on T0CKI pin
    OPTION_REGbits.T0SE = 0;  // bit 4 TMR0 Source Edge Select bit 0 = low/high 1 = high/low
    OPTION_REGbits.PSA = 0;   // bit 3  Prescaler Assignment bit...0 = Prescaler is assigned to the Timer0
    OPTION_REGbits.PS2 = 1;   // bits 2-0  PS2:PS0: Prescaler Rate Select bits
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    TMR0 = 59;             // preset for timer register
    
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1; 
    
    INTCONbits.GIE = 1;         
    INTCONbits.RBIE = 1; 
    INTCONbits.T0IE = 1;
    IOCBbits.IOCB0 = 1; 
    IOCBbits.IOCB1 = 1;
    
    OSCCONbits.SCS = 1;
    OSCCONbits.IRCF = 0b101;
    TMR0 = 59; 
    INTCONbits.RBIF = 0;
    INTCONbits.T0IF = 0;
   
    return;
}
void main(void) {
    setup();
    while(1){}
    
    return;
}
