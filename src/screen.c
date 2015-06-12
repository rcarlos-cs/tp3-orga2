/* ** por compatibilidad se omiten tildes **
================================================================================
TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
definicion de funciones del scheduler
*/

#include "screen.h"
#include "game.h"


extern jugador_t jugadorA, jugadorB;


static ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;

const char reloj[] = "|/-\\";
#define reloj_size 4


void screen_actualizar_reloj_global()
{
    static uint reloj_global = 0;

    reloj_global = (reloj_global + 1) % reloj_size;

    screen_pintar(reloj[reloj_global], C_BW, 49, 79);
}

void screen_pintar(uchar c, uchar color, uint fila, uint columna)
{
    p[fila][columna].c = c;
    p[fila][columna].a = color;
}

uchar screen_valor_actual(uint fila, uint columna)
{
    return p[fila][columna].c;
}

void print(const char * text, uint x, uint y, unsigned short attr) {
    int i;
    for (i = 0; text[i] != 0; i++)
     {
        screen_pintar(text[i], attr, y, x);

        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(uint numero, int size, uint x, uint y, unsigned short attr) {
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_dec(uint numero, int size, uint x, uint y, unsigned short attr) {
    int i;
    char letras[16] = "0123456789";

    for(i = 0; i < size; i++) {
        int resto  = numero % 10;
        numero = numero / 10;
        p[y][x + size - i - 1].c = letras[resto];
        p[y][x + size - i - 1].a = attr;
    }
}
/** Funciones implementadas por nuestro grupo**/
void screen_inicializar()
{
    int i, j;

    // Fondo de la pantalla
    for(i=0; i<VIDEO_FILS; i++) {
        for(j=0; j<VIDEO_COLS; j++){
            screen_pintar( CHAR_SPACE, C_BG_LIGHT_GREY, i, j );
        }
    }

    /** Pinto la parte superior del la pantalla de color negro, osea la fila 0 **/
    screen_pintar_linea_h(CHAR_SPACE, C_BG_BLACK, 0, 0, 80 );
    /** Pinto la parte inferior de la pantalla de negro,las ultimas 5 filas**/
    screen_pintar_linea_h(CHAR_SPACE, C_BG_BLACK, 45, 0, 80 );
    screen_pintar_linea_h(CHAR_SPACE, C_BG_BLACK, 46, 0, 80 );
    screen_pintar_linea_h(CHAR_SPACE, C_BG_BLACK, 47, 0, 80 );
    screen_pintar_linea_h(CHAR_SPACE, C_BG_BLACK, 48, 0, 80 );
    screen_pintar_linea_h(CHAR_SPACE, C_BG_BLACK, 49, 0, 80 );

    // Barras inferiores correspondientes a cada jugador (rojo y azul)
    for(i=FILA_INICIAL_JUG; i<=FILA_FINAL_JUG; i++) {
        for(j=COLU_INICIAL_JUG_A; j<=COLU_FINAL_JUG_A; j++){
            screen_pintar( CHAR_SPACE, C_BG_RED, i, j );

        }
        for(j=COLU_INICIAL_JUG_B; j<=COLU_FINAL_JUG_B; j++){
           screen_pintar( CHAR_SPACE, C_BG_BLUE, i, j );
       }
    }

    /** Imprimir los 8 numeros de cada pirata**/
    screen_pintar_numero_de_piratas();    
    /** Imprimir el nombre del grupo **/
    screen_pintar_nombre_del_grupo(); 
}

void screen_pintar_linea_h(unsigned char c, unsigned char color, int fila, int columna, int ancho){
    int i  ;
    for ( i = columna; i < ancho; ++i)
    {
        screen_pintar(c,color,fila,i);
    }
}

void screen_pintar_numero_de_piratas(){
    /** Imprimir los 8 numeros de cada pirata**/
    screen_pintar('1',C_BG_BLACK | C_FG_WHITE,46,4);
    screen_pintar('1',C_BG_BLACK | C_FG_WHITE,46,60);

    screen_pintar('2',C_BG_BLACK | C_FG_WHITE,46,6);
    screen_pintar('2',C_BG_BLACK | C_FG_WHITE,46,62);

    screen_pintar('3',C_BG_BLACK | C_FG_WHITE,46,8);
    screen_pintar('3',C_BG_BLACK | C_FG_WHITE,46,64);

    screen_pintar('4',C_BG_BLACK | C_FG_WHITE,46,10);
    screen_pintar('4',C_BG_BLACK | C_FG_WHITE,46,66);

    screen_pintar('5',C_BG_BLACK | C_FG_WHITE,46,12);
    screen_pintar('5',C_BG_BLACK | C_FG_WHITE,46,68);

    screen_pintar('6',C_BG_BLACK | C_FG_WHITE,46,14);
    screen_pintar('6',C_BG_BLACK | C_FG_WHITE,46,70);

    screen_pintar('7',C_BG_BLACK | C_FG_WHITE,46,16);
    screen_pintar('7',C_BG_BLACK | C_FG_WHITE,46,72);

    screen_pintar('8',C_BG_BLACK | C_FG_WHITE,46,18);
    screen_pintar('8',C_BG_BLACK | C_FG_WHITE,46,74);

}


void screen_pintar_nombre_del_grupo(){
    /** Imprimir el nombre del grupo **/
    screen_pintar('S',C_BG_BLACK | C_FG_WHITE,0,66);
    screen_pintar('o',C_BG_BLACK | C_FG_WHITE,0,67);
    screen_pintar('n',C_BG_BLACK | C_FG_WHITE,0,68);
    screen_pintar('i',C_BG_BLACK | C_FG_WHITE,0,69);
    screen_pintar('c',C_BG_BLACK | C_FG_WHITE,0,70);
    screen_pintar('_',C_BG_BLACK | C_FG_WHITE,0,71);
    screen_pintar('/',C_BG_BLACK | C_FG_WHITE,0,72);
    screen_pintar('_',C_BG_BLACK | C_FG_WHITE,0,73);
    screen_pintar('S',C_BG_BLACK | C_FG_WHITE,0,74);
    screen_pintar('e',C_BG_BLACK | C_FG_WHITE,0,75);
    screen_pintar('g',C_BG_BLACK | C_FG_WHITE,0,76);
    screen_pintar('a',C_BG_BLACK | C_FG_WHITE,0,77);

}
