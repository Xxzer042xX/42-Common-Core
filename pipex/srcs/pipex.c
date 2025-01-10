#include "../include/pipex.h"

int	main(void)
{
	t_pipex		data;
	pid_t		wpid;
	pid_t		cpid;
	size_t		numwords;
	size_t		i;
	int			status;
	const char	*argv[] = {(char *)"sort", NULL};
	const char	*words[] = {"pear", "peach", "apple"};

	if (pipe(data.pipe_fd) == -1)
	{
		ft_putstr_fd("pipe", 2);
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1)
	{
		ft_putstr_fd("fork", 2);
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{
		dup2(data.pipe_fd[0], STDIN_FILENO);
		close(data.pipe_fd[0]);
		close(data.pipe_fd[1]);
		if (execvp(argv[0], argv) < 0)
			exit(0);
	}
	close(data.pipe_fd[0]);
	numwords = sizeof(words) / sizeof(words[0]);
	i = 0;
	while (i < numwords)
	{
		dprintf(data.pipe_fd[1], "%s\n", words[i]);
		i++;
	}
	close(data.pipe_fd[1]);
	wpid = waitpid(cpid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

// 3. EXEMPLE COMPLET : SIMULATION DE COMMANDE SHELL
// 🟦 Simulation de : ls -l | wc -l
/*
int main()
{
    int pipefd[2];
    pid_t pid1, pid2;

    // 🟨 Création du pipe
    pipe(pipefd);

    // 🟩 Premier fork pour 'ls -l'
    pid1 = fork();
    if (pid1 == 0) {  // 🟦 PREMIER ENFANT (ls)
        // 🟪 Redirige la sortie standard vers le pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // 🟥 Ferme les descripteurs de fichier non utilisés
        close(pipefd[0]);
        close(pipefd[1]);

        // 🟨 Exécute 'ls -l'
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        perror("execvp ls");  // N'est exécuté que si execvp échoue
        exit(EXIT_FAILURE);
    }

    // 🟩 Second fork pour 'wc -l'
    pid2 = fork();
    if (pid2 == 0) {  // 🟦 SECOND ENFANT (wc)
        // 🟪 Redirige l'entrée standard depuis le pipe
        dup2(pipefd[0], STDIN_FILENO);

        // 🟥 Ferme les descripteurs de fichier non utilisés
        close(pipefd[0]);
        close(pipefd[1]);

        // 🟨 Exécute 'wc -l'
        char *args[] = {"wc", "-l", NULL};
        execvp("wc", args);
        perror("execvp wc");  // N'est exécuté que si execvp échoue
        exit(EXIT_FAILURE);
    }

    // 🟦 PROCESSUS PARENT
    // 🟥 Ferme les extrémités du pipe dans le parent
    close(pipefd[0]);
    close(pipefd[1]);

    // 🟨 Attend la fin des deux processus enfants
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
*/