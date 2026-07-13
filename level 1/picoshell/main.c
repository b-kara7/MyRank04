#include <string.h>
#include <stdlib.h>

int picoshell(char **cmds[]);

int main(int ac, char **av)
{
    int i = 1;
    int cmd_idx = 0;
    
    // Maksimum 100 komut ve her komut için 100 argümanlık yer açıyoruz
    char ***cmds = calloc(100, sizeof(char**));
    cmds[cmd_idx] = calloc(100, sizeof(char*));
    int arg_idx = 0;

    while (i < ac)
    {
        if (strcmp(av[i], "|") == 0)
        {
            cmds[cmd_idx][arg_idx] = NULL;
            cmd_idx++;
            cmds[cmd_idx] = calloc(100, sizeof(char*));
            arg_idx = 0;
        }
        else
        {
            cmds[cmd_idx][arg_idx] = av[i];
            arg_idx++;
        }
        i++;
    }
    cmds[cmd_idx][arg_idx] = NULL;
    cmds[cmd_idx + 1] = NULL;

    picoshell(cmds);

    // Temizlik
    i = 0;
    while (cmds[i])
    {
        free(cmds[i]);
        i++;
    }
    free(cmds);
    return 0;
}