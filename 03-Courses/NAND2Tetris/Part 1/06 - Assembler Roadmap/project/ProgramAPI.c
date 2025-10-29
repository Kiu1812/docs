#include "ProgramAPI.h"



void program_init(tProgram* program) {
  assert(program != NULL);

  program->instructions = NULL;
  program->instructions_count = 0;
}


void program_appendInstruction(tProgram* program, tInstruction instruction) {
  assert(program != NULL);

  if (program->instructions == NULL) {
    program->instructions = malloc(sizeof(tInstruction));
  } else {
    program->instructions = realloc(program->instructions, sizeof(tInstruction) * (program->instructions_count+1));
  }

  instruction_cpy(&(program->instructions[program->instructions_count]), instruction);
  program->instructions_count += 1;
}


void program_free(tProgram* program) {
  int i;
  for (i = 0; i < program->instructions_count; i++) {
    instruction_free(program->instructions[i]);
  }
  free(program->instructions);
  program->instructions = NULL;
}
