#include "SymbolTable.h"

void symbolTable_init(tSymbolTable* table) {
  assert(table != NULL);

  table->count = 0;
  table->elems = NULL;
}


void symbolTable_append(tSymbolTable* table, tSymbol symbol) {
  assert (table != NULL);

  if (table->count == 0) {
    table->elems = (tSymbol*) malloc(sizeof(tSymbol));
  } else {
    table->elems = (tSymbol*) realloc(table->elems, (table->count + 1) * sizeof(tSymbol));
  }
  assert(table->elems != NULL);

  symbol_cpy(&(table->elems[table->count]), symbol);
  table->count += 1;
}

void symbolTable_print(tSymbolTable table) {
  for (int i = 0; i < table.count; i++) {
    printf("Symbol: %s\tValue: %i\n", table.elems[i].name, table.elems[i].value);
  }
}

int symbolTable_findIdx(tSymbolTable table, char* name) {

  if (table.count > 0) {
    for (int i = 0; i < table.count; i++) {
      if (strcmp(table.elems[i].name, name) == 0) return i;
    }
  }

  return -1;
}

void symbolTable_free(tSymbolTable* table) {
  if (table->count > 0) {
    for (int i = 0; i < table->count; i++) {
      symbol_free(&(table->elems[i]));
    }
    if (table->elems != NULL) {
      free(table->elems);
      table->elems = NULL;
    }
  }
}


void symbol_init(tSymbol* symbol, char* name, int value) {
  assert(symbol != NULL);
  symbol->name = name;
  symbol->value = value;
}

void symbol_cpy(tSymbol* dest, tSymbol src) {
  assert(dest != NULL);
  dest->name = malloc(sizeof(src.name) + 1);
  strcpy(dest->name, src.name);
  dest->value = src.value;
}

void symbol_free(tSymbol* symbol) {
  assert(symbol != NULL);

  if (symbol->name != NULL) {
    free(symbol->name);
    symbol->name = NULL;
  }
}
