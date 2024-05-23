#ifndef EXEC_REDIRECT_H
# define EXEC_REDIRECT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# include "../LIBFT/includes/libft.h"

typedef struct s_data
{
    char	**split_args;
    int		fd;
    char    *path;
    char    **env;
    char    *cmd;
} t_data;

//Initialise my structures
void	init_struc(t_data *data);

//BUILDIN
void	get_builtin(char **argv, t_data *data);
int		cd(char **argv);

//EXECUTION functions
char	*check_path(char *cmd, t_data *data);

//OPERATOR checkers and managers
void    split_redirection(char *str, t_data *data);
void    make_redirection(char *str);

//PROTECTED functions so make other functionsmy code shorter
int		protected_open(char *file, int flags);

//parsing commands, path, envp
void	split_path(char **envp, t_data *data);

//functions to help debug and improve my projet
void	print_array(char **array);

#endif