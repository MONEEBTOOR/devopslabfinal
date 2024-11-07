#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Create a child process using fork()
    pid = fork();

    if (pid < 0) {
        // fork() failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process block
        printf("Child Process: My PID is %d\n", getpid());
        printf("Child Process: Performing child-specific tasks...\n");
    } else {
        // Parent process block
        printf("Parent Process: My PID is %d\n", getpid());
        printf("Parent Process: Beginning assigned tasks...\n");
    }

    return 0;
}