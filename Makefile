# Generate executable
sshell: sshell.o
	gcc -Wall -Wextra -Werror -o sshell sshell.o 
# Generate objects files from C files #idk if we need this if we don't have h files
# prog.o: prog.c utils.h
#     gcc -Wall -Wextra -Werror -c -o prog.o prog.c
# utils.o: utils.c utils.h
#     gcc -Wall -Wextra -Werror -c -o utils.o utils.c
# Clean generated files
clean:
	rm -f sshell sshell.o 
