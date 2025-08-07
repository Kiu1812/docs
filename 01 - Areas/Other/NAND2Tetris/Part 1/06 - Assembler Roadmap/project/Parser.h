#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "InstructionAPI.h"

tInstruction parseLine(char* full_line);
char* extractInstruction(char* full_line);
void extractFields(char* instruction, tFields* fields, tInstructionType* type);

void extractAInstruction(char* instruction, tFields* fields, tInstructionType* type);
void extractLABELInstruction(char* instruction, tFields* fields, tInstructionType* type);
void extractCInstruction(char* instruction, tFields* fields, tInstructionType* type);
#endif
