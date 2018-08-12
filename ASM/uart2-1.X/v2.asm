; PIC18F4550 Configuration Bit Settings

; Assembly source line config statements

#include "p18f4550.inc"

; CONFIG1L
  CONFIG  PLLDIV = 1            ; PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
  CONFIG  CPUDIV = OSC1_PLL2    ; System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
  CONFIG  USBDIV = 1            ; USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

; CONFIG1H
  CONFIG  FOSC = HS             ; Oscillator Selection bits (HS oscillator (HS))
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

; CONFIG2L
  CONFIG  PWRT = OFF            ; Power-up Timer Enable bit (PWRT disabled)
  CONFIG  BOR = OFF             ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
  CONFIG  BORV = 3              ; Brown-out Reset Voltage bits (Minimum setting 2.05V)
  CONFIG  VREGEN = OFF          ; USB Voltage Regulator Enable bit (USB voltage regulator disabled)

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3H
  CONFIG  CCP2MX = ON           ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
  CONFIG  PBADEN = OFF           ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = OFF              ; Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
  CONFIG  ICPRT = OFF           ; Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
  CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
  CONFIG  CP0 = OFF             ; Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
  CONFIG  CP1 = OFF             ; Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
  CONFIG  CP2 = OFF             ; Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
  CONFIG  CP3 = OFF             ; Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
  CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    START                   ; go to beginning of program

var	equ	0x10
var1	equ	0x20
num0	equ	0x30
num1	equ	0x40
num2	equ	0x50
num3	equ	0x60
num4	equ	0x70
num5	equ	0x80
num6	equ	0x90
num7	equ	0x100
aux	equ	0x110

org 0x1000
START
   movlw   0x00
   movwf   TBLPTRU
   movlw   0x12
   movwf   TBLPTRH
   movlw    0x80
   movwf    TRISC
   clrf	    TRISD
   movlw    0x00
   movwf    TRISB
   movlw    0xFE
   movwf    LATB
   movlw    0x20
   movwf    TXSTA
   movlw    0x90
   movwf    RCSTA
   movlw    0x00
   movwf    BAUDCON
   movlw    0xC8
   movwf    SPBRG
   ciclo:
    movf    RCREG,w
    ;movwf   LATD
    movwf   aux
    call setter
    call Display
    goto ciclo
setter
    clrf    num0
    clrf    num1
    clrf    num2
    clrf    num3
    clrf    num4
    clrf    num5
    clrf    num6
    clrf    num7
    movlw   0x01

    btfsc   aux,0
    movwf   num0
    btfsc   aux,1
    movwf   num1
    btfsc   aux,2
    movwf   num2
    btfsc   aux,3
    movwf   num3
    btfsc   aux,4
    movwf   num4
    btfsc   aux,5
    movwf   num5
    btfsc   aux,6
    movwf   num6
    btfsc   aux,7
    movwf   num7

    return

Display
    ;***************
    movlw 0xFE
    movwf LATB
    movf    num0,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xFD
    movwf LATB
    movf    num1,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xFB
    movwf LATB
    movf    num2,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xF7
    movwf LATB
    movf    num3,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xEF
    movwf LATB
    movf    num4,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xDF
    movwf LATB
    movf    num5,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xBF
    movwf LATB
    movf    num6,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0x7F
    movwf LATB
    movf    num7,W
    call ptr_w_latd
    call DelayOneMs
    return

ptr_w_latd
    movwf   TBLPTRL
    tblrd   *
    movf    TABLAT,W
    movwf   LATD
    return
DelayOneMs
    movlw 0x07
    movwf var
    ret1
    movlw D'236'
    movwf var1
    ret2
    decfsz var1
    goto ret2
    decfsz var
    goto ret1
    return

    ;Tabla de verdad
    org 0x1200
    DB 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0xBF,0xFF
end
