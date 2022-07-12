# Data

Data represents information that is to be processed to produce a final result or more data.
Computers store, retrieve and compute data. This process involves 4 entities: the programmer, the programming language, the operating system and the hardware.

From a programmer's perspective, data is represented by the variables.
These are declared and utilized depending on the rules of the programming language that is employed.
The programming language analyzes the use of these variables and outputs code that uses an interface provided by the operating system.
This interface offers the possibility to allocate/deallocate different variables in certain memory regions.
Next, the operating system manages the execution of the program and provides the actual physical addresses that are used to interact with the data.

Moreover, the operating system governs the competing access of multiple programs to memory ensuring that a program does not have access to a different programs memory.

## Memory regions

## Ease of use, Security, Performance

## Strategies on memory allocation
### Manual memory management
### Automatic memory management
### Hybrid approach


Although the OS

To better manage a programs memory, the operating systems creates an address space for each process.
The address space is compartmentalized in 6 different zones:

1. Stack
2. Heap
3. Data
4. Bss
5. Rodata
6. Text



## Explain some stuff here

## Exercices

### Memory allocation strategy

Navigate to the `memory-alloc` directory. It contains 3 implementations of the same program in different languages:
C, Python and D. The program creates a list of entries, each entry storing a name and an id.
The purpose of this exercise is to present the different strategies that programming languages adopt to manage memory.

#### C implementation

The C implementation manages the memory manually.
You can observe that all allocations are performed via `malloc` and the memory is freed using `free`.
Arrays can be defined as static (on the stack) or dynamic (a pointer to some heap memory).
Stack memory need not be freed, hence static arrays are automatically de-allocated.
Heap memory, however, is managed by the user, therefore it is the burden of the programmer to find the optimal memory strategy.
This offers the advantage that you can fine tune the memory usage depending on your application, but this comes with a cost: more often than not, managing memory is a highly complex error-prone task.

#### Python implementation

The python implementation of the program has no notion of memory allocation.
It simply defines variables and the garbage collector takes care of allocating and deallocating memory.
Notice how the destructor is called automatically at some point when the garbage collector deems that the list is not used anymore.
Garbage collection lifts the burden of memory management from the user, however, it may be unsuitable for certain scenarios.
For example, real-time applications that need to take action immediately once a certain event occurs cannot use a garbage collector. That is because the GC usually stops the application to free dead objects.

#### D implementation

The previous 2 examples have showcased extreme situations: full manual vs. full automatic memory management.
In D, both worlds are combined: variables may be allocated manually on the stack/heap or allocated via the garbage collector (for brevity, malloc allocation is not presented in this example).
Arrays that are allocated on the stack behave the same as in C, whereas array allocated with the garbage collector mimic python lists. Classes are also garbage collected.

### Memory vulnerabilities

The purpose of this exercise is to provide examples on how memory corruption may occur and what are the safety guards implemented by different programming languages.
Navigate to the `memory-vuln` directory.
It features 3 files, each showcasing what happens in case of actions that may lead to memory corruption.

#### C implementation

The C implementation showcases some of the design flaws of the language can lead to memory corruption.

The first example demonstrates how a pointer to an expired stack frame may be leaked to an outer scope.
The C language does not implement any guards against such behavior, although dataflow analysis could be used to detect such cases.

The second example highlights the fact that C does not check any bounds when performing array operations.
This leads to all sorts of undefined behavior.
In this scenario some random memory is overwritten with `5`.
The third example exhibits a manifestation of the previous design flaw where the return address of the `main` function is overwritten with `0`, thus leading to a segmentation fault.

Although today it seems obvious that such behavior should not be accepted, we should take into account that the context in which the C language was created was entirely different than today.
At that time the resource constraints - DRAM memory was around a few KBs, operating systems were at their infancy, branch predictors did not exist etc. - were overwhelming.
Moreover, security was not a concern because the internet basically did not exist. As a consequence, the language was not developed with memory safety in mind.

#### Python implementation

Technically, it is not possible to do any memory corruption in python (that is if you avoid calling C functions from it).
Pointers do not formally exist and any kind of array access is checked to be within its bounds.
The example simply showcases what happens when an out of bounds access is performed - an IndexError is thrown and execution halts.

#### D implementation

The D implementation uses almost the same code as the C implementation, but suffers from minor syntax modidications.
In essence, the two implement the same logic.
When compiling this code, it can be observed that the D compiler notices at compile time that an out of bounds access is performed.
This makes sense, since a static array cannot modify its length and therefore the compiler has all the information to spot the mistake.
The only way to make the code compile si to comment the faulting lines or to replace the out of bounds index with a corect one.
After doing so, the program compiles and we can see that memory corruption occurs.
However, D also has safety checks, however, these are not performed by default.
To enable such checks, the user must annotate a function with the `@safe` keyword:

```d
int* bad() @safe
```

By doing so, the mechanical checks are enabled and a new set of criteria needs to be followed for the code to be accepted.
Taking the address of a local, doing pointer arithmentics, reinterpret casts, calling non-`@safe` functions etc. are not allowed in `@safe` code.
If any of these unsafe features are manully proven to be safe, the `@trusted` keyword may be used to disable the checks but still consider the code `@safe`.
This is to allow writting system code which by its nature is unsafe.

### Memory corruption

For this exercise you will need to identify the programming mistake that makes it possible to corrupt memory.
Navigate to the `memory-corruption` folder.
Inspect the source file `segfault.c`.

1. What does the program do? (this could be a quiz in the final form)
2. Compile and run it. What happens?
3. Debug the program and find the line that causes the segfault. (Note: although using printfs is a viable option, we strongly suggest you use gdb)
4. Fix the program.
5. Analyze the corresponding python and D implementation.
What is the expected result in each case?
Why?
Run the programs and see what happens.



