# Advanced Programming Course (CS204) Assignments


This repository contains my solutions for the assignments given in the CS204 Advanced Programming course given at Sabanci University in the 2021-2022 Fall semester.

Concepts used in the assignments:
* Pointers and dynamic memory allocation
* Linked lists
* Stacks and queues
* Templates, templated classes and functions
* Advanced issues on classes and object oriented programming
* Data representation, bitwise operations
* Inheritance, polymorphism and advanced object oriented design


### Minesweeper

This assignment is about developing a simplified version of the Minesweeper game. Minesweeper is a single-player 
puzzle video game. The objective of the game is to clear a rectangular board containing hidden "mines" or 
“bombs” without detonating any of them, with the help from clues about the number of mines in the neighboring
cells. The game originates from the 1960s, and it has been written for many computing platforms in use today.
It has many variations and offshoots. The aim of this assignments is to practice matrices (vectors of vectors).
Some versions of Minesweeper set up the board so that the solution does not require guessing. If a
square (cell) containing a mine is revealed (opened), the player loses the game. If no mine is revealed, a
digit is instead displayed in the square, indicating how many adjacent (neighboring) cells contain mines; if
no mines are adjacent, the square becomes blank, and all adjacent squares will be recursively revealed. The
player uses this information to deduce the contents of other squares and may either safely reveal each
square or mark the square as containing a mine.


### Add Drop Courses

This assignment is about implement a program that stores the courses taken by students
organized (sorted in ascending order) according to the name of the courses during the add/drop period. This
program must use a Linked List structure for storage. Initially, course names, course codes and IDs of the
students who have taken a certain course(s) are going to be read from a text file. Afterwards the user will be
able to add or drop students from the courses.

### Bus Route System 

This assignment is about to use a hybrid data structure consisted of singly linked lists and
doubly linked lists. It will be employed these structures to implement a bus line/stop
management system. Since the number of bus lines and stops cannot be known in advance
and changes from case to case, it will be used dynamic memory allocation, i.e., new/delete
operations to dynamically allocate and delete the corresponding nodes of the structures.

### SU Services

This assignment’s aim is to make you familiar with the logic behind queues and stacks (and a bit of
simply linked lists of linked list, again) as well as recursions by practically using them in a real-case
scenario. Namely, SU offers a certain number of services to its academic stuff and students (such as printing, supercomputer data
processing, …), implemented as functions.These services provided by SU will be kept in the following data structures
. Service requests of the students and the academic stuff (instructors) are kept separately and
served in a First In First Out (FIFO) manner, thus it will be needed two separate queues for both of them. Each
service (function) request is consisted of set of instructions (commands) described in the corresponding folder. A
certain service (function) can be part of (called from) another function (e.g. print the output data after
processed from the supercomputer). As it is common in modern day systems, for this reason we will
need a single, commonly shared stack to put on and serve in First In Last Out (FILO) manner those
subsequent service (function). Also, in order to process those consecutive function calls, you
will be asked to implement a recursive function that calls an instance of
itself at any time a new function call is issued. 

### Car Sharing

This assignment aims to practice on object sharing via reference variables. In this assignment, you are
asked to develop an IT system for a taxi company where two or more drivers share a taxi vehicle (car). In
your implementation you are going to write two classes, Car and Driver, such that two (or more)
driver objects share one car object via reference variables. 

### Bitwise Operations with GUI

This assignment asked to implement a simple bit calculator with a Graphical User Interface
(GUI). The calculator accepts as input two unsigned integers and based on the selected operation - bitwise
AND, OR, XOR - the result is computed (again as an unsigned integer). Moreover, the bits of the operands
might be shifted left or right by a user-specified number of bits before the selected operation. You can see explained
the details of the GUI design and the work flow in corresponding folder.

### Geometrical Shapes with Inheritance and Polymorphism

This assignment aims to make you familiar with inheritance (multi-inheritance) and
polymorphism issues. You will deal with multi-inheritance through implementing, from scratch,
several small classes, some of which inherit a class that already inherited another class. The content
and a brief description of each the classes can be seen in corresponding folder.
