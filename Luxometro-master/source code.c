#include <xc.h>
#include <pwm.h>
#include <stdio.h>
#include <stdlib.h>

//BITS DE CONFIGURACION.....
#pragma config PLLDIV = 5, CPUDIV = OSC1_PLL2, USBDIV = 2
#pragma config FOSC = HSPLL_HS, FCMEN = OFF, IESO = OFF
#pragma config PWRT = OFF, BOR = OFF, VREGEN = OFF
#pragma config WDT = OFF, WDTPS = 32768
#pragma config MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF
#pragma config STVREN = ON, LVP = OFF, ICPRT = OFF, XINST = OFF
#define _XTAL_FREQ 48000000


void main() {

TRISBbits.TRISB0 = 1; //RB0 es entrada.
TRISBbits.TRISB1 = 1; //RB1 es entrada.
TRISCbits.RC1 = 0;//salida a cpp2 a los motores generado por el setdcpwm();
TRISCbits.RC2 = 0;//salida a cpp1 a los motores generado por el setdcpwm();

 
OpenTimer2(T2_PS_1_16);//prescaler a utilizar 16
OpenPWM1(187); //PWM1 trabaja a 4KHz
OpenPWM2(187); //PWM2 trabaja a 4KHz


do {

    while(PORTBbits.RB0 == 1 && PORTBbits.RB1 == 1){
    SetDCPWM1(550);
    SetDCPWM2(740);
    }
    while(PORTBbits.RB0 == 1 && PORTBbits.RB1 == 0){
    SetDCPWM1(550);
    SetDCPWM2(0);
    }
    while(PORTBbits.RB0 == 0 && PORTBbits.RB1 == 1){
    SetDCPWM1(0);
    SetDCPWM2(740);
    }
    } while(1);
}
