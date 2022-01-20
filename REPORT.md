# ECS150 Project 1 Report

### By Sarah Gerard and Anthony Nguyen

For our implantation of project 1, we decided to follow the phases provided by 
the professor in the project description. We found this to be really helpful in
dividing the work between us and for gradually developing the project, so that 
each part would build on itself. We spent the time doing through each phase throughly
to make sure each phase ran accordingly. 

## Fork

One of the main parts of our code is the `fork()` command, underneath which 
lives all of the different commands we were supposed to implement and the 
logic needed to implement them correctly. This was also the first phase of the
project, and ended up being important in order to properly return the right
exit status for each command, among other uses. This is where we put each of 
the built-in commands, the logic for redirecting output, and the regular
command line functions. Since each of these commands needed to use `fork()`
in the same way to create the parent and child instances, we felt it was most 
efficient to put them all under the same initial `fork()` command, instead of 
checking which command we were doing first, and then calling `fork()` and 
running the associated logic.

## Parsing
The other large section of our code was our parsing code. This ended up
being divided into three sections. 

 1. Pipes
 2. Redirects
 3. Regular commands

Each of these sections were important for properly parsing each of the
possible inputs we could have gotten. We used `strtok()` to do the majority
of the parsing for us, since it could check for each of the special 
characters we needed to look for, as well as divide the arguments by spaces 
and put them into an array, which was necessary for the `execvp()` 
command used later. Although the parsing for each section was similar, each
had it's own unique aspects that we had to work through, so we decided to
write out the code for each instead of creating a parse function, for simplicity.

## Future Improvements 
If we had more time, we could have improved our code by implementing more 
functions and defining centralized data structures. We tried to create functions
that would create the array of arguments for us, so we wouldn't have to write
out the same while loop every time, however this led to a lot of segmentation
faults that we didn't have time to fix. This led us to the decision that it was 
best to get our code working first before trying to improve it with possible
complications. Given what we were able to accomplish, we did our best to keep
our code organized and readable, and keep our logic as simple as possible.

## Testing

To test our project, we made sure to continuously check our code in ssh,
since this was the environment we would be tested in. We also worked 
through the tester file that was provided to us. This allowed us to check our
outputs against the example file, which we did anytime we were unsure of 
what the output was supposed to look like.

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

*getcwd*
https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-getcwd-get-path-name-working-directory

*Create a linux pipeline in c*
https://stackoverflow.com/questions/21923982/how-to-create-a-linux-pipeline-example-in-c
