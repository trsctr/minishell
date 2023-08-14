#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/include/libft.h"
#include <stdlib.h>

unsigned char *command_buf;

int main()
{
    while(1)
    {
        command_buf = readline("test> ");
        if (!ft_strncmp(command_buf, "exit", 4))
            break;
    }
    return 0;
}
