# Generate executable
myprog: prog.o utils.o
    gcc -Wall -Wextra -Werror -o myprog prog.o utils.o
# Generate objects files from C files
prog.o: prog.c utils.h
    gcc -Wall -Wextra -Werror -c -o prog.o prog.c
utils.o: utils.c utils.h
    gcc -Wall -Wextra -Werror -c -o utils.o utils.c
# Clean generated files
clean:
    rm -f myprog prog.o utils.o