/*
 -----------------------------------------------------------------------------------
 Laboratory  : 11
 File        : main.c
 Author(s)   : Maurice Lehmann,Ahmed Farouk Ferchichi, Florian Schaufelberger
 Date        : 29.05.2019

 Goal        : Will test that our code to split a text into an index with the line
 			   is working correctly.

 Compiler    : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>

#include "stop_words.h"
#include "book_index.h"
#include "heading.h"
#include <string.h> //strcmp

int main(int argc, char **argv) {

	//Command line arguments : (Labo 11)
	// "-h" option, show the syntax
	if(!strcmp(argv[1],"-h")){
		printf("Syntax : main.exe \"input text\" \"output file\" \"stopwords file (optional)\"\n");
		return EXIT_SUCCESS;
	}
	//Check the input text to index
	if(argv[1] == NULL){
		printf("Error : no input text given\n");
		return EXIT_FAILURE;
	}
	//Check the output index file
	if(argv[2] == NULL){
		printf("Error : no output index given\n");
		return EXIT_FAILURE;
	//Check if the output index file already exists, if so, ask for overwrite
	}else{
		FILE* outputFile = fopen(argv[2],"r");
		if(outputFile){
			char overwrite;
			printf("Index file already exist, do you want to overwrite it? [y / n]\n");
			scanf("%c", &overwrite);
			fclose(outputFile);
			if(overwrite == 'n'){
				return EXIT_SUCCESS;
			}
		}
	}
	//check for stopword file, it is optional.
	if(argv[3] == NULL){
		//If there is no file, we create an empty one
		argv[3] = "empty.txt";
		FILE* stopwordsFile = fopen(argv[3],"ab+");
		fclose(stopwordsFile);
	}

	//Get the arguments in const string
	const char* TEXT_FILE = argv[1];
	const char* OUTPUT_FILE = argv[2];
	const char* STOPWORDS_FILE = argv[3];

	Index index = NULL;
	char* paragraph = getStringFromFile(TEXT_FILE);
	split_text(paragraph,&index,STOPWORDS_FILE);
	printf("Indexation is over!\n");
	index_write(index,OUTPUT_FILE);
	printf("Writing is over !\n");
	//Unless running a memory tool, we cannot know if the memory is perfectly cleaned
	index_delete(index);
	system("PAUSE");

	return EXIT_SUCCESS;
}
