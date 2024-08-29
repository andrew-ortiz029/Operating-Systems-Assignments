
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author ??? (Mitchell Curtis, Andrew Ortiz)
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[])
{
    int numCommands = -1;   //account for initial loop

    //remove newline character at the end of the command (ls -l fix) 
    size_t len = strlen(command);
    if (len > 0 && command[len - 1] == '\n') {
        command[len - 1] = '\0';
    }

    while (*command != '\0')    //loop unitl end of command
    {
        while (*command == ' ' || *command == '\t' || *command == '\n') //replace space/tab/nl with null
        {
            *command++ = '\0'; //make white space null
        }
        *args++ = command; //save the argument position
        numCommands++;
        while (*command != '\0' && *command != ' ' && *command != '\t' && *command != '\n') //loop until end of argument
        {
            command++; // skip the argument until
        }
    }
    return numCommands; //return the number of arguments
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    char *argsPipe[MAX_LINE / 2 + 1]; // hold parsed out command line arguments for pipe
    int should_run = 1;           /* flag to determine when to exit program */
    char commandHistory[MAX_LINE];  //save previous command for !! utilization
    int num_args;   //number of arguments in command
    bool ampersand = false; //check for ampersand symbol
    bool pipeIdentifier = false;  //check for pipe symbol

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);

        //***DEBUG***
        //strcpy(command, "ls -l > output.txt\n");
        //cout << command << endl;

        //check for history command
        if (strcmp(command, "!!\n") == 0) {
            if (commandHistory[0] == '\0') {   //no history
                cout << "No command history found." << endl;
            }
            else { //print history
                //parse history
                num_args = parse_command(commandHistory, args);

                cout << "osh>";
                for (int i = 0; i <= num_args; i++) {
                    cout << args[i] << " ";
                }
                cout << endl;
            }
        }
        else if (strcmp(command, "exit\n") == 0)
            return 0;
        else { //normal command
            strcpy(commandHistory, command);    //save command for history
            num_args = parse_command(command, args);

            ampersand = args[num_args][strlen(args[num_args]) -1] == '&'; //check for ampersand symbol
            if (ampersand)
                args[num_args][strlen(args[num_args]) -1] = '\0'; //remove ampersand symbol from command

            if (num_args)
            if (strcmp(args[num_args-1], ">") == 0) {  //output to file
                cout << "OUTPUT TO FILE" << endl;
                char filename[MAX_LINE];
                strcpy(filename, args[num_args]);
                args[num_args-1] = NULL;    //remove > from arguments
                args[num_args] = NULL;      //remove filename from arguments

                //open file with write permissions, create if not found, set permissions
                int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                if (fd == -1) { //check for file error
                    perror("open");
                    return 1;
                }

                if (dup2(fd, STDOUT_FILENO) == -1) { //duplicate file descriptor to standard output
                    perror("dup2");
                    close(fd);
                    return 1;
                }
                close(fd);  //close file descriptor
            }
            else if (strcmp(args[num_args-1], "<") == 0) {  //input from file
                cout << "INPUT FROM FILE" << endl;
                char filename[MAX_LINE];
                strcpy(filename, args[num_args]);
                args[num_args-1] = NULL;    //remove < from arguments
                args[num_args] = NULL;      //remove filename from arguments

                int fd = open(filename, O_RDONLY); //open file with read permissions
                if (fd == -1) { //check for file error
                    perror("open");
                    return 1;
                }

                if (dup2(fd, STDIN_FILENO) == -1) { //duplicate file descriptor to standard input
                    perror("dup2");
                    close(fd);
                    return 1;
                }
                close(fd);  //close file descriptor
            }
            else if (strcmp(args[num_args-1], "|") == 0){    //pipe
                cout << "PIPE" << endl;
                pipeIdentifier = true;
                args[num_args-1] = NULL;    //remove | from arguments
                argsPipe[0] = args[num_args];   //save second command
            }
        }
        

        /*debug outputs
        if (num_args > 0) {
        cout << "num_args: " << num_args << endl;
        cout << "program: " << args[0] << endl;
        cout << "args(1): " << args[1] << endl;
        } */

        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) parent will invoke wait() unless command included &
         */
        int pid = fork();
        if (!pipeIdentifier){  //normal execution
        if (pid < 0)
        {
            //fprintf(stderr, "Fork Failed");
            return 1;
        }
        else if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
                cout << "Command not found" << endl;
        }
        else if (!ampersand) //check for ampersand symbol to skip waiting
        {
            wait(NULL);
        } }
        else {  //pipe execution
            int pipefd[2];
            pipe(pipefd);

            int pidPipeOne = fork();   //fork for first command

            if (pid == 0)   //first child
            {
                close(pipefd[0]);   //close read end of pipe
                dup2(pipefd[1], STDOUT_FILENO); //change standard input to read from pipe
                close(pipefd[1]);   //close write end of pipe
                if (execvp(args[0], args) == -1)
                    cout << "Command not found" << endl;
                    exit(0);
            }

            int pidPipeTwo = fork();   //fork for second command

            if(pidPipeTwo == 0)     //second child
            {
                close(pipefd[1]);   //close write end of pipe
                dup2(pipefd[0], STDIN_FILENO); //change standard output to write to pipe
                close(pipefd[0]);   //close read end of pipe
                if (execvp(argsPipe[0], argsPipe) == -1)
                    cout << "Command not found" << endl;
                exit(0);
            }

            //parent
            close(pipefd[0]);   //close read end of pipe
            close(pipefd[1]);   //close write end of pipe
            waitpid(pidPipeOne, NULL, 0);   //wait for first child
            waitpid(pidPipeTwo, NULL, 0);   //wait for second child
        }
        //should_run = false;   //prevent infinite loop during debug
    }
    return 0;
}
