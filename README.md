# Model Checker

This is a simple stateless model checker that can be used to check the correctness of concurrent programs.

## Example programs

Below are some of the example programs that I'd like to check. The goal is to be able to pass in simple concurrent programs with integer variables, for example:

### Example 1: Simple Race Condition
```cpp
int x = 0, y = 0;

void thread1() {
    x = 1;
    y = 2;
}

void thread2() {
    y = 3;
    x = 4;
}
```

### Example 2: Read-Write Dependencies
```cpp
int x = 0, y = 0;

void thread1() {
    x = 1;
    y = x;
}

void thread2() {
    y = 2;
    x = y;
}
```

### Example 3: Multiple Threads
```cpp
int x = 0, y = 0, z = 0;

void thread1() {
    x = 1;
    y = 2;
}

void thread2() {
    y = 3;
    z = 4;
}

void thread3() {
    z = 5;
    x = 6;
}
```

The program should then parse the program, create an Execution Graph and then check for violations.

This doesn't use sequential consistency or checks the code in terms of interleavings, rather just enumerates all consistent execution graphs of a program.

## Challenges:

Generate all consistent execution graphs without:

1. Generating any inconsistent graphs
2. Generating the same graph multiple times
3. Storing the set of graphs that are already generated

## Key ideas

1. It suffices to start with initial (empty) graph and extend it gradually by adding one event at a time (in every possible way). Consistency can then be checked at every step. 
2. Introduce something called "revisit sets" to capture a subset of reads whose incoming reads-from edges may be changed when a write event is added to the graph. 
3. 