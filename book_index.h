/*
 -----------------------------------------------------------------------------------
 Laboratory  : 10
 File        : book_index.h
 Author(s)   : Maurice Lehmann,Ahmed Farouk Ferchichi, Florian Schaufelberger
 Date        : 29.05.2019

 Goal        : Declaration of our function that can permit us to print an index
 			   and to delete an index. 
 Compiler    : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
*/

#ifndef BOOK_INDEX_H
#define BOOK_INDEX_H
#include "heading.h"

// Beginning of our list
typedef  Heading* Index ;
/**
 * Display all words and their line number in a text
 * @param index Pointer on the first "Heading" in our linked list
 */
void index_print(const Index index);
/**
 * Free the memory of all headings (linked list) of index and all locations
 * (linked list) of each heading
 * @param Index [index]
 */
void index_delete(Index Index);

#endif
