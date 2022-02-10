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


