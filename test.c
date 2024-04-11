#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIRST 1000
#define BETWEEN 1001
#define LAST 1002

// Fonction pour créer tous les pipes
void create_all_pipes(int **fd, int num_of_pipe) {
    int i;
    for (i = 0; i < num_of_pipe; i++) {
        if (pipe(fd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
}

// Fonction pour attendre tous les processus fils
void wait_all_pid(pid_t *pid) {
    int i = 0;
    while (pid[i]) {
        waitpid(pid[i], NULL, 0);
        i++;
    }
}

// Fonction pour fermer les descripteurs de fichiers et rediriger les entrées/sorties
void close_redir_fd(int **fd, int type) {
    if (type == FIRST) {
        close(fd[0][0]);
        close(fd[1][0]);
        close(fd[1][1]);
        dup2(fd[0][1], STDOUT_FILENO);
    } else if (type == BETWEEN) {
        close(fd[0][1]);
        close(fd[1][0]);
        dup2(fd[0][0], STDIN_FILENO);
        dup2(fd[1][1], STDOUT_FILENO);
    } else if (type == LAST) {
        close(fd[1][1]);
        dup2(fd[1][0], STDIN_FILENO);
    }
}

// Fonction exécutée par les processus fils
void child(int **fd, int num_of_pipe, int pipe_left) {
    if (pipe_left == 0)
        close_redir_fd(fd, LAST);
    else if (pipe_left == num_of_pipe)
        close_redir_fd(fd, FIRST);
    else
        close_redir_fd(fd, BETWEEN);

    execlp("ls", "ls", NULL); // Exécuter la commande "ls"
}

// Fonction pour fermer les descripteurs de fichiers dans le processus parent
void parent_close_fd(pid_t *pid, int **fd, int num_of_pipe, int pipe_left) {
    if (pipe_left > 0 && pipe_left < num_of_pipe) {
        close(fd[num_of_pipe - pipe_left - 1][0]);
        close(fd[num_of_pipe - pipe_left][1]);
    } else if (pipe_left == num_of_pipe) {
        close(fd[0][0]);
        close(fd[0][1]);
    } else if (pipe_left == 0) {
        close(fd[num_of_pipe - 1][0]);
        close(fd[num_of_pipe - 1][1]);
        wait_all_pid(pid);
    }
}

// Fonction exécutée par le processus parent
void parent(pid_t *pid, int **fd, int num_of_pipe, int pipe_left) {
    if (pipe_left >= 0) {
        pid[num_of_pipe - pipe_left - 1] = fork(); // Créer un nouveau processus fils
        if (pid[num_of_pipe - pipe_left - 1] == -1) { // Vérifier s'il y a une erreur lors de la création du processus
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid[num_of_pipe - pipe_left - 1] == 0) // Code exécuté par le processus fils
            child(fd, num_of_pipe, pipe_left);
        else { // Code exécuté par le processus parent
            parent_close_fd(pid, fd, num_of_pipe, pipe_left);
            if (pipe_left > 0)
                parent(pid, fd, num_of_pipe, --pipe_left); // Appeler récursivement parent avec un pipe de moins
        }
    }
}

int main(void) {
    int num_of_pipe = 2;
    int pipe_left = num_of_pipe;
    pid_t pid[num_of_pipe];
    int *fd[num_of_pipe];
    int i;

    // Allocation de mémoire pour les descripteurs de fichier
    for (i = 0; i < num_of_pipe; i++) {
        fd[i] = (int *)malloc(2 * sizeof(int));
        if (fd[i] == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }

    create_all_pipes(fd, num_of_pipe); // Créer tous les pipes
    parent(pid, fd, num_of_pipe, pipe_left); // Lancer le processus parent

    // Libération de la mémoire allouée pour les descripteurs de fichier
    for (i = 0; i < num_of_pipe; i++) {
        free(fd[i]);
    }
    return 0;
}
