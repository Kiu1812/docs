#include "Parser.h"

tInstruction parseLine(char* full_line) {
  char* instruction_str;
  instruction_str = extractInstruction(full_line);
  
  tInstruction instruction;
  instruction_init(&(instruction), full_line, instruction_str);
  free(instruction_str);

  extractFields(instruction.instruction, instruction.fields, &(instruction.type));
  return instruction;
}

char* extractInstruction(char* full_line) {
  char* instruction = NULL;

  char currentChar;

  int linePos = 0;
  int instructionPos = 0;
  
  bool skipChar = false;

  while (linePos < strlen(full_line)) {
    currentChar = full_line[linePos];
    skipChar = false;

    if (currentChar == '/') {
      linePos = strlen(full_line);
      skipChar = true;
    }

    if (currentChar == ' ' || currentChar == '\n' || currentChar == '\r') {
      skipChar = true;
    }

    if (!skipChar) {
      if (instruction == NULL) {
        instruction = malloc(sizeof(char));
      } else {
        instruction = realloc(instruction, sizeof(char) * (instructionPos+1));
      }

      instruction[instructionPos] = currentChar;
      instructionPos += 1;
    }

    linePos++;
  }
 
  if (instruction != NULL) {
    instruction = realloc(instruction, sizeof(char) * (instructionPos+1));
    instruction[instructionPos] = '\0';
  }

  if (instruction == NULL) {
    instruction = malloc(sizeof(char));
    instruction[0] = '\0';
  }

  return instruction;
}

void extractFields(char* instruction, tFields* fields, tInstructionType* type) {
  assert(fields != NULL);

  // A-instruction -> First char is @
  // (LABEL) -> Contains a (
  // C-instruction -> Not matches the other
  // - Full -> DEST=COMP;JUMP
  // - Save -> DEST=COMP
  // - Jump ->      COMP;JUMP
  // - Comp ->      COMP
  if (instruction[0] == '@') {
    extractAInstruction(instruction, fields, type);
  } else if (instruction[0] == '(') {
    extractLABELInstruction(instruction, fields, type);
  } else if (instruction[0] == '\0') {
    *(type) = TYPE_EMPTY;
  } else {
    extractCInstruction(instruction, fields, type);
  } 
}

void extractAInstruction(char* instruction, tFields* fields, tInstructionType* type) {
  char* field = NULL;
  int i;
  int fieldArrayPos = 0;
  int fieldStrPos = 0;
  tFieldNode node;

  for (i = 1; i < strlen(instruction); i++) {
    if (field == NULL) field = malloc(sizeof(char) * (strlen(instruction)+1));
    field[fieldStrPos] = instruction[i];
    fieldStrPos += 1;
    if (i == (strlen(instruction)-1)) { // If last char copy to fields array
      field[fieldStrPos] = '\0'; // Add NUL caracter at end to represent end of string.
      field_init(&(node), field);
      fieldList_append(fields, node);
      field_free(&(node));
      free(field);
      field = NULL;
      fieldStrPos = 0;
    }
  }

  *(type) = TYPE_A;
}

void extractLABELInstruction(char* instruction, tFields* fields, tInstructionType* type) {
  char* field = NULL;
  int i = 1;
  int fieldArrayPos = 0;
  int fieldStrPos = 0;
  tFieldNode node;

  if (field == NULL) field = malloc(sizeof(char) * strlen(instruction)); // No need of +1 because we are deleting two chars from it

  while (instruction[i] != ')') {
    field[fieldStrPos] = instruction[i];
    fieldStrPos += 1;
    i++;
  }

  field[fieldStrPos] = '\0';
  field_init(&(node), field);
  fieldList_append(fields, node);
  field_free(&(node));
  free(field);
  field = NULL;
  fieldStrPos = 0;

  *(type) = TYPE_LABEL;
}

void extractCInstruction(char* instruction, tFields* fields, tInstructionType* type) {
  char* field = NULL;
  int i;
  int fieldArrayPos = 0;
  int fieldStrPos = 0;
  tFieldNode node;

  bool hasDest = false;
  bool hasComp = false;
  bool hasJump = false;
  
  for (i = 0; i < strlen(instruction); i++) {
    hasComp = true; // As it's a C instruction will always have the cmp field

    if (field == NULL) {
      field = malloc(sizeof(char));
    } else {
      field = realloc(field, sizeof(char) * fieldStrPos+1);
    }
  
    if (instruction[i] == '=') {
      hasDest = true;
    }

    if (instruction[i] == ';') {
      hasJump = true;
    }

    if (instruction[i] == '=' || instruction[i] == ';') {
      field = realloc(field, sizeof(char) * fieldStrPos+1);
      field[fieldStrPos] = '\0';
      fieldStrPos += 1;
      field_init(&(node), field);
      fieldList_append(fields, node);
      field_free(&(node));
      free(field);
      field = NULL;
      fieldStrPos = 0;
    } else {
      field[fieldStrPos] = instruction[i];
      fieldStrPos += 1;
    } 

    if (i == (strlen(instruction)-1)) {
      field = realloc(field, sizeof(char) * fieldStrPos+1);
      field[fieldStrPos] = '\0';
      fieldStrPos += 1;
      field_init(&(node), field);
      fieldList_append(fields, node);
      field_free(&(node));
      free(field);
      field = NULL;
      fieldStrPos = 0;
    }
    if (hasComp) {
      *(type) = TYPE_C_COMP;
      if (hasDest && hasJump) {
        *(type) = TYPE_C_FULL;
      } else if (hasDest) {
        *(type) = TYPE_C_DEST;
      } else if (hasJump) {
        *(type) = TYPE_C_JUMP;
      }
    }
  }
}

