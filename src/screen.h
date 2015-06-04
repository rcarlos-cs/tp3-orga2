/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80
	/* Definicion de la pantalla POR NUESTRO GRUPO*/
	#define FILA_INICIAL_JUG    45
	#define FILA_FINAL_JUG      49
	#define COLU_INICIAL_JUG_A   33
	#define COLU_INICIAL_JUG_B   40
	#define COLU_FINAL_JUG_A     39
	#define COLU_FINAL_JUG_B     46



#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */


#include "colors.h"
#include "defines.h"
/** Include incuidos por nuestro grupo **/
#include "caracteres.h" // definicion de los caracteres 

/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;


struct pirata_t;
typedef struct pirata_t pirata_t;

struct jugador_t;
typedef struct jugador_t jugador_t;

int ee_printf(const char *fmt, ...);


void screen_pintar(unsigned char c, unsigned char color, uint fila, uint columna); // implementacion de la catedra
void print(const char * text, unsigned int x, unsigned int y, unsigned short attr); // implementacion de la catedra
void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr); // implementacion de la catedra
void screen_pintar_rect(unsigned char c, unsigned char color, int fila, int columna, int alto, int ancho);
void screen_pintar_linea_h(unsigned char c, unsigned char color, int fila, int columna, int ancho);
void screen_pintar_linea_v(unsigned char c, unsigned char color, int fila, int columna, int alto);
void screen_inicializar();
void screen_pintar_puntajes();

void screen_actualizar_reloj_global(); // implementacion de la catedra
void screen_actualizar_reloj_pirata (jugador_t *j, pirata_t *pirata);
unsigned char screen_color_jugador(jugador_t *j);
unsigned char screen_caracter_pirata(unsigned int tipo);
void screen_pintar_pirata(jugador_t *j, pirata_t *pirata);
void screen_borrar_pirata(jugador_t *j, pirata_t *pirata);
void screen_pintar_reloj_pirata(jugador_t *j, pirata_t *pirata);
void screen_pintar_reloj_piratas(jugador_t *j);
void screen_pintar_relojes();

void screen_actualizar_posicion_mapa(uint x, uint y);
void screen_stop_game_show_winner(jugador_t *j);


#endif  /* !__SCREEN_H__ */
