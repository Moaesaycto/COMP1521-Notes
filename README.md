# **COMP1521 Notes**

**Type:** Educational Code Collection · **Tech Stack:** C, MIPS Assembly · **Status:** Completed

## **Overview**

A set of programs written while studying **COMP1521 (Computer Systems Fundamentals)**, showcasing low-level programming in **C** and **MIPS Assembly**. The repository was used to practise for exams and to demonstrate understanding of threads, file operations, bitwise logic, and assembly functions.

## **C Programs**

* `threads.c`: Multithreaded computation using `pthread`, mutexes, and shared data structures.
* `bitwise.c`: Implements bitwise manipulation utilities (`get_bit`, `change_bit`, binary and hex output).
* `file.c`: Demonstrates file I/O: find-and-replace, byte counting, and random access with `fseek`.
* `pipe.c`: Uses POSIX pipes and `posix_spawn` to capture and display subprocess output.
* `processes.c`: Examples of `fork`, `exec`, `system`, and `popen` for process creation and communication.
* `test.c`: UTF-8 string reversal and manipulation with careful byte-level handling.

## **MIPS Programs**

* `simple.s`: Reads numbers and a command (`s` for sum, `p` for product) then outputs the computed result.
* `function.s`: Demonstrates MIPS function calls, stack frames, and arithmetic via a manual summation routine.

## **Purpose**

To solidify understanding of low-level systems programming concepts by implementing direct memory, file, and process operations in C and MIPS assembly.
