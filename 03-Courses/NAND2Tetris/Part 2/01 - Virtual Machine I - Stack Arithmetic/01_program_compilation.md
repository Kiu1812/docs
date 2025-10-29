
# Program Compilation Preview

In this course we will use the Jack programming language.

This language is based in Java, and, as it's father, it will use Tier 2 compilation.
In this type, instead of creating a compilator for each target device, we will create one that will translate from Jack language to **VM code** or **bytecode**. Then, this VM code will be able to run in any target device just with a Virtual Machine that supports it.

By doing this we are dividing the complex task of compilation to each device, into two smaller and simpler tasks.

In the first part of this course we created the Hack computer, in this first module we will create the Virtual Machine implementation, this is known as the back-end of our Jack programming language.

Later on, we will study, analyze and create the Jack language and it's compiler into our virtual machine, which is known as the front-end.