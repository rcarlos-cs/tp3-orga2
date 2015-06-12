/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

/* Atributos paginas */
/* -------------------------------------------------------------------------- */
void mmu_inicializar_dir_kernel(){
  // /** Rutina encargada de inicializar el directorio y tablas de kernel **/

  page_directory_entry *pd;
  page_table_entry *pt;

  unsigned int i;
  unsigned int j;
  //  /* Inicializo directorio de paginas*/

  pd = (page_directory_entry *) 0x27000;
  for(i = 0; i < 1024; i++) {
    pd[i].p_0 = 0x0; // Present[0]
    pd[i].rw_1 = 0x1; // Read/Write[1]
    pd[i].us_2 = 0x0; // User/Supervisor[2]
    pd[i].pwt_3 = 0x0; // Page-Level-Write-Through[3]
    pd[i].pcd_4 = 0x0; // Page-Level-cache-disable[4]
    pd[i].a_5 = 0x0; // Accessed[5]
    pd[i].ignore_6 = 0x0; // Ignored[6]
    pd[i].ps_7 = 0x0; // PageSize[7]
    pd[i].g_8 = 0x0; // Global[8]
    pd[i].disponible_11_9 = 0x0; // Disponible[11..9]
    pd[i].baseDir_31_12 = 0x0; // DirBasePagina[31..12]
  }

  //  /*habilito el bit PRESENT P del directorio de paginas  */
  pd[0].p_0 = 0x1;
  pd[1].p_0 = 0x1;
  pd[2].p_0 = 0x1;
  pd[3].p_0 = 0x1;
  //  /* Ingreso la base de de las primeras 4 paginas de tabla */

  pd[0].baseDir_31_12 = 0x28; // kernel 
  pd[1].baseDir_31_12 = 0x29; // area libre
  pd[2].baseDir_31_12 = 0x2a; // area libre
  pd[3].baseDir_31_12 = 0x2b; // area libre
  
  //  Inicializo tabla de paginas de paginas 
  //  usado Identity Maping, las dirreciones 0x00000000 a 0x003FFFFF 
  // IDENTITY MAPING

  for ( i = 0; i < 4; ++i)
  { /* donde i E {tablakerne0,,tablaKernel3} */
    pt = (page_table_entry *) (pd[i].baseDir_31_12 << 12);
    for ( j = 0; j < 1024; ++j)
    {
      pt[j].p_0 = 0x1; //  Present[0]
      pt[j].rw_1 = 0x1; // Read/Write[1]
      pt[j].us_2 = 0x0; // User/Supervisor[2]
      pt[j].pwt_3 = 0x0; // Page-Level-Write-Through[3]
      pt[j].pcd_4 = 0x0; // Page-Level-cache-disable[4]
      pt[j].a_5 = 0x0; // Accessed[5]
      pt[j].dirtyBit_6 = 0x0; // Dirtybit[6]
      pt[j].pat_7 = 0x0; // Page_table_attribute_index[6]
      pt[j].g_8 = 0x0; // Global[8]
      pt[j].disponible_11_9 = 0x0; // Disponible[11..9]
      pt[j].baseDir_31_12 = 1024 * i + j; // DirBasePagina[31..12]
    }    
  }  
  
  /*
  pt = (page_table_entry *) (pd[0].baseDir_31_12 << 12);
  for (i = 0; i < 1024; i++) {
    pt[i].p_0 = 0x1;
    pt[i].rw_1 = 0x1;
    pt[i].us_2 = 0x0;
    pt[i].pwt_3 = 0x0;
    pt[i].pcd_4 = 0x0;
    pt[i].a_5 = 0x0;
    pt[i].dirtyBit_6 = 0x0;
    pt[i].pat_7 = 0x0;
    pt[i].g_8 = 0x0;
    pt[i].disponible_11_9 = 0x0;
    pt[i].baseDir_31_12 = i;
  }
  
  pt = (page_table_entry *) (pd[1].baseDir_31_12 << 12);
  for (i = 0; i < 1024; i++) {
    pt[i].p_0 = 0x1;
    pt[i].rw_1 = 0x1;
    pt[i].us_2 = 0x0;
    pt[i].pwt_3 = 0x0;
    pt[i].pcd_4 = 0x0;
    pt[i].a_5 = 0x0;
    pt[i].dirtyBit_6 = 0x0;
    pt[i].pat_7 = 0x0;
    pt[i].g_8 = 0x0;
    pt[i].disponible_11_9 = 0x0;
    pt[i].baseDir_31_12 = 1024 + i;
  }
  
  pt = (page_table_entry *) (pd[2].baseDir_31_12 << 12);
  for (i = 0; i < 1024; i++) {
    pt[i].p_0 = 0x1;
    pt[i].rw_1 = 0x1;
    pt[i].us_2 = 0x0;
    pt[i].pwt_3 = 0x0;
    pt[i].pcd_4 = 0x0;
    pt[i].a_5 = 0x0;
    pt[i].dirtyBit_6 = 0x0;
    pt[i].pat_7 = 0x0;
    pt[i].g_8 = 0x0;
    pt[i].disponible_11_9 = 0x0;
    pt[i].baseDir_31_12 = 1024*2 + i;
  }
  
  pt = (page_table_entry *) (pd[3].baseDir_31_12 << 12);
  for (i = 0; i < 1024; i++) {
    pt[i].p_0 = 0x1;
    pt[i].rw_1 = 0x1;
    pt[i].us_2 = 0x0;
    pt[i].pwt_3 = 0x0;
    pt[i].pcd_4 = 0x0;
    pt[i].a_5 = 0x0;
    pt[i].dirtyBit_6 = 0x0;
    pt[i].pat_7 = 0x0;
    pt[i].g_8 = 0x0;
    pt[i].disponible_11_9 = 0x0;
    pt[i].baseDir_31_12 = 1024*3 + i;
  } // 452
  */
  
}
/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
