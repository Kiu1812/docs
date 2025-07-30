#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <stdio.h>
#include <string.h>
#include "SymbolTable.h"

#define SYMBOL_FILENAME "symbols.ini"

void loadSymbols(tSymbolTable* symbolTable, char* filename);

#endif
