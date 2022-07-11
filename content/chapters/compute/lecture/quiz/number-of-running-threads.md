## Question Text

What is the maximum number of threads that can be in the RUNNING state at any time?

## Question Answers

- All of them
- Only one
- It depends on the ISA
+ As many as the number of CPU cores

## Feedback

A RUNNING thread needs a CPU core on which to run.
Therefore, we cannot have more threads in the RUNNING state than the number of CPU cores.