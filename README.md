# Arch-Lab-3
C programming - pointers, function pointers and simple data structures

Task 2b
Replace the "switch-case" in the State Machine by one call to the appropriate handler of each state. 
Use an array of function pointers.
Define an array of size as the number of the states in the state machine. Each cell in the array holds a handler. Each enum value is is mapped to a numerical value, so each index in the array will describe the handler for that state. e.g. array[st_printf_init] will hold the handler for init state
Replace the "switch-case" in the state machine by calling the appropriate function which you retrieve from the array. Note, you should not have if-else chains or switch-case in the state machine anymore (you can use switch-case in the handlers).

Task 2c
you are required to replace the switch-case in the handlers implementation in a similar way. 
