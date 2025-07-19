---
tags:
---

# Project 03

In the third project we will be building the memory of our computer. The modules to build are:

- Bit -> One bit memory unit.
- Register -> 16-bit memory unit.
- RAM8 -> 8 Registers.
- RAM64 -> 8 RAM8.
- RAM512 -> 8 RAM64.
- RAM4K -> 8 RAM512.
- RAM16K -> 4 RAM4K.
- PC -> Program Counter.

For the different RAM units we will use `MUX` and `DMUX` to select where do we write the data, feeding all inputs into all modules at the same time.

The definition for this chips was explained in [memory](memory.md), so we will go directly to their implementation.

As we have sequential bits we will not use truth table and only show the HDL files.

## BIT

[Download](resources/hdl/Bit.hdl)

```hdl
/**
 * 1-bit register:
 * If load is asserted, the register's value is set to in;
 * Otherwise, the register maintains its current value:
 * if (load(t)) out(t+1) = in(t), else out(t+1) = out(t)
 */
CHIP Bit {
    IN in, load;
    OUT out;

    PARTS:
    Mux(a=dffout, b=in, sel=load, out=muxout);
    DFF(in=muxout, out=dffout);
    Or(a=dffout, b=false, out=out);
}
```

## Register

[Download](resources/hdl/Register.hdl)

```hdl
/**
 * 16-bit register:
 * If load is asserted, the register's value is set to in;
 * Otherwise, the register maintains its current value:
 * if (load(t)) out(t+1) = int(t), else out(t+1) = out(t)
 */
CHIP Register {
    IN in[16], load;
    OUT out[16];

    PARTS:
    Bit(in=in[0], load=load, out=out[0]);
    Bit(in=in[1], load=load, out=out[1]);
    Bit(in=in[2], load=load, out=out[2]);
    Bit(in=in[3], load=load, out=out[3]);
    Bit(in=in[4], load=load, out=out[4]);
    Bit(in=in[5], load=load, out=out[5]);
    Bit(in=in[6], load=load, out=out[6]);
    Bit(in=in[7], load=load, out=out[7]);
    Bit(in=in[8], load=load, out=out[8]);
    Bit(in=in[9], load=load, out=out[9]);
    Bit(in=in[10], load=load, out=out[10]);
    Bit(in=in[11], load=load, out=out[11]);
    Bit(in=in[12], load=load, out=out[12]);
    Bit(in=in[13], load=load, out=out[13]);
    Bit(in=in[14], load=load, out=out[14]);
    Bit(in=in[15], load=load, out=out[15]);
}
```

## RAM8

[Download](resources/hdl/RAM8.hdl)

```hdl
/**
 * Memory of eight 16-bit registers.
 * If load is asserted, the value of the register selected by
 * address is set to in; Otherwise, the value does not change.
 * The value of the selected register is emitted by out.
 */
CHIP RAM8 {
    IN in[16], load, address[3];
    OUT out[16];

    PARTS:
    DMux8Way(in=load, sel=address, 
             a=reg1load, 
             b=reg2load, 
             c=reg3load, 
             d=reg4load, 
             e=reg5load, 
             f=reg6load, 
             g=reg7load, 
             h=reg8load);

    Register(in=in, load=reg1load, out=reg1out);
    Register(in=in, load=reg2load, out=reg2out);
    Register(in=in, load=reg3load, out=reg3out);
    Register(in=in, load=reg4load, out=reg4out);
    Register(in=in, load=reg5load, out=reg5out);
    Register(in=in, load=reg6load, out=reg6out);
    Register(in=in, load=reg7load, out=reg7out);
    Register(in=in, load=reg8load, out=reg8out);

    Mux8Way16(a=reg1out,
              b=reg2out, 
              c=reg3out, 
              d=reg4out, 
              e=reg5out, 
              f=reg6out, 
              g=reg7out, 
              h=reg8out,
              sel=address, out=out);
}
```

## RAM64

[Download](resources/hdl/RAM64.hdl)

```hdl
/**
 * Memory of sixty four 16-bit registers.
 * If load is asserted, the value of the register selected by
 * address is set to in; Otherwise, the value does not change.
 * The value of the selected register is emitted by out.
 */
CHIP RAM64 {
    IN in[16], load, address[6];
    OUT out[16];

    PARTS:
    DMux8Way(in=load, sel=address[3..5], 
             a=reg1load, 
             b=reg2load, 
             c=reg3load, 
             d=reg4load, 
             e=reg5load, 
             f=reg6load, 
             g=reg7load, 
             h=reg8load);

    RAM8(in=in, load=reg1load, address=address[0..2], out=reg1out);
    RAM8(in=in, load=reg2load, address=address[0..2], out=reg2out);
    RAM8(in=in, load=reg3load, address=address[0..2], out=reg3out);
    RAM8(in=in, load=reg4load, address=address[0..2], out=reg4out);
    RAM8(in=in, load=reg5load, address=address[0..2], out=reg5out);
    RAM8(in=in, load=reg6load, address=address[0..2], out=reg6out);
    RAM8(in=in, load=reg7load, address=address[0..2], out=reg7out);
    RAM8(in=in, load=reg8load, address=address[0..2], out=reg8out);

    Mux8Way16(a=reg1out,
              b=reg2out, 
              c=reg3out, 
              d=reg4out, 
              e=reg5out, 
              f=reg6out, 
              g=reg7out, 
              h=reg8out,
              sel=address[3..5], out=out);
}
```

## RAM512

[Download](resources/hdl/RAM512.hdl)

```hdl
/**
 * Memory of 512 16-bit registers.
 * If load is asserted, the value of the register selected by
 * address is set to in; Otherwise, the value does not change.
 * The value of the selected register is emitted by out.
 */
CHIP RAM512 {
    IN in[16], load, address[9];
    OUT out[16];

    PARTS:
    DMux8Way(in=load, sel=address[6..8], 
             a=reg1load, 
             b=reg2load, 
             c=reg3load, 
             d=reg4load, 
             e=reg5load, 
             f=reg6load, 
             g=reg7load, 
             h=reg8load);

    RAM64(in=in, load=reg1load, address=address[0..5], out=reg1out);
    RAM64(in=in, load=reg2load, address=address[0..5], out=reg2out);
    RAM64(in=in, load=reg3load, address=address[0..5], out=reg3out);
    RAM64(in=in, load=reg4load, address=address[0..5], out=reg4out);
    RAM64(in=in, load=reg5load, address=address[0..5], out=reg5out);
    RAM64(in=in, load=reg6load, address=address[0..5], out=reg6out);
    RAM64(in=in, load=reg7load, address=address[0..5], out=reg7out);
    RAM64(in=in, load=reg8load, address=address[0..5], out=reg8out);

    Mux8Way16(a=reg1out,
              b=reg2out, 
              c=reg3out, 
              d=reg4out, 
              e=reg5out, 
              f=reg6out, 
              g=reg7out, 
              h=reg8out,
              sel=address[6..8], out=out);
}
```

## RAM4K

[Download](resources/hdl/RAM4K.hdl)

```hdl
/**
 * Memory of 4K 16-bit registers.
 * If load is asserted, the value of the register selected by
 * address is set to in; Otherwise, the value does not change.
 * The value of the selected register is emitted by out.
 */
CHIP RAM4K {
    IN in[16], load, address[12];
    OUT out[16];

    PARTS:
    DMux8Way(in=load, sel=address[9..11], 
             a=reg1load, 
             b=reg2load, 
             c=reg3load, 
             d=reg4load, 
             e=reg5load, 
             f=reg6load, 
             g=reg7load, 
             h=reg8load);

    RAM512(in=in, load=reg1load, address=address[0..8], out=reg1out);
    RAM512(in=in, load=reg2load, address=address[0..8], out=reg2out);
    RAM512(in=in, load=reg3load, address=address[0..8], out=reg3out);
    RAM512(in=in, load=reg4load, address=address[0..8], out=reg4out);
    RAM512(in=in, load=reg5load, address=address[0..8], out=reg5out);
    RAM512(in=in, load=reg6load, address=address[0..8], out=reg6out);
    RAM512(in=in, load=reg7load, address=address[0..8], out=reg7out);
    RAM512(in=in, load=reg8load, address=address[0..8], out=reg8out);

    Mux8Way16(a=reg1out,
              b=reg2out, 
              c=reg3out, 
              d=reg4out, 
              e=reg5out, 
              f=reg6out, 
              g=reg7out, 
              h=reg8out,
              sel=address[9..11], out=out);
}
```

## RAM16K

[Download](resources/hdl/RAM16K.hdl)

```hdl
/**
 * Memory of 16K 16-bit registers.
 * If load is asserted, the value of the register selected by
 * address is set to in; Otherwise, the value does not change.
 * The value of the selected register is emitted by out.
 */
CHIP RAM16K {
    IN in[16], load, address[14];
    OUT out[16];

    PARTS:
    DMux4Way(in=load, sel=address[12..13], 
             a=reg1load, 
             b=reg2load, 
             c=reg3load, 
             d=reg4load);

    RAM4K(in=in, load=reg1load, address=address[0..11], out=reg1out);
    RAM4K(in=in, load=reg2load, address=address[0..11], out=reg2out);
    RAM4K(in=in, load=reg3load, address=address[0..11], out=reg3out);
    RAM4K(in=in, load=reg4load, address=address[0..11], out=reg4out);

    Mux4Way16(a=reg1out,
              b=reg2out, 
              c=reg3out, 
              d=reg4out, 
              sel=address[12..13], out=out);
}
```

## PC

[Download](resources/hdl/PC.hdl)

```hdl
/**
 * A 16-bit counter.
 * if      reset(t): out(t+1) = 0
 * else if load(t):  out(t+1) = in(t)
 * else if inc(t):   out(t+1) = out(t) + 1
 * else              out(t+1) = out(t)
 */
CHIP PC {
    IN in[16], reset, load, inc;
    OUT out[16];
    
    PARTS:
    Or(a=reset, b=load, out=orcontrol1);
    Or(a=orcontrol1, b=inc, out=orcontrol2);
    Not(in=reset, out=notreset);
    And(a=notreset, b=orcontrol2, out=sel1);

    And(a=sel1, b=load, out=andsel0);
    Or(a=andsel0, b=reset, out=sel0);

    Mux4Way16(a=regout,
              b=false,
              c=reginc,
              d=in,
              sel[0]=sel0, sel[1]=sel1, out=regin);
    Register(in=regin, load=true, out=regout);
    Inc16(in=regout, out=reginc);
    Or16(a=regout, b=false, out=out);
}
```
