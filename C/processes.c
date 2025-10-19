#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>


void spawn_usage(void) {
    pid_t pid;
    extern char **environ;
    char *cmd_argv[] = {"/bin/date", "--utc", NULL};
                    //    ^ goes v
    if (posix_spawn(&pid, "/bin/date", NULL, NULL, cmd_argv, environ) != 0) {
        perror("spawn");
        exit(1);
    }

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        exit(1);
    }
}


void exec_usage(void) {
    char *cmd_argv[] = {"/bin/date", "--utc", NULL};
    execv("/bin/date", cmd_argv);
}


void fork_usage(void) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    else if (pid == 0) {
        char *cmd_argv[] = {"/bin/date", "--utc", NULL};
        execv("/bin/date", cmd_argv);
        perror("execvpe");
    }

    else {
        int exit_status;
        if (waitpid(pid, &exit_status, 0) == -1) {
            perror("waitpid");
            exit(1);
        }
    }

}


void system_usage(void) {
    int exit_status = system("/bin/date --utc");
    printf("Exit status: %d\n", exit_status);
}


void environment_variable(void) {
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    char *value = getenv("STATUS");
    printf("Environment variable 'STATUS' has value '%s'\n", value);

}


void popen_usage() {
    FILE *p = popen("/bin/date --utc", "r");
    if (p == NULL) {
        perror("");
        exit(1);
    }

    char line[256];
    if (fgets(line, sizeof line, p) == NULL) {
        fprintf(stderr, "no output from date\n");
        exit(1);
    }

    printf("output captured from /bin/date was: '%s'\n", line);
    pclose(p);
}


int main(void) {
    popen_usage();
    return EXIT_SUCCESS;
}
