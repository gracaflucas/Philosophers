# 🧠 Philosophers

**Philosophers** is a multithreaded C project from the 42 curriculum that simulates the classic **Dining Philosophers Problem**. It focuses on thread creation, synchronization, and avoiding concurrency issues like deadlocks and race conditions using the **pthread** library.

---

## ✨ Features

- **Concurrency**: Each philosopher is a separate thread.
- **Thread Synchronization**: Managed with mutexes to avoid race conditions.
- **Deadlock Avoidance**: Careful use of timing and lock order.
- **Simulation Goals**:
  - Philosophers alternate between thinking, eating, and sleeping.
  - They need two forks (mutexes) to eat.
  - The simulation ends when a philosopher dies (fails to eat in time) or when each philosopher has eaten a set number of times.

---

## 🛠 How It Works

- Each philosopher is implemented as a thread.
- Forks are represented by mutexes.
- A monitoring thread checks for:
  - Philosophers dying (not eating within `time_to_die`)
  - Simulation ending if all philosophers have eaten enough times
- Timing is managed using `gettimeofday()` and `usleep()` for precision.

---

## 🧪 Usage

### 🛠 Compile the project

```bash
make
```
### Run the program
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

⚠️ Rules & Constraints

    Only allowed to use C and the pthreads library

    No deadlocks, no starvation

    No data races or memory leaks

    Accurate timing and printing required

    Must handle input and errors properly

🔗 Connect
if you have any questions, feel free to open an issue or contact me directly at [LinkedIn](https://www.linkedin.com/in/lucasgraca/)
