#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "xorerFunct.h"
#include "misc.h"


FILE* fopen_xor(char fname[], char * modo)
{
	FILE* file;
	char* xorname = (char*) malloc(strlen(fname) + 5);

	strcpy(xorname, fname);
	strcat(xorname, ".XOR");

	file = fopen(xorname, modo);

	free(xorname);

	return file; 
}

FILE* fopen_part(char fname[], int i, char* modo)
{
	FILE* file;
	char* partname = (char*) malloc(strlen(fname) + 10);
	char* num = inttostring(i);

	strcpy(partname, fname);
	strcat(partname, ".part");
	strcat(partname, num); 

	file = fopen(partname, modo);

	free(partname);
	free(num);

	return file; 
}

com_p* new_compipe(int p_in_l, int p_out_l, int p_out_r, int p_in_r)
{
	com_p* pipes = (com_p*) malloc(sizeof(com_p));

	pipes->left_in = p_in_l;
	pipes->left_out = p_out_l;
	pipes->right_in = p_in_r;
	pipes->right_out = p_out_r;

	return pipes;
}

int comunicar(char fname[], int n_proc, long r_from, long nbytes, com_p* pipes )
{
	FILE* file_in, *file_out;	//< Archivo de entrada y salida
	void* data_f;				//< Bytes leidos del archivo
	void* data_p;				//< Bytes leidos del pipe
	long bytes_left = nbytes;	//< Bytes que me quedan por leer
	int rdbytes_f, rdbytes_p;	//< Numero de bytes leidos del archivo y pipe

	if ((file_in = fopen(fname, "r")) == NULL)
		return 1;		// No existe fichero

	if (fseek(file_in, r_from, SEEK_SET) != 0)
		return 1;		// El archivo no es tan largo

	if ((data_f = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria

	if ((data_p = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria


	file_out = fopen_part(fname, n_proc, "w");

	while (bytes_left > 0)
	{
		int cuanto = (TASA > bytes_left ? bytes_left:TASA);
		rdbytes_f = rdbytes_p = 0;

		if (!feof(file_in))
		{
			rdbytes_f = fread(data_f, 1, cuanto, file_in);
		}

		limpiar(data_f, rdbytes_f, TASA);
		fwrite(data_f, 1, cuanto, file_out); 

		if (pipes->left_in != -1)
		{
			rdbytes_p = read(pipes->left_in, data_p, TASA);
			write(pipes->left_out, "1", 2);
		}

		limpiar(data_p, rdbytes_p, TASA);

		xor_(data_f, data_p, TASA);

		char trash[2];

		write(pipes->right_out, data_f, cuanto);
		
		bytes_left -= cuanto;

		if(bytes_left<=0){//no espera confirmación al enviar el último pack de datos.
			break;
		}
		else
		{
			read(pipes->right_in, trash, 2);
		}

	} 

	free(data_f);
	free(data_p);

	fclose(file_in);
	fclose(file_out);

	return 0;
}

void xor_(void* ptr1, void* ptr2, int lenght)
{
	char* cpptr1 = ptr1;
	char* cpptr2 = ptr2;

	for (int i=0; i < lenght; i++)
	{
		cpptr1[i] = cpptr1[i] ^ cpptr2[i]; 
	}
}

void limpiar(void* ptr, int wspaces, int lenght)
{
	char* cpptr = ptr;

	for (int i=wspaces; i<lenght; i++)
	{
		cpptr[i] = '\0';
	}
}

int crear_xor(char fname[], long nbytes, int left_in, int left_out)
{
	FILE* fout;
	long bytes_left = nbytes;
	void* data_p;

	if ((fout = fopen_xor(fname, "a")) == NULL)
		return 1;

	if ((data_p = malloc(TASA)) == NULL)
		return 1;

	while (bytes_left > 0)
	{
		int rdbytes_p;

		rdbytes_p = read(left_in, data_p, TASA);
		write(left_out, "1", 2);
		
		bytes_left-= rdbytes_p;
		
		fwrite(data_p, 1, rdbytes_p, fout); 
	}
	fclose(fout);

	return 0;
}
