#ifndef __PROGRAM_API_H__
#define __PROGRAM_API_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "InstructionAPI.h"

typedef struct {
  tInstruction* instructions;
  int instructions_count;
} tProgram;

void program_init(tProgram* program);
void program_appendInstruction(tProgram* program, tInstruction instruction);
void program_free(tProgram* program);

#endif
