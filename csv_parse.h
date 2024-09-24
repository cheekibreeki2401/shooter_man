#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getfield(char* line, int num){
	char *token;
	for(token = strtok(line, ","); token && *token; token = strtok(NULL, ",\n")){
		if(!--num){
			return token;
		}
	}
	return NULL;
}
