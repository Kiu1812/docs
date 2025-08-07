#include "InstructionAPI.h"


void fieldList_init(tFields* fields) {
  assert(fields != NULL);

  fields->count = 0;
  fields->elems = NULL;
}


void fieldList_append(tFields* fields, tFieldNode node) {
  assert (fields != NULL);

  if (fields->count == 0) {
    fields->elems = (tFieldNode*) malloc(sizeof(tFieldNode));
  } else {
    fields->elems = (tFieldNode*) realloc(fields->elems, (fields->count + 1) * sizeof(tFieldNode));
  }
  assert(fields->elems != NULL);

  field_cpy(&(fields->elems[fields->count]), node);
  fields->count += 1;
}

void fieldList_print(tFields fields) {
  for (int i = 0; i < fields.count; i++) {
    printf("Content [%d]: %s\n", i, fields.elems[i].content);
  }
}

void fieldList_cpy(tFields* dest, tFields src){
  assert(dest != NULL);
  tFieldNode dstNode;
  int i;

  for (i = 0; i < src.count; i++) {
    field_cpy(&(dstNode), src.elems[i]);
    fieldList_append(dest, dstNode);
    field_free(&(dstNode));
  }
}

void fieldList_free(tFields* fields) {
  if (fields->count > 0) {
    for (int i = 0; i < fields->count; i++) {
      field_free(&(fields->elems[i]));
    }
    if (fields->elems != NULL) {
      free(fields->elems);
      fields->elems = NULL;
    }
  }
}


void field_init(tFieldNode* node, char* content) {
  assert(node != NULL);
  node->content = malloc(sizeof(char) * (strlen(content)+1));
  strcpy(node->content, content);
}

void field_cpy(tFieldNode* dest, tFieldNode src) {
  assert(dest != NULL);
  dest->content = malloc(sizeof(char) * (strlen(src.content) + 1));
  strcpy(dest->content, src.content);
}

void field_free(tFieldNode* node) {
  assert(node != NULL);

  if (node->content != NULL) {
    free(node->content);
    node->content = NULL;
  }
}


void instruction_init(tInstruction* instruction, char* full_line, char* instruction_str) {
  assert(instruction != NULL);
  assert(full_line != NULL);
  assert(instruction_str != NULL);

  instruction->full_line = malloc(sizeof(char) * strlen(full_line)+1);
  strcpy(instruction->full_line, full_line);

  instruction->instruction = malloc(sizeof(char) * strlen(instruction_str)+1);
  strcpy(instruction->instruction, instruction_str);
  
  tFields* fields;
  fields = malloc(sizeof(tFields));
  instruction->fields = fields;
  fieldList_init(instruction->fields);
}

void instruction_print(tInstruction instruction) {
  if (instruction.full_line != NULL) printf("Original line:\t'%s'\n", instruction.full_line);
  if (instruction.instruction != NULL) printf("Instruction:\t'%s'\n", instruction.instruction);
  printf("Type:\t\t");
  switch (instruction.type) {
    case 0: printf("TYPE_A"); break;
    case 1: printf("TYPE_C_FULL"); break;
    case 2: printf("TYPE_C_DEST"); break;
    case 3: printf("TYPE_C_JUMP"); break;
    case 4: printf("TYPE_C_COMP"); break;
    case 5: printf("TYPE_LABEL"); break;
    case 6: printf("TYPE_EMPTY"); break;
  }
  printf("\n");
  fieldList_print(*(instruction.fields));
}


void instruction_cpy(tInstruction* dest, tInstruction src) {
  assert(dest != NULL);

  instruction_init(dest, src.full_line, src.instruction);
  //dest->full_line = malloc(sizeof(char) * strlen(src.full_line));
  //dest->instruction = malloc(sizeof(char) * strlen(src.instruction));
  fieldList_cpy(dest->fields, *(src.fields));
  dest->type = src.type;

}


void instruction_free(tInstruction instruction) {
  free(instruction.full_line);
  instruction.full_line = NULL;
  free(instruction.instruction);
  instruction.instruction = NULL;
  fieldList_free(instruction.fields);
  free(instruction.fields);
  instruction.fields = NULL;
}

