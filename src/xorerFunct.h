#define TASA 2000

/**
 * Estructura que encapsula los pipes.
 */
typedef struct
{
	int left_in, left_out;		//< pipes hacia el proceso hermano izquierdo
	int right_in, right_out;	//< pipes hacia el proceso hermano derecho
}com_p; 

/**
 * Entrega el puntero al archivo \.part<i> del archivo original.
 * @param fname Es el nombre del archivo original
 * @param i Es el numero de parte
 * @param modo Es el modo al cual se quiere abrir el archivo
 */
FILE* fopen_part(char fname[], int i, char* modo);

/**
 * Entrega el puntero al archivo XOR del archivo con el nombre fname.
 * @param fname Es el nombre del archivo original
 * @param modo Es el modo en el que se quiere abrir el archivo
 */
FILE* fopen_xor(char fname[], char * modo);
/**
 * Funcion que genera un nueva estructura com_p que tendra encapsulados
 * los descriptores.
 * @param p_in_l Es el descriptor del pipe del cual leer los bytes del proceso
 * 				hermano izquierdo.
 * @param p_out_l Es el descriptor del pipe en el cual se manda el mensaje de 
 * 				confirmacion de lectura al proceso hermano izquierdo.
 * @param p_out_r Es el descriptor del pipe en el cual mandar los bytes al 
 * 				proceso hermano derecho.
 * @param p_in_r Es el descriptor del pipe en al cual recibir el mensaje de 
 * 				confirmacion de lectura del proceso hermano derecho.
 */
com_p* new_compipe(int p_in_l, int p_out_l, int p_out_r, int p_in_r);

/**
 * Comunica los bytes leidos entre procesos hermanos. Hace que el proceso lea
 * del archivo fname cada cierta tasa de bytes y se los pase al hermano para
 * que le aplique el XOR. Escribe ademas los bytes leidos en su archivo de 
 * respaldo, y dependiendo el numero del proceso va a escribir en un archivo de
 * tipo .part[nro_proceso] o en uno .XOR
 *
 * @param fname Es el nombre del archivo del cual va a leer
 * @param n_proc Es el numero del proceso
 * @param r_from Indica desde donde leera el proceso
 * @param nbytes Indica la cantidad de bytes que debe leer
 * @param pipes Es el puntero a com_p de donde sacara los descriptores de los 
 * 			pipes que va a utilizar
 */
int comunicar(char fname[], int n_proc, long r_from, long nbytes, com_p* pipes );

/**
 * Rellena con ceros los espacios de la memoria no ocupados.
 * @param ptr Es el puntero al espacio de memoria que queremos limpiar
 * @param wspaces Son los espacios que si estamos ocupando en bytes.
 * @param lenght Es el tamanio de la memoria en bytes
 */
void limpiar(void* ptr, int wspaces, int lenght);

/**
 * Ejecuta la operacion binaria XOR. 
 * Hace un xor entre el contenido de dos bloques de memoria guardando el
 * resultado en el primer puntero - sobreescribe el primer puntero -. Hay
 * que tener en cuenta que los dos espacios de memoria deben ser del mismo
 * tamaño, o si no puede arrojar un error de violacion de segmento.
 *
 * @param ptr1 Es el primer puntero y es donde se guardara el XOR
 * @param ptr2 Es el segundo puntero.
 * @param lenght Es el largo en bytes de los bloques de memoria.
 */
void xor_(void* ptr1, void* ptr2, int lenght);

/**
 * Funcion que hace el trabajo del padre. Es decir, crea el .XOR para luego
 * poder unir las partes denuevo.
 *
 * @param fname Es el nombre del fichero
 * @param left_in Es el descriptor del pipe de entrada
 * @param left_out Es el descriptor del pipe de confirmacion
 */
int crear_xor(char fname[], long nbytes, int left_in, int left_out);
