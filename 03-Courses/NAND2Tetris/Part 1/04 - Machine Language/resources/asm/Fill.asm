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
