/*
 -----------------------------------------------------------------------------------
 Laboratory  : 11
 File        : heading.h
 Author(s)   : Maurice Lehmann,Ahmed Farouk Ferchichi, Florian Schaufelberger
 Date        : 29.05.2019

 Goal        : Declaration of our heading's function. Define our Heading and
 			   Location structure. We can print, delete and create, allocate
 			   a heading and we can create a location. Permit us to split the text
 			   into words without the ponctuation.
 Compiler    : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
*/

#ifndef HEADING_H
#define HEADING_H

typedef char* Word;
typedef size_t Line;

/**
 * Heading structure, matches at a word in the text and contains the
 * beginning of a linked list with a location struct that matches with
 * the line where our word appear in the text
 * The attribute lastLine is used to prevent any multiple occurences in the same line
 */
typedef struct Heading{
  Word word;
  struct Location* location;
  struct Location* lastLocation;
  struct Heading* next;
  Line lastLine;
} Heading;
/**
 * Structure Location
 * Node of a linked list that matches with a line number
 */
typedef struct Location{
  Line line;
  struct Location* next;
} Location ;

/**
 * Write a heading in a input file
 * @param heading Heading to write
 * @param file    Input file to write in
 */
void heading_write(const Heading* heading, FILE* file);
/**
 * Display a heading and all of his locations
 * @param heading Structure Heading to display
 */
void heading_print(const Heading* heading);
/**
 * Delete a heading of the memory and before that all of his locations
 * @param heading Struct Heading to delete
 */
void heading_delete(Heading* heading);
/**
 * Create a heading
 * @param word [word that we want to add in the heading]
 * @param line [line where the word appear in the text]
 */
void heading_create(Heading** index,Word word, Line line);
/**
 * Allocate the memory for our heading
 * @param  word [word that we want to add in the heading]
 * @param  line [line where the word appear in the text]
 * @return      [heading]
 */
Heading* heading_alloc(Word word,Line line);
/**
 * Create a location
 * @param heading [heading where the word appear]
 * @param line    [line where the word appear in the text]
 */
Location* location_create(Heading* heading, Line line);
/**
 * Will split the text in word and will put them in an index.
 * @param text  [text that we want to split]
 * @param index [index where we want our word to go]
 * @param stopwordsFile Path of file with the stopwords
 */
void split_text(char* text,Heading** index,const char* stopwordsFile);

#endif
