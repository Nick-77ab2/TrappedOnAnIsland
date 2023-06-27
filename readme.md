
# CS 361 Homework 06
Professor Mark W. Boady



## Overview


In this homework, you will work with locks and/or condition variables to solve another resource management problem. This is another problem inspired by Operating Systems and determining how to allow many independent threads to use the same resources.


## Trapped on an Island


There is an island with $a$ adults and $c$ children trapped on it. There is exactly one boat available. The job of your program is to get all the people off the island and back to the mainland.

Your program will take two command line inputs. Both must be integers and strictly larger than 0. The first number is how many adults are on the island. The second input is how many children are on the island. Your program should produce an error if no value is given or an invalid input is given. 

For example, to run with 5 adults and 3 children we would run `./bin/island 5 3`

Each adult and each child **must** be implemented as an individual thread. Once a thread is on the mainland and is no longer needed, it may exit. 

The shared resource between the threads is the boat. There is only one boat available. It has two seats, a driver and a passenger. The driver may row the boat from the island to the mainland. The boat has the following requirements:

- It has exactly two seats. One driver (who rows the boat) and one passenger who just rides in the boat.
- The boat is small and has a weight limit. It cannot hold two full grown adults.
	- 1 child or adult can ride in the boat alone (passenger seat empty)
	- 2 children can ride in the boat
	- 1 child and 1 adult can ride in the boat
	- 2 adults **cannot** ride in the boat
- It takes between 1-4 seconds (random) to row from the island to the mainland or vice versa
- No thread may row the boat more than 4 times without a break.  (Sitting in the passenger seat for 1 direction or on the island counts as a break.)

You need to make sure to always return the boat to the island for the next group. If the boat is not returned to the island, all remaining threads will be trapped forever. This means that if two threads take the boat to the mainland, you cannot have both exit or the boat will never be returned.

Once all the threads are safely off the island, print out the following statistics about your program.

1. Number of times the boat traveled to the mainland
2. Number of times the boat returned to the island
3. Number of boats with 2 children
4. Number of boats with 1 child and 1 adult
5. Number of boats with only 1 person (child or adult)
6. Number of times adults were the driver
7. Number of times children were the driver

You **may not** use the lock classes provided in lecture: semaphore, lightswitch, or starvation free mutex. You **must** use the C++ standard classes like mutex locks and conditional variables. You may use these directly or implement them as part of one or more classes. You need to build up your tools using just the features provided by the C++ standard library.

You may use the basic `rand` command or use the C++11 non-deterministic hardware entropy based random number generator.

You **must** make sure that your I/O and any shared data structures are thread safe.

You **must** ensure the following:

- All threads make it to the mainland
- The boat never contains an incorrect number of people

Once you have completed your code, you will run a few tests and write your thoughts on how your code works. You will write your thoughts in a readme file.

## Output Style

When a thread gets in the boat print out what has happened.

Template: `[Thread Name] got into the [position] seat of the boat.`

For example, if a child got into the driver seat and an adult got into the passenger seat we print

```text
Child 1 got into the driver's seat of the boat.
Adult 4 got into the passenger seat of the boat.
```

When that boat is being used print out what happens.

Template: `Boat is traveling from [start] to [stop].`

For example, if the boat was going from the island to the mainland we print

```text
Boat is traveling from island to mainland.
```

Once the all threads have made it to the mainland, print out a final summary using the following template.  (Numbers below are nonsense, they are just provided for formatting. We don't want to give any hints about the design by providing real results.)

```text
Summary of Events
Boat traveled to the mainland: 12
Boat returned to the island: 11
Boats with 2 children: 7
Boats with 1 child and 1 adult: 3
Boats with only 1 person (child or adult): 4
Times adults where the driver: 4
Times children where the driver: 11
```

## Implementation

You are expected to write professional code. Use good variable and function names. Provide comments explaining how the code works. Documents each function in the header file with comments. You will be graded on style as well as functionality.

## Citations

If you use any outside resources, talk about algorithm design with other students, or get help on assignments you **must** cite your resources in the comments. Uncited sources are an Academic Honesty Violation. Cited sources may lead to a deduction depending on the amount of code used, but will not violate Academic Honesty Policies. 

You are expect to write the majority of the code yourself and use resources for things like looking up commands. For example, if you forgot how to test if a file can be opened for reading you could look it up and cite a source. If you copy a critical algorithm and cite the code, you may still get a deduction for not developing the code yourself.

## Readme 

Your readme.md will include both instructions and reflections on your code. It must be stored on the root of your folder structure. It must use markdown formatting and be named readme.md.

There is no minimum or maximum length for the short essay questions, you are graded entirely on content. A short but comprehensive answer is better than a long confusing answer.

1. Your name and drexel ID (abc123@drexel.edu)

	Nicholas Pelletier, nwp28

2. Instructions to run you code.

	Standard instructions, no additions.

3. Short Essay Question 1: What did you use to protect the boat and why?

	I used a semaphore I created and a variable boat contains called "full" to protect the boat. It's the easiest way to be honest. the children set the variable to full while running so no others can get on.

4. Short Essay Question 2: How did threads decide what position to take in the boat?

	Their position was dependent upon their type (child or adult) and whether there were more adults left than children. Since there cannot be 2 adults on the same boat we want to make sure that there's a higher chance for an adult to leave the island first. They also took into account the number of rows they had left.

5. Short Essay Question 3: How did you reset the boat for the next group?

	I removed the driver from the boat within the boat thread so when the boat was empty all human threads had an "equal" (never really equal) chance to at least try to get onto the boat.

6. Short Essay Question 4: Why are you **certain** everyone will get off the island?

	I exhaustively checked all cases and made sure there were always enough children left for each adult. I also made sure that if there's only 1 child he's not always the driver. This game's focus was child labor though so the children did end up rowing more than the adults.

7. Short Essay Question 5: What was the most challenging part of this assignment?

	SEGMENTATION FAULTS. BAD_ALLOC. I realized I had a lot of cases where my code looked fine and there were no errors in IDE, but of course there were errors in run. I realized I also needed to have all of the child threads in the same vector because it was std::sys_erroring whenever one of the two original vectors for humans I made went out of scope and therefore got lost. This one was a massive pain and I hope I learned enough from this one to be able to complete the next assignments well.

## Makefile

You **must** provide a makefile to compile your code. We will type `make` and it **must** build your program. We will the type **make run** and it must test your program. If there are any compile errors or a makefile is not provided we cannot test your code.

You must have the following make targets:

- `make`  - Builds the Program
- `make run` - Runs a simulation with 7 adult and 9 children
- `make clean` - Remove compiled code

## Other Requirements

If you submission does not meet the following guidelines we will not be able to grade it.

- You **must** use the C++ 17 Standard threads. No other thread libraries (pthreads, boost, etc) may be used. [https://en.cppreference.com/w/cpp/header/thread](https://en.cppreference.com/w/cpp/header/thread)
- Code **must** run on tux and be compiled with g++.
- All code **must** compile using the C++ 17 or above standard. (`--std=c++17`)
- All code **must** be submitted in the class GitHub
- A working makefile **must** be provided.
- Must provide a readme file
- You may use libraries in the C++ 17 standard unless noted elsewhere in the instructions. [https://en.cppreference.com/w/cpp/header](https://en.cppreference.com/w/cpp/header)
- Your code **must** compile. You should always submit stable code, we will not debug code that does not compile.


## Grading

This homework is worth 100 points.

| Section | Component | Points |
| ------- | --------- | ------ |
| Main Program | Handles Command Line Arguments | 2 |
| Main Program | Starts all threads | 2 |
| Main Program | Joins all threads before exiting | 2 |
| Main Program | Overall Style | 3 |
| Threads | Adult Thread Logic | 20 |
| Threads | Child Thread Logic | 20 |
| Threads | Boat Logic | 20 |
| Readme.md | Name and Email | 1 |
| Readme.md | Instructions | 1 |
| Readme.md | Short Essay 1 | 3 |
| Readme.md | Short Essay 2 | 3 |
| Readme.md | Short Essay 3 | 3 |
| Readme.md | Short Essay 4 | 3 |
| Readme.md | Short Essay 5 | 3 |
| Instructions | Makefile is correct | 2 |
| Instructions | Required Files Submitted | 2 |

## Student Answers

You may write your answers to the Readme.md questions in this section.
