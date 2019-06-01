/*
 -----------------------------------------------------------------------------------
 Laboratory  : 10
 File        : stop_words.c
 Author(s)   : Maurice Lehmann,Ahmed Farouk Ferchichi, Florian Schaufelberger
 Date        : 29.05.2019

 Goal        : Definition of "stopwords" functions
  			   The idea is to make an indexed string array with all the stop words in it.
			   This method will reduce the complexity during the indexing of the input text.
			   We use a dichotomic search wich is O(log(n)) on the array of stop word.
			   In order to make the array, we need to :
			   - Count the number of stopword from the input files
			   - Allocate an array of pointer of string
			   - Split the files into strings an put it on the array of pointers
 Compiler    : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stop_words.h"

char** createEmptyStringTab(const size_t nbWord){
	char** stopWordArray = calloc(nbWord,sizeof(char*));
	if(stopWordArray)
		return stopWordArray;
	else
		return NULL;
}
size_t getNbOfWords(char* string){

	size_t i = 0;
	size_t counter = 0;
	while (*(string+i) != '\0') {
		if(*(string+(++i)) == '\n')
			++counter;
	}
	//Result may change if there is only one word or none
	return i > 0 ? counter+1 : counter;
}
void splitString(char** stopWordArray, char* string){

	#define MAX_CHAR_WORD 100
	const char DELIMITEUR = '\n';
	size_t j = 0;
	size_t i = 0;
	size_t wordIndex = 0;
	char c;
	char word[MAX_CHAR_WORD];

	while((c = *(string + j)) != '\0' ){
		if(c == DELIMITEUR){
			word[i] = '\0';
			char* inPlaceWord = calloc(i+1,sizeof(char));
			strcpy(inPlaceWord,word);
			stopWordArray[wordIndex] = inPlaceWord;
			i = 0;
			wordIndex++;
		}else{
			word[i] = c;
			i++;
		}
		j++;
	}
}
char* getStringFromFile(const char* fileName){

	FILE* srcFile = fopen(fileName,"r");
	if(srcFile == NULL){
		printf("Error : Cannot open file \"%s\"\n",fileName);
	}

	size_t lenght = 0;
	char* string;
   	char c;
	//The size is arbitrary here
    size_t size = 10;
	//allocation of the string
	string = malloc(sizeof(char)*size);
	//If the realloc didnt worked
    if(!string){
		return string;
	}
	//While we didnt reach the end of file (EOF)
	while((c = fgetc(srcFile)) != EOF){
	   //Put the char in the string
	   string[lenght++] = c;
	   //Extend the string if not enough
		if(lenght == size){
			string = realloc(string, sizeof(char)*( size += 16));
			if(!string){
				return string;
			}
		}
   }
   string[lenght-1] = '\0';
   return realloc(string, sizeof(char)*lenght);
}
char** createStopWordsArray(const char* filename){
	//Crée dynamiquement une string contenant les data du fichier
	char* rawStopWord = getStringFromFile(filename);
	//Compte le nombre de mot dans le fichier
	size_t nbWords = getNbOfWords(rawStopWord);
	//Alloue un tableau de string en fonction du nombre de mots dans le fichier
	char** stopWordArray = createEmptyStringTab(nbWords);
	//Rempli le tableau de string avec tous les mots
	splitString(stopWordArray,rawStopWord);
	return (char**)stopWordArray;
}
