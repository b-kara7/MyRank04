#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
    int fd[2];
    int in_fd = 0;
    pid_t pid;
    int i = 0;

    if (!cmds || !cmds[i])
        return 1; // Soruya göre hata durumunda 1 dönmeli

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(fd) < 0)
        {
            if (in_fd != 0)
                close(in_fd);
            return 1; // -1 yerine 1
        }
        pid = fork();
        if (pid < 0)
        {
            if (in_fd != 0)
                close(in_fd);
            if (cmds[i + 1])
            {
                close(fd[0]);
                close(fd[1]);
            }
            return 1; // -1 yerine 1
        }

        if (pid == 0)
        {
            if (in_fd != 0)
            {
                dup2(in_fd, 0);
                close(in_fd);
            }
            if (cmds[i + 1])
            {
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        if (in_fd != 0)
            close(in_fd);

        if (cmds[i + 1])
        {
            close(fd[1]);
            in_fd = fd[0];
        }
        i++;
    }
    if (in_fd != 0)
        close(in_fd);
    
    // Sadece çocukların bitmesini bekle, exit status'larına bakma
    while (wait(NULL) > 0)
        ;

    return 0; // Başarılıysa her zaman 0 dönmeli
}