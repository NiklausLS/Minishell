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
void	get_builtin(char **argv, t_data *data, char **envp);
int		make_cd(char **argv);
int     make_env(char **envp);
int     make_exit(void);

//EXECUTION functions
//char	*check_path(char *cmd, t_data *data);
void	make_path(char **envp, t_data *data, char *cmd);

//OPERATOR checkers and managers
void    split_redirection(char *str, t_data *data);
int     check_redirection(char *str);
void    make_redirection(char *str);
int     check_before_after(char *str, t_data *data);

//PROTECTED functions so make other functionsmy code shorter
int		protected_open(char *file, int flags);

//PARSING commands, path, envp
//void	split_path(char **envp, t_data *data);

//functions to help debug and improve my projet
void	print_array(char **array);

#endif