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

;----------------------------------PIC18's--------------------------------------
;
 org    0x0008
    goto ISR_HIGH
 ;GOTO    HIGH_ISR
 ;org    0x0018
 ;    GOTO    LOW_ISR
;
;ISRH      CODE                     ; let linker place high ISR routine
;HIGH_ISR
    ;goto ISR_HIGH
    ;RETFIE  FAST
;
; ISRL      CODE                     ; let linker place low ISR routine
; LOW_ISR
;       <Search the device datasheet for 'context' and copy interrupt
;       context saving code here>
;     RETFIE
;-------------------------------------------------------------------------------

MAIN_PROG CODE                      ; let linker place main program

num0	equ  0x10
num1	equ  0x20
num2	equ  0x30
num3	equ  0x40
num4	equ  0x50
num5	equ  0x60
numc	equ  0x70
var	equ  0x80
var1	equ  0x90
f_tmr0	equ  0x100
f1_tmr0	equ  0x110
org 0x1000
START
    movlw   0x00
    movwf   TBLPTRU
    movlw   0x12
    movwf   TBLPTRH
    movlw   .10
    movwf   numc
    movlw   .0
    movwf   num0
    movlw   .0  
    movwf   num1
    movlw   .0
    movwf   num2
    movlw   .0  
    movwf   num3
    movlw   .0
    movwf   num4
    movlw   .0  
    movwf   num5
    call config_ports
    call config_interrupts
    loop
    call Display
    ;call Increment_clock
    goto loop
	
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
    movf    numc,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xF7
    movwf LATB
    movf    num2,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xEF
    movwf LATB
    movf    num3,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xDF
    movwf LATB
    movf    numc,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0xBF
    movwf LATB
    movf    num4,W
    call ptr_w_latd
    call DelayOneMs
    ;***************
    movlw 0x7F
    movwf LATB
    movf    num5,W
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
Increment_clock
    incf  num0
    movlw   .9
    cpfsgt  num0
    return
    
    clrf    num0
    incf  num1
    movlw   .5
    cpfsgt  num1
    return
    
    clrf    num1
    incf  num2
    movlw   .9
    cpfsgt  num2
    return
    
    clrf    num2
    incf  num3
    movlw   .5
    cpfsgt  num3
    return
    ;**************
    clrf    num3
    incf  num4
    movlw   .1
    cpfsgt  num5
    goto cmpnum4
    movlw   .3
    cpfsgt  num4
    return
    clrf    num4
    clrf    num5
    
    cmpnum4
    movlw   .9
    cpfsgt  num4
    return
    clrf    num4
    incf    num5
    return
    
config_interrupts
	bcf INTCON,GIEH
	movlw	b'10001000'
	movwf	T0CON
	bcf  INTCON,TMR0IF  ;Pone en cero la bandera de TMR0 para que no acceda
	bsf  INTCON,TMR0IE  ;Habilita la interrupcion en TMR0
	bsf  INTCON2,TMR0IP ;Alta prioridad
	movlw b'00001011' 
	movwf T1CON
	bcf PIR1,TMR1IF	    ;Pone en cero la bandera de TMR0 para que no acceda
	bsf PIE1,TMR1IE	    ;Habilita la interrupcion en TMR0
	bsf IPR1,TMR1IP	    ;Alta prioridad
	bsf RCON,IPEN	    ;Habilita las prioridades
	bcf INTCON,GIEL	    ;desabilita las interrupciones de baja prioridad
	bsf INTCON,GIEH	    ;Habilita el sistema global de interrupciones
return
config_ports
    movlw 0x0f
    movwf ADCON1
    movlw 0x07
    movwf CMCON
    movlw 0xFF
    movwf TRISA
    movlw 0X00
    movwf TRISB
    movlw 0xFF
    movwf TRISC
    movlw 0x00
    movwf TRISD
    return 
    ;Tabla de verdad
    org 0x1200
    DB 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0xBF,0xFF
org 0x100
ISR_HIGH
    btfsc   PIR1,TMR1IF
    call TMR1_ISR
    btfsc INTCON,TMR0IF
    call    TMR0_ISR
RETFIE  FAST
TMR0_ISR
    bcf INTCON,TMR0IF
    movlw   0x78
    movwf   TMR0L
    movlw   0xEC
    movwf   TMR0H
    incf f_tmr0
    tstfsz  f_tmr0
    return
    movlw   .10
    cpfseq  numc
    goto num10
    movlw   .11
    movwf   numc
    return
    num10
    movlw   .10
    movwf   numc
    return
TMR1_ISR
    bsf	TMR1H,7
    bcf	PIR1,TMR1IF
    call Increment_clock
return
END