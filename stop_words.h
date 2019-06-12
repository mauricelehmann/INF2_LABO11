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
 * Labo 11
 * Init. an empty string array with a given number of elements
 * @param  nbWord Number of element
 * @return        Pointer to the string array
 */
char** createEmptyStringTab(const size_t nbWord);
/**
 * Labo 11
 * Get the number of word ( separated by \n ) in a string
 * @param  string String to analyse
 * @return        Number of words
 */
size_t getNbOfWords(char* string);
/**
 * Labo 11
 * Split a stopwords string into a string array
 * @param stopWordArray Empty string array
 * @param string        Stopwords string
 */
void splitStopWords(char** stopWordArray, char* string);
/**
 * Labo 11
 * Return a string from a file
 * @param  fileName file to load in string
 * @return          String contains the file data
 */
char* getStringFromFile(const char* fileName);

/**
 * Labo 11
 *  Split a "stopword" file into an indexed array in place in memory
 * @param  filename File to split
 * @return          Array of strings
 */
size_t createStopWordsArray(const char* filename,char** stopWords);
/**
 *  Labo 11
 *  Dichotomic search into a ordered list of word
 * @param  text  String array of ordored words
 * @param  word  Searched word
 * @param  size  Size of the string array
 * @return       True if found, else false
 */
bool dichotomicSearch(char** text, char* word, size_t size);
#endif //STOP_WORDS_H
