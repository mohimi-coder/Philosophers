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

 you can read about Mutex here:

🚀 https://shor.tf/mutex

# First Step: Checking Valid Input

The first thing we need to do before we even start initializing anything is to check the program input. 
The program will receive 4 or 5 arguments so the first thing should be to throw an error if we receive more or less. 
Let’s analyze the input we will receive: 5 800 200 200 7

5   — The number of philosophers
800 — The time a philosopher will die if he doesn’t eat
200 — The time it takes a philosopher to eat
200 — The time it takes a philosopher to sleep
7   — Number of times all the philosophers need to eat before terminating the program **
** optional argument

Basically, all we need to do is to check that the input contains only numbers, 
they should all be bigger than 0 except the number of meals each philo needs to eat (edge case). 
In the evaluation form, it says we should not test with more than 200 philos so you can set the limit not to be more than 200.

# Second Step: Structures

In order for you to understand the way I approached and solved this project I’ll share with you the structures I made. 
Because each philosopher needs to be a thread and all the data needs to pass to the routine functions, 
structures are the best option. I created 2 structures, The program structure which holds all of the philosophers (in an array), 
3 mutex, and one dead_flag, and the philo structure where we have all of the general data, 
3 mutex pointers that point to the mutex in the program structure, 2 mutex pointers for the forks,
and on dead pointer which points to the dead flag in the program structure.

<img width="322" alt="Screen Shot 2024-08-15 at 11 02 46 AM" src="https://github.com/user-attachments/assets/690bafa9-827c-42c1-8651-c10c28902920">

# Third Step: Initialization

Because we know the maximum amount of philosophers our program can be tested with (200) and I wanted to avoid dealing with leaks, 
freeing, and allocating, and mainly because I wanted the performance to be faster
I decided to keep all the memory on the stack and not on the heap by initializing a philo structure array, 
a mutex array for the forks and the program structure all in the main. From there I initialize the program variables,
initialize all the mutexes for the mutex fork array, and lastly the philosophers — input variables and point the pointers to all the mutexes and the dead_flag.

# Fourth Step: Thread Creation, Philo Routine, And Monitor

Now we need to create the threads and join them. We will create as many threads as philosophers we have, 
each philo needs to be a thread and we will create an extra thread (I called it observer) which will monitor everything.
Each philo thread will run the philo routine function and the observer will run the monitor function.

# Philo Routine()

The routine will be the function executed over and over by the philos, Basically ,I created a loop that will break as soon as the dead flag is 1, 
in other words as soon as a philo is dead. Remember:

The philosophers alternatively eat, sleep, or think. While they are eating, they are not thinking nor sleeping, while thinking, 
they are not eating nor sleeping, and, of course, while sleeping, they are not eating nor thinking.

So in our loop, they will eat, sleep and think. Let’s start with the easiest one when they think we just need to print a message “X is thinking” (X is the philo number),
When they sleep we need to make them sleep the length of the input inserted by the user using our ft_usleep (described in the bottom of this page) and then print the message “X is sleeping”. 
Now to the eating part, We will lock the right fork first using pthread_mutex_lock and print the message, 
and do the same with the left fork. Then he will eat using ft_usleep again and only then he will drop the forks by unlocking the locks,
before that we change some variables that give our monitor indications but that’s the general idea.

# Monitor()

This thread will be running and monitoring the whole program, it has 2 checks in it that run infinitely until a philo dies or they all ate the number of meals they need to (last input argument). Basically, we will check that the time a philo needs to die didn’t surpass the last meal he had and that he is not concurrently eating. 
If he indeed died we change the dead flag to 1 and that will break the loop in all of the threads. 
The other check is to see if all the philos finished eating the amount of meals they need to,
and if they did we will again change the dead flag to one and break the threads loop.

# Fifth Step: Destroying All The Mutexes

The last step is to Destroy all the mutexes you initialized, otherwise, they won’t work.
In this step, we will free all the data we allocated if we chose to allocate it(we didn’t).

######## that's all 😀

