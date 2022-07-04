# philosophers
 #### Final Score [125/100](https://github.com/ldusty/philosophers/blob/main/pass.pdf)
 Dining philosophers problem.  
All files must pass the [norminette](https://github.com/42School/norminette) check.  
 ## Mandatory part
One need to solve the problem so that there is no deadlock. Philosophers are seated in a circle and a fork is placed to the right of each. Philosophers do not communicate and do not know anything about each other. Philosophers should eat, sleep and think. 4 or 5 parameters are fed into the program: **number_of_philosophers**, **time_to_die**, **time_to_eat**, **time_to_sleep**, **number_of_times_each_philosopher_must_eat** (optional). All philosophers are in range from 1 to number_of_philosophers. Any state change of a philosopher looks like: *"timestamp_in_ms num_of_philosopher message"*. In this part philosopher is a thread, other details in the [subject](https://github.com/ldusty/philosophers/blob/main/en.subject.pdf).  
 ## Algorithm  
 1. Create a structure for collecting all needed information about each philosopher and a pointer to base parameters structure [philo.h](https://github.com/ldusty/philosophers/blob/main/philo/philo.h).  
 2. Check parameters which is fed into the program and save these into the sctructures [validate.c](https://github.com/ldusty/philosophers/blob/main/philo/src/validate.c).  
 3. Initialize all structures for every philosopher (from 1 to number_of_philosophers) [begin.c](https://github.com/ldusty/philosophers/blob/main/philo/src/begin.c).  
 4. Use get_max_fork() and get_min_fork(). For every philosopher except the last first gives get_min_fork() then give get_max_fork(), this will guarantee no deadlock. [forks.c](https://github.com/ldusty/philosophers/blob/main/philo/src/forks.c)  
 5. Create algorithm for each philosopher to wait: [timing.c](https://github.com/ldusty/philosophers/blob/main/philo/src/timing.c)  
 - if **number_of_philosopher** == 1 then wait some delay (START_MS = 10ms)  
 - if **id** is even then wait some delay + **time_tie_eat** (id = ordinal number of philosopher).  
 - if **id** is the last one then wait some delay twice + **time_tie_eat**.  
 - if **id** is odd then wait some delay.  
 6. The algorithm still won't guarantee death of philosopher so in this case thinking will help [steps.c](https://github.com/ldusty/philosophers/blob/main/philo/src/steps.c).  
 7. Create thread for every philosopher and thread for checking if philosopher is dead.  
 8. Mutex_lock and mutex_unlock everything that is needed and mutex print status and go until someone dies or until everyone eats **number_of_times_each_philosopher_must_eat** else move forever.  
 In thinking():  [steps.c](https://github.com/ldusty/philosophers/blob/main/philo/src/steps.c)  
 - If time to eat is less than time to sleep then we are going to wait some delay again and get uniform cycles.  
 - For odd **number_of_philosopher** it is needed to wait some delay.  
 ## Usage
 ```make```         - to compile mandatory part go to philo/ else philo_bonus/
 ```make clean```   - to remove objects  
 ```make fclean```  - to remove objects and binary files  
 ```make re```   - to re-compile  
## Visualizer
 To see color data output output: [nafuka11](https://nafuka11.github.io/philosophers-visualizer)
