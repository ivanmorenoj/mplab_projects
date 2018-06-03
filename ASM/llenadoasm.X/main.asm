
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
  CONFIG  PBADEN = ON           ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
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


;Manejo de tablas
  i	equ 0x10
  num0	equ 0x20
  num1	equ 0x30
  num2	equ 0x40
  num3	equ 0x50
  var	equ 0x60
  var1	equ 0x70
  var2	equ 0x80
	
org 0x1000
main:
    call    config_ports
    movlw   0x00
    movwf   TBLPTRU
    movlw   0x12
    movwf   TBLPTRH
    movlw   0x00
    movwf   LATC
    movwf   num0
    movwf   num1
    movwf   num2
    movwf   num3
    
ciclo:
    movlw D'10'
    movwf i
    cic0Delay
    call Display
    decfsz i
    goto cic0Delay
    
    btfsc PORTB,0
    goto n2
    goto llenar
    n2
    btfsc PORTB,1
    goto parar
llenar
    movlw 0x01
    movwf LATE
    movwf num0
    goto ciclo
parar
    movlw 0x00
    movwf LATE
    movlw 0x02
    movwf num0
    goto ciclo
Display
    movlw   0x80
    movwf   LATC
    
    movf    num0,W
    movwf   TBLPTRL
    tblrd   *
    movf    TABLAT,W
    iorlw   0x80
    movwf   LATD
    
    call DelayDisp
    
    movlw   0x40
    movwf   LATC
    
    movf    num1,W
    movwf   TBLPTRL
    tblrd   *
    movf    TABLAT,W
    iorlw   0x80
    movwf   LATD
    
    call DelayDisp  
    
    movlw   0x01
    movwf   LATC
    bsf	    LATC,5
    
    movf    num2,W
    movwf   TBLPTRL
    tblrd   *
    movf    TABLAT,W
    iorlw   0x80
    movwf   LATD
    
    call DelayDisp
    
    movlw   0x02
    movwf   LATC
    bsf	    LATC,4
    
    movf    num3,W
    movwf   TBLPTRL
    tblrd   *
    movf    TABLAT,W
    iorlw   0x80
    movwf   LATD
    
    call DelayDisp
    return
DelayDisp
    movlw D'5'
    movwf var2
    cycDelay
    call DelayOneMs
    decfsz var2
    goto cycDelay
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

config_ports
    movlw 0x0f
    movwf ADCON1
    movlw 0x07
    movwf CMCON
    movlw 0xFF
    movwf TRISA
    movlw 0XFF
    movwf TRISB
    movlw 0x3C
    movwf TRISC
    movlw 0x00
    movwf TRISD
    movlw 0xFC
    movwf TRISE
    return 
    ;Tabla de verdad
    org 0x1200
    DB 0x40,0x79,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x18,0x08,0x03,0x46,0x21,0x06,0x0E
    
end