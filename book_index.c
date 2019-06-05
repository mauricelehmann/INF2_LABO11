/*
 -----------------------------------------------------------------------------------
 Laboratory  : 11
 File        : book_index.c
 Author(s)   : Maurice Lehmann,Ahmed Farouk Ferchichi, Florian Schaufelberger
 Date        : 29.05.2019

 Goal        : Definition of our function that can permit us to print an index
 			   and to delete an index.
 Compiler    : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include "book_index.h"

void index_write(const Index index,const char* outputFile){
	printf("outputfile : %s\n", outputFile );
	FILE* file = fopen(outputFile,"ab+");
	if(file == NULL){
		perror("Error with outputFile\n");
		return;
	}
	Heading* currentHeading = index;
	//For each heading in index
	while(currentHeading != NULL){
		heading_write(currentHeading,file);
		currentHeading = currentHeading->next;
		fputs("\n",file);
	}
	fclose(file);
}
void index_print(const Index index){
	Heading* currentHeading = index;
	//For each heading in index
	while(currentHeading != NULL){
		heading_print(currentHeading);
		printf("\n");
		currentHeading = currentHeading->next;
	}
}
void index_delete(Index index){
	//Free all heading in index
	Heading* currentHeading = index;
	Heading* nextHeading;
	while(currentHeading != NULL){
		nextHeading = currentHeading->next;
		heading_delete(currentHeading);
		currentHeading = nextHeading;
	}
	//Free the index
	free(index);
}
