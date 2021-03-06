# ECS150 Project 1 Report

### By Sarah Gerard and Anthony Nguyen

For our implementation of project 1, we decided to follow the phases provided by 
the professor in the project description. We found this to be really helpful in
dividing the work between us and for gradually developing the project, so that 
each part would build on itself. We spent the time going through each phase throughly
to make sure each phase ran accordingly. We also used github to take turns to code
whenever we were free, since most of the time we were busy with our personal needs.

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
 3. Regular Commands

Each of these sections were important for properly parsing each of the
possible inputs we could have gotten. We used `strtok()` to do the majority
of the parsing for us, since it could check for each of the special 
characters we needed to look for, as well as divide the arguments by spaces 
and put them into an array, which was necessary for the `execvp()` 
command used later. Although the parsing for each section was similar, each
had it's own unique aspects that we had to work through, so we decided to
write out the code for each instead of creating a parse function, for simplicity.

## Pipes

Within the piping portion, we broke the piping into three different section, 
sincethere can be up to three pipes. Each section took the possible pipe and
divided each of the arguments for a pipe into it's own array. This was 
intended to make it easier to actually implement each given command since we
needed an array of argumentsto execute each execvp() funcion. If there were 
pipes to execute, we decided to do it separately from the main 
`fork() + exec() + wait ()`, since the steps to actually create and execute
a pipe were different from other functions. Since we didn't quite have enough
time to finish implementing the pipe completely, this also helped us
implement part of the pipe without sacrificing the integrity of the rest of the
project. This way we were able to keep the rest of the code functional while 
also being able to test and experiment with the pipes.

## Redirects 

To implement redirects, we first had to parse the input for possible redirect
commands. This was discussed in the Parsing section. Then, if there was a 
redirect we were able to handle it within the main `fork()` function of our 
code. We kept a variable that kept track of wether or not there was need for
a redirect, and if there was, the given logic was executed to make sure the 
output was not printed to the console and instead printed to a file.


## Regular Commands

For the rest of the code, we followed what we learned in class, with the 
`fork() + exec() + wait ()` method to execute each arguments. And within 
 each section, we compared the argument using `strcomp` to what we were given 
to ensure no other input would work on the code. With that, we had builtin
commands execute once the arugment is called. If the command was not built
in, then we used execvp() to execute the function with the given array
of arguments that was parsed in the begining of the code.

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
what the output was supposed to look like. When we were close to finishing
the project, we ran our code through the tester shell and on gradescope.
This helped us to see any final vulnerabilities in our project. For example,
we were originally printing the exit codes on std out instead of std error,
which caused problems in almost all of the test cases. Other than that, we
were pretty confident that what we had was working as intended. There were
some parts of the project, such as pipes, which we wished we had more time
to spend on so we could better implement them and ensure they worked as
intended.

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

*How to use chdir()*
https://pubs.opengroup.org/onlinepubs/009695299/functions/chdir.html
