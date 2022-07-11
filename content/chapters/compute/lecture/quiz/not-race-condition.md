## Question Text

What type of parallel actions never cause race conditions?

## Question Answers

- Only reads
- Reads and writes
+ Reads and executions
- All parallel actions can cause race conditions

## Feedback

Race conditions only appear when a thread **writes** and another thread depends on the write / update of the other thread.
Other types of access (read and execute) do not modify the data, thus they do not cause race conditions.
