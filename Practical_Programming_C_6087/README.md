course link : https://ocw.mit.edu/courses/6-087-practical-programming-in-c-january-iap-2010/

I have fairly good experience on C from work but no formal study from university so this notes will just capture the things that i might not know or find it interesting to note down 

## Lecture 1 - Introduction. Writing, compiling, and debugging C programs. Hello world.

- No range checking 
- Limited type safety at compile time 
- No type checking at runtime 
- `-Wall` enables most compiler warnings 
- probably we just use vscode provided gdb but these are good to know
- gdb ./hello.o
- Using GDB 
    - `break linenumber` - create breakpoint at specified line 
    - `break file:linenumber` - create breakpoint at line in file 
    - `run` - run program 
    - `c` - c`ontinue execution 
    - `next` - exectue next line 
    - `step` - execute next line or step into function 
    - `quit` - quit gdb
    - `print expression` - print current value of specified expression 
    - `help command` - in program help 
- Memory Debugging 
    - valgrind ./hello.o
- Strings are stored as char arrays and are terminated with \0 , special chars are specified using \ char
- macros can take arguments and be treated like functions `#define add2(x,y) ((x)+(y))`
- preprocessor macros :- #if ,#ifdef,#ifndef,#elif , etc:- 
    - The gcc option -Dname=value sets a preprocessor define that can be used  
- #pragma - preprocessor directive (akhil : used sometimes compiler optimizations ie. pragma pack 0 )
- #error , #warning - trigger a custom compiler warning 
- #undef msg - remove definition of message during compile time

## Lecture 2 - Variables, Datatypes and Operators
- C is weakly typed language. It allows implicit conversions as well as forced casting. 
- Depending on precision and range : short , default , long , float , double and char are used. 
- Individual sizes are machine and compiler dependent 

- Big Endian : the MSB occupy the lower address 
- Little Endian : LSB occupy the lower address . Used in x86 
- 0x - hex , 0 - Octal , 3UL - unsigned long , 3.14f - float , 3.14L - double 
- 1 = True , 0 = False 

## Lecture 3 - Control flow. Functions and modular programming. Variable scope. Static and global variables

- Blocks can substitute for simple statement , complied as single unit 
- Variables can be declared inside , no semicolon necessary at the end 
- C89/90 doesnt have boolean type , c99 bool type is available in stdbool.h
- Expression is non zero - true 
- Expression must be numeric  
- Extern Keyword 
    - Need to inform other sourcefiles about functions/global variables in somefile.c
    - for functions : put function prototypes in header file 
    - for variables : re-declare the global variable using the extern keyword in header file 
    - extern informs compiler that variable defined somewhere else 
    - enable access/modifying of global variable from other source files 
- Static variables 
    - Static keyword has two meanings depending on where the static variable is declared 
    - Outside the function , static variables/functions only visible within that file, not globallly (cannot be externed)
    - Inside a function , static variables : 
        - are still local to that function 
        - are initialized only during program initialization 
        - donot get re-initialized with each function call 

- Register Variables 
    - During execution , data processed in registers 
    - Explicitly store commonly used data in registers - minimize load/store overhead 
    - Can explicitly declare certain variables as registers using register keyword 
        - must be simple type (implementation dependent)
        - only local vars and function arguments eligible 
        - excess/unallowed register declarations ignored, compiled as regular variables 
        - Registers donot reside in addressed memory so pointer of a register variable is illegal 






















