#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xorerFunct.h"
#include "misc.h"

#define _RD 0
#define _WR 1


/**
 * argv[1] es el nombre del archivo que se quiere cortar
 * argv[2] es el numero de partes en que se quiere cortar el archivo
 */
int main (int argc, char* argv[])
{

	if (argc < 3)
	{
		return 1;
	}

	FILE* ptrFile ;
	long fsize;
	long nbytes;
	int pid;
	int nprocess = atoi(argv[2]);

	ptrFile = fopen(argv[1], "r");

	if (ptrFile!=NULL)
	{
		fsize = fsof(ptrFile);
		nbytes = fsize/nprocess;
		if((fsize % nprocess)!=0){// si no es división exacta, le da un byte más.
			nbytes++;
		}
		fclose(ptrFile);
	}
	else
	{
		printf("Error: No se encontro el archivo <%s>. Operacion abortada\n", argv[1]);
		return 1;
	} 

	if ((nprocess==0) || fsize/nprocess == 0)
	{
		printf("Numero de partes no permitida \n");
		return 1;
	}

	int** pipes = (int**) malloc(sizeof(int*)*2*nprocess);

	for (int i=0; i< (2*nprocess); i++)
	{
		pipes[i] = (int*) malloc(sizeof(int)*2);
	}

	for (int i=0; i< (2*nprocess); i++)
	{
		pipe(pipes[i]);
	}

	for (int i=0; i< nprocess; i++)
	{
		pid = fork();

		if (pid == -1)
		{
			return 1;
		}
		else if (pid == 0) //hijo
		{
			com_p* pipesHijo;
			switch (i)
			{
				case 0:
					pipesHijo = new_compipe(-1,-1,pipes[0][_WR], pipes[1][_RD]);
					break;
				default:
					pipesHijo = new_compipe(pipes[i*2-2][_RD], pipes[i*2-1][_WR], pipes[i*2][_WR], pipes[i*2+1][_RD]);
					break;

			}

			comunicar(argv[1], i+1, i*nbytes, nbytes, pipesHijo);

			return 0; 
		}
	}

	// Ejecucion del padre
	
	int sobra = nbytes*nprocess - fsize ;
	int ok;

	if ((ptrFile = fopen_xor(argv[1], "w")) == NULL)
		printf("No se pudo crear el archivo .XOR \n");

	fwrite((void*)&nprocess, sizeof(int), 1, ptrFile);
	fwrite((void*)&sobra, sizeof(int), 1, ptrFile);
	fclose(ptrFile);
	
	ok = crear_xor(argv[1], nbytes, pipes[nprocess*2-2][_RD], pipes[nprocess*2-1][_WR]);

	if (ok==0)
	{
		printf("<%s> fue dividido con exito en %i partes.\n", argv[1], nprocess);
	}
	else
	{
		printf("Error: La division no ha podido llevarse a cabo\n");
	} 

	return 0;
}
