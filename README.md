# Philosophers

## Project Overview

This project is a simulation of the classic Dining Philosophers problem, implemented in C. It explores concepts of multi-threading, process synchronization, and resource allocation.

### The Problem

- A number of philosophers sit at a round table with a large bowl of spaghetti in the center.
- Philosophers alternatively eat, think, or sleep.
- There are as many forks on the table as there are philosophers.
- A philosopher needs two forks to eat spaghetti.
- After eating, they put the forks back on the table and start sleeping, then thinking again.
- The simulation stops when a philosopher dies of starvation.

### Key Challenges

1. **Concurrency**: Managing multiple philosophers as separate threads or processes.
2. **Deadlock Prevention**: Ensuring philosophers don't end up in a deadlock where each holds one fork and waits indefinitely for another.
3. **Resource Management**: Properly allocating and deallocating forks (resources) using mutexes or semaphores.
4. **Timing**: Accurately tracking time to determine when a philosopher should die if they haven't eaten.

## How to Run

### Compilation

1. Navigate to the project directory.
2. Run `make` to compile the program.

### Execution

Run the program with the following command:

```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

Parameters:
- `number_of_philosophers`: The number of philosophers and forks.
- `time_to_die` (in milliseconds): Time a philosopher can go without eating before dying.
- `time_to_eat` (in milliseconds): Time it takes for a philosopher to eat.
- `time_to_sleep` (in milliseconds): Time a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): If specified, simulation stops when all philosophers have eaten this many times.

Example:
```
./philo 5 800 200 200 7
```

This runs the simulation with 5 philosophers, where each philosopher has 800ms to start eating before they die, takes 200ms to eat, 200ms to sleep, and must eat at least 7 times.
