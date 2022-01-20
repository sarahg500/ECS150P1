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
                
                int error=0;
                char originalCmd[CMDLINE_MAX];
                char checkCmd[CMDLINE_MAX]; // for checking how many arguments
                strcpy(originalCmd, cmd); // copy the original command- cmd will be changed
                strcpy(checkCmd, cmd); 

                char *checking = strtok(checkCmd, " ");
                int x = 0;
                while (checking != NULL){
                        x++;
                        checking = strtok(NULL, " ");
                        if(x == 17){
                               write(STDERR_FILENO, "Error: too many process arguments\n", 35);
                               error = 1;
                               break;
                        }
                }

                //Piping :(
                int pipeNum=0;
                char *piping1 = strtok(cmd,"|");
                char *piping2;
                char *piping3;
                if(!strcmp(piping1, originalCmd)){
                        pipeNum = 0;
                }else{
                        pipeNum = 1;
                        piping1 = strtok(NULL,"|");
                        printf("pipe1: %s\n", piping1);
                        piping2 = strtok(NULL,"|");
                        printf("pipe2: %s\n", piping2);
                        piping3 = strtok(NULL,"|");
                        printf("pipe3: %s\n", piping3);
                }


                int redirect;
                int redirectSDE = 0;
                //check to see if we need to redirect
                char *redirection = strtok(cmd, ">");
                if(!strcmp(redirection, originalCmd) || pipeNum > 0){
                        redirect = 0;
                }else{
                        if(!strcmp(cmd, originalCmd)){
                                error = 1;
                                write(STDERR_FILENO, "Error: missing command\n", 23);
                        }else{
                                redirect = 1;
                                redirection = strtok(NULL,">");
                                int i = 0;
                                if(redirection == NULL){
                                        error = 1;
                                        write(STDERR_FILENO, "Error: no output file\n", 23);
                                }else{
                                        if(redirection[0] == '&'){
                                                redirectSDE = 1;
                                                redirection++;
                                        }
                                        while(redirection[i] == ' ') 
                                                redirection++;
                                }
                        }
                } 
                //make array of arguments
                char *curword = strtok(cmd, " ");
                char *args[17] = {};
                int n = 0;
                while (curword != NULL){
                        args[n] = curword;
                        n++;
                        curword = strtok(NULL, " ");
                }
                char *pipe1args[17] = {};
                if(piping1 != NULL && pipeNum > 0){
                        char *pipe1word = strtok(piping1, " ");
                        int n = 0;
                        while (pipe1word != NULL){
                                pipe1args[n] = pipe1word;
                                n++;
                                pipe1word = strtok(NULL, " ");
                        }
                }
                char *pipe2args[17] = {};
                if(piping2 != NULL && pipeNum > 0){
                        pipeNum++;
                        char *pipe2word = strtok(piping2, " ");
                        int n = 0;
                        while (pipe2word != NULL){
                                pipe2args[n] = pipe2word;
                                n++;
                                pipe2word = strtok(NULL, " ");
                        }
                }
                char *pipe3args[17] = {};
                if(piping3 != NULL && pipeNum > 0){
                        pipeNum++;
                        char *pipe3word = strtok(piping3, " ");
                        int n = 0;
                        while (pipe3word != NULL){
                                pipe3args[n] = pipe3word;
                                n++;
                                pipe3word = strtok(NULL, " ");
                        }
                }
                
                /* printing out the array to check its right*/
                //printf("array: ");
                //for (int i = 0; i < 3; i++){
                //        printf("%s ", args[i]);   
                //}
                //printf("\n"); 

                char firstCmd[CMDLINE_MAX]; //save first argument (name of the command)
                strcpy(firstCmd,args[0]);

                if (!strcmp(firstCmd, "cd")){
                                chdir(args[1]);     
                        }

                /* fork, exec, wait method - actually executing commands */
                if(pipeNum > 0){
                        printf("attempting pipe: %i\n", pipeNum);
                        int fd[2];
                        int childpid;
                        pipe(fd);
                        if((childpid = fork())){
                                       //parent
                                       close(fd[1]);
                                       dup2(fd[0], STDIN_FILENO);
                                       execvp(pipe1args[0], pipe1args);
                                       exit(1);
                        }else{
                                       close(fd[0]);
                                       dup2(fd[1],STDOUT_FILENO);
                                       execvp(firstCmd, args);
                                       exit(1);
                               }
                       }

                else if(error!=1){
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
                                //free(cwd);
                                break;
                        }

                        /* Builtin command - cd */
                        else if (!strcmp(firstCmd, "cd")){
                                break;
                        }

                        /* Builtin command - sls */
                        else if (!strcmp(firstCmd, "sls")){
                                DIR *dp;
                                struct dirent *ep;
                                struct stat sb;
                                dp = opendir ("./");
                                if (dp != NULL)
                                        {
                                        char* filename;
                                        while ((ep = readdir (dp))!= NULL){
                                                strcpy(filename, ep->d_name);
                                                if(filename[0]!='.'){
                                                        stat(filename, &sb);
                                                        printf("%s ",filename);
                                                        printf("(%ld bytes)\n",sb.st_size);
                                                }
                                                
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
                                if(redirectSDE == 1){
                                        dup2(fd, STDERR_FILENO);
                                }
                                close(fd);
                                execvp(firstCmd, args);
                                perror("execvp");
                                exit(1);
                                break;
                        } else{
                                /* Regular command */
                                execvp(firstCmd, args);
                                write(STDERR_FILENO, "Error: command not found\n", 26);
                                //perror("execvp");
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
        }
        }

        return EXIT_SUCCESS;
}
