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
