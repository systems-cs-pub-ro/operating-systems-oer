# Data

From a program's perspective, data is represented by the variables it uses to store,
retrieve or compute information. From an operating systems point of view, data is
represented by the information stored in the memory hierarchy.

## Explain some stuff here

## Exercices

### Prerequisites

Install gdc:

```bash
sudo apt-get install gdc
```

### Memory allocation strategy

Navigate to the `memory-alloc` directory. It contains 3 implementations of the same program in different languages:
C, Python and D. The program creates a list of entries, each entry storing a name and an id.

#### C implementation

The C implementation manages the memory manually. You can observe that all allocations
are performed via `malloc` and the memory is freed using `free`. Arrays can be defined
as static (on the stack) or dynamic (a pointer to some heap memory). Stack memory need
not be freed, hence static arrays are automatically de-allocated. Heap memory, however,
is managed by the user, therefore it is the burden of the programmer to find the optimal
memory strategy. This offers the advantage that you can fine tune the memory usage
depending on your application, but this comes with a cost: more often than not, managing
memory is highly complex error-prone task.

#### Python implementation

The python implementation of the program has no notion of memory allocation. It simply
defines the entry and uses a garbage collected list to store the elements. Notice how
the destructor is called automatically at some point when the garbage collector
deems that the list is not used anymore.

#### D implementation

The previous 2 examples have showcased extreme situations: full manual vs.
full automatic memory management. In D, both worlds are combined: variables
may be allocated manually on the stack/heap or allocated via the garbage collector
(for brevity, malloc allocation is not presented in this example). Arrays that
are allocated on the stack behave the same as in C, whereas array allocated with
the garbage collector mimic python lists. Classes are also garbage collected.

### Memory vulnerabilities
