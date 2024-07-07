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

typedef struct s_redirection {
    char    *file;
    int     type;
    struct s_redirection *next;
} t_redirection;

typedef struct s_commands
{
    char    **args;
    char    *path;
    //char    **env;
    char    *cmd;
    int     input_type;
    char    *input;
    int     output_type;
    char    *output;
    int     pipe_type;
    char    *heredoc_delim;
    int     file_type;
    int     cmd_type;
    int     exec_fail;
    struct  s_commands *next;
    int     error;
} t_commands;

typedef struct s_exec {
    int     pipefd[2];
    int     prev_pipe;
    char    **env;
} t_exec;

typedef struct s_data {
    t_commands      *cmd_lst;
    //int             can_exec;

    //char            **env;
    //t_redirection   *redir_lst;
} t_data;

//Initialise my structures
//void	init_struc(t_data *data);
void    init_exec_structure(t_exec *ex, char **envp);

//Free everything inside my structure
void    free_exec_structure(t_exec *ex);

//BUILDIN
int     get_builtin(t_commands *cmd, t_exec *ex);
int		make_cd(char **argv);
int     make_env(char **envp);
int     make_exit(void);
int     make_export(t_commands *cmd, t_exec *ex);

//EXECUTION functions
void	make_path(t_exec *ex, t_data *data);
//void    make_child(t_data *data, char **env);
//void	exec_command_lst(t_commands *cmd, t_exec *ex);
//void	exec_only_cmd(t_data *data);
//void   make_child(t_commands *cmd, int prev_pipe, int pipefd[2], t_exec *ex);
void    make_child(t_commands *start, t_commands *end, t_exec *ex);

//OPERATOR checkers and managers
void    split_redirection(char *str, t_data *data);
int     check_redirection(char *str);
//void    make_redirection(char *str);
int		check_pipe(char *str);
//int     check_before_after(char *str, t_data *data);

int     open_input(t_commands *cmd);
int     open_output(t_commands *cmd);
//void	make_heredoc(int fd, char *delim);
void	make_all_redirections(t_commands *start, t_commands *end);
int     make_one_redirection(t_redirection *redir);
int     make_redirections_lst(t_commands *cmd);
void	open_all(t_commands *cmd);
void    make_pipe(t_commands *cmd, int *prev_pipe, int pipefd[2]);
void    close_pipe(t_commands *cmd, int *prev_pipe, int pipefd[2]);

t_commands  *parse_input(char *input);

//PROTECTED functions to make other functions shorter
//int		protected_open(char *file, int flags);
void    protected_pipe(int pipefd[2]);

//PARSING commands, path, ex->env
//void	split_path(t_exec *ex, t_data *data);
void    get_args(char **argv, t_data *data);

//modified functions for chained list
void    add_node(t_commands **head, t_commands *new_node);
t_commands *init_node(char *cmd);
void    check_lst(t_data *data);
void    add_redirection_node(t_commands *cmd, char *file, int type);
void    init_redirections_lst(t_data *data);

//errors functions
void    pipe_errors(t_commands *cmd);
void    print_error(int error, char *cmd);
void	redirection_errors(t_commands *cmd);

//functions to help debug and improve my projet
void	print_array(char **array);
void	print_linked_list(t_data *head);
void	print_node(t_commands *cmd);

#endif