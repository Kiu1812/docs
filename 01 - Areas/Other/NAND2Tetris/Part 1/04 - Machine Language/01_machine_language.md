---
tags:
---

# Machine Language

The machine language is a composition of sequences made up with `0` and `1`, each sequence is called an instruction, and this instruction tells the computer what to do.

The instructions are stored in the computer memory, ready to be read at a any moment in time. Each instruction is at a certain address, which is where is placed in the memory.


## Mnemonics

Now, a sequence of `0` and `1` is difficult to read for a human, that's why we use what's known as *mnemonics*, this is our way to "read" machine language as humans. What we do is "link" certain sequence with certain action that the computer can do. For example, with the instruction `010001000110010` we can say that, from left to right:

- `0100010` is the equivalent of ADD.
- `0011` is a register of the CPU, in this case R3.
- `0010` is another register of the CPU, being R2.

So the instruction `010001000110010` can be read as `ADD R3 R2` for us humans.

Now we have multiple interpretations for this.
The first one tells us that this form doesn't really exist, and is just a convenient mnemonic to present machine language instruction to us humans.

The second one sees this mnemonics as *assembly language* and we use an "Assembler" to convert it to the bit-form.



By using this new interpretations we can also have **symbols**, which is an easier way to represent some elements, so, if for example we want to represent the 129th address of the memory with `Mem[129]`, we could use a *symbol* for it, which would describe the same with another word, we can use for example the word `index`, and now, `index` would be the same as `Mem[129]`.


## Elements


### Memory Hierarchy

Accessing a memory location is an expensive operation:
- Need to supply a long address
- Getting the memory contents into the CPU takes time

The hierarchy usually follows:
Registers > Cache > Memory > Disk

The most-right is the larger memory unit, but is the most expensive to get data from.

### Registers

CPUs usually contain a few Registers, as they are inside the CPU we can access them with ease.

As this is the fastest memory unit in a computer their number and functions are a central part of the machine language.

The types of registers usually are:
- Data Registers. Contains some data, the value itself.
- Address Registers. Contains an address to a value.

#### Addressing modes

Register.
- `ADD R1,R2` = `R2 <- R2 + R1`

Direct.
- `ADD R1,M[200]` = `M[200] <- M[200] + R1`

Indirect.
- `ADD R1,@A` = `M[A] <- M[A] + R1`

Immediate.
- `ADD 73,R1` = `R1 <- R1 + 73`


### Flow Control

Usually the flow of the program will be just go to the next instruction, so if we are at instruction `70`, we will go to instruction `71`, but sometimes we will want to change that behavior, for example when using loops.

We have two types of *jumps*.

- Direct Jump. Which jumps no matter what.
- Conditional Jump. Which jumps only if certain condition is met, defined in the instruction itself.

