/*
 -----------------------------------------------------------------------------------
 Laboratory  : 10
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

int main(int argc, char **argv) {
	
	if(argc != 3){
		printf("No files passed by arguments (need text file and stopwords file)\n");
		return EXIT_FAILURE;
	}
	const char* TEXT_FILE = argv[1];
	const char* STOPWORDS_FILE = argv[2];

	Index index = NULL;
	char* paragraph = getStringFromFile(TEXT_FILE);
	printf("Texte\n-------------------------\n%s\n\nIndex\n-------------------------\n", paragraph );

	split_text(paragraph,&index,STOPWORDS_FILE);
	index_print(index);
	//Unless running a memory tool, we cannot know if the memory is perfectly cleaned
	index_delete(index);
	system("PAUSE");
	return EXIT_SUCCESS;
}
