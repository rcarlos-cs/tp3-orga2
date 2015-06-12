/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"




/* Definicion de la GDT */
/* -------------------------------------------------------------------------- */

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /** ejercicio 1)                                 **/
    /**         a) Segmento de CODIGO nivel    0  (kernel)**/
    [GDT_IDX_CODE_DESCRIPTOR_0] = (gdt_entry) {
        (unsigned short)    0xf3ff,         /* limit[0:15]  */ // limite =(#bloques_4kb) -1 = (500MB/4KB)-1 =128000-1=127999= 0x1F3FF 
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0a,           /* type         */ // type = EXECUTE/READ = Oxa = 10
        (unsigned char)     0x01,           /* s            */ // Descriptor type ( 0 = system; 1 = code or data)
        (unsigned char)     0x00,           /* dpl          */ //descriptor de nivel de privilegio : dpl = 0 = nivel de privilegio 0 (KERNEL)
        (unsigned char)     0x01,           /* p            */ // Present = p = if p ==1 then  SEGMENTO ESTA EN MEMO RAM else ESTA EN MEMO VIRTUAL  
        (unsigned char)     0x01,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ // avl queda libre para el programador de sistema operativo 
        (unsigned char)     0x00,           /* l            */  // l = 0
        (unsigned char)     0x01,           /* db           */ // Default/big = 1
        (unsigned char)     0x01,           /* g            */ // granularidad = 1
        (unsigned char)     0x00,           /* base[31:24]  */

    },
    /**      Segmento de CODIGO nivel    3 (usuario) **/
    [GDT_IDX_CODE_DESCRIPTOR_3] = (gdt_entry) {
        (unsigned short)    0xf3ff,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0a,           /* type         */ // type = EXECUTE/READ = Oxa = 10
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ // dpl = 3 = nivel de privilegio CODIGO 3 (USUARIO)
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x01,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */

    },

    /**     Segmento de DATO de nivel 0  (KERNEL)            **/
    [GDT_IDX_DATA_DESCRIPTOR_0] = (gdt_entry) {
        (unsigned short)    0xf3ff,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */ // type = 2 = data and read/write
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */ // dpl = 0 = nivel de privilegio CODIGO 0 (KERNEL)
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x01,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */

    },
    /**     Segmento de DATO de nivel 3  (usuario)         **/
    [GDT_IDX_DATA_DESCRIPTOR_3] = (gdt_entry) {
        (unsigned short)    0xf3ff,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */ 
        (unsigned char)     0x02,           /* type         */ // type = 2 = data and read/write
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ // dpl = 3 = nivel de privilegio 3 (USUARIO)
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x01,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */

    },
    /**   Segmento de datos de nivel 0, SEGMENTO DE VIDEO **/
    [GDT_IDX_DATA_DESCRIPTOR_VIDEO_0] = (gdt_entry) {
        (unsigned short)    0x7fff,         /* limit[0:15]  */
        (unsigned short)    0x8000,         /* base[0:15]   */
        (unsigned char)     0x0b,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */ // type = 2 = data and read/write
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */ // dpl = 0 = nivel de privilegio CODIGO 0 (KERNEL)
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */ // porque estoy en modo protegido
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */

    }
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};
