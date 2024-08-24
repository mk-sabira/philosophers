🎉 Dining Philosophers Project

📋 Overview
The Dining Philosophers Project is a classic concurrency problem that demonstrates issues related to synchronization, deadlock, and resource sharing in multi-threaded programming. This project simulates a scenario where philosophers alternate between thinking and eating, requiring careful management of shared resources to avoid deadlock and starvation.

Features
🧩 Concurrency Management: Simulates multiple philosophers as threads, handling concurrent operations.

🚫 Deadlock Prevention: Implements strategies to avoid deadlock situations where philosophers could be stuck waiting indefinitely.

🍽️ Starvation Prevention: Ensures that no philosopher is permanently excluded from eating.

⚙️ Customizable Parameters: Allows setting the number of philosophers, time to think, and time to eat through configuration.


Requirements
- C Compiler: GCC or any other C compiler supporting POSIX threads.
- POSIX Threads Library: For thread management and synchronization.
  
⚙️  Installation

Clone the Repository:
`git clone https://github.com/mk-sabira/philosophers.git`

-> Navigate to the Project Directory:
`cd philo`

To build the project, use the `make` command.

🧩 Usage: 

Run the Simulation:

./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals]
number_of_philosophers: The number of philosophers in the simulation.
time_to_die: The time in milliseconds after which a philosopher will die if they cannot eat.
time_to_eat: The time in milliseconds each philosopher will spend eating.
time_to_sleep: The time in milliseconds each philosopher will spend sleeping.
number_of_meals: The number of meals each philosopher should eat before terminating (set to 0 for unlimited).


Example:
`./philo 5 800 200 200 3`

This will start a simulation with 5 philosophers, where each philosopher will die if they cannot eat within 800 milliseconds, will eat for 200 milliseconds, sleep for 200 milliseconds, and aim to eat 3 meals.

