#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define CMDLINE_MAX 512

int main(void)
{
        char cmd[CMDLINE_MAX];
        char* PARSE_ERROR_1 = "too many process arguments";
        //char* PARSE_ERROR_2 = "missing command";
        char* PARSE_ERROR_3 = "no output file";
        //char* PARSE_ERROR_4 = "cannot open output file";
        //char* PARSE_ERROR_5 = "mislocated output redirection";
        //char* LAUNCH_ERROR_1 = "cannot cd into directory";
        //char* LAUNCH_ERROR_2 = "command not found";
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
                 //////////////////////////////////////////////////////////////////////////////////////
                /* struct for a command and it's arguements */
                // basic struct idea- this was causing seg faults when I ran this on 
                // the ssh computers so I took it out for now
                /*struct command {
                        char *originalCommand; //string with all the arguments
                        char *arguments[16]; // array of each individual argument
                        char *name; // the first argument, which is the name of the command
                };*/
                //use strtok to parse command into an array of arguments
                // hopefully eventually we can get this into the struct
                int error=0;
                char originalCmd[CMDLINE_MAX];
                strcpy(originalCmd, cmd); // copy the original command- cmd will be changed

                int redirect;
                //check to see if we need to redirect
                char *redirection = strtok(cmd, ">");
                if(!strcmp(redirection, originalCmd)){
                        redirect = 0;
                }else{
                        redirect = 1;
                        redirection = strtok(NULL,">");
                        int i = 0;
                        if(redirection == NULL){
                                error = 1;
                                printf("Error: %s\n", PARSE_ERROR_3);
                        }else{
                                while(redirection[i] == ' ') 
                                redirection++;
                        }
                }
                //make array of arguments
                char *curword = strtok(cmd, " ");
                char *args[16] = {};
                int n = 0;
                while (curword != NULL){
                        args[n] = curword;
                        n++;
                        curword = strtok(NULL, " ");
                        if(n == 15){
                               printf("Error: %s\n", PARSE_ERROR_1);
                               error = 1;
                               break;
                        }
                }
                /* printing out the array to check its right
                printf("array: ");
                for (int i = 0; i < n; i++){
                        printf("%s ", args[i]);   
                }
                printf("\n"); */

                char firstCmd[CMDLINE_MAX]; //save first argument (name of the command)
                strcpy(firstCmd,args[0]);
                /* fork, exec, wait method - actually executing commands */
                if(error!=1){
                pid_t pid;
                pid = fork();
                if (pid == 0) {
                        /* Child */
                        /* Builtin command - exit */
                        if (!strcmp(firstCmd, "exit")) {
                                fprintf(stderr, "Bye...\n");
                                break;
                        }

                        /* Builtin command - pwd */
                        else if (!strcmp(firstCmd, "pwd")){
                                char *cwd = getcwd(NULL, 0);
                                printf("%s\n", cwd);
                                free(cwd);
                                break;
                        }

                        /* Builtin command - cd */
                        else if (!strcmp(firstCmd, "cd")){
                                printf("attempting cd\n");
                                break;
                        }

                        /* Builtin command - sls */
                        else if (!strcmp(firstCmd, "sls")){
                                DIR *dp;
                                struct dirent *ep;
                                struct stat sb;
                                dp = opendir (".");
                                if (dp != NULL)
                                        {
                                        while ((ep = readdir (dp))!= NULL){
                                                stat(ep->d_name, &sb);
                                                printf("%s ",ep->d_name);
                                                printf("(%lld bytes)\n",sb.st_size);
                                        }
                                        (void) closedir (dp);
                                        }
                                else
                                        perror ("Couldn't open the directory");
                                break;
                        }

                        if ( redirect == 1 ){
                                int fd;
                                fd = open(redirection, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                                dup2(fd, STDOUT_FILENO);
                                close(fd);
                                execvp(firstCmd, args);
                                perror("execvp");
                                exit(1);
                                break;
                        } else{
                                /* Regular command */
                                execvp(firstCmd, args);
                                perror("execvp");
                                exit(1);
                        }

                } else if (pid > 0) {
                        /* Parent */
                        int status;
                        waitpid(pid, &status, 0);
                        printf("+ completed '%s' [%d]\n", originalCmd,
                        WEXITSTATUS(status));
                        if(!strcmp(firstCmd, "exit"))
                                break;
                } else {
                        perror("fork");
                        exit(1);
                }
        }}

        return EXIT_SUCCESS;
}
