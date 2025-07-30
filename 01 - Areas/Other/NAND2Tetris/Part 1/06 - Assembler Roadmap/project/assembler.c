/* Objective
* Convert .asm into .hack files.
*
* Considerations:
* - Need to ignore comments / whitespaces.
* - Usage of symbols.
* - .asm file name will be received by parameter
* 
* Structure:
* Parser -> Unpacks each instruction into its underlying fields.
* Code -> Translates each field into its corresponding binary value. Responsible of looking up symbols and adding new ones.
* SymbolTable -> Manages the symbol table.
* Main -> Initializes the I/O files and drives the process.
*
* Steps:
* 1. Read full original .asm file.
*
* 2. For each line:
* 2.1 Remove any whitespace.
* 2.2 Remove any comments.
* 2.3 If final line is empty remove it.
* 2.4 If any label declaration in it.
* 2.4.1 Add it to the symbol table with the line number value.
* 2.4.2 Then delete the line
* 2.5 Save final line in a new file / structure.
* 
* 3. Using the new file, for each line.
* 3.1 Send line to Parser.
* 3.2 Send fields to Code.
* 3.3 Merge fields.
* 3.4 Save into final .hack file.
*/

#include "assembler.h"


#define SYMBOL_DELIMITER '='

void loadSymbols(tSymbolTable* symbolTable, char* filename) {

  tSymbol symbol;
  //symbol_init(&symbol, symbol_name, symbol_value);

  FILE *file;
  int bufferLength = 1024;
  char buffer[bufferLength];

  file = fopen(filename, "r");
  if (file == NULL) {
    return;
  }

  char* name = NULL;
  char* str_value = NULL;
  int delimiter_idx, i, value;
  int nameIterator, valueIterator;
  while (fgets(buffer, bufferLength, file)) {
    delimiter_idx = 0;
    nameIterator = 0;
    valueIterator = 0;

    while (buffer[delimiter_idx] != SYMBOL_DELIMITER) delimiter_idx++; // Searching the IDX of the delimiter.

    // Extract name
    for (i = 0; i<delimiter_idx; i++) {
      if (name == NULL) {
        name = malloc((delimiter_idx + 1) * sizeof(char));
      }
      name[nameIterator] = buffer[i];
      nameIterator += 1;
    }
    name[nameIterator] = '\0';

    // Extract value
    for (i = delimiter_idx+1; i < strlen(buffer)-1; i++) {
      if (str_value == NULL) {
        str_value = malloc((strlen(buffer) - delimiter_idx-1) * sizeof(char));
      }
      str_value[valueIterator] = buffer[i];
      valueIterator += 1;
    }
    str_value[valueIterator] = '\0';
    value = atoi(str_value); // Convert value to int

    symbol_init(&symbol, name, value);
    symbolTable_append(symbolTable, symbol);
    symbol_free(&symbol);

    free(str_value);
    str_value = NULL;
    name = NULL; // As we are freeing the value inside of symbol_free, we need to make sure the pointer is NULL
  }
  fclose(file);
}


int main(int argc, char *argv[]) {
  // Check parameter amount
  if (argc != 2) {
    printf("[-] ERROR: Incorrect parameter amount\n");
    printf("Usage: ./assembler <asm_file>\n");
    return 1;
  }

  // TESTS START HERE
  // Test to extract symbols from symbols.ini
  tSymbolTable table;
  symbolTable_init(&table);
  loadSymbols(&table, SYMBOL_FILENAME);
  symbolTable_print(table);
  
  // Test the findIdx function
  char name[] = "SCREEN";
  int idx;
  idx = symbolTable_findIdx(table, name);
  printf("IDX: %d\tVALUE: %d\n", idx, table.elems[idx].value);

  symbolTable_free(&table);
  // TESTS END HERE


  return 0;
}
