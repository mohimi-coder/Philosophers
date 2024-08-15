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

