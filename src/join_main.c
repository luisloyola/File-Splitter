#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "misc.h"
#include "joinerFunct.h"

#ifndef TASA
	#include "xorerFunct.h"
#endif

#define _RD 0
#define _WR 1

/**
 * argv[1] debe ser el nombre del archivo
 */
int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Falta el nombre de archivo\n");
		return 1;
	}
	FILE* xorfile;

	if ((xorfile = fopen_xor(argv[1], "r")) == NULL)
	{
		printf("No existe respaldo para <%s> \n", argv[1]);
		return 1;
	}

	int npartes, bytes_sobrantes, imissing;

	fread((void*)&npartes, sizeof(int), 1, xorfile);	// leo el numero de partes
	fread((void*)&bytes_sobrantes, sizeof(int), 1, xorfile);	// leo los bytes que sobran

	fclose(xorfile);

	imissing = missing(argv[1], npartes);

	if (imissing == -1) 	//imposible reconstruir
	{
		printf("Imposible reconstruir archivo, falta mas de una parte\n");
		return 1;
	}
	else if (imissing > 0)	// reconstruccion de la parte faltante
	{
		int** pipes = (int**) malloc(sizeof(int*)*2*npartes);
		int ok ;
		int pid = -1;

		printf("Reconstruyendo la parte que falta \t\t\t");
		fflush(NULL);

		for (int i=0; i< (2*npartes); i++)
		{
			pipes[i] = (int*) malloc(sizeof(int)*2);
		}

		for (int i=0; i< (2*npartes); i++)
		{
			pipe(pipes[i]);
		}

		for (int i=0; i< npartes; i++)
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

				recovery(argv[1], i+1, imissing, pipesHijo);

				return 0; 
			}
		} 

		ok = rebuild(argv[1], imissing, pipes[npartes*2-2][_RD], pipes[npartes*2-1][_WR]);

		if (ok == 0)
		{
			printf("[Ok] \n");
		}
		else
		{
			printf("[Failed] \n");
			printf("No se pudo reconstruir el archivo. Abortado\n");
			return 1;
		}
	} 

	// union de las partes
	
	int ok = joinALL(argv[1], npartes, bytes_sobrantes);

	if (ok == 0)
	{
		printf("<%s> se ha reconstruido con exito\n", argv[1]);
	}
	else
	{
		printf("Fallo la reconstruccion \n");
	} 

	return 0; 
}
