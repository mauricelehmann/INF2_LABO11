/*
 -----------------------------------------------------------------------------------
 Laboratory  : 11
 File        : stop_words.h
 Author(s)   : Maurice Lehmann,Ahmed Farouk Ferchichi, Florian Schaufelberger
 Date        : 29.05.2019

 Goal        : Declaration of "stopwords" functions
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

#ifndef STOP_WORDS_H
#define STOP_WORDS_H

#include <stdbool.h>
#include <stdio.h>
/**
 * [createEmptyStringTab description]
 * @param  nbWord [description]
 * @return        [description]
 */
char** createEmptyStringTab(const size_t nbWord);
/**
 * [getNbOfWords description]
 * @param  string [description]
 * @return        [description]
 */
size_t getNbOfWords(char* string);
/**
 * Split une string en "mot" qu'on alloue dynamiquement et qu'on indexe dans un tableau de string
 * @param stopWordArray Tableau de string
 * @param string        String à split
 */
void splitString(char** stopWordArray, char* string);
/**
 * [getStringFromFile description]
 * @param  fileName [description]
 * @return          [description]
 */
char* getStringFromFile(const char* fileName);

/**
 * Split a "stopword" file into an indexed array in place in memory
 * @param  filename File to split
 * @return          Array of strings
 */
size_t createStopWordsArray(const char* filename,char** stopWords);
/**
 * TODO
 * @param  text  [description]
 * @param  word  [description]
 * @param  size   [description]
 * @return       [description]
 */
bool dichotomicSearch(char** text, char* word, size_t begin, size_t end);
#endif //STOP_WORDS_H
