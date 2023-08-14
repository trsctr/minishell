#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/include/libft.h"
#include <stdlib.h>


int main()
{

	unsigned char *command_buf;

    while(1)
    {
        command_buf = readline("shell on earth> ");
        if (!ft_strncmp(command_buf, "exit", 4))
		{
			printf("Bye\n");
            break;
		}
		else 
			printf("Command not found\n");
    }
    return 0;
}
