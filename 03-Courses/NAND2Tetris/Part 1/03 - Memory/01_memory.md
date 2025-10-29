---
tags:
---

# Memory


## Sequential Logic

In sequential logic we have to take care not only about the inputs and outputs, but also about the time. This will help us, among other things, to use the same hardware multiple times and to remember a state of certain piece of hardware at certain moment.

The time in sequential logic it's controlled by a clock, which divides the continuous timeline in which we live and turn it into segments that we can control and analyze, those segments are identified by integer numbers.

A combinatorial circuit returns the output in "real-time", but a sequential circuit will return the output of whichever input was at the previous time of execution, essentially:

Combinatorial: `out[t] = function( in[t] )`
Sequential: `out[t] = function( in[t-1] )`


## Flip Flop

A Flip Flop is a circuit that can remember a bit of information. For this purpose we will use a `Clocked Data Flip Flop`.

This component will be called `DFF`, the circuit will need to remember the input "forever" instead of changing at each clock Cycle, that purpose will be done with another input bit called `load`, as the name suggests, this control bit will tell the component to either load a new value or keep using the last one, that behavior will be controlled by feeding the `load` into a `MUX`, and the output of the `DFF` will feed directly into the `MUX`, so when `load=0`, the selected input will be the same as the output of the `DFF`, essentially remembering "forever" that state, this circuit is known as a 1-bit register, because we can store and remember one bit of information.


## Memory Units

The most basic memory element: Register.

We saw on the previous unit how to build a 1-bit register, to build an X-bit register we just need an input of that same length.
For the purpose of this course we will now assume that every register is a 16-bit register.

> Most of the elements mentioned in this section will contain a clock input, but that will not be shown.

### Register / Read Logic

To read the register we just have to check the current value of the output.

### Register / Write Logic

To write into a register we have to put the values into the input and then put a `1` into the `load` input, then from the next cycle the output of this register will be this new value.

### RAM unit

A RAM unit, in an abstract definition, can be considered as a sequence of `n` addressable registers, with address 0 to `n-1`.

So, every RAM unit will have 2 inputs, which are: data and address, then it has 1 control input, called `load`, and we have only one output.

Knowing previous properties we can define the following properties:
- At any given point of time, only *one* register in the RAM is selected.
- `k` (width of the address input) can be calculated as `k = log2(n)`. So, for 8 registers, we will have a 3-bit address input.
- `w` (word width), doesn't affect the RAM logic, as said, in this case we will use a 16-bit word length.
- RAM is a sequential chip with a clocked behavior.

#### RAM / Read Logic

To read from the RAM we have to set the address input the address of the register we want to read, and then check the output to see the actual value.

#### RAM / Write Logic

In order to write into the RAM first we will set the address in which we will write, then load the input data, and finally set `load=1` to actually load the value. In the next clock cycle the RAM will be outputting the value we've just loaded.


#### 16-bit RAM chips

In this course we will build the following RAM chips:

| **Name** | **n** | **k** |
| -------- | ----- | ----- |
| RAM8     | 8     | 3     |
| RAM64    | 64    | 6     |
| RAM512   | 512   | 9     |
| RAM4K    | 4096  | 12    |
| RAM16K   | 16384 | 14    |


## Counters

Counters must keep track of which instruction should be fetched and executed next.
This control is realized by a Program Counter (`PC`).

Typically a counter will have 3 control settings.
- Reset: Sets the counter to 0.
- Next: Increases the counter value by 1.
- Load: Sets the counter to `n`.

In other words:
- Reset: Fetch first instruction.
- Next: Fetch next instruction.
- Load: Fetch instruction `n`.


For our PC we will have the mentioned control bits, and if multiple have a value of `1` the order of priority is `Reset > Next > Load`, and only one action will be taken.



