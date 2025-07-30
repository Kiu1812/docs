---
tags:
---

# Assembler Roadmap

We need a software that can convert from our Assembly code into the Hack Machine Language (0 and 1). This software is called an Assembler.

The basic logic of an Assembler is:

Repeat:

- Read the next Assembly language command.
- Break it into the different fields it is composed of.
- Lookup the binary code for each field.
- Combine these codes into a single machine language command.
- Output this machine language command.

Until end-of-file reached.


While doing these steps we need to take some considerations:

1. Whitespaces. Empty lines / indentation, line comments, in-line comments.
2. Use of symbols. How to convert the labels, variables, and pre-defined ones.
3. Types of instructions. A-Instruction vs C-Instruction.

> To have more details about the Hack Machine Language please visit [this](../04%20-%20Machine%20Language/02_hack_machine_language.md) document.

In this case we will add 5 more pre-defined symbols. This will be used later on the second part of the course.
These symbols are:

| **Name** | **Value** |
| -------- | --------- |
| SP       | 0         |
| LCL      | 1         |
| ARG      | 2         |
| THIS     | 3         |
| THAT     | 4         |
