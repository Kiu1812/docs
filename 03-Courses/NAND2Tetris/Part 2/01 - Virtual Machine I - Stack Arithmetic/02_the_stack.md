
# The Stack


The stack is, as the name suggests, a Stack of values, one "on top" of another. Generally in physical stacks of elements, like plates for example, you could lift some of them up, place one in the middle, and then leave the ones lifted on top of it, but in this digital stack we are not allowed to do so.

In a digital stack like this one we are only allowed to `push` and `pop` elements from the top of it. This means that our stack will be a LIFO or `Last In First Out` stack.

We need a pointer to know the current memory location of the stack, which is usually called the `Stack Pointer`.

Using this same stack we can perform some arithmetic operations, for example, we can `add` from it, this action will pop the first two top values, add them together, and then push the result into the stack.
Same can happen with the `neg` operation, which will pop one value from the stack, negate it's value, and then push the result again.

Logical operations are also supported, if we have two boolean values next to each other, we can perform operations like `or`, `and` or `not`.