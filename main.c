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

#include "book_index.h"
#include "heading.h"

int main(void) {

	Index index = NULL;
	char paragraphe[] = "The five five boxing boxing coco boxing \nwizards jump quickly. \n \nPack my box with five \ndozen liquor jugs";
	printf("Texte\n-------------------------\n%s\n\nIndex\n-------------------------\n", paragraphe );
	split_text(paragraphe,&index);
	index_print(index);
	//Unless running a memory tool, we cannot know if the memory is perfectly cleaned
	index_delete(index);
	return EXIT_SUCCESS;
}
