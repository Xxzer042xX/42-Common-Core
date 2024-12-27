#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char **parse_command(char *input)
{
    char **args = malloc(MAX_ARGS * sizeof(char*));
    char *token;
    int position = 0;

    token = strtok(input, " \t\n");
    while (token != NULL && position < MAX_ARGS - 1) {
        args[position] = strdup(token);
        position++;
        token = strtok(NULL, " \t\n");
    }
    args[position] = NULL;
    return args;
}

void free_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
	{
        free(args[i]);
    }
    free(args);
}

void execute_command(char **args)
{
    pid_t pid = fork();

    if (pid == -1)
	{
        perror("fork");
        return;
    }

    if (pid == 0)
	{  // Child process
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
	else
	{  // Parent process
        wait(NULL);
    }
}

void handle_builtin_commands(char **args)
{
    if (strcmp(args[0], "cd") == 0)
	{
        if (args[1] == NULL)
		{
            fprintf(stderr, "cd: missing argument\n");
        }
		else if (chdir(args[1]) != 0)
		{
            perror("cd");
        }
    }
	else if (strcmp(args[0], "exit") == 0)
	{
        exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    char input[MAX_INPUT_SIZE];
    char **args;

    while (1)
	{
        printf("madelmen@minishell\n %% ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
            printf("\n");
            break;
        }
		// Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        // Skip empty input
        if (strlen(input) == 0)
		{
            continue;
        }

        args = parse_command(input);
        if (args[0] == NULL) {
            free_args(args);
            continue;
        }

        // Handle built-in commands
        if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "exit") == 0)
		{
            handle_builtin_commands(args);
        } else {
            execute_command(args);
        }

        free_args(args);
    }

    return 0;
}