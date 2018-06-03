
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
  CONFIG  PBADEN = OFF          ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = ON              ; Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
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

  ;Enable   C0
  ;RS	    C1
  ;DATA	    LATD<3:0>
  org 0x1000
    i equ 0x10
    var equ 0x20
    var1 equ 0x30
    vart equ 0x40
    aux equ  0x50
    count equ 0x60
inicio
 call ConfigPorts
 call lcd_init
 call vacio
 clrf count
 
iniciot:
clrf vart
movlw 0x0e
movwf PORTB

fila:
btfss PORTB,4
goto rebotes
incf vart
btfss PORTB,5
goto rebotes
incf vart
btfss PORTB,6
goto rebotes
incf vart
btfss PORTB,7
    goto rebotes
incf vart

movlw 0x10
subwf vart,0
btfsc STATUS,Z
goto iniciot
bsf STATUS,C
rlcf PORTB
goto fila

rebotes:
	btfss PORTB,4
	goto rebotes
rebotes1:
	btfss PORTB,5
	goto rebotes1
rebotes2:
	btfss PORTB,6
	goto rebotes2
rebotes3:
	btfss PORTB,7
	goto rebotes3
movf vart,W
;movwf PORTD
movlw 0x00
cpfsgt vart
goto iniciot
incf count
movlw 0x01	
cpfslt	count
goto c2
call vacio
c2
movlw D'2'	
cpfsgt	count
goto c3
call m_lleno
c3
movlw D'3'	
cpfsgt	count
goto iniciot
call completo
goto iniciot

 

lcd_init
    movlw   0x00
    movwf   LATD
    movwf   LATC
    
    movlw   D'15'
    call Delay_ms_by_w
    
    bcf	    LATC,1
    movlw   0x03
    call lcd_send_nibble
    movlw   D'5'
    call Delay_ms_by_w
    movlw   0x03
    call lcd_send_nibble
    movlw   D'5'
    call Delay_ms_by_w
    movlw   0x03
    call lcd_send_nibble
    movlw   D'5'
    call Delay_ms_by_w
    
    bcf	    LATC,1
    movlw   0x02
    call lcd_send_nibble
    movlw   D'5'
    call Delay_ms_by_w
    
    bcf	    LATC,1
    movlw   0x28
    call lcd_send_byte
    movlw   D'5'
    call Delay_ms_by_w
    bcf	    LATC,1
    movlw   0x0C
    call lcd_send_byte
    movlw   D'5'
    call Delay_ms_by_w
    bcf	    LATC,1
    movlw   0x01
    call lcd_send_byte
    movlw   D'5'
    call Delay_ms_by_w
    bcf	    LATC,1
    movlw   0x06
    call lcd_send_byte
    movlw   D'5'
    call Delay_ms_by_w
    return
lcd_send_nibble
    bsf	    LATC,0
    NOP
    andlw   0x0F
    movwf   LATD
    NOP
    bcf	    LATC,0
    movlw   D'40'
    call Delay_by_w
    return 
lcd_send_byte
    movwf   aux
    swapf   aux,0
    call lcd_send_nibble
    movf   aux,W
    call lcd_send_nibble
    return
Delay_by_w
    movwf i
    cicDelay
    NOP
    decfsz i
    goto cicDelay
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
Delay_ms_by_w
    movwf i
    cdelay
    call DelayOneMs
    decfsz i
    goto cdelay
    return
ConfigPorts
    movlw	0x0F	;Configura las entradas mutiplexadas con el	
    movwf	ADCON1	;convertidor A/D como entradas digitales.
    movlw	0x07	;Configura las entradas multiplexadas con 
    movwf	CMCON	;los comparadores como entradas digitales.
    movlw	0xFF	;Configura todas las líneas del 
    movwf	TRISA	;puerto A como Entrada
    movlw	0xf0
    movwf	TRISB	;puerto B como ENTRADA
    movlw	0xF0	;Configura todas las líneas del
    movwf	TRISD	;puerto d como salida
    movlw	0xF0
    movwf	TRISC
    bcf INTCON2,RBPU
    return

 vacio
    movlw 0x01
    bcf	LATC,1	;DATA
    call lcd_send_byte
    movlw 0x05
    call Delay_ms_by_w
    movlw 'P'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 'i'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 's'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 'o'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw '1'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    return
 m_lleno
    movlw 0x01
    bcf	LATC,1	;DATA
    call lcd_send_byte
    movlw 0x05
    call Delay_ms_by_w
    movlw 'p'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 'i'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 's'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 'o'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw '2'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    return 
completo
    movlw 0x01
    bcf	LATC,1	;DATA
    call lcd_send_byte
    movlw 0x05
    call Delay_ms_by_w
    movlw 'p'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 'i'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 's'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw 'o'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw ' '
    bsf	LATC,1	;DATA
    call lcd_send_byte
    movlw '3'
    bsf	LATC,1	;DATA
    call lcd_send_byte
    return
end
  
  