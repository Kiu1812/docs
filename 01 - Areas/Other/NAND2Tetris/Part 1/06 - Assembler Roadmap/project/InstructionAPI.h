#ifndef __INSTRUCTION_API_H__
#define __INSTRUCTION_API_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum {
  TYPE_A,
  TYPE_C_FULL, // DEST=CMP;JUMP
  TYPE_C_DEST, // DEST=CMP
  TYPE_C_JUMP, // CMP;JUMP
  TYPE_C_COMP, // CMP
  TYPE_LABEL,   // LABEL
  TYPE_EMPTY // COMMENT / EMPTY LINE 
} tInstructionType;

typedef struct {
  char* content;
} tFieldNode;

typedef struct _tFields {
  tFieldNode* elems;
  int count;
} tFields;

typedef struct {
  char* full_line;
  char* instruction;
  tFields* fields;
  tInstructionType type;
} tInstruction;

void fieldList_init(tFields* fields);
void fieldList_append(tFields* fields, tFieldNode node);
void fieldList_print(tFields fields);
void fieldList_cpy(tFields* dest, tFields src);
void fieldList_free(tFields* fields);

void field_init(tFieldNode* node, char* content);
void field_cpy(tFieldNode* dest, tFieldNode src);
void field_free(tFieldNode* node);

void instruction_init(tInstruction* instruction, char* full_line, char* instruction_str);
void instruction_print(tInstruction instruction);
void instruction_cpy(tInstruction* dest, tInstruction src);
void instruction_free(tInstruction instruction);

#endif
