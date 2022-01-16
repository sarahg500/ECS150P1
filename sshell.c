#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

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

        //////////////////////////////////////////////////////////////////////////////////////
                /* struct for a command and it's arguements */
                // basic struct idea- I implemented originalCommand and name but couldn't
                // figure out how to get the arg array into the struct arguments
                struct command {
                        char *originalCommand; //string with all the arguments
                        char *arguments[16]; // array of each individual argument
                        char *name; // the first argument, which is the name of the command
                        
                };
                struct command curCmd;
                strcpy( curCmd.originalCommand, cmd); //copy original command
                int redirect;
                //Check to see if we need to redirect
                char *redirection = strtok(cmd, ">");
                if(!strcmp(redirection, curCmd.originalCommand)){
                        redirect = 0;
                 }else{
                        redirect = 1;
                        char* tempcmd;
                        strcpy(tempcmd, cmd);
                        redirection = strtok(NULL,">");
                        printf("file to redirect: %s\n", redirection);
                }

                //use strtok to parse command into an array of arguments
                // hopefully eventually we can get this into the struct
                char *curword = strtok(cmd, " ");
                char *args[16] = {};
                int n = 0;
                while (curword != NULL){
                        args[n] = curword;
                        n++;
                        curword = strtok(NULL, " ");
                }
                strcpy( curCmd.name, args[0]); // first argument is the name of the command
                /* printing out the array to check its right
                printf("array: ");
                for (int i = 0; i < n; i++){
                        printf("%s ", args[i]);   
                }
                printf("\n"); */


                /* fork, exec, wait method - actually executing commands */
                pid_t pid;
                pid = fork();
                if (pid == 0) {
                        /* Child */
                        /* Builtin command - exit */
                        if (!strcmp(curCmd.name, "exit")) {
                                fprintf(stderr, "Bye...\n");
                                break;
                        }

                        /* Builtin command - pwd */
                        else if (!strcmp(curCmd.name, "pwd")){
                                char *cwd = getcwd(NULL, 0);
                                printf("%s\n", cwd);
                                free(cwd);
                                break;
                        }

                        /* Builtin command - cd */
                        else if (!strcmp(curCmd.name, "cd")){
                                printf("attempting cd\n");
                                break;
                        }

                        if ( redirect == 1 ){
                                int fd;
                                printf("opened a file\n");
                                fd = open(redirection, O_TRUNC);
                                break;
                        } else{
                                /* Regular command */
                                execvp(curCmd.name, args);
                                perror("execvp");
                                exit(1);
                        }
                        
                } else if (pid > 0) {
                        /* Parent */
                        int status;
                        waitpid(pid, &status, 0);
                        printf("+ completed '%s' [%d]\n", curCmd.originalCommand,
                        WEXITSTATUS(status));
                        if(!strcmp(curCmd.name, "exit"))
                                break;
                } else {
                        perror("fork");
                        exit(1);
                }
        }

        return EXIT_SUCCESS;
}
      