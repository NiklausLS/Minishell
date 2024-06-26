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

#define READ_END 0
#define WRITE_END 1

typedef struct s_commands
{
    char    **args;
    int     input_fd;
    int     output_fd;
    char    *path;
    char    **env;
    char    *cmd;
    int     input_type;
    char    *input;
    int     output_type;
    char    *output;
    int     pipe_type;
    char    *heredoc_delim;
    int     file_type;
    int     cmd_type;
    struct  s_commands *next;
} t_commands;

typedef struct s_data {
    t_commands *cmd_lst;
} t_data;

//Initialise my structures
//void	init_struc(t_data *data);

//BUILDIN
int     get_builtin(t_data *data, char **envp);
int		make_cd(char **argv);
int     make_env(char **envp);
int     make_exit(void);

//EXECUTION functions
void	make_path(char **envp, t_data *data);
//void    make_child(t_data *data, char **env);
//void	exec_command_lst(t_commands *cmd, char **envp);
//void	exec_only_cmd(t_data *data);
void   make_child(t_commands *cmd, int prev_pipe, int pipefd[2], char **envp);

//OPERATOR checkers and managers
void    split_redirection(char *str, t_data *data);
int     check_redirection(char *str);
//void    make_redirection(char *str);
int		check_pipe(char *str);
//int     check_before_after(char *str, t_data *data);

void    make_input(t_commands *cmd);
void	make_output(t_commands *cmd);
void	make_heredoc(int fd, char *delim);
void	make_all_redirections(t_commands *cmd, int prev_pipe, int pipefd[2]);

//PROTECTED functions to make other functions shorter
int		protected_open(char *file, int flags);
void    protected_pipe(int pipefd[2]);

//PARSING commands, path, envp
//void	split_path(char **envp, t_data *data);
void    get_args(char **argv, t_data *data);

//modified functions for chained list
void add_node(t_commands **head, t_commands *new_node);
t_commands *init_node(char *cmd);
void    check_lst(t_data *data);

//errors functions
void    pipe_errors(t_commands *cmd);

//functions to help debug and improve my projet
void	print_array(char **array);
void	print_linked_list(t_data *head);

#endif