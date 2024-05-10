//Strand struct & function prototypes
//Author: Folu Taiwo                                                          
//CPSC1070 - Spring 2024                                                       
//Project 01: Strands

#ifndef STRAND_H
#define STRAND_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//strand struct
typedef struct strand
{
  char** words;
  char** letters;
  int rows, cols;
  int numWords;
  int wordLen;
  
} strand_t;

//Function prototypes
strand_t * create_strand(FILE * dataFP, FILE * dictFP);
bool is_word_in_strand(strand_t * strand, char * word);
bool check_word_from_cell(strand_t *strand, char *word, int row, int col, int index, int prevRow, int prevCol);
void print_strand_matrix(strand_t * strand);
void free_strand(strand_t * strand);

#endif
