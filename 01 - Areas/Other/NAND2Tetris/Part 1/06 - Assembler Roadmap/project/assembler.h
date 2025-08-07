#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <stdio.h>
#include <string.h>
#include "SymbolTable.h"
#include "Parser.h"
#include "Code.h"
#include "InstructionAPI.h"
#include "ProgramAPI.h"

#define SYMBOL_FILENAME "symbols.ini"
#define DEST_FILENAME "dest.ini"
#define COMP_FILENAME "comp.ini"
#define JUMP_FILENAME "jump.ini"

void loadSymbols(tSymbolTable* table, char* FILENAME);
void parseFile(tProgram* program, char* FILENAME,
               tSymbolTable* dynamic_table,
               tSymbolTable dest_table,
               tSymbolTable comp_table,
               tSymbolTable jump_table);

#endif
