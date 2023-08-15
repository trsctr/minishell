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
        command_buf = readline("shell on earth : ");
        if (!ft_strncmp(command_buf, "exit", 4))
		{
			ft_putendl_fd("exit", 2);
            clear_history();
            exit(0);
		}
        else if (!ft_strncmp(command_buf, "cd", 2) && command_buf[2] == ' ')
        {
            chdir(command_buf+3);
        }
        else if (!ft_strncmp(command_buf, "echo", 4) && (command_buf[4] == '\0' || command_buf[4] == ' '))
        {
            ft_printf("%s\n", command_buf+5);
        }
		else 
			ft_printf("%s: Command not found\n", command_buf);
        add_history(command_buf);
    }
    return 0;
}
