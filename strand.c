//Strand function definitions
//Author: Folu Taiwo                                                          
//CPSC1070 - Spring 2024                                             
//Project 01: Strands

#include "strand.h"

strand_t * create_strand(FILE * dataFP, FILE * dictFP) {
  //Allocate memory for the strand structure
  strand_t * strand = (strand_t *)malloc(sizeof(strand_t));
  if (strand == NULL) {
    printf("Error: Memory allocation failed for strand structure\n");
    return NULL;
  }

  //Read dimensions of the grid and word length
  if (fscanf(dataFP, "%d %d%*c%d", &strand->rows, &strand->cols, &strand->wordLen) != 3) {
    printf("Error: Failed to read strand information from data file\n");
    free(strand);
    return NULL;
  }

  //Allocate memory for the letters grid
  strand->letters = (char **)malloc(strand->rows * sizeof(char *));
  if (strand->letters == NULL) {
    printf("Error: Memory allocation failed for letters grid\n");
    free(strand);
    return NULL;
  }
  
  for (int i = 0; i < strand->rows; i++) {
    //Allocate memory for each row of the letters grid
    strand->letters[i] = (char *)malloc((strand->cols + 1) * sizeof(char));
    if (strand->letters[i] == NULL) {
      printf("Error: Memory allocation failed for letters grid\n");
      //Free allocate memory before returning NULL
      free_strand(strand);
      return NULL;
    }
    
    //Read characters for each row from the file
    for (int j = 0; j < strand->cols; j++) {
      if (fscanf(dataFP, " %c", &strand->letters[i][j]) != 1) {
        printf("Error: Failed to read letters grid from data file\n");
        //Free allocated memory before returning NULL
        free_strand(strand);
        return NULL;
      }
    }
    //Null-terminate the string
    strand->letters[i][strand->cols] = '\0';
  }

  //Read words from the dictionary file and store valid words in the words array
  int numWords = 0;
  char word[25];
  while (fscanf(dictFP, "%s", word) == 1) {
    //Check if length of the word matches the specified word length for the strand
    if (strlen(word) == strand->wordLen && is_word_in_strand(strand, word)) {
      //Reallocate  memory for the word in the words array and copy the word
      char **temp = (char **)realloc(strand->words, (numWords + 1) * sizeof(char *));
      if (temp == NULL) {
	printf("Error: Memory reallocation failed for words array\n");
	free_strand(strand);
	return NULL;
      }
      strand->words = temp;
      strand->words[numWords] = strdup(word);
      if (strand->words[numWords] == NULL) {
	printf("Error: Memory allocation failed for word\n");
	free_strand(strand);
	return NULL;
      }
      numWords++;
    }
  }
    
  //Set the number of words found     
  strand->numWords = numWords;

  //Close files
  fclose(dataFP);
  fclose(dictFP);
  
  return strand; //Return the allocated memory
}

bool is_word_in_strand(strand_t * strand, char * word) {
  // Iterate over each cell in the grid and check if the word can be formed starting from that cell
  for (int row = 0; row < strand->rows; row++) {
    for (int col = 0; col < strand->cols; col++) {
      //Check if the word can be formed starting from this cell
      if (check_word_from_cell(strand, word, row, col, 0, -1, -1)) {
        return true;
      }
    }
  }
  return false;  // Word not found in the strand
}

bool check_word_from_cell(strand_t *strand, char *word, int row, int col, int index, int prevRow, int prevCol) {
  // Base case: If the index reaches the length of the word, the entire word has been found
  if (index == strlen(word)) {
    return true;
  }

  // Boundary check: Ensure that the row and column indices are within the bounds of the grid
  if (row < 0 || row >= strand->rows || col < 0 || col >= strand->cols) {
      return false;
  }

  // Check if the current letter matches the next letter in the word
  if (strand->letters[row][col] == word[index]) {
    // Define the relative directions to explore: horizontal, vertical, and diagonal
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Recursively check neighboring cells for the next letter in the word
    for (int d = 0; d < 8; d++) {
      int newRow = row + dr[d];
      int newCol = col + dc[d];
      if (check_word_from_cell(strand, word, newRow, newCol, index + 1, row, col)) {
	return true;
      }
    }
  }
  
  // If the current letter does not match, the word cannot be formed from this cell
  return false;
} 

void print_strand_matrix(strand_t * strand) {
  printf("\n");
  printf("\t+---");
  for (int i = 1; i < strand->cols; i++) {
    printf("+---");
  }
  printf("+\n");

  for (int i = 0; i < strand->rows; i++) {
    printf("\t| ");
    for (int j = 0; j < strand->cols; j++) {
      if (strand->letters[i][j] != '\0') {
	printf("%c | ", strand->letters[i][j]);
      } else {
	printf("  | "); // Placeholder for empty cells
      }
    }
    printf("\n");

    if (i != strand->rows - 1) {
      printf("\t+---");
      for (int j = 1; j < strand->cols; j++) {
	printf("+---");
      }
      printf("+\n");
    }
  }

  printf("\t+---");
  for (int i = 1; i < strand->cols; i++) {
    printf("+---");
  }
  printf("+\n");
}

void free_strand(strand_t * strand) {
  if (strand != NULL) {
    //Free the dynamically allocated memory for the letters array
    if (strand->letters != NULL) {
      for (int i = 0; i < strand->rows; i++) {
        free(strand->letters[i]);
      }
      free(strand->letters);
    }

    //Free the dynamically allocated memory for the words array
    if (strand->words != NULL) {
      for (int i = 0; i < strand->numWords; i++) {
        free(strand->words[i]);
      }
      free(strand->words);
    }
  
    //Free the strand struct itself
    free(strand);
  }
}
