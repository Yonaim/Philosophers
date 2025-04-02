# Philosophers

`Philosophers` is a personal study project implementing the classic Dining Philosophers problem using threads and synchronization primitives in C. The project focuses on understanding multithreading, synchronization, and resource management to avoid deadlocks and starvation.

## Project Purpose

- Learn and practice concurrent programming and thread synchronization.
- Implement mutexes and semaphores to manage resources.
- Avoid common concurrency problems like deadlock, starvation, and race conditions.

## The Dining Philosophers Problem

- Philosophers sit at a circular table.
- There is one fork between each philosopher.
- Philosophers alternate between thinking, eating, and sleeping.
- To eat, each philosopher must pick up two forks (left and right).
- Forks must be managed to avoid deadlocks and ensure fairness.

## Key Objectives

- Ensure no philosopher dies of starvation.
- Guarantee no deadlocks or race conditions occur.
- Optimize the program for robustness and efficiency.

## Compilation

Clone and compile the project using the provided Makefile:

```bash
git clone https://github.com/Yonaim/Philosophers.git
cd Philosophers
make
```

## Usage

Run the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Number of philosophers and forks.
- `time_to_die`: Time (in ms) before a philosopher dies without eating.
- `time_to_eat`: Time (in ms) a philosopher spends eating.
- `time_to_sleep`: Time (in ms) a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]`: Optional, to specify meal count.

## Example

```bash
./philo 5 800 200 200 7
```

This will create 5 philosophers who must eat at least 7 times each.

## Concepts Explored

- Threads (`pthread`)
- Mutexes and Semaphores
- Deadlock Prevention
- Race Condition Avoidance
