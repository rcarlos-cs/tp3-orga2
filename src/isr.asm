; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_tick
extern sched_tarea_actual


;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

	;; Definiciones de mensajes de las ecepciones
_excepcion0: db "0  #DE divide error, fault"
_longitud0: equ $ - _excepcion0				

_excepcion1: db "1 #DB RESERVED, fault/trap, for intel use only"
_longitud1: equ $ - _excepcion1				
_excepcion2: db "2 NMI interrup"
_longitud2: equ $ - _excepcion2				
_excepcion3: db "3 #BP Breakpoint, Trap, INT 3 instruction"
_longitud3: equ $ - _excepcion3				
_excepcion4: db "4 #OF Overflow, Trap, INTO instruction"
_longitud4: equ $ - _excepcion4				
_excepcion5: db "5 #BR BOUND Range Exceeded, fault, bound instruction"
_longitud5: equ $ - _excepcion5				
_excepcion6: db "6 #UD Invalid Opcode (Undefined Opcode), fault"
_longitud6: equ $ - _excepcion6				
_excepcion7: db "7 #NM Device Not Available (No Math Coprocessor), fault"
_longitud7: equ $ - _excepcion7				
_excepcion8: db "8 #DF double fault, abort, error code"
_longitud8: equ $ - _excepcion8				
_excepcion9: db "9 Coprocessor Segment Overrun (reserved), fault"
_longitud9: equ $ - _excepcion9				
_excepcion10: db "10 #TS Invalid TSS, Fault, error code"
_longitud10: equ $ - _excepcion10				
_excepcion11: db "11 #NP Segment Not Present, fault, error code"
_longitud11: equ $ - _excepcion11				
_excepcion12: db "12 #SS Stack-Segment Fault, error code"
_longitud12: equ $ - _excepcion12				
_excepcion13: db "13 #GP General Protection, fault. error code"
_longitud13: equ $ - _excepcion13				
_excepcion14: db "14 #PF Page Fault, error code"
_longitud14: equ $ - _excepcion14				
_excepcion15: db "15 Intel Reserved(do not use)"
_longitud15: equ $ - _excepcion15				
_excepcion16: db "16 #MF x87 FPU floating-point or WAIT/FWAIT instruction,fault"
_longitud16: equ $ - _excepcion16				
_excepcion17: db "17 #AC Alignment ckeck, Fault, error code."
_longitud17: equ $ - _excepcion17				
_excepcion18: db "18 #MC Machine check, Abort"
_longitud18: equ $ - _excepcion18				
_excepcion19: db "19 #XM SIMD Floating-Point Exception, fault"
_longitud19: equ $ - _excepcion19				


%macro ISR 1
global _isr%1

_isr%1:
    mov eax, %1
    imprimir_texto_mp _excepcion%1, _longitud%1, 0x7, 3, 3 ;
    jmp $

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;


