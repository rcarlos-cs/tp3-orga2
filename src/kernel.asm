; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

extern GDT_DESC ; | 2 bytes del tamaño de la tabla | 4 bytes de dirrecion de la tabla |
extern screen_inicializar ; void screen_inicializar(); pinta la pantalla de gris
extern idt_inicializar ; void idt_inicializar(); 
extern IDT_DESC
global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de defines
;; -------------------------------------------------------------------------- ;;
%define _BASE_PILA   0x27000


;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0


    ; Habilitar A20
        call habilitar_A20

    ; Cargar la GDT

        lgdt [GDT_DESC]; gdtr = | 2 bytes del tamaño de la tabla GDT | 4 bytes de dirrecion de la tabla GDT| 

    ; Setear el bit PE del registro CR0
        ; /** ACTIVO EL MODO PROTEGIDO: poniendo el bit PE en 1,  en el registro cr0**/    
        mov eax, cr0
        or eax, 1
        mov cr0, eax
        ; /** FIN CODIGO ACTIVACION MODO PROTEGIGO **/ 
    ; Saltar a modo protegido
        jmp 0x40:protected_mode ; Donde mp := modo protegido
                                ; 0x40 = #segmentos_nulos * 8 (bytes) = 8 * 8 = 64 decimal = 0x40
BITS 32
protected_mode:        

    ; Establecer selectores de segmentos
        xor eax, eax ;
        mov ax, 1010000b ; { index: 10 | gdt/ldt: 0 | rpl: 00} osea 1010 (index 10 decimal), 0 (gdt), rpl = 00 
        mov ds, ax  
        mov es, ax
        mov gs, ax
        mov ss, ax
        mov ax, 1100000b ; { index: 12 | gdt/ldt: 0 | rpl: 00} osea 1100 (index 12 decimal), 0 (gdt), rpl = 00 
        mov fs, ax      ; fs selector de segmento de video
    ; Establecer la base de la pila
        
        mov ebp, _BASE_PILA ; _BASE_PILA = 0X27000
        mov esp,ebp 
    
    ; Imprimir mensaje de bienvenida
        ; /**IMPRIMO QUE PASE A MODO PROTEGIDO **/
        imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0

    ; Inicializar el juego

    ; Inicializar pantalla

        call screen_inicializar ; void screen_inicializar();

    ; Inicializar el manejador de memoria

    ; Inicializar el directorio de paginas

    ; Cargar directorio de paginas

    ; Habilitar paginacion

    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT

        call idt_inicializar ; void idt_inicializar();

    ; Cargar IDT
        lidt [IDT_DESC]

        ;mov ax, 8
        ;mov bl, 0;
        ;div bl
    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
