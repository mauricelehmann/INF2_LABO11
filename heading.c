/*
 -----------------------------------------------------------------------------------
 Laboratory  : 11
 File        : heading.c
 Author(s)   : Maurice Lehmann,Ahmed Farouk Ferchichi, Florian Schaufelberger
 Date        : 29.05.2019

 Goal        : Definition of our heading's function. Define our Heading and
 			   Location structure. We can print, delete and create, allocate
 			   a heading and we can create a location. Permit us to split the text
 			   into words without the ponctuation.
 Compiler    : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "stop_words.h"
#include "heading.h"

//Min char we want in a word
#define MIN_CHAR 3

void heading_write(const Heading* heading, FILE* file){
	Location* currentLocation = heading->location;
	//We write the word
	fputs(heading->word,file);
	//We seek each line where the word appear
	while(currentLocation != NULL){
		fputs(", ",file);
		//Convert the line in string
		//We choose a large 100 char sized buffer
		char sLine[100];
		//print in the output the line
		sprintf(sLine, "%ld",(unsigned long)currentLocation->line);
		fputs(sLine,file);

		currentLocation = currentLocation->next;
	}
}
void heading_print(const Heading* heading){
	Location* currentLocation = heading->location;
	//We display the word
	printf("%s", heading->word );
	//We seek each line where the word appear
	while(currentLocation != NULL){
		printf(", %lu",(unsigned long) currentLocation->line);
		currentLocation = currentLocation->next;
	}
}
void heading_delete(Heading* heading){
	//Free all locations of the heading
	Location* currentLocation = heading->location;
	Location* nextLocation;
	while(currentLocation != NULL){
		nextLocation = currentLocation->next;
		free(currentLocation);
		currentLocation = nextLocation;
	}
	//Free the heading
	free(heading);
}
Heading* heading_alloc(Word word,Line line){
	Heading* newHeading = calloc(1,sizeof(Heading));
	if(newHeading == NULL){
		printf("Error on heading allocation!\n");
		return NULL;
	}
	newHeading->word = word;
	newHeading->next = NULL;
	newHeading->location = NULL;
	location_create(newHeading,line);
	return newHeading;
}
void heading_create(Heading** index, Word word, Line line){

	//Case when the list is empty
	if(*index == NULL){
		//We create the struct with the word
		Heading* newHeading = heading_alloc(word,line);
		*index = newHeading;
		return;
	}

	//Case when the list is NOT empty
	Heading* currentHeading = *index;
	Heading* previousHeading = NULL;

	//We seek the good place of the word, or if the word is already in our list
	while(strcmp(currentHeading->word,word) < 0 && currentHeading->next != NULL ){
		previousHeading = currentHeading;
		currentHeading = currentHeading->next;
	}
	//Case when it's the same word
	if(strcmp(currentHeading->word,word) == 0){
		location_create(currentHeading,line);
	}else{
		//We create the struct with the word
		Heading* newHeading = heading_alloc(word,line);
		//If the word is going at the beginning of the list
		if(currentHeading == *index){
			//Make index point on this first heading AND next will be heading = index
			newHeading->next = *index;
			*index = newHeading;
		}else{
			//Case when the word is the smaller than the smallest one of the list
			//We do a split in the list : between 2 elements :
			// Before : [previousHeading]-->[currentHeading]-->[ ... ]
			// After : [previousHeading]-->[newHeading]-->[currentHeading]->[ ... ]
			// Or at the end : [currentHeading] --> [newHeading] --> NULL
			// If the element goes at the end
			if(strcmp(currentHeading->word,word) < 0){
				currentHeading->next = newHeading;
				newHeading->next = NULL;
			}else{
				previousHeading->next = newHeading;
				newHeading->next = currentHeading;
			}
		}
	}
}

Location* location_create(Heading* heading, Line line){
	//check if the word is not in the same line
	if(heading->lastLine == line)
		return NULL;

	Location* newLocation = calloc(1,sizeof(Location));
	if(newLocation == NULL){
		printf("Error on location allocation!\n");
		return NULL;
	}
	newLocation->line = line;
	newLocation->next = NULL;
	heading->lastLine = line;

	Location* currentLocation = heading->location;
	//IF there isnt a linked list of location
	if(currentLocation == NULL){
		heading->location = newLocation;
		heading->lastLocation = newLocation;
	//Else we will inster it at the end
	}else{
		//We will seek at the last location of the linked list
		while(currentLocation->next != NULL){
			currentLocation = currentLocation->next;
		}
		//We will add our new location
		currentLocation->next = newLocation;
	}
	return newLocation;
}

void split_text(char* text,Heading** index,const char* stopwordsFile) {

	//Not wanted char when indexing words
	const char* UNWANTED_CHAR = " <>[]()\"';:,.-?!+1234567890";
	size_t nbWords;
	char** stopWords;
	if(stopwordsFile != NULL){
		//Create an array of string with indexed stopWords
		char* rawStopWord = getStringFromFile(stopwordsFile);
		//Compte le nombre de mot dans le fichier
		nbWords = getNbOfWords(rawStopWord);
		//Alloue un tableau de string en fonction du nombre de mots dans le fichier
		stopWords = createEmptyStringTab(nbWords);
		//Rempli le tableau de string avec tous les mots
		splitStopWords(stopWords,rawStopWord);
	}

	Line lineNumber = 1;
    Word token = strtok(text, UNWANTED_CHAR);
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL) {
		for(size_t i = 0; token[i]; i++){
		  if(token[i] == '\n'){
			 lineNumber++;
			 token[i] = '\0';
		  }
		  token[i] = tolower(token[i]);
		}
        if(strlen(token) >= MIN_CHAR) {
			//tolower on all of the string
			if(stopwordsFile != NULL){
				if(!dichotomicSearch(stopWords,token,nbWords)){
					heading_create(index,token,lineNumber);
				}
			}else{
				heading_create(index,token,lineNumber);
			}
        }
        token = strtok(NULL, UNWANTED_CHAR);
    }
}
