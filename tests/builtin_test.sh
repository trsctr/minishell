gcc -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include tests/builtins_test.c src/builtins.c src/prompt_utils.c src/env_var.c libft/libft.a -Iinclude -o bitest
./bitest