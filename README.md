# Philosophers

In this project, you will learn the basics of threading a process.
You will see how to create threads and you will discover mutexes

The Dining Philosophers Problem
The dining philosophers problem is a famous problem in computer science used to illustrate common issues in concurrent programming. 
The problem was originally formulated in 1965 by Edsger Dijkstra, and is stated as follows:

X amount of philosophers sit at a round table with bowls of food.
Forks are placed in front of each philosopher.
There are as many forks as philosophers.
All day the philosophers take turns eating, sleeping, and thinking.
A philosopher must have two forks in order to eat, and each fork
may only be used by one philosopher at a time. At any time a
philosopher can pick up or set down a fork,
but cannot start eating until picking up both forks.
The philosophers alternatively eat, sleep, or think.
While they are eating, they are not thinking nor sleeping,
while thinking, they are not eating nor sleeping,
and, of course, while sleeping, they are not eating nor thinking.

Let me start by explaining the general idea. First of all, we have to imagine a round table, X num of philosophers sitting around it and each of them brings a fork and places it in front of them.
At this point we know that a philosopher can do three things: eat, sleep, or think, 
but in order to eat he has to pick two forks (the one in front of him and another one to his right or to his left,
in my solution he picks the one to his right, both work — different implementation). Let’s use a picture to have a more concrete idea of what we are talking about:

![philo](https://github.com/user-attachments/assets/503686b3-f6ae-4851-8a7d-9feab20cee39)

Imagine there are five philosophers sitting at a table. When Philosopher 1 wants to eat,
they pick up the fork in front of them and the one to their right (which is also in front of Philosopher 5).
As a result, Philosopher 2 and Philosopher 5 are unable to eat, as Philosopher 1 has taken both of the necessary forks.
While this scenario might seem straightforward, it highlights the core challenge of this project: organizing the eating process for the philosophers.

A simple solution that might come to mind is to allow only the odd or even-numbered philosophers to eat at the same time. 
However, this approach is too rigid and defeats the purpose of the project. The goal is for the philosophers to coordinate amongst themselves dynamically.

To achieve this, we will be using threads to implement a multithreading solution. The project details are attached to help you fully understand the requirements.

In order to understand the solution you’ll needs to understand the concept of threads first, here are some good videos I recommend you watch:

General introduction to threads:

🚀 https://shor.tf/threads

Introduction to threads with code examples :

🚀 https://shor.tf/intru_thread

# Data Races (Race Conditions) — What Are They?

Data races are a common problem in multithreaded programming. Data races occur when multiple tasks or threads access a shared resource without sufficient protections, leading to undefined or unpredictable behavior.

➥ two or more threads concurrently accessing a location of memory
➥ one of them is a write
➥ one of them is unsynchronized

In simple terms, a race condition occurs when two or more threads attempt to access and modify the same variable simultaneously. 
This can lead to an incorrect final value of the variable, though it doesn't necessarily happen every time.

For example, consider a function that deposits a specified amount into your bank account.
If we use multithreading, with one thread depositing $300 and another thread depositing $200, you might expect the total balance to be $500. 
However, due to race conditions, this might not be the case.

# this is the simple exemple:

<img width="682" alt="Screen Shot 2024-08-15 at 10 30 22 AM" src="https://github.com/user-attachments/assets/9a5c62e6-9fd7-442b-82af-8ab6b8702193">



When the two deposit functions run at the same time, they both read the balance which is 0, 
they both deposit the amount inserted and change the balance variable locally, but when they write it to the variable itself, they overwrite each other. 
thread #1 writes 300 first but thread #2 writes as well and changes the variable to 200. 
How can we solve this? easily we just need to attach a lock, let me introduce you to mutex.


# Mutex

Now that we understand what a race condition is, let's explore the solution. 
Imagine a lock that safeguards a block of code, allowing only the lock's owner to execute it until the lock is released.

Using the previous example, we can prevent overwriting by adding a lock to the deposit function. 
If thread #1 acquires the lock, thread #2 must wait until thread #1 has finished executing the code and releases the lock.
Only then can thread #2 enter and execute its own operations.

You have surely noticed that we initialize and destroy the mutex, 
and you have to do that every time you want to use a mutex (destroy it after you finished using it) otherwise it won’t work.

Here is another visualization with the locks:

 <img width="687" alt="Screen Shot 2024-08-15 at 10 27 45 AM" src="https://github.com/user-attachments/assets/59f56a08-ecc3-43b2-b52d-6586c58b30a6">

