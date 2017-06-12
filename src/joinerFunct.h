#include "xorerFunct.h"

/**
 * Encuantra la parte faltante del archivo fname luego de ser cortado
 * por el programa CUT.
 *
 * @param fname Es el nombre del archivo original
 * @param total Es el numero total de partes en que fue cortado fname
 * @return El numero de la parte que falta, cero si no falta ninguna o 
 * -1 si falta mas de una parte.
 *
 *  - Ej. Si falta la parte 3 (<archivo>.part3) devuelve 3
 */
int missing(char fname[], int total);

/**
 * Pasa los bytes resultado del XOR entre los archivos existentes para
 * poder reconstruir el que falta.
 *
 * @param fname Es el nombre del fichero original
 * @param n_proc Es el numero del proceso
 * @param i_faltante Es el numero de la parte que falta
 * @param pipes Son los descriptores de los pipes con los cuales se va a
 * comunicar
 */
int recovery(char fname[], int n_proc, int i_faltante, com_p* pipes );

/**
 * Reconstruye la parte que falta.
 *
 * @param fname Es el nombre del archivo original
 * @param i_faltante Es el numero de la parte que falta
 * @param left_in Es el descriptor del pipe por donde recibo los bytes
 * @param left_out Es el descriptor del pipe por donde mando la confirmacion
 * @return 0 si el archivo pudo crearse de nuevo o 1 si no se pudo.
 */
int rebuild(char fname[], int i_faltante, int left_in, int left_out);

/**
 * Función que se encarga de restaurar un archivo, juntando las partes.
 * @param fname Es el nombre del archivo que se quiere restaurar.
 * @param n_partes Es el numero de partes que componen el archivo.
 * @param endsize cantidad de bytes que NO copiar, desde el final del archivo de entrada.
 * @return 0 si todo salio bien, -1 si no puede abrir un archivo. 
 */
int joinALL(char* fname, int n_partes, int endsize);

/**
 * Copia el contenido de un archivo a otro.
 * Excluye los últimos "endsize" bytes de la copia.
 * NOTA: fout debe estar abierto en modo escritura y el archivo 
 * indicado por fin_name debe estar cerrado.
 * @param fout Es el nombre del archivo donde escribir.
 * @param fin_name Es el nombre del archivo a leer.
 * @param endsize cantidad de bytes que NO copiar, desde el final del archivo de entrada.
 * @return 0 si todo salio bien, -1 si no puede abrir un archivo.
 */
int copiar_contenido(FILE* fout, char* fin_name, int endsize);
