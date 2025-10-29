---
tags:
---

# Project 04

In this fourth project we will have to program two simple applications using the Hack Machine Language.

The apps to design are called:
- Mult.asm -> Does a multiplication of two numbers.
- Fill.asm -> Fills the screen with black when pressing a key. After releasing it returns to white.


## Mult

The objective of this program is to multiply the number from `R0` and `R1`, finally store the result in `R2`.

To do a simple multiplication of `x*y=z` what we have to do is add `x` to itself as many times as `y`. So we need to loop using `y` (or `R1`) as the iterator.

The code for the program is the following.

[Download](resources/asm/Mult.asm)

```
// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// R2 = R0 * R1
@R1
D=M
@i
M=D

// Make sure the initial value is 0.
@result
M=0

(MULTIPLY_LOOP)
	// Decrease iterator by 1 and multiply if >= than 0.
	@i
	M=M-1
	D=M
	@MULTIPLY // Multiply results if iterator >= 0.
	D;JGE
	@END_LOOP
	D;JLT


(MULTIPLY)
	@R0
	D=M
	@result
	M=D+M
	@MULTIPLY_LOOP
	0;JMP
	

(END_LOOP)

// Save result into R2.
@result
D=M
@R2
M=D

// End loop
(END)
@END
0;JMP
```


## Fill

In this program we will need to read the keyboard input, as long as it differs from 0 we will fill the screen with black, if the keyboard returns to 0 (Keyboard idle), the screen will return to white.
Remember we have symbols to get the screen and keyboard addresses, those are `SCREEN` and `KBD`.

[Download](resources/asm/Fill.asm)

```
// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(B_KBD_LOOP)
	@AFTER_SET_COLOR
	D=A
	@R15
	M=D
	
	@KBD // if key pressed fill with white, if not with black.
	D=M
	@SET_COLOR_WHITE
	D;JEQ
	@SET_COLOR_BLACK
	D;JNE
	
	(AFTER_SET_COLOR)
	@B_KBD_LOOP // Set the address to return to.
	D=A
	@R15
	M=D
	@FILL_SCREEN
	0;JMP


(SET_COLOR_WHITE)
	// Sets the screen_color register to 0.
	// Returns to address in R15.
	@screen_color
	M=0
	@R15
	A=M
	0;JMP

(SET_COLOR_BLACK)
	// Sets the screen_color register to -1.
	// Returns to address in R15.
	@screen_color
	M=-1
	@R15
	A=M
	0;JMP

(FILL_SCREEN)
	// Set screen_color to value to fill.
	// Returns to address in R15.
	
	@screen_address // Initialize variables at 0
	M=0
	@screen_offset
	M=0
	
	// if objective_screen_color = actual_screen_color return
	// Just to optimize and don't do the full loop at each iteration.
	@screen_color
	D=M
	@SCREEN
	D=D-M
	@R15
	A=M
	D;JEQ
	
	(B_SCREEN_LOOP)
	
		@screen_offset
		D=M
		@SCREEN // Obtain real address by adding the offset
		D=D+A
		@screen_address
		M=D
	
		@screen_color // Fill with the value
		D=M
		@screen_address
		A=M
		M=D
		
		@8192 // Loop if not at the last address
		D=A
		@screen_offset
		M=M+1
		D=D-M
		@B_SCREEN_LOOP
		D;JGT
		// End loop

	// return
	@R15
	A=M
	0;JMP

// End loop
(END)
@END
0;JMP
```