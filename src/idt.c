
/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"

#include "tss.h"

idt_entry idt[255] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);

        ...
    }
*/

/*
#define IDT_ENTRY(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x00;                                                                  \
    idt[numero].attr = (unsigned short) 0x0000;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);
*/

/**1000111100000000 = 0x8f00;  
  segsel = {indice | TI | RPL} = selector de segmento = {8 decimal | 0 bit (GDT) | 00 bits (mayor privilegio) }
         = {1000 bits | 0 bists | 00 bits} = 1000000b = 0x40

  attr = atributo = { P | DPL | 0 | D | 111 (bits) | 000 (bits) | 00000 bits} 
                  = { 1 | 00  | 0 | 1 | 111        | 000        | 00000}  
                  = {1000 1111 0000 0000} = 0x8f00       
    Nota: D=1 porque estoy 32bits
**/
#define IDT_ENTRY(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x40;                                                                  \
    idt[numero].attr = (unsigned short) 0x8f00;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);



void idt_inicializar() {
    // Excepciones
  //  IDT_ENTRY(0); // #DE ERROR DE DIVISION (Fault)
    IDT_ENTRY(1); // #DB Reservado para uso de intel (Fault/Trap)
    IDT_ENTRY(2); // - NMI ( interupcion no enmascarable. pin NMi) (interupcion)
    IDT_ENTRY(3); // #BP breakpoint (Trap)
    IDT_ENTRY(4); // #OF Overflow (Trap)
    IDT_ENTRY(5); // #BR BOUND range Exeeded (Fault)
    IDT_ENTRY(6); // #UD Invalid code (Fault)
    IDT_ENTRY(7); // #NM Coprocesador no disponible (Fault)
    IDT_ENTRY(8); // #DF doble fault (Abort)
    IDT_ENTRY(9); // Coprocessor Segment Overrun (reservada) (Fault)
    IDT_ENTRY(10); // #TS TSS invalido (Fault)
    IDT_ENTRY(11); // #NP Segmento no presente (Fault)
    IDT_ENTRY(12); // #SS Falta en el stack segment (Fault)
    IDT_ENTRY(13); // #GP General Protection (fault)
    IDT_ENTRY(14); // #PF Page fault (fault)
    IDT_ENTRY(15); // - Reservado por intel (no usar)
    IDT_ENTRY(16); // #MF X-87 FPU Error de punto flotante (fault)
    IDT_ENTRY(17); // #AC Alignment check (Fault)  
    IDT_ENTRY(18); // #MC machine check (Abort)
    IDT_ENTRY(19); // #XF Exeption SIMD Floating point (fault)
 
    /** Reservado por intel (no usar)
    IDT_ENTRY(20); 
    ...
    IDT_ENTRY(31); 
    **/
    /** A definir por el usuario (interupcion). Interupciones externas o instuccion INTn
    IDT_ENTRY(32);
    ...
    IDT_ENTRY(255);
    **/
}
