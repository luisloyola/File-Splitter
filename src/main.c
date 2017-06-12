#ifndef STDIO
#define STDIO 1
#include <stdio.h>
#endif
#ifndef STDLIB
#define STDLIB 1
#include <stdlib.h>
#endif
#ifndef STRING
#define STRING 1
#include <string.h>
#endif
#ifndef GETOPT
#define GETOPT 1
#include <getopt.h>
#endif
#ifndef UNISTD
#define UNISTD 1
#include <unistd.h>
#endif



void argerror(char* pname){
	printf("ERROR!\n");
	printf("Usage: %s [--join] myfilename\n", pname);
	printf("Usage: %s filename [--cut] x, then x is the number of part that you want to cut myfilename\n", pname);
	exit(-1);
}


int main(int argc, char **argv){
	if((argc !=3)&&(argc !=4)){
		argerror(argv[0]);
	}
	static int option_flag;
	if(argc == 3){// ./program --join filename
		int c;
		char filename[250];
		static struct option long_options[] = {
			{"join", required_argument, &option_flag, 1}
		};
		c = getopt_long(argc, argv, "", long_options, 0);
		while(c !=-1){//mientras hayan opciones para leer + el primer argumento sin opcion
			if((c == 0)&&(optarg)){//la opcion es join y tiene argumento
				strcpy(filename,optarg);
			}
			else{
				argerror(argv[0]);
			}
			c = getopt_long(argc, argv, "", long_options, 0);
		}
		if(option_flag==1){
			//LLAMAR JOINER
			const char* program_name = "JOIN";
			char** argv2 = (char**)malloc(2*sizeof(char*));
			argv2[0] = "JOIN";
			argv2[1] = (char*)malloc(strlen(filename)*sizeof(char)+1);
			strcpy(argv2[1],filename);

			printf("Executing: JOIN\n");
			execv(program_name,argv2);
		}
		else{
			argerror(argv[0]);
		}
	}

	if(argc == 4){// ./program filename --cut n
		int c = 0;
		int n;
		static int option_flag;
		char filename[250];
		char strn[5];
		static struct option long_options[] = {
			{"cut", required_argument, &option_flag, 1}
		};
		while(c != -1){
			c = getopt_long(argc, argv, "", long_options,0);
			if((c == 0)&&(optarg)){//la opcion es cut y tiene argumento
				n = atoi(optarg);// n es el argumento de cut
				if(n!=0){// es un número válido.
					option_flag=1;
					strcpy(strn,optarg);		
				}else{//no se puede interpretar como int o es 0.
					argerror(argv[0]); 
				}
			}
			if(c == -1){//debiera ser el nombre del archivo a cortar
				if(strcmp(argv[1],"--cut")==0){
					strcpy(filename,argv[3]);
				}
				else{
					strcpy(filename,argv[1]);
				}
			}
		}
		if(option_flag == 1){
			//LLAMAR XORER
			const char* program_name = "CUT";
			char** argv2 = (char**)malloc(4*sizeof(char*));
			argv2[0] = (char*)malloc(2*sizeof(char));
			strcpy(argv2[0],"a");
			argv2[1] = (char*)malloc(strlen(filename)*sizeof(char));
			strcpy(argv2[1],filename);
			argv2[2] = (char*)malloc(strlen(strn)*sizeof(char));
			strcpy(argv2[2],strn);
			argv2[3] = NULL;
			printf("Executing: CUT\n");
			execv(program_name,argv2);
		}
		else{
			argerror(argv[0]);
		}
	}



	/*
	OLD VERSION
	int c = 0;
	int optind = 0;
	static int option_flag;
	int option_index = 0;
	while(c != -1){
		optind++;
		printf("Empiezawhile: optind:%d\n",optind);
		static struct option long_options[] = {
			{"cut",  required_argument, &option_flag, 1},
			{"join", required_argument, &option_flag, 2}
		};
		c = getopt_long(argc, argv, "", long_options, &option_index);
		printf("switch_c:%d\n",c);
		switch(c){

			case 0:
				printf("%s",long_options[option_index].name);
				if(optarg){
					printf(": %s\n", optarg);
					optind++;
				}else{
					printf("\n");
				}
				printf("\noptind:%d\n",optind);
				if(option_flag==1){
					printf("LLAMEN AL XORER\n");
				}
				if (option_flag==2){
					printf("LLAMEN AL JOINER\n");
				}
				printf("\noptind:%d\n",optind);
				break;
			default:
				printf("SERA EL NOMBRE:%s\n",argv[optind]);
				printf("optind:%d\n",optind);
				printf("default:%s\n",argv[optind]);
				printf("optind:%d\n",optind);
		}
	}
	*/
	return 0;
}
