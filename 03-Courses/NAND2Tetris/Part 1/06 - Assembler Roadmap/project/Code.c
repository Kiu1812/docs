#include "Code.h"

// FROM: gpt-4o
char* intToBinary(int n, size_t bits) {
    char *binary = malloc(bits + 1); 
    
    binary[bits] = '\0'; 

    for (size_t i = 0; i < bits; i++) {
        binary[bits - 1 - i] = (n & (1 << i)) ? '1' : '0';
    }

    return binary;
}


char* instructionToBinary(tInstruction instruction,
                          tSymbolTable* dynamic_symbols,
                          tSymbolTable dest_symbols,
                          tSymbolTable comp_symbols,
                          tSymbolTable jump_symbols,
                          int* variables_next_address) {
  char* binary;
  char* field_str;
  int idx, value, i;
  tFields binary_fields;
  tSymbol new_variable;
  tFieldNode field_node;

  /*
  TYPE_A,
  TYPE_C_FULL, // DEST=CMP;JUMP
  TYPE_C_DEST, // DEST=CMP
  TYPE_C_JUMP, // CMP;JUMP
  TYPE_C_COMP, // CMP
  */

  fieldList_init(&(binary_fields));
  if (instruction.type == TYPE_A) {
    idx = symbolTable_findIdx(*(dynamic_symbols), instruction.fields->elems[0].content);
    if (idx == -1) {
      value = atoi(instruction.fields->elems[0].content);
      if (value == 0 && instruction.fields->elems[0].content[0] != '0') {
        value = *(variables_next_address);
        *(variables_next_address) += 1;
        symbol_init(&(new_variable), instruction.fields->elems[0].content, value);
        symbolTable_append(dynamic_symbols, new_variable);
        symbol_free(&(new_variable));
      }
    } else {
      value = dynamic_symbols->elems[idx].value;
    }

    // OP CODE FOR A INSTRUCTION
    binary = malloc(sizeof(char) * strlen(OPCODE_A)+1);
    strcpy(binary, OPCODE_A);
    binary[1] = '\0';
    field_init(&(field_node), binary);
    fieldList_append(&(binary_fields), field_node);
    field_free(&(field_node));
    free(binary);
    binary = NULL;
    
    binary = intToBinary(value, SYMBOL_BITS);
    field_init(&(field_node), binary);
    fieldList_append(&(binary_fields), field_node);
    field_free(&(field_node));
    free(binary);
    binary = NULL;
    //fieldList_print(binary_fields);

  } else {
    // OP CODE FOR C INSTRUCTION
    binary = malloc(sizeof(char) * strlen(OPCODE_C)+1); 
    strcpy(binary, OPCODE_C);
    binary[3] = '\0';
    field_init(&(field_node), binary);
    fieldList_append(&(binary_fields), field_node);
    field_free(&(field_node));
    free(binary);
    binary = NULL;

    if (instruction.type == TYPE_C_FULL) {
      parseField(instruction.fields->elems[1].content, comp_symbols, &(binary_fields), COMP_FIELD_BITS);
      parseField(instruction.fields->elems[0].content, dest_symbols, &(binary_fields), DEST_FIELD_BITS);
      parseField(instruction.fields->elems[2].content, jump_symbols, &(binary_fields), JUMP_FIELD_BITS);
    } else if (instruction.type == TYPE_C_DEST) {
      parseField(instruction.fields->elems[1].content, comp_symbols, &(binary_fields), COMP_FIELD_BITS);
      parseField(instruction.fields->elems[0].content, dest_symbols, &(binary_fields), DEST_FIELD_BITS);
      addEmptyField(&(binary_fields), JUMP_FIELD_BITS);
    } else if (instruction.type == TYPE_C_JUMP) {
      parseField(instruction.fields->elems[0].content, comp_symbols, &(binary_fields), COMP_FIELD_BITS);
      addEmptyField(&(binary_fields), DEST_FIELD_BITS);
      parseField(instruction.fields->elems[1].content, jump_symbols, &(binary_fields), JUMP_FIELD_BITS);
    } else if (instruction.type == TYPE_C_COMP) {
      parseField(instruction.fields->elems[0].content, comp_symbols, &(binary_fields), COMP_FIELD_BITS);
      addEmptyField(&(binary_fields), DEST_FIELD_BITS);
      addEmptyField(&(binary_fields), JUMP_FIELD_BITS);
    }
  }

  binary = joinFields(binary_fields);
  fieldList_free(&(binary_fields));
  return binary;
}


void parseField(char* name, tSymbolTable table, tFields* fieldList, size_t bits) {
  char* field_str;
  int idx, value;
  tFieldNode field_node;

  idx = symbolTable_findIdx(table, name);
  value = table.elems[idx].value;
  field_str = intToBinary(value, bits);
  field_init(&(field_node), field_str);
  fieldList_append(fieldList, field_node);
  field_free(&(field_node));
  free(field_str);
}

void addEmptyField(tFields* fields, size_t bits) {
  char* binary = intToBinary(0, bits);
  tFieldNode field_node;
  field_init(&(field_node), binary);
  fieldList_append(fields, field_node);
  field_free(&(field_node));
  free(binary);
}

char* joinFields(tFields fields) {
  int total_str_length = 0;
  int i, instruction_idx, field_str_idx;

  for (i = 0; i < fields.count; i++) {
    total_str_length += strlen(fields.elems[i].content);
  }

  char* instruction;
  instruction = malloc(sizeof(char) * (total_str_length+1));
  instruction[total_str_length] = '\0';

  instruction_idx = 0;
  for (i = 0; i < fields.count; i++) {
    for (field_str_idx = 0; field_str_idx < strlen(fields.elems[i].content); field_str_idx++) {
      instruction[instruction_idx] = fields.elems[i].content[field_str_idx];
      instruction_idx += 1;
    }
  }

  return instruction;
}


