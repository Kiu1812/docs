#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_DELIMITER '='

typedef struct _tSymbol {
  char* name;
  int value;
} tSymbol;

typedef struct _tSymbolTable {
  tSymbol* elems;
  int count;
} tSymbolTable;

void symbolTable_init(tSymbolTable* table);
void symbolTable_append(tSymbolTable* table, tSymbol symbol);
void symbolTable_print(tSymbolTable table);
int symbolTable_findIdx(tSymbolTable table, char* name);
void symbolTable_free(tSymbolTable* table);
void symbol_init(tSymbol* symbol, char* name, int value);
void symbol_cpy(tSymbol* dest, tSymbol src);
void symbol_free(tSymbol* symbol);
void symbolTable_load(tSymbolTable* symbolTable, char* filename);

#endif
