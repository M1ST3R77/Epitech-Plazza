# 🍕 The Plazza

**A pizzeria simulation in C++20 built on processes, threads and inter-process communication.**

A reception takes pizza orders from a shell and dispatches them to kitchens. Each kitchen is a separate **process** with its own pool of cook **threads** and its own ingredient stock, and talks to the reception through **System V message queues**. Kitchens are opened when the existing ones are full and close themselves after 5 seconds without work.

> Built in 2024 by a team of Epitech Paris students, as part of the concurrent programming curriculum.

## ✨ Features

- **Multi-process architecture**: one process per kitchen, created on demand
- **Thread pool per kitchen**: cooks are threads that take orders from a shared queue
- **IPC with message queues** (`msgget` / `msgsnd` / `msgrcv`) wrapped in a typed C++ class
- **Load balancing**: each order goes to the least busy kitchen; a new kitchen opens when every kitchen holds twice its number of cooks
- **Ingredient stock** shared by the cooks of a kitchen, protected by mutexes and refilled on a timer by its own thread
- **Live status**: the `status` command asks every kitchen for its orders, active cooks and remaining ingredients
- **Logging** of every order and kitchen event to `log.txt`
- **Bonus**: an ncurses interface that shows the kitchens in real time

## 🍽️ Menu

| Pizza | Ingredients | Base cooking time |
|---|---|---|
| Margarita | dough, tomato, gruyère | 1 s |
| Regina | dough, tomato, gruyère, ham, mushrooms | 2 s |
| Americana | dough, tomato, gruyère, steak | 2 s |
| Fantasia | dough, tomato, eggplant, goat cheese, chief love | 4 s |

## 🚀 Build and run

Requirements: Linux, CMake 3.27+, a C++20 compiler (and ncurses for the bonus).

```sh
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd .. && ./plazza 1 3 2000
```

```
./plazza m c t
  m   multiplier for the cooking time of the pizzas (>= 0)
  c   number of cooks per kitchen (> 0)
  t   time in milliseconds the kitchen stock takes to replace ingredients (> 0)
```

The bonus version is built the same way from the `bonus/` folder and produces `bonus_plazza`.

## 💬 Ordering

Orders follow this grammar, several orders can be chained with `;`:

```
TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*
SIZE   := S | M | L | XL | XXL
NUMBER := x[1..9][0..9]*
```

```
> regina XXL x2; fantasia M x3; margarita S x1
> status
> exit
```

## 🗂️ Project structure

```
src/Shell/        Reception: reads orders, dispatches them, shows kitchen status
src/Process/      Creates and tracks kitchen processes
src/Kitchen/      Kitchen loop, cooks and ingredient stock
src/ThreadPool/   Thread pool used by the cooks
src/IPC/          Message-queue wrapper
src/Pizza/        Pizza types, factory and serialisation for IPC
src/Parsing/      Order parsing
bonus/            Same program with an ncurses interface
```

## 🛠️ Tech stack

C++20 · CMake · POSIX processes (`fork`) · `std::thread` · System V message queues · ncurses · GitHub Actions
