
# Memory Segments

As we know, the VM Code is a middle language between the high-level language Jack, and the low level machine language.
This means that we need to "adapt" our VM to possible features included in the Jack language, for example, if we implement Object Oriented Programming, we will have *at least* the following types of variables:

- Argument
- Local
- Static

We can't store all of them at the same place, because we would get lost at where one type finishes and the other one starts.

To fix this we will use the known as `Memory Segments`, this will allow us to "separate" our memory into different pieces, each one for a use case.

Following the previous example we will have three memory segments, using this method we will be able to keep track of every variable in the Jack language, while maintaining the simplicity in the low level language.

Those memory segments will work in together with the stack, in which now we will have to specify the segment to load from, and the index of that segment, so, as an example instruction `push argument 2`, this instruction will load the value inside the 3rd address in the `argument` segment to the stack.

For the purpose of this course we will have the following memory segments:

- local
- argument
- this
- that
- constant
- static
- pointer
- temp

