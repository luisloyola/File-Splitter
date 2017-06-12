#include <stdio.h>

/**
 * Funcion que transforma un entero de hasta 9 digitos en un string.
 * CUIDADO!: Esta funcion reserva memoria necesaria para poder transformar
 * transformar el entero a string que va dependiendo del la cantidad de 
 * digitos que tenga el numero, por lo tanto, no debe usar esta funcion dentro
 * de un ciclo sin usar referencias puesto que no podra liberar la memoria
 * reservada.
 * @param num Es el entero que se transformara
 * @return El string terminado en caracter NULL que represente al entero
 */
char * inttostring(int num);

/**
 * Dice el tamaño del archivo del descriptor ptrFILE.
 * @param ptrFILE Es el puntero que apunta al archivo ya abierto
 * @return El tamaño del archivo en bytes si es que no hubo problemas, o -1 si
 * 		el puntero no ha sido inicializado
 */
long fsof(FILE * ptrFILE);
