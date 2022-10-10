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
