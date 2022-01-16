#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CMDLINE_MAX 512

int main(void)
{
        char cmd[CMDLINE_MAX];

        while (1) {
                char *nl;
                int retval;

                /* Print prompt */
                printf("sshell@ucd$ ");
                fflush(stdout);

                /* Get command line */
                fgets(cmd, CMDLINE_MAX, stdin);

                /* Print command line if stdin is not provided by terminal */
                if (!isatty(STDIN_FILENO)) {
                        printf("%s", cmd);
                        fflush(stdout);
                }

                /* Remove trailing newline from command line */
                nl = strchr(cmd, '\n');
                if (nl)
                        *nl = '\0';

                ////////////////////////////////////////////////////////////////////////
                /* struct for a command and it's arguements */
                // this works to have arguments, but it should be turned into a struct/data structure
                // so we can keep this better organized as we go along (as suggested in the phases)

                //use strtok to parse command into an array of arguments
                char *curword = strtok(cmd, " ");
                char *args[16] = {};
                int n = 0;
                while (curword != NULL){
                        args[n] = curword;
                        n++;
                        curword = strtok(NULL, " ");
                }
                // printing out the array to make sure its right
                printf("array: ");
                for (int i = 0; i < n; i++)
                        printf("%s ", args[i]);
                printf("\n");

                /* Builtin command - exit */
                if (!strcmp(cmd, "exit")) {
                        fprintf(stderr, "Bye...\n");
                        break;
                }

                /* Builtin command - pwd */
                
                /* Builtin command - cd */

                /* Regular command */

                /* attempting with the fork, exec, wait method */
                pid_t pid;
                pid = fork();
                if (pid == 0) {
                        /* Child */
                        execvp(cmd, args);
                        perror("execvp");
                        exit(1);
                } else if (pid > 0) {
                        /* Parent */
                        int status;
                        waitpid(pid, &status, 0);
                        printf("+ completed '%s' [%d]\n", cmd,
                        WEXITSTATUS(status));
                } else {
                        perror("fork");
                        exit(1);
                }
        }

        return EXIT_SUCCESS;
}
        
      