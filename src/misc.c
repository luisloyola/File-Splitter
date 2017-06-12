/**
 *	Se debe compilar con std 99:
 *	gcc -std=c99
 */

#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

char * inttostring(int num)
{
	char* buff = (char*) malloc (sizeof(char)*10);

	sprintf(buff, "%i", num);
	buff[9]='\0';

	return buff; 
}

long fsof(FILE * ptrFILE)
{
	long size;
	long current;

	if (ptrFILE == NULL)
	{
		return -1;
	}

	current = ftell(ptrFILE);

	fseek(ptrFILE, 0, SEEK_END);
	size = ftell(ptrFILE);
	fseek(ptrFILE, current, SEEK_SET);

	return size; 
}


