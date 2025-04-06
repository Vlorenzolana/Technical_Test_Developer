# Technical_Test_Developer
# COMPILING AND EXEC INSTRUCTIONS
--------------------------------
# addnum – Multithreaded Even/Odd Number Separator in C

A modular C program using POSIX threads to generate random numbers concurrently, separate them into even and odd lists, and manage thread-safe access with read/write locks (`pthread_rwlock_t`).

## Features

- ✅ **Multithreaded number generation**
- ✅ **Thread-safe shared memory access **
- ✅ **READ-WRITE optimization ensured with pthread_rwlock_t locks.**
- ✅ **Separation into even/odd number lists**
- ✅ **Graceful signal handling (SIGINT / SIGQUIT)**
- ✅ **Validated config file input**
- ✅ **Modular source structure**
- ✅ **VALGRIND-tested , clean memory management**
- ✅ **UNIT TEST and Makefile test target**
- ✅ **User-friendly `Makefile` & runtime logs**

---

## Project Structure

<pre>
.
├── inc/
│   └── addnum.h
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── addnum.c
│   ├── utils.c
│   └── sighandler.c
├── test/
│   └── test_addnum.c
├── configfile/
│   └── cfg.txt
├── obj/                  ← created automatically
├── Makefile              ← 💡 this file
└── README.md

</pre>


---

## Build Instructions

### ✅ Compile the Project

```bash
make
make re
make valgrind
---

## Build Instructions

### ✅ Compile the Project

```bash
make

### ✅ Rebuild From Scratch

make re

### ✅  Clean the Project

make clean

### ✅ Help

make help

### ✅  Run the Program

./addnum -f configfile/cfg.txt

Or via:

make run

### ✅ Run Tests

make test

---

## Default config file:
     configfile/cfg.txt
     
### Configuration File Format

Configuration must follow a key = value format (case-insensitive keys allowed):

numbers_per_thread = 10
thread_num = 4

    numbers_per_thread: how many random numbers each thread will generate (max: 1000)

    thread_num: how many threads to spawn (max: 100)

## Limits:

    numbers_per_thread <= 1000

    thread_num <= 100

# Example file path: configfile/cfg.txt