#ifndef EXEC_REDIRECT_H
# define EXEC_REDIRECT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

# include "../LIBFT/includes/libft.h"

typedef struct s_data
{
    char	**split_args;
    char    **args;
    int		fd;
    int     pipefd[2];
    char    *path;
    char    **env;
    char    *cmd;
    struct  s_data *next;
    struct  s_data *redirect;
} t_data;

//Initialise my structures
void	init_struc(t_data *data);

//BUILDIN
void	get_builtin(char **argv, t_data *data, char **envp);
int		make_cd(char **argv);
int     make_env(char **envp);
int     make_exit(void);

//EXECUTION functions
void	make_path(char **envp, t_data *data, char *cmd);
void    make_child(t_data *data, char **env);
void	exec_command(t_data *head);

//OPERATOR checkers and managers
void    split_redirection(char *str, t_data *data);
int     check_redirection(char *str);
void    make_redirection(char *str);
int     check_before_after(char *str, t_data *data);

//PROTECTED functions so make other functionsmy code shorter
int		protected_open(char *file, int flags);

//PARSING commands, path, envp
//void	split_path(char **envp, t_data *data);
void    get_args(char **argv, t_data *data);

//modified functions for chained list
t_data	*ft_lstnew(char **args, char **envp);
void	ft_addlst(char **args, t_data **head, char **envp);

//functions to help debug and improve my projet
void	print_array(char **array);
void	print_linked_list(t_data *head);

#endif