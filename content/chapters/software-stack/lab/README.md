# Software Stack

Software comprises of code and data that is loaded in memory and used by the CPU.
Code means instructions that are to be fetched by the CPU, decoded and executed.
This is called **machine code**, i.e. binary instructions that are understood by the CPU.

So, when compared to hardware, **software is highly flexible**.
We can tie together specific instructions to handle a given task and run them on hardware (CPU, memory, I/O).
Different pieces of these instructions solve different tasks and run on the same hardware.
Moreover, these pieces of instructions can be duplicated and run on different pieces of hardware, thus providing **software reusability**.
All we are left with is creating those pieces of instructions, also called programs.

The most direct way is to write programs in machine code.
We check the CPU understanding of instructions (also called the ISA - *Instruction Set Architecture*) and then we write the binary (machine code) instructions for our program.
This is how things happened in the early days of computing, when [punched cards](https://en.wikipedia.org/wiki/Punched_card) were used.
Obviously, this is cumbersome, error prone and a mess to maintain, update and reuse.

The next step was to use assembly language.
Assembly language is a human-readable variant of machine code, that is more easily written.
Assembly language programs are assembled into machine code that is then loaded in memory and run on the CPU.
While this makes program writing easier, it still is difficult to maintain.

So higher-level programming languages were devised.
These programming languages provide a set of instructions that are closer to natural language.
This way, programs can be relatively easy written, providing **fast software development**.
Programs are compiled intro corresponding assembly language code, that is then assembled into machine code, that is then loaded in memory and run on the CPU.
Maintenance is simplified and other people can contribute to existing programs.
Another important feature of higher-level programming languages is **portability**: the same program can be compiled and assembled to run on different architectures.

In summary, software has intrinsic characteristics:
* flexibility: We can (easily) create new pieces of software.
  Little is required, we don't need raw materials as in the case of hardware or housing or transportation.
* reusability: Software can be easily copied to new systems and provide the same benefits there.

Other characteristics are important to have, as they make life easier for both users and developers of software:
* portability: This is the ability to build and run the same program on different computing platforms.
  This allows a developer to write the application code once and then run it everywhere.
* fast development: We want developers to be able to write code faster, using higher-level programming languages.

The last two characteristics rely on two items:
* higher-level programming languages: As discussed above, a compiler will take a higher-level program and transform it into binary code for different computing platforms, thus providing portability.
  Also, it's easier to read (comprehend) and write (develop) source code in a higher-level programming language, thus providing fast development.
* software stacks: A software stack is the layering of software such that each lower layer provides a set of features that the higher layer can directly use.
  This means that there is no need for the higher layer to reimplement those features;
  this provides fast development: focus on only the newer / required parts of software.

  Also, each lower layer provides a generic interface to the higher layer.
  This generic interfaces "hides" possible differences in the even lower layers.
  This way, a software stack ensures portability across different other parts of software (and hardware as well).
  For example, the standard C library, that we will present shortly, ensures portability across different operating systems.

TODO: Diagram of generic software stack

TODO: Quiz

## Modern Software Stacks

Most modern computing systems use a software stack such as the one in the figure below:

TODO: modern software stack

This modern software stack allows fast development and provides a rich set of applications to the user.

The basic software component is the **operating system** (OS) (technically the operating system **kernel**).
The OS provides the fundamental primitives to interact with hardware (read and write data) and to manage the running of applications (such as memory allocation, thread creation, scheduling).
These primitives form the **system call API** or **system API**.
An item in the system call API, i.e. the equivalent of a function call that triggers the execution of a functionality in the operating system, is a **system call**.

The system call API is well defined, stable and complete: it exposes the entire functionality of the operating system and hardware.
However, it is also minimalistic with respect to features and it provides a low-level (close to hardware) specification, making it cumbersome to use and **not portable**.

Due to the downsides of the system call API, a basic library, the **standard C library** (also called **libc**), is built on top of it.
The standard C library wraps the system call APIs and provides an easier-to-use and partially portable interface.
Because the system call API uses an OS-specific calling convention, the standard C library typically wraps each system call into an equivalent function call, following a portable calling convention.
More than these wraps, the standard C library provides its own API that is typically portable.
Part of the API exposed by the standard C library is the **standard C API**, also called **ANSI C** or **ISO C**;
this API is typically portable across all platforms (operating systems and hardware).
Despite its name, the standard C library provides APIs that may not be standard, but particular to the underlying operating systems, such as system call wrapper functions.

The existence of the standard C library is reliant on the C programming language, a very simple programming language and very close to the low-level view of the memory.
Because of this, most higher-level and more feature rich programming languages rely on the C library.
Each programming language typically provides a standard library of its own together with a runtime library, both of which rely on the C library.
The standard C library is used to develop programs in the respective programming language.
While the runtime library is transparent to the user and its used during runtime to provide the features required (such as exception handling, bounds checking, garbage collection etc.).

Other topic-specific libraries (image processing, encryption, compression, regular expression handling etc.) are then built on top of the standard C library and / or specific programming language libraries.
These contribute to the overall set of APIs made available to the developer.

With these APIs made available (system call API, C library API, programming language API, topic-specific APIs), the developer can rapidly create (portable) applications that are then provided to users.
Applications benefit from the larger set of libraries available on a system;
in other words, they employ **software reusability**.

In the rest of this chapter, we will analyze the software stack for different applications, we will build and run different types of applications and libraries and we will take a peek in the implementation of modern operating systems and low-level components.

## Analyzing the Software Stack

To get a better grasp on how the software stack works, let's do a bottom-up approach:
we build and run different programs, that start of by using the system call API (the lowest layer in the software stack) and progressively use higher layers.

### Basic System Calls

The `support/basic-syscall/` folder stores the implementation of a simple program in assembly language for the x86_64 (64 bit) architecture.
The program invokes two system calls: `write` and `exit`.
The program is duplicated in two files using the two x86 assembly language syntaxes: the Intel / NASM syntax (`hello.asm`) and the AT&T / GAS syntax (`hello.s`).

The implementation follows the [x86_64 Linux calling convention](https://x64.syscall.sh/):
* system call ID is passed in the `rax` register
* system call arguments are passed, in order, in the `rdi`, `rsi`, `rdx`, `r10`, `r8`, `r9` registers

Let's build and run the two programs:

```Bash
student@os:~/.../lab/support//basic-syscall$ ls
hello.asm  hello.s  Makefile

student@os:~/.../lab/support/basic-syscall$ make
nasm -f elf64 -o hello-nasm.o hello.asm
cc -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none  hello-nasm.o   -o hello-nasm
gcc -c -o hello-gas.o hello.s
cc -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none  hello-gas.o   -o hello-gas

student@os:~/.../lab/support/basic-syscall$ ls
hello.asm  hello-gas  hello-gas.o  hello-nasm  hello-nasm.o  hello.s  Makefile

student@os:~/.../lab/support/basic-syscall$ ./hello-nasm
Hello, world!
student@os:~/.../lab/support/basic-syscall$ ./hello-gas
Hello, world!
```

The two programs end up printing the `Hello, world!` message at standard output by issuing the `write` system call.
Then they complete their work by issuing the `exit` system call.

We use `strace` to inspect system calls issued by a program:

```Bash
student@os:~/.../lab/support/basic-syscall$ strace ./hello-nasm
execve("./hello-nasm", ["./hello-nasm"], 0x7ffc4e175f00 /* 63 vars */) = 0
write(1, "Hello, world!\n", 14Hello, world!
)         = 14
exit(0)                                 = ?
+++ exited with 0 +++
```

There are three system calls captured by `strace`:
* `execve`: this is issues by the shell to create the new process
* `write`: called by the program to print `Hello, world!` to standard output
* `exit`: to exit the program

This is the most basic program for doing system calls.
Given that system calls require a specific calling convention, their invocation can only be done in assembly language.
Obviously, this is not portable (specific to a given CPU architecture, x86_64 in our case) and too verbose and difficult to maintain.
For portability and maintainability, we require a higher level language, such as C.
In order to use C, we need function wrappers around system calls.

#### Practice

Update the `hello.asm` and / or `hello.s` files to print both `Hello, world!` and `Bye, world!`.
This means adding another `write` system call.

TODO: Quiz

### System Call Wrappers

The `support/syscall-wrapper/` folder stores the implementation of a simple program written in C (`main.c`) that calls the `write()` and `exit()` functions.
The functions are defined in `syscall.asm` as wrappers around corresponding system calls.
Each function invokes the corresponding system call using the specific system call ID and the arguments provided for the function call.

The implementation of the two wrapper functions in `syscall.asm` is very simple, as the function arguments are passed in the same registers required by the system call.
This is because of the overlap of the first three registers for the [x86_64 Linux function calling convention](https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI) and the [x86_64 Linux system call convention](https://x64.syscall.sh/).

`syscall.h` contains the declaration of the two functions and it's included in `main.c`.
In this way, C programs can be written that make function calls that end up making system calls.

Let's build, run and trace system calls for the program:

```Bash
student@os:~/.../lab/support/syscall-wrapper$ ls
main.c  Makefile  syscall.h  syscall.s

student@os:~/.../lab/support/syscall-wrapper$ make
gcc -c -o main.o main.c
nasm -f elf64 -o syscall.o syscall.s
cc -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none  main.o syscall.o   -o main

student@os:~/.../lab/support/syscall-wrapper$ ls
main  main.c  main.o  Makefile  syscall.h  syscall.o  syscall.s

student@os:~/.../software-stack/lab/syscall-wrapper$ ./main
Hello, world!

student@os:~/.../lab/support/syscall-wrapper$ strace ./main
execve("./main", ["./main"], 0x7ffee60fb590 /* 63 vars */) = 0
write(1, "Hello, world!\n", 14Hello, world!
)         = 14
exit(0)                                 = ?
+++ exited with 0 +++
```

The trace is similar to the previous example, showing the `write` and `exit` system calls.

By creating system call wrappers as C functions, we are now relieved of the burden of writing assembly language code.
Of course, there has to be an initial implementation of wrapper functions written in assembly language;
but, after that, we can use C only.

#### Practice

Update the files in the `support/syscall-wrapper/` folder to make available the `read` system call as a wrapper.
Make a call to the `read` system call to read data from standard input in a buffer.
The call `write` to print data from that buffer.

We can see that it's easier to have wrapper calls and write most of the code in C than in assembly language.

TODO: Quiz

### Common Functions

By using wrapper calls, we are able to write our programs in C.
However, we still need to implement common functions for string management, working with I/O, working with memory.

The simple attempt is to implement these functions and then reuse the implementation each time we require them.
So we would implement `printf()` or `strcpy()` or `malloc()` once in a C source code file, and reuse them.
This saves us time (we don't have to reimplement) and gives us the opportunity to constantly improve one implementation and then reuse the implementation;
there will only be one implementation that we update to increase its safety, efficiency or performance.

The `support/common-functions/` folder stores the implementation of string management functions, in `string.c` and `string.h` and of printing functions in `printf.c` and `printf.h`.
The `printf` implementation is [this one](https://github.com/mpaland/printf).

There are two programs: `main_string.c` showcases string management functions, `main_printf.c` also showcases the `printf()` function.

`main_string.c` depends on the `string.h` and `string.c` files that implement the `strlen()` and `strcpy()` functions.
In the `main_string.c` file we call `strlen()` and `strcpy()`;
these functions are implemented in `string.c`.
We print messages using the `write()` system call wrapper implemented in `syscall.s`

Let's build and run the program:

```Bash
student@os:~/.../lab/support/common-functions$ make main_string
gcc -fno-stack-protector   -c -o main_string.o main_string.c
gcc -fno-stack-protector   -c -o string.o string.c
nasm -f elf64 -o syscall.o syscall.s
gcc -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none  main_string.o string.o syscall.o   -o main_string

student@os:~/.../lab/support/common-functions$ ./main_string 
Destination string is: warhammer40k

student@os:~/.../lab/support/common-functions$ strace ./main_string
execve("./main_string", ["./main_string"], 0x7ffd544d0a70 /* 63 vars */) = 0
write(1, "Destination string is: ", 23Destination string is: ) = 23
write(1, "warhammer40k\n", 13warhammer40k
)          = 13
exit(0)                                 = ?
+++ exited with 0 +++
```

When using `strace` we see that only the `write()` system call wrapper triggers a system call.
There are no system calls triggered by `strlen()` and `strcpy()` as can be seen in their implementation.

In addition, `main_printf.c` depends on the `printf.h` and `printf.c` files that implement the `printf()` function.
There is a requirement to implement the `_putchar()` function;
we implement it in the `main_printf.c` file using the `write()` syscall call wrapper.
The `main()` function `main_printf.c` file contains all the string and printing calls.
`printf()` offers a more powerful printing interface, allowing us to print addresses and integers.

Let's build and run the program:

```Bash
student@os:~/.../lab/support/common-functions$ make main_printf
gcc -fno-stack-protector   -c -o printf.o printf.c
gcc -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none  main_printf.o printf.o string.o syscall.o   -o main_printf

student@os:~/.../lab/support/common-functions$ ./main_printf
[before] src is at 00000000004026A0, len is 12, content: "warhammer40k"
[before] dest is at 0000000000603000, len is 0, content: ""
copying src to dest
[after] src is at 00000000004026A0, len is 12, content: "warhammer40k"
[after] dest is at 0000000000603000, len is 12, content: "warhammer40k"

student@os:~/.../lab/support/common-functions$ strace ./main_printf
execve("./main_printf", ["./main_printf"], 0x7ffcaaa1d660 /* 63 vars */) = 0
write(1, "[", 1[)                        = 1
write(1, "b", 1b)                        = 1
write(1, "e", 1e)                        = 1
write(1, "f", 1f)                        = 1
write(1, "o", 1o)                        = 1
write(1, "r", 1r)                        = 1
write(1, "e", 1e)                        = 1
write(1, "]", 1])                        = 1
write(1, " ", 1 )                        = 1
write(1, "s", 1s)                        = 1
write(1, "r", 1r)                        = 1
[...]
```

We see that we have greater printing flexibility with the `printf()` function.
However, one downside of the current implementation is that it makes a system call for each character.
This is inefficient and could be improved by printing a whole string.

#### Practice

Enter the `support/common-functions/` folder and go through the practice items below.

1. Update `string.c` and `string.h` to make available the `strcat()` function.
   Call that function in `main_string.c` and print the result.

1. Update the `main_printf.c` file to use the implementation of `sprintf()` to collect information to be printed inside a buffer.
   Call the `write()` function to print the information.
   The `printf()` function will no longer be called.
   This results in a single `write` system call.

Using previously implemented functions allows us to more efficiently write new programs.
These functions provide us with extensive features that we use in our programs

TODO: Quiz

## Arena

Go through the practice items below to hone your skills in working with layers of the software stack.

### System Calls

Enter the `support/basic-syscall/` folder and go through the practice items below.
If you get stuck, take a sneak peak at the solutions in the `solution/basic-syscall/` folder.

For debugging, use `strace` to trace the system calls from your program and make sure the arguments are set right.

1. Update the `hello.asm` and / or `hello.s` files to pause the execution of the program before the `exit` system call.

   You need to make the `sys_pause` system call, with no arguments.
   Find its ID [here](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/).

1. Update the `hello.asm` and / or `hello.s` files to read a message from standard input and print it to standard output.

   You'll need to define a buffer in the `data` or `bss` section.
   Use the `read` system call to read data in the buffer.
   The return value of `read` (placed in the `rax` register) is the number of bytes read.
   Use that value as the 3rd argument or `write`, i.e. the number of bytes printed.

   Find the ID of the `read` system call [here](https://x64.syscall.sh/).
   To find out more about its arguments, see [its man page](https://man7.org/linux/man-pages/man2/read.2.html).
   Standard input descriptor is `0`.

1. **Difficult**: Port the initial program to ARM on 64 bits (also called **aarch64**).

   Use the skeleton files in the `arm/` folder.
   Find information about the aarch64 system calls [here](https://arm64.syscall.sh/).

1. Create your own program, written in assembly, doing some system calls you want to learn more about.
   Create a Makefile for that program.
   Run the resulting program with `strace` to see the actual system calls being made (and their arguments).

### System Call Wrappers

Enter the `support/syscall-wrapper/` folder and go through the practice items below.

1. Update the files in the `syscall-wrapper/` folder to make available the `getpid` system call as a wrapper.
   Create a function with the signature `void itoa(int n, char *a)` that converts an integer to a string.
   For example the `1234` turn to the `"1234"` string (NUL-terminated, 5 bytes length).

### Common Functions

Enter the `support/common-functions/` folder and go through the practice items below.

1. Update the `putchar()` function in `main_printf.c` to implement a buffered functionality of `printf()`.
   Characters passed via the `putchar()` call will be stored in a predefined static global buffer.
   The `write()` call will be invoked when a newline is encountered or when the buffer is full.
   This results in a reduced number of `write` system calls.

1. Update the `main_printf.c` file to also feature a `flush()` function that forces the flushing the static global buffer and a `write` system call.
