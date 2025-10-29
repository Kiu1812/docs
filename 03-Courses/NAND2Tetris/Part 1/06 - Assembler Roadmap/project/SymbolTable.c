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
    printf("Symbol: '%s'\tValue: %i\n", table.elems[i].name, table.elems[i].value);
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
  symbol->name = malloc(sizeof(char) * (strlen(name)+1));
  if (symbol->name == NULL) {
    exit(1);
  }
  strcpy(symbol->name, name);
  symbol->value = value;
}

void symbol_cpy(tSymbol* dest, tSymbol src) {
  assert(dest != NULL);
  dest->name = malloc(sizeof(char) * (strlen(src.name) + 1));
  if (dest->name == NULL) {
    exit(1);
  }
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




void symbolTable_load(tSymbolTable* symbolTable, char* filename) {

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
    free(name);
    free(str_value);
    str_value = NULL;
    name = NULL;
  }
  fclose(file);
}

