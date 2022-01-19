# ECS150 Project 1 Report

### By Sarah Gerard and Anthony Nguyen

For our implantation of project 1, we decided to follow the phases provided
by the professor in the project description. We found this to be really 
helpful in dividing the work between us and for gradually developing the 
project, so that each part would build on itself. 

One of the main parts of our code is the fork() command, underneath lives all
of the different commands we were supposed to implement and the logic
needed to implement them correctly. This was also the first phase of the
project, and ended up being important in order to properly return the right
exit status for each command, among other uses. 

The other large section of our code was our parsing code. This ended up
being divided into three sections. 
 1. Pipes
 2. Redirects
 3. Regular commands
Each of these sections were important for properly parsing each of the
possible inputs we could have gotten. 

## Testing

To test our project, we made sure to continuously check our code in ssh,
since this was the environment we would be tested in. We also worked 
through the tester file that was provided to us.

## Sources
Here are the sources we used to help implement our solution. 
*How-to-remove-first-character-from-c-string*
https://stackoverflow.com/questions/4295754/how-to-remove-first-character-from-c-string
*Accessing Directories* 
https://www.gnu.org/software/libc/manual/html_node/Accessing-Directories.html
*Executing a File*
https://www.gnu.org/software/libc/manual/html_mono/libc.html#Executing-a-File
*String and Array Utilities*
https://www.gnu.org/software/libc/manual/html_mono/libc.html#String-and-Array-Utilities