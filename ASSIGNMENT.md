# Assignment 4: Stacks II

## Description

In this assignment, you will build a new Stack implementation using the design ideas from Stacks I, but with a more realistic data type, dynamic storage, overloaded constructors, and modular testing.

Stacks I used a fixed-size array of integers and deliberately kept all testing in one monolithic script. Stacks II advances that design in two important ways:

1. the Stack will store structured `Data` objects in dynamically allocated storage; and
2. testing must be moved out of `main.cpp` and organized into appropriate testing functions.

This is a new project. Do **not** copy the Stacks I repository into this assignment. Use your completed Stacks I work and the instructor reference solution, when it becomes available, as **design references**.

You are responsible for creating the project files, implementing the Stack, designing the testing architecture, thoroughly testing the program, and documenting your work.

---

## Learning Objectives

After completing this assignment, you should be able to:

- use a `struct` to represent a self-contained unit of related data;
- use a header-only data definition across multiple modules, `data.h`;
- distinguish between passing by value and passing by reference;
- use references to provide structured output through a caller-owned object;
- dynamically allocate and release an array of objects;
- explain ownership and lifetime of dynamically allocated memory;
- implement overloaded constructors;
- validate constructor input and preserve object invariants;
- implement and use a destructor when a class owns dynamic memory;
- distinguish current object state from maximum capacity;
- organize a multi-file C++ project from a specification;
- separate testing from reporting;
- design testing functions that communicate results without printing;
- test stateful objects across meaningful transitions, boundaries, and failure conditions;
- verify that multiple objects maintain independent state;
- use Git to document the development process;
- use AI as a programming partner while remaining responsible for correctness.

---

## Background

You should complete or review the following before beginning this assignment:

- Stacks I
- interface vs. implementation
- header files and loose coupling
- structs and ADTs
- pointers and references
- value vs. reference
- dynamic memory
- ownership and object lifetime
- testing stateful objects
- course commenting standards
- course Git and commit standards
- course AI-use expectations

The official Stacks I reference solution will be released after the final Stacks I submission deadline. You may use it as a design reference, but Stacks II must be implemented as a clean new project.

---

## Starter Files

The repository contains only:

```text
ASSIGNMENT.md
ESSAY.md
data.h
```

You must create the rest of the project yourself.

You must create at least the following files:

```text
main.cpp
main.h
stack.cpp
stack.h
test.cpp
test.h
README.md
.gitignore
```

Do not rename the required files.

---

## Provided `data.h`

The provided `data.h` defines the record stored by the Stack:

```cpp
struct Data {
    int id;
    std::string information;
};
```

Do **not** modify `data.h`.

`data.h` is intentionally a standalone header. It defines a shared data type and does not require a corresponding `.cpp` file.

Include `data.h` in `stack.h` so the `Data` type is available to the Stack interface and implementation.

---

## Stack Requirements

Your Stack must store `Data` objects rather than integers.

The Stack must use dynamically allocated contiguous storage.

The private attributes must include these and **only these**:

```cpp
Data* stack;
int top;
int capacity;
```

The Stack must **not** use:

- `std::stack`
- `std::vector`
- another container class
- an array of `Data*`
- dynamic allocation of individual `Data` objects

The Stack owns one dynamically allocated array of `Data`.

---

## Required Public Interface

Your `Stack` class must provide the following public interface:

```cpp
Stack();
Stack(int);
~Stack();

bool push(int, std::string&);
bool pop(Data&);
bool peek(Data&);
bool isEmpty();
int getCapacity();
```

As required by the course header-file standard, omit parameter names from declarations in `stack.h`.

Do not add public attributes.

Do not return pointers or references to private Stack storage.

---

## Constructors

### Default Constructor

The default constructor:

```cpp
Stack();
```

must:

- set the capacity to `SIZE`, defined in `stack.h`;
- initialize the Stack to empty;
- dynamically allocate an array of `Data` large enough to hold `SIZE` elements.

Use:

```cpp
#define SIZE 10
```

for the default capacity.

### Parameterized Constructor

The overloaded constructor:

```cpp
Stack(int);
```

allows the caller to request a Stack capacity.

If the requested capacity is **2 or greater**, use the requested capacity.

If the requested capacity is **less than 2**, use `SIZE` instead.

The constructor must then dynamically allocate the array using the validated capacity.

For example:

```cpp
Stack a;
Stack b(20);
Stack c(1);
```

should create:

- `a` with capacity `SIZE`;
- `b` with capacity `20`;
- `c` with capacity `SIZE`.

The object must never be created with an invalid capacity. It is your responsibility to enforce this requirement.

---

## Destructor

Because the Stack owns dynamically allocated memory, it must release that memory when the object is destroyed.

Implement:

```cpp
~Stack();
```

The destructor must correctly release the dynamically allocated array using the appropriate array form of `delete`.

The Stack owns its storage. The caller does not.

---

## `getCapacity()`

Implement:

```cpp
int getCapacity();
```

This accessor returns the maximum number of `Data` objects the Stack can hold.

Do not confuse **capacity** with the number of items currently stored.

---

## `push()`

Implement:

```cpp
bool push(int, std::string&);
```

The caller supplies the information to be stored.

The Stack must package that information into a `Data` object internally and store it in the Stack.

If space is available:

- create or populate the required `Data`;
- store it at the top of the Stack;
- update Stack state;
- return `true`.

If the Stack is full:

- do not modify the Stack;
- return `false`.

The Stack must not store an address to the caller's string.

The Stack stores its own `Data` object in its own allocated storage.

---

## `pop()`

Implement:

```cpp
bool pop(Data&);
```

If the Stack is not empty:

- copy the top `Data` into the caller-supplied `Data` object;
- remove that item from the logical Stack;
- update Stack state;
- return `true`.

If the Stack is empty:

- do not modify the caller's `Data`;
- do not modify Stack state;
- return `false`.

Do not return an address or pointer to the Stack's private storage.

The caller supplies the `Data` object to be filled.

---

## `peek()`

Implement:

```cpp
bool peek(Data&);
```

If the Stack is not empty:

- copy the top `Data` into the caller-supplied `Data` object;
- do **not** remove or modify the stored item;
- do not change Stack state;
- return `true`.

If the Stack is empty:

- do not modify the caller's `Data`;
- do not modify Stack state;
- return `false`.

Do not return an address or pointer to the Stack's private storage.

---

## `isEmpty()`

Implement:

```cpp
bool isEmpty();
```

Return `true` only when the Stack contains no items.

Otherwise return `false`.

---

## Single Entry / Single Exit

Continue following the course requirement of one entry and one exit per function or method.

Functions should have one and only one `return` statement.

Do not use early returns to simplify control flow.

Constructors and destructors do not return values.

---

## Header and Module Requirements

Follow the course interface/implementation standard.

Each `.cpp` file must have a corresponding `.h` file:

```text
main.cpp  <-> main.h
stack.cpp <-> stack.h
test.cpp  <-> test.h
```

`data.h` is a standalone header and does not require a `.cpp` file.

Use the course convention:

- declarations belong in headers;
- definitions belong in source files;
- module directives, constants, and required includes belong in the appropriate header;
- each `.cpp` includes its own header;
- dependencies should be explicit;
- do not rely on transitive includes;
- do not place method implementations in `stack.h`.

---

## Testing Architecture

Stacks I deliberately used one long monolithic test script in `main.cpp`.

That architecture is **not acceptable for Stacks II**.

Testing must be moved into `test.cpp` and declared through `test.h`.

You are responsible for deciding:

- how testing should be divided into meaningful functions;
- what parameters those functions need;
- what those functions should return or otherwise communicate;
- how `main()` should collect and report the results.

### Testing functions must not print.

Do **not** place `cout` statements inside testing functions to report `"pass"`, `"fail"`, test counts, or other test results.

Testing functions determine correctness.

`main()` is responsible for reporting results.

Your testing-function interfaces should communicate enough information for `main()` to report useful test results.

Do not simply cut and paste the old Stacks I test blocks into functions without redesigning the testing interface.

---

## Testing Requirements

There is **no behavioral autograder for this assignment**.

You are responsible for establishing that your implementation is correct.

Your testing must be thorough and must verify both successful operations and operations that are supposed to fail.

A test passes when the observed behavior matches the specification. For example:

- a push onto a full Stack should fail;
- a pop from an empty Stack should fail;
- a peek at an empty Stack should fail.

Those are successful tests when the operation correctly returns `false` and preserves state.

Your testing should include, at minimum:

- default-constructor behavior;
- valid custom capacity;
- invalid custom capacity falling back to `SIZE`;
- `getCapacity()`;
- empty Stack behavior;
- successful pushes;
- successful pops;
- successful peeks;
- LIFO ordering;
- `peek()` not changing Stack state;
- transitions from empty to partially full;
- transitions from partially full to full;
- overflow;
- transitions from full back toward empty;
- underflow;
- failed operations preserving Stack state;
- failed `pop()` and `peek()` not modifying the caller's `Data`;
- exact verification of both `Data.id` and `Data.information`;
- repeated transitions between states;
- systematic testing;
- randomized or stress testing where appropriate.

Do not treat "the program did not crash" as sufficient evidence of correctness.

---

## Multiple Stack Objects

Your testing must create and use at least three `Stack` objects at the same time (default, valid size passed, invalid size passed).

The objects must be tested in a way that demonstrates independent state.

For example, operations on one Stack must not change:

- the contents of another Stack;
- the top position of another Stack;
- the capacity of another Stack.

Use different capacities where appropriate.

Do **not** test this by copying one Stack object into another.

Copy construction and copy assignment for a class that owns dynamic memory are outside the scope of this assignment.

However many stacks you make, each stack must be tested fully.  For example, do not make one stack to test overflow, and another to test underflow, etc. Each stack you make must be tested fully to make sure it can handle all state transitions. You will need to make at least three `Stack` objects to test the two constructors.

Be careful with your testing design. Three stacks does not mean three times the code to test them. Remember the rule: Write one, use many.

---

## Dynamic Memory and Ownership

The Stack owns the array it allocates.

That means:

- allocation occurs inside the Stack;
- the Stack manages the array;
- the Stack releases the array in its destructor;
- callers must not receive pointers or references to private Stack storage.

Do not expose internal memory addresses.

Do not dynamically allocate individual `Data` objects for this assignment.

This assignment uses one dynamically allocated array of `Data`.

---

## Development Process

Develop the assignment incrementally.

Do not attempt to write the entire program before compiling or testing.

You must make at least **15 meaningful student-created program-development commits**.

A meaningful commit represents a coherent development step.

Examples might include:

```text
Create initial project structure
Implement default Stack constructor
Add parameterized constructor and validation
Implement dynamic Stack storage
Implement Data push behavior
Implement pop and peek for Data
Add constructor and capacity testing
Refactor testing into test module
Add independent Stack object tests
Add randomized state testing
```

These are examples only. You are responsible for choosing your own development sequence and commit messages.

Arbitrarily splitting one change into multiple commits does not make those commits meaningful.

README, ESSAY, and `.gitignore`-only changes do not count toward the minimum program-development commit requirement.

Compile and test regularly before committing.

Push your work to GitHub regularly.

---

## AI Use

AI use is expected and required.

You may use AI as:

- a tutor;
- a programming partner;
- a code reviewer;
- a debugging assistant;
- a testing critic;
- an explanation tool;
- a design critic.

AI-generated code is not automatically correct.

You remain responsible for:

- understanding the code;
- verifying the interface;
- checking dynamic-memory behavior;
- verifying ownership and cleanup;
- testing constructor validation;
- testing all Stack states and transitions;
- ensuring testing functions follow the assignment architecture;
- rejecting unnecessary complexity;
- confirming that every requirement is satisfied.

Your `ESSAY.md` must document your AI use and your evaluation of AI suggestions.

---

## Documentation and Commenting

All source and header files must follow the course commenting standard.

Use the course-required:

- file documentation;
- function and method documentation;
- appropriate explanatory comments;
- class/module organization.

Do not use excessive comments that merely restate obvious code.

---

## README

Create `README.md` from scratch.

Follow the course README guidelines.

At minimum, document:

- what the project does;
- how to build it;
- how to run it;
- the project file structure;
- the major design decisions;
- how testing is organized.

---

## `.gitignore`

Create an appropriate `.gitignore`.

Compiled executables and other generated build artifacts must not be committed to the repository.

---

## Building

Your program must build from the command line.

A normal build should be possible with either of these:

```bash
g++ main.cpp stack.cpp test.cpp -o stack
g++ -I. *.cpp -o stack
```

Run it with:

```bash
./stack
```

Do not depend on an IDE-specific project file to build or run the program.

---

## Final Verification

Before submitting:

1. Build the complete project from the command line.
2. Run the complete test suite.
3. Verify that all required behaviors are tested.
4. Verify constructor capacities and validation.
5. Verify multiple Stack objects maintain independent state.
6. Verify dynamic memory is released correctly.
7. Verify testing functions do not print.
8. Verify `main()` performs reporting.
9. Review `git status` and ensure the repository is clean.
10. Review `git log` and confirm at least 15 meaningful program-development commits.
11. Review the repository on GitHub and confirm all required files are present.
12. Confirm no executable or other generated build artifact is tracked.
13. Complete `README.md`.
14. Complete `ESSAY.md`.

---

## Submission

Submit the normal HTTPS URL of your completed GitHub repository through Blackboard.

There is **no behavioral autograding for this assignment**.

Your testing is part of the assignment and part of the evidence that your Stack works correctly.
