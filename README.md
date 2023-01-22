# Philosophers


## About this project
This program is a simulation of the "Philosopher's problem" using threads and mutexes. It uses the pthread library for creating and managing threads and mutexes for synchronizing access to shared resources.


## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.


### Prerequisites 
A C compiler (gcc or clang)</br>
Make 


### Installing

Clone this repository
   ```sh
   git clone https://github.com/shetteemah/philosophers
   ```
Navigate to the directory and run make
   ```sh
   cd philosophers
   make 
   ```


## Running the simulation

The program takes command line arguments for the number of philosophers, the amount of time for which a philosopher can die, eat, and sleep. Optionally you may specify the maximum number of times a philosopher can eat.
   ```sh
   ./philo [number of philosophers] [time to die] [time to eat] [time to sleep] [max number of time a philosopher can eat]
   ```

For example, to run the simulation with 7 philosophers, where the time to die is set to 200 miliseconds, time to eat is set to 80 miliseconds, time to sleep is set to 80 miliseconds, and each philosopher can eat up to 10 times:
   ```sh
   ./philo 7 200 80 80 10
   ```


### Built With
[![C](https://skillicons.dev/icons?i=c)](https://skillicons.dev)


## Author:
Shettima Ali
### Contact
Twitter - [@Shetteemah](https://twitter.com/shetteemah)


## Acknowledgments
This program was done as a project in 42 Heilbronn, inspired by the "Philosopher's problem" which is a classic problem in computer science and concurrent programming. Note This is a simulation and it will run infinite loop until all philosophers die. To stop it use `CTRL + C`
