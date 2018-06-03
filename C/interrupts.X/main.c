/*
 * File:   main.c
 * Author: ivan-
 *
 * Created on 9 de marzo de 2018, 12:11 AM
 */
// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 20000000

#include <xc.h>

void interrupt high_priority RSI_int1(){    //Serivicio de interrupcion alta prioridad
    if(INTCON3bits.INT1IF){         //bandera de interrupcion de INT1
        LATBbits.LB5 = 1;           //enciende un led en RB5
        __delay_ms(5000);           //pausa de 5 seg
        LATBbits.LB5 = 0;           //apaga un led en RB5
        INTCON3bits.INT1IF = 0;     //se resetea la bandera
    }
} 
void interrupt low_priority RSI_int2(){ //Serivicio de interrupcion para INT2
    if(INTCON3bits.INT2IF){         //Si la bandera de INT2 es 1 accede 
        LATBbits.LB6 = 1;           //enciende un led en RB6
        __delay_ms(5000);           //hace una pausa de 5 seg
        LATBbits.LB6 = 0;           //apaga un led en LB6
        INTCON3bits.INT2IF = 0;     //resetea la bandera de INT2
    }
} 
void main(void) {
    INTCONbits.GIEH=0;          //Desactiva el sistema global de interrupciones
    TRISBbits.RB1 = 1;          //Pone como entrada RB1 INT1
    TRISBbits.RB2 = 1;          //Pone como entrada RB2 INT2
    TRISBbits.RB5 = 0;          //Pone como salida RB5
    TRISBbits.RB6 = 0;          //Pone como salida RB5
    LATBbits.LB5 = 0;           //Establece 0 en RB5
    LATBbits.LB6 = 0;           //Establece 0 en RB6

    INTCON3bits.INT1IF = 0;     //Pone en cero la bandera de INT1 para que no acceda
    INTCON3bits.INT1IE = 1;     //Habilita la interrupcion en INT1
    INTCON3bits.INT1IP = 1;     //La establece como de alta prioridad
    
    INTCON2bits.INTEDG1 = 1;    //Detecta el flanco de bajada
    
    INTCON3bits.INT2IF = 0;     //Pone en cero la bandera de INT2 para que no acceda
    INTCON3bits.INT2IE = 1;     //Habilita la interrupcion en INT2
    INTCON3bits.INT2IP = 0;     //La establece como de baja prioridad
    
    INTCON2bits.INTEDG2 = 1;    //Detecta el flanco de bajada
    
    RCONbits.IPEN = 1;          //Habilita las prioridades
    
    INTCONbits.GIEL = 1;        //Habilita las prioridades de baja prioridad
    INTCONbits.GIEH = 1;        //Habilita el sistema global de interrupciones
    
    while(1);

    return;
}
