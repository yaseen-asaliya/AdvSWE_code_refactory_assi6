All the changes I made with the Explanation : 

1- I created a function to get the name of the month, another to print the names of operations you can perform, and another to get the start location to print.
Explanation: Some of them are due to the repeated use of the code, or cause the function to be long, and the presence of these codes must be separate from the basic function.
 
2- I changed the jobs name to the one that fits their job.
Explanation: To facilitate understanding of the work of each function.

3- I've avoided using any global variable, and put existing variables in a convenient place.
Explanation: Because the global variable may cause a lot of problems because everyone can access and modify it.

4- Get rid of any unused (dead) function or variable
Explanation: Because it is a waste of space and there is no benefit in its existence.

5- I specified the magic number as fixed values ​​for the whole code (they are at the beginning of the code)
Explanation: To find out the function of this number in the code.

6- You have deleted any operator mapping to a parameter and stored a copy of the parameter in a new variable to save the original value
Explanation: It is not necessary to deal with the parameter directly and change its value, because sometimes you need this value without changing it.

7- I've applied all simplification and code refactoring (in if statements, loops,.....etc)
Explanation: To make the code as understandable as possible by the writer or reader.
