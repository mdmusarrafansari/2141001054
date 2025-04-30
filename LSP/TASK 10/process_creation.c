#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // Child process
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    else { // Parent process
        int status;
        waitpid(pid, &status, 0);
        printf("Child process completed with status %d\n", status);
    }
    
    return 0;
}
