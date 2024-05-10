//Game function definitions
//Author: Folu Taiwo                                                           
//CPSC1070 - Spring 2024                                                       
//Project 01: Strands

#include "game.h"

FILE * open_data_file(int argc, char** argv) {
  FILE * dataFP;
  if (argc > 1) {
    dataFP = fopen(argv[1], "r");
    if (dataFP != NULL) {
      return dataFP;
    }
  }
  //Prompt user for strand data filename
  printf("Provide strand data filename: ");
  char filename[20];
  scanf("%s", filename);
  dataFP = fopen(filename, "r");
  if (dataFP == NULL) {
    printf("Error: Unable to open data file %s\n", filename);
    return NULL;
  }
  return dataFP;
}

FILE * open_dict_file(int argc, char** argv) {
  FILE * dictFP;
  if (argc > 2) {
    dictFP = fopen(argv[2], "r");
    if (dictFP != NULL) {
      return dictFP;
    }
  }
  //Default to opening file defined by DICT_PATH
  dictFP = fopen(DICT_PATH, "r");
  if (dictFP == NULL) {
    printf("Error: Unable to open dictionary file %s\n", DICT_PATH);
    return NULL;
  }
  return dictFP;
}

void print_instructions(strand_t * strand) {
    printf("\n  +-- Welcome to Strands! --+\n");
    printf("\nInstructions:\n");
    printf("\tFind all %d %d-letter words\n", strand->numWords, strand->wordLen);
    printf("\tEach word's letters must touch\n");
    printf("\tA letter can be repeated in a word\n");
    printf("\tType a word then press 'Enter'\n");
    printf("\tType 'quit' when done\n");
}

void play_game(strand_t * strand) {
  if (strand == NULL) {
    printf("Error: NULL pointer passed to play_game\n");
    return;
  }

  //Variable to keep track of the number of correctly guessed words
  int foundWords = 0;
  
  //Array to store guessed words
  char guessedWords[strand->numWords][25];
  
  //Initialize the 'found' array to all false values
  memset(guessedWords, 0, sizeof(guessedWords));
  
  //Variable to store the player's input word
  char input[25];

  while (foundWords < strand->numWords) {
    printf("\nGuess a word or 'quit':\n");
    scanf("%24s", input); // Read up to 24 characters, excluding the null terminator, to avoid buffer overflow

    // Clear the input buffer to remove any extra characters
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    if (strcmp(input, "quit") == 0) {
      printf("You found %d out of %d %d-letter words.\nThanks for playing!\n", foundWords, strand->numWords, strand->wordLen);
      return;
    }
    
    //Check if the word has already been found
    bool alreadyGuessed = false;
    for (int i = 0; i < foundWords; i++) {
      if (strcmp(input, guessedWords[i]) == 0) {
	alreadyGuessed = true;
	break;
      }
    }
    if (alreadyGuessed) {
      printf("You have already guessed %s!\n", input);
      printf("You have found %d of %d %d-letter words in the strand so far.\n", foundWords, strand->numWords, strand->wordLen);
      continue; // Skip further processing for this word
    }

    //Check if the guessed word is valid
    if (is_word_in_strand(strand, input) && strlen(input) == strand->wordLen &&foundWords < strand->numWords) {
      strcpy(guessedWords[foundWords], input);
      foundWords++;
      printf("%s is a valid word in the strand!\n", input);
    } else {
      printf("%s is not a valid word in the strand.\n", input);
    }

    if (foundWords < strand->numWords && !alreadyGuessed) {
      printf("You have found %d of %d %d-letter words in the strand so far.\n", foundWords, strand->numWords, strand->wordLen);
    } else {
      printf("You found all %d %d-letter words!\nGreat job! Thanks for playing!\n", foundWords, strand->wordLen);
    }
  }
}


  
