/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "game.h"

//agregado por el grupo

#define CODIGO_BASE       0X400000

#define MAPA_BASE_FISICA  0x500000
#define MAPA_BASE_VIRTUAL 0x800000



//  Struct de directorio de tablas de paginas 
struct str_page_directory_entry {
  unsigned char p_0:1;
  unsigned char rw_1:1;
  unsigned char us_2:1;
  unsigned char pwt_3:1;
  unsigned char pcd_4:1;
  unsigned char a_5:1;
  unsigned char ignore_6:1;
  unsigned char ps_7:1;
  unsigned char g_8:1;
  unsigned char disponible_11_9:3;
  unsigned int baseDir_31_12:20;
} __attribute__((__packed__, aligned (4)));
//  Struct tablas de paginas 
struct str_page_table_entry {
  unsigned char p_0:1;
  unsigned char rw_1:1;
  unsigned char us_2:1;
  unsigned char pwt_3:1;
  unsigned char pcd_4:1;
  unsigned char a_5:1;
  unsigned char dirtyBit_6:1;
  unsigned char pat_7:1;
  unsigned char g_8:1;
  unsigned char disponible_11_9:3;
  unsigned int baseDir_31_12:20;
} __attribute__((__packed__, aligned (4)));


typedef struct str_page_directory_entry page_directory_entry;
typedef struct str_page_table_entry page_table_entry;


extern page_directory_entry *pde;


void mmu_inicializar_dir_kernel();

void mmu_inicializar();



#endif	/* !__MMU_H__ */
/*
//  Struct de directorio de tablas de paginas 
struct str_page_directory_entry {
    unsigned char  p_0:1;
    unsigned char  r_w_1:1;
    unsigned char   u_s_2:1;
    unsigned char   pwt_3:1;
    unsigned char   pcd_4:1;
    unsigned char   a_5:1;
    unsigned char   ignored_6:1;
    unsigned char   ps_7:1;
    unsigned char   g_8:1;
  unsigned char   disponible_11_9:3;
    unsigned int   baseDir_31_12:20;
} __attribute__((__packed__, aligned (4))) ;

//  Struct tablas de paginas 
struct str_page_table_entry {
    unsigned char  p_0:1;
    unsigned char  r_w_1:1;
    unsigned char   u_s_2:1;
    unsigned char   pwt_3:1;
    unsigned char   pcd_4:1;
    unsigned char   a_5:1;
    unsigned char   dirtyBit_6:1;
    unsigned char   pat_7:1;
    unsigned char   g_8:1;
    unsigned char   disponible_11_9:3;
    unsigned int   baseDir_31_12:20;
} __attribute__((__packed__, aligned (4)));

typedef struct str_page_directory_entry page_directory_entry;
typedef struct str_page_table_entry page_table_entry;

extern page_directory_entry* pde; //pde[]
//extern page_directory_entry PDE_DESC;

extern page_table_entry* pte; //pte[]
//extern page_table_entry PTE_DESC;

*/








