#ifndef __CODE_H__
#define __CODE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "InstructionAPI.h"
#include "SymbolTable.h"

#define INSTRUCTION_BITS 16
#define DEST_FIELD_BITS 3
#define COMP_FIELD_BITS 7
#define JUMP_FIELD_BITS 3

#define OPCODE_A "0"
#define OPCODE_C "111"

#define SYMBOL_BITS 15

char* intToBinary(int n, size_t bits);

char* instructionToBinary(tInstruction instruction,
                          tSymbolTable* dynamic_symbols,
                          tSymbolTable dest_symbols,
                          tSymbolTable comp_symbols,
                          tSymbolTable jump_symbols,
                          int* variables_next_address);
void parseField(char* name, tSymbolTable table, tFields* fieldList, size_t bits);
void addEmptyField(tFields* fields, size_t bits);
char* joinFields(tFields fields);

#endif
