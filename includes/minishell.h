#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

# include "../LIBFT/includes/libft.h"

#define READ_END 0
#define WRITE_END 1

extern int global_signal_received;

typedef struct s_redirection {
    char	*file;
    int		type;
    struct	s_redirection *next;
} t_redirection;

typedef struct s_input_data
{
    char    **args;
    char    *path;
    //char    **env;
    char    *data;
    int     input_type;
    char    *input;
    int     output_type;
    char    *output;
    int     pipe_type;
    char    *heredoc_delim;
    int     file_type;
    int     cmd_type;
    int     exec_fail;
    struct  s_input_data *next;
    int     error;
    int     arg_type;
} t_input_data;

typedef struct s_exec {
    int		pipefd[2];
    int		prev_pipe;
    char	**env;
} t_exec;

int     make_env(char **envp);
int make_path(t_exec *ex, t_input_data *data);

int parse_redirection(t_input_data *current);
int parse_pipe(t_input_data *current);

//Initialise my structures
//void	init_struc(t_data *data);
int    init_exec_structure(t_exec *ex, char **envp);

//Free everything inside my structure
int		free_exec_structure(t_exec *ex);
void	free_array(char **array);
int		free_input_data(t_input_data **input_data);

//BUILDIN
int     get_builtin(t_input_data *cmd, t_exec *ex);
int		make_cd(char **argv);
int     make_exit(void);
int     make_export(t_input_data *cmd, t_exec *ex);
char    *add_quotes(char *var);
void	update_env_loop(t_exec *ex, char **up_env, char *quote_var, int i);
//int     make_unset(t_input_data *cmd, t_exec *ex);

int	exec_command(t_input_data *data, t_exec *ex);
int handle_piped_commands(t_input_data *current, t_exec *ex);
int execute_piped_command(t_input_data *cmd, int in_fd, int out_fd, t_exec *ex);

int setup_pipes(t_exec *ex);
int setup_in_and_out(t_exec *ex);
void    setup_pipe_end(t_exec *ex);
int execute_pipeline(t_input_data *cmd_list, t_exec *ex);
void wait_for_children(void);

//EXECUTION functions
int	make_path(t_exec *ex, t_input_data *data);
int	exec_command_lst(t_input_data *cmd, t_exec *ex);

//OPERATOR checkers and managers
void    split_redirection(char *str, t_input_data *data);
int     check_redirection(char *str);
int		check_pipe(char *str);

int     open_input(t_input_data *cmd);
int     open_output(t_input_data *cmd);
//void	make_heredoc(int fd, char *delim);
int	make_all_redirections(t_input_data *start, t_input_data *end);
int	exec_all(t_input_data *cmd, t_exec *ex);
int	exec_only_command(t_input_data *cmd, t_exec *ex);
int exec_pipe_commands(t_input_data *start, t_input_data *end, t_exec *ex);

t_input_data  *parse_input(char *input);

//PROTECTED functions to make other functions shorter
//int		protected_open(char *file, int flags);
int    protected_pipe(int pipefd[2]);

//PARSING commands, path, ex->env
//void	split_path(t_exec *ex, t_data *data);
//char **split_path(char *path);
void    get_args(char **argv, t_input_data *data);
int	parse_args(t_input_data *data);

//modified functions for chained list
void    add_node(t_input_data **head, t_input_data *new_node);
t_input_data *init_node(char *cmd);
int    check_lst(t_input_data *data);
//void    add_redirection_node(t_input_data *cmd, char *file, int type);
//void    init_redirections_lst(t_data *data);

//errors functions
int    pipe_errors(t_input_data *cmd);
void    print_error(int error, char *cmd);
int	redirection_errors(t_input_data *cmd);

//functions to help debug and improve my projet
void	print_array(char **array);
void	print_linked_list(t_input_data *head);
void	print_node(t_input_data *cmd);
void	print_env(t_exec *ex);

#endif