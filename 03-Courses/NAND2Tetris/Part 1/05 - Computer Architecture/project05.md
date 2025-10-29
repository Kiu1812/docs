---
tags:
---

# Project 05

This is the final project in the hardware of our computer. In this project we will connect everything together to build our final computer.

We will have to build 3 chips in total.
- Memory
- CPU
- Computer

## Memory

For the memory we just have to check if we are accessing an IO device instead of the actual Data Memory.
If the address corresponds to an IO device, we will output it's value too.

[Download](resources/hdl/Memory.hdl)

```hdl
/**
 * The complete address space of the Hack computer's memory,
 * including RAM and memory-mapped I/O. 
 * The chip facilitates read and write operations, as follows:
 *     Read:  out(t) = Memory[address(t)](t)
 *     Write: if load(t-1) then Memory[address(t-1)](t) = in(t-1)
 * In words: the chip always outputs the value stored at the memory 
 * location specified by address. If load=1, the in value is loaded 
 * into the memory location specified by address. This value becomes 
 * available through the out output from the next time step onward.
 * Address space rules:
 * Only the upper 16K+8K+1 words of the Memory chip are used. 
 * Access to address>0x6000 is invalid and reads 0. Access to any address
 * in the range 0x4000-0x5FFF results in accessing the screen memory 
 * map. Access to address 0x6000 results in accessing the keyboard 
 * memory map. The behavior in these addresses is described in the Screen
 * and Keyboard chip specifications given in the lectures and the book.
 */
CHIP Memory {
    IN in[16], load, address[15];
    OUT out[16];

    PARTS:

    // Check bits to know which device to select.
    // 00 -> RAM
    // 10 -> SCREEN
    // 11 -> KBD

    And(a=address[14], b=true, out=selectdevice);
    And(a=address[13], b=selectdevice, out=setkbdout);
    Not(in=setkbdout, out=setscr);
    And(a=setscr, b=selectdevice, out=selectscr);
    And(a=selectscr, b=load, out=loadscr);

    Screen(in=in, load=loadscr, address=address[0..12], out=scrout);
    Keyboard(out=kbdout);
    // Select the output device
    Mux16(a=scrout, b=kbdout, sel=setkbdout, out=devicesout);

    Not(in=selectdevice, out=selectram);
    And(a=load, b=selectram, out=loadram);
    RAM16K(in=in, load=loadram, address=address[0..13], out=ramout);
    
    Mux16(a=devicesout, b=ramout, sel=selectram, out=out);
}
```

## CPU

The CPU will be responsible (as the name suggests) of the control of the actual computer, this chip will decide whether to JUMP, Write into memory, Write into a Register, use the ALU, etc...

This will be done by looking at the values provided by the `instruction` input pin. For example, we will check the MSB to know if we have an `A` or `C` instruction.

[Download](resources/hdl/CPU.hdl)

```hdl
/**
 * The Hack Central Processing unit (CPU).
 * Parses the binary code in the instruction input and executes it according to the
 * Hack machine language specification. In the case of a C-instruction, computes the
 * function specified by the instruction. If the instruction specifies to read a memory
 * value, the inM input is expected to contain this value. If the instruction specifies
 * to write a value to the memory, sets the outM output to this value, sets the addressM
 * output to the target address, and asserts the writeM output (when writeM = 0, any
 * value may appear in outM).
 * If the reset input is 0, computes the address of the next instruction and sets the
 * pc output to that value. If the reset input is 1, sets pc to 0.
 * Note: The outM and writeM outputs are combinational: they are affected by the
 * instruction's execution during the current cycle. The addressM and pc outputs are
 * clocked: although they are affected by the instruction's execution, they commit to
 * their new values only in the next cycle.
 */
CHIP CPU {

    IN  inM[16],         // M value input  (M = contents of RAM[A])
        instruction[16], // Instruction for execution
        reset;           // Signals whether to re-start the current
                         // program (reset==1) or continue executing
                         // the current program (reset==0).

    OUT outM[16],        // M value output
        writeM,          // Write to M? 
        addressM[15],    // Address in data memory (of M)
        pc[15];          // address of next instruction

    PARTS:
	
    // Check if A or C instruction.
    // instruction[15] == 0 -> A Instruction
    // instruction[15] == 0 -> C Instruction
    Mux16(a=instruction, b=aluout, sel=instruction[15], out=aregin);

    // A Register
    // Load into A reg when
    // instruction[5] == 1 -> Saving from ALU
    // OR
    // instruction[15] == 0 -> It's an A instruction.
    Not(in=instruction[15], out=ainstruction);
    Or(a=instruction[5], b=ainstruction, out=aregload);
    ARegister(in=aregin, load=aregload, out=aregout);
    
    // Output the A reg to addressM
    Or16(a=aregout, b=false, out[0..14]=addressM);

    // Select from A or M register.
    // instruction[12] == 0 -> A
    // instruction[12] == 1 -> M
    Mux16(a=aregout, b=inM, sel=instruction[12], out=yaluin);

    // ALU
    // Control bits instruction[6..11]
    ALU(x=dregout, y=yaluin,
        zx=instruction[11],
        nx=instruction[10],
        zy=instruction[9],
        ny=instruction[8],
        f=instruction[7],
        no=instruction[6],
        out=aluout,
        zr=zrflag, ng=ngflag);
    
    // Output of ALU to outM
    Or16(a=aluout, b=false, out=outM);

    // D Register
    // Load into D reg when
    // instruction[4] == 1 -> Saving from ALU
    And(a=instruction[15], b=instruction[4], out=dregload);
    DRegister(in=aluout, load=dregload, out=dregout);
    

    // writeM output when
    // instruction[15] == 1
    // AND
    // instruction[3] == 1
    And(a=instruction[15], b=instruction[3], out=writeM);

    // PC
    // j1 == instruction[2]
    // j2 == instruction[1]
    // j3 == instruction[0]
    // pcload is 1 when (between lines OR)
    // JGT > zr==0 ^ ng==0
    // JEQ > zr==1
    // JGE > JGT v JEQ
    // JLT > ng==1
    // JNE > (NOT JEQ)
    // JLE > JLT v JEQ
    // JMP
    Not(in=zrflag, out=notzrflag);
    Not(in=ngflag, out=notngflag);
    Not(in=reset, out=notreset);

    // Check if greater
    And(a=notzrflag, b=notngflag, out=gtflag);

    // Check if equal
    And(a=zrflag, b=true, out=eqflag);

    // Check if lower
    And(a=ngflag, b=true, out=ltflag);

    // j3
    And(a=instruction[0], b=gtflag, out=setpcload1);

    // j2
    And(a=instruction[1], b=eqflag, out=setpcload2);

    // j1
    And(a=instruction[2], b=ltflag, out=setpcload3);

    Or(a=setpcload1, b=setpcload2, out=setpcload4);
    Or(a=setpcload3, b=setpcload4, out=setpcload5);
    And(a=setpcload5, b=notreset, out=setpcload6);
    And(a=setpcload6, b=instruction[15], out=pcload);

    // pcinc is 1 when
    // pcload==0 ^ reset==0
    Not(in=pcload, out=notpcload);
    And(a=notpcload, b=notreset, out=pcinc);
    PC(in=aregout, load=pcload, inc=pcinc, reset=reset, out[0..14]=pc);
}
```
## Computer

As we said, the computer chip will just connect every other main chip together.

[Download](resources/hdl/Computer.hdl)

```hdl
/**
 * The Hack computer, consisting of CPU, ROM and RAM.
 * When reset = 0, the program stored in the ROM executes.
 * When reset = 1, the program's execution restarts. 
 * Thus, to start running the currently loaded program,
 * set reset to 1, and then set it to 0. 
 * From this point onwards, the user is at the mercy of the software.
 * Depending on the program's code, and whether the code is correct,
 * the screen may show some output, the user may be expected to enter
 * some input using the keyboard, or the program may do some procerssing. 
 */
CHIP Computer {

    IN reset;

    PARTS:
    CPU(inM=ramout,
        instruction=romout,
        reset=reset,
        outM=outm, writeM=writem, addressM=addressm,
        pc=pcout);
    ROM32K(address=pcout, out=romout);
    Memory(in=outm, load=writem, address=addressm, out=ramout);
}
```