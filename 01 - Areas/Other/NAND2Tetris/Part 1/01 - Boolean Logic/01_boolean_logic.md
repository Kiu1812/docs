---
tags:
---

# Boolean Logic

A boolean value can be just represented as False or True, No or Yes, 0 or 1, this represents two physical values.

## Boolean Operations


### AND

Takes two 0 1 signals and returns 1 only if both are 1.

(x AND y)

x∧y

| **x** | **y** | **AND** |
| ----- | ----- | ------- |
| 0     | 0     | 0       |
| 0     | 1     | 0       |
| 1     | 0     | 0       |
| 1     | 1     | 1       |

### OR

Takes two 0 1 signals and returns 1 if any of them are 1.

(x OR y)

x∨y

| **x** | **y** | **OR** |
| ----- | ----- | ------ |
| 0     | 0     | 0      |
| 0     | 1     | 1      |
| 1     | 0     | 1      |
| 1     | 1     | 1      |

### NOT

Takes one 0 1 signal and returns the opposite of it.

NOT(x)

¬x

| **x** | **NOT** |
| ----- | ------- |
| 0     | 1       |
| 1     | 0       |


### NAND

Takes two 0 1 signals and returns 1 if there's at least one 0.

| **x** | **y** | **NAND** |
| ----- | ----- | -------- |
| 0     | 0     | 1        |
| 0     | 1     | 1        |
| 1     | 0     | 1        |
| 1     | 1     | 0        |

### XOR

Takes two 0 1 signals and returns 1 only if one of the two inputs is 1.

| **x** | **y** | **XOR** |
| ----- | ----- | ------- |
| 0     | 0     | 0       |
| 0     | 1     | 1       |
| 1     | 0     | 1       |
| 1     | 1     | 0       |


## Boolean Expressions

Once we have the basics operations we can start evaluating expressions like the following:

NOT(0 OR (1 AND 1)) = NOT(0 OR 1) = NOT(1) = 0


## Boolean Functions

Now that we know how to evaluate expressions we can convert them to functions which take indeterminated values like `x`,`y`,`z` and produce an output, for example:

f(x,y,z) = (x AND y) OR (NOT(X) AND z)

We can create a truth table for this function to see all the possible combinations at once:

| **x** | **y** | **z** | **f** |
| ----- | ----- | ----- | ----- |
| 0     | 0     | 0     | 0     |
| 0     | 0     | 1     | 1     |
| 0     | 1     | 0     | 0     |
| 0     | 1     | 1     | 1     |
| 1     | 0     | 0     | 0     |
| 1     | 0     | 1     | 0     |
| 1     | 1     | 0     | 1     |
| 1     | 1     | 1     | 1     |

### Truth Table to Boolean Expression

For each value of 1 at the function column we create the expression which causes it to be a 1 based on the input bits.

Once we have all the expressions we just have to OR them together and manipulate the expression to simplify it.


## Logic gates


As a non-exhaustive list of the elementary logic gates we have the previously explained, and we are gonna add two more to the list.

### Multiplexor (MUX)

Takes two inputs and a selector input, output will be equivalent to the one we are selecting through the `sel` pin.

| **a** | **b** | **sel** | **out** |
| ----- | ----- | ------- | ------- |
| 0     | 0     | 0       | 0       |
| 0     | 1     | 0       | 0       |
| 1     | 0     | 0       | 1       |
| 1     | 1     | 0       | 1       |
| 0     | 0     | 1       | 0       |
| 0     | 1     | 1       | 1       |
| 1     | 0     | 1       | 0       |
| 1     | 1     | 1       | 1       |

We can also abbreviate the truth table:

| **sel** | **out** |
| ------- | ------- |
| 0       | a       |
| 1       | b       |

Note that the showed one is a 2-way multiplexor because we select one out of two inputs.

### Demultiplexor (DMUX)

Takes a single output and outputs into a single destination out of all the possible, the other ones are set at 0.
Acts like the inverse of a MUX.

We have the following truth table for it:

| **in** | **sel** | **a** | **b** |
| ------ | ------- | ----- | ----- |
| 0      | 0       | 0     | 0     |
| 0      | 1       | 0     | 0     |
| 1      | 0       | 1     | 0     |
| 1      | 1       | 0     | 1     |
