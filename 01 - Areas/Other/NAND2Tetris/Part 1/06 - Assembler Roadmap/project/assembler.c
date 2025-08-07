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
* 2.1 Send line to Parser. Which will take care of whitespaces / empty lines / instruction types.
*     If we find a label. We save the line number and it's name into a symbol table.
* 2.2 Save processed line in a new file / structure.
* 
* 3. Using the new file / structure, for each line.
* 3.1 Send fields to Code. Which will convert the instruction to it's binary.
* 3.2 Save into final .hack file.
*
*/

#include "assembler.h"

void loadSymbols(tSymbolTable* table, char* FILENAME) {
  symbolTable_init(table);
  symbolTable_load(table, FILENAME);
}

void parseFile(tProgram* program, char* FILENAME,
               tSymbolTable* dynamic_table,
               tSymbolTable dest_table,
               tSymbolTable comp_table,
               tSymbolTable jump_table) {
  FILE* file;

  file = fopen(FILENAME, "r");
  if (file == NULL) {
    return;
  }

  int bufferLength = 1024;
  char buffer[bufferLength];

  tInstruction current_instruction;
  int lineNumber = 0;
  tSymbol label;
  char* binary_instruction;

  // Loop to find labels and extract fields
  while (fgets(buffer, bufferLength, file)) {
    current_instruction = parseLine(buffer);
    if (current_instruction.type == TYPE_LABEL) {
      symbol_init(&(label), current_instruction.fields->elems[0].content, lineNumber);
      symbolTable_append(dynamic_table, label);
      symbol_free(&(label));
    }
    if (current_instruction.type != TYPE_EMPTY && current_instruction.type != TYPE_LABEL) {
      lineNumber += 1;
      program_appendInstruction(program, current_instruction);
    }
    instruction_free(current_instruction);
  }
  fclose(file);

  int i = 0;
  char* output_filename;
  output_filename = malloc(sizeof(char) * strlen(FILENAME) + 2); // Add 1 for \0 and another for extra letter in extension.
  while (i < strlen(FILENAME)-3) {
    output_filename[i] = FILENAME[i];
    i++;
  }
  // Append the extension
  output_filename[strlen(FILENAME)-3] = 'h';
  output_filename[strlen(FILENAME)-2] = 'a';
  output_filename[strlen(FILENAME)-1] = 'c';
  output_filename[strlen(FILENAME)] = 'k';
  output_filename[strlen(FILENAME)+1] = '\0';
  
  file = fopen(output_filename, "w");
  if (file == NULL) {
    return;
  }
  printf("Writing to: %s\n", output_filename);
  free(output_filename);
  int variables_next_address = 16;
  for (i = 0; i < program->instructions_count; i++) {
    binary_instruction = instructionToBinary(program->instructions[i], dynamic_table, dest_table, comp_table, jump_table, &(variables_next_address));
    fwrite(binary_instruction, sizeof(char), strlen(binary_instruction), file);
    fwrite("\n", sizeof(char), 1, file);
    free(binary_instruction);
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

  
  tSymbolTable dynamic_table, dest_table, comp_table, jump_table;
  loadSymbols(&(dynamic_table), SYMBOL_FILENAME);
  loadSymbols(&(dest_table), DEST_FILENAME);
  loadSymbols(&(comp_table), COMP_FILENAME);
  loadSymbols(&(jump_table), JUMP_FILENAME);
  
  tProgram program;
  program_init(&(program));

  parseFile(&(program), argv[1], &(dynamic_table), dest_table, comp_table, jump_table);

  program_free(&(program));
  symbolTable_free(&(dynamic_table));
  symbolTable_free(&(dest_table));
  symbolTable_free(&(comp_table));
  symbolTable_free(&(jump_table));
  return 0;
}
