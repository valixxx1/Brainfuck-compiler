# What is it?
This is a simple Brainfuck compiler that I have made in C. It isn't slow, I think it faster than Python.
# Quick Start
1. Find `./bf` file;
2. In the command line run `./bf hello_world.bf` and you will see "Hello, world!" (this example is from Wikipedia);
3. If the program doesn't run, try compile it again `gcc -o bf -O3 -Wall main.c`;
4. For other BF program, run `./bf your_program.bf`.
# How does the program work?
1. If there aren't any arguments, you will see the error "No arguments!";
2. If the program can't open your file, it will print error "File does not exist!";
3. If the program can't get some RAM, you will see "... buffer did not created!". Try to restart your computer.

When the program reads a file, for example:
```
++++++++++[>+++++++>++++++++++>+++<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.
```
it turns this file into a bytecode that looks like this:
```
+10
[0
>1
+7
 . . .
```
and then interpretate it. I think it's a new way for Brainfuck compilers. In the file main.c there is the code of this compiler, so you can read it (I know that it's a very hard to read it :(  ).
