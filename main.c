//Main driver of the program 
//Author: Folu Taiwo                                                          
//CPSC1070 - Spring 2024                                                       
//Project 01: Strands   

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "strand.h"

int main(int argc, char** argv) {
  //Open strand data file
  FILE * dataFP = open_data_file(argc, argv);
  if (dataFP == NULL) return 1;

  //Open dictionary file
  FILE * dictFP = open_dict_file(argc, argv);
  if (dictFP == NULL) {
    fclose(dataFP); //Close data file before returning
    return 1;
  }
  
  //Create strand struct: allocate memory & populate accordingly
  strand_t * strand = create_strand(dataFP, dictFP);
  if (strand == NULL) {
    fclose(dataFP); //Close data file 
    fclose(dictFP); //Close dictionary file
    return 1;
  }
  
  //Print strand & game instructions
  print_strand_matrix(strand);
  print_instructions(strand);

  //Play the game
  play_game(strand);

  //Free all strand memory
  free_strand(strand);
  
  //Close files
  fclose(dataFP);
  fclose(dictFP);
  
  return 0;
}

