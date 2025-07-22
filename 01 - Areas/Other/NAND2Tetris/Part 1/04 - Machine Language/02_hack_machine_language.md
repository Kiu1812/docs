---
tags:
---
---

# Hack Machine Language


## Elements

The Hack computer that we are creating offers support for the following elements.

- Two types of instructions, called `A` and `C`.
- 2 registers and 1 *virtual* register.
- Symbols.
- Variables.
- Input / Output device mappings.

### Instructions

#### A Instruction

An `A` instruction is used to modify the data of the `A` register.
The syntax is:

```
@value
```

Where value is either:
- a non-negative decimal constant lower or equal than 32767.
- a symbol referring to such a constant.

This is the mnemonic symbol, the actual binary value of this type of instruction is the following. The first bit set to `0` defines an `A` instruction, then the value itself gets converted to binary.

```
0value
```


#### C Instruction

A `C` instruction is used to perform computational operations.

The syntax is:

```
dest = comp ; jump
```

Where `dest` and `jump` are optional.

The binary form of this instruction is the following. First bit is set to `1` to define a `C` instruction. The following two bits are not used, we will set them to `1` for convention.

Then we have 7 bits for the `comp` section of the instruction. The last 6 bits are used to define which action to do in the ALU. The first one is used to decide whether to use `A` or `M` to do the operation.

Following 6 bits are used in the `dest` and `jump` section, each one of them using 3 bits.

A full instruction in binary form will look like the following.

```
1 1 1 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3
```

The truth table for each section is the following.

**comp**

| **a=0**  | **a=1**  | **c1**  | **c2**  | **c3**  | **c4**  | **c5**  | **c6**  |
| ---- | ---- | --- | --- | --- | --- | --- | --- |
| 0    |      | 1   | 0   | 1   | 0   | 1   | 0   |
| 1    |      | 1   | 1   | 1   | 1   | 1   | 1   |
| -1   |      | 1   | 1   | 1   | 0   | 1   | 0   |
| D    |      | 0   | 0   | 1   | 1   | 0   | 0   |
| A    | M    | 1   | 1   | 0   | 0   | 0   | 0   |
| !D   |      | 0   | 0   | 1   | 1   | 0   | 1   |
| !A   | !M   | 1   | 1   | 0   | 0   | 0   | 1   |
| -D   |      | 0   | 0   | 1   | 1   | 1   | 1   |
| -A   | -M   | 1   | 1   | 0   | 0   | 1   | 1   |
| D+1  |      | 0   | 1   | 1   | 1   | 1   | 1   |
| A+1  | M+1  | 1   | 1   | 0   | 1   | 1   | 1   |
| D-1  |      | 0   | 0   | 1   | 1   | 1   | 0   |
| A-1  | M-1  | 1   | 1   | 0   | 0   | 1   | 0   |
| D+A  | D+M  | 0   | 0   | 0   | 0   | 1   | 0   |
| D-A  | D-M  | 0   | 1   | 0   | 0   | 1   | 1   |
| A-D  | M-D  | 0   | 0   | 0   | 1   | 1   | 1   |
| D&A  | D&M  | 0   | 0   | 0   | 0   | 0   | 0   |
| D\|A | D\|M | 0   | 1   | 0   | 1   | 0   | 1   |

**dest**

| **dest** | **d1** | **d2** | **d3** | **effect: the value is stored in:**   |
| -------- | ------ | ------ | ------ | ------------------------------------- |
| null     | 0      | 0      | 0      | The value is not stored.              |
| M        | 0      | 0      | 1      | `RAM[A]`.                             |
| D        | 0      | 1      | 0      | D register.                           |
| MD       | 0      | 1      | 1      | `RAM[A]` and D register.              |
| A        | 1      | 0      | 0      | A register.                           |
| AM       | 1      | 0      | 1      | A register and `RAM[A]`.              |
| AD       | 1      | 1      | 0      | A register and D register.            |
| AMD      | 1      | 1      | 1      | A register, `RAM[A]`, and D register. |


**jump**

| **jump** | **j1** | **j2** | **j3** | **effect**         |
| -------- | ------ | ------ | ------ | ------------------ |
| null     | 0      | 0      | 0      | no jump            |
| JGT      | 0      | 0      | 1      | if out > 0 jump    |
| JEQ      | 0      | 1      | 0      | if out = 0 jump    |
| JGE      | 0      | 1      | 1      | if out >= 0 jump   |
| JLT      | 1      | 0      | 0      | if out < 0 jump    |
| JNE      | 1      | 0      | 1      | if out != 0 jump   |
| JLE      | 1      | 1      | 0      | if out <= 0 jump   |
| JMP      | 1      | 1      | 1      | unconditional jump |


### Registers

For the registers we have the following ones.

- A -> Contains current address selected at the RAM.
- D -> Data register, can store 16 bits of data.
- M -> (Virtual) Content of `RAM[A]`. It's called virtual because it's just a representation for the value of the RAM at the address stored in register `A`.

### Symbols

In order to avoid using numbers when programming in this language, the support for symbols was added.

A symbol is just a "marker" for the Assembler to know which number to replace with certain string, for example:

Let's create a symbol, it's declared with `(SYMBOL_NAME)` at an empty line. Then it can be used at any point of the code with an `A` instruction, using as value the same we used in `SYMBOL_NAME`, for example `@SYMBOL_NAME`.
This way the assembler will replace `@SYMBOL_NAME` with the number of the next line where the symbol was created.

We have some pre-defined symbols for the input / output mapping as well as the first few addresses of the RAM.

| **Symbol Name** | **Address** |
| ----------- | ------- |
| R0..R15     | 0..15   |
| SCREEN      | 16384   |
| KBD         | 24576   |

### Variables

A variable in this language can be used as any other programming language. You declare it and the compiler (in this case the Assembler) will "reserve" certain memory for that variable.

To create and use a variable we will do it using an `A` instruction, and instead of using an integer we will use a text, which will define the name of our variable. This text cannot be one of the reserved symbol names.

The address used for the first variable will be the address 16, and with each variable that address will increase by one.

### Input

As an input we have the keyboard. Each time you press a key it's keycode will be recorded into the address `24576`, defined with the symbol `KBD`. When the keyboard is idle `keycode=0`, if any letter is pressed `keycode=letter_code` until that key released. A list of the supported codes is:

| **Key**     | **Code** |
| ----------- | -------- |
| 0..9        | 48..57   |
| A..Z        | 65..90   |
| (space)     | 32       |
| !           | 33       |
| "           | 34       |
| \#          | 35       |
| $           | 36       |
| %           | 37       |
| &           | 38       |
| '           | 39       |
| (           | 40       |
| )           | 41       |
| \*          | 42       |
| +           | 43       |
| ,           | 44       |
| -           | 45       |
| .           | 46       |
| /           | 47       |
| :           | 58       |
| ;           | 59       |
| <           | 60       |
| =           | 61       |
| >           | 62       |
| ?           | 63       |
| @           | 64       |
| \[          | 91       |
| \\          | 92       |
| ]           | 93       |
| ^           | 94       |
| _           | 95       |
| newline     | 128      |
| backspace   | 129      |
| left arrow  | 130      |
| up arrow    | 131      |
| right arrow | 132      |
| down arrow  | 133      |
| home        | 134      |
| end         | 135      |
| Page up     | 136      |
| Page down   | 137      |
| insert      | 138      |
| delete      | 139      |
| esc         | 140      |
| f1..f12     | 141..152 |

### Output

Then, as an output device we have an screen. This screen is actually just a piece of memory represented visually. It has a size of 256 rows and 512 columns and only supports black and white.

As we mentioned the screen is a direct mapping between the memory and the display itself. It's initial starting address is `16384` (or the symbol `SCREEN`).

With the size of the screen mentioned we would need `131072` bits to represent all of the screen. What we will do is use each bit of the memory to represent certain row and column. So, for example, with the first address, `16384`, the MSB will represent the Top-Left pixel of the screen, the second MSB will represent the second pixel of the screen and so on. Once we finish with all of the 16 bits we can continue with the next address.

To calculate which pixel we need to modify we can use the following operations.

1. Set address to `32*row + col/16`. Remember we are dividing only integers, so the remainder will be discarded (actually will be used in the next step).
2. Now that we have the address of the memory that we want to modify we now need to now which bit of it to modify. This will be calculated using `col % 16`.
3. Set certain bit to `1` in order to display black, or to `0` for displaying white.

Once the changes are written to memory the screen will update itself.