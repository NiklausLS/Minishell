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
# include <stdbool.h>
# include "../LIBFT/includes/libft.h"

# define PROMPT "\033[1;34mminishell\033[0m> "
# define WHITESPACES " \t\v\n\r"
# define OPERATORS "><|"

#define READ_END 0
#define WRITE_END 1
#define MAX_ARGS 20

extern int global_signal_received;

typedef enum e_token_type
{
    TEXT,
    COMMAND,
    PIPE,
    INPUT,
    HEREDOC,
    OUTPUT,
    APPEND,
    FI,
} t_token_type;

typedef struct s_redirection {
    char	*file;
    int		type;
    struct	s_redirection *next;
} t_redirection;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
    char    **args;
    char    *path;
    char    *input;
    char    *output;
    char    *heredoc_delim;
    int     error;
} t_token;

typedef struct s_input
{
    char    *total;
    char    *left;
    int     token_nb;
    int     i;
    int     j;
    t_token *tokens;
} t_input;

typedef struct s_minishell
{
	t_input	input;
}			t_minishell;

typedef struct s_exec {
    int		pipefd[2];
    int		prev_pipe;
    char	**env;
    int     last_status;
} t_exec;

//Initialise my structures
int    init_exec_structure(t_exec *ex, char **envp);

//Free everything inside my structure
int		free_exec_structure(t_exec *ex);
void	free_array(char **array);

//BUILDIN
int     get_builtin(t_token *data);
int     make_builtin(t_token *data, t_exec *ex);
int     make_env(char **envp);
int     make_cd(t_exec *ex, t_token *data);
int     make_pwd(void);
int     make_unset(t_token *data, t_exec *ex);
int     make_echo(t_token *data);
int     make_export(t_token *cmd, t_exec *ex);
char    *make_quotes(char *var);
int     update_env_loop(t_exec *ex, char **up_env, char *quote_var, int i);
void	sort_ex(char **env, int count);
void	print_export(char **env, int count);
int     make_exit(void);

//EXECUTION functions
int     make_path(t_exec *ex, t_token *data);
int     check_if_cmd(t_token *data);
int     exec_builtin(t_token *data, t_exec *ex);

//OPERATOR checkers and managers
int     check_last_node(t_token *data);

int     open_input(t_token *cmd);
int     open_output(t_token *cmd);
//int     redirections(t_token *current, int *last_input, int *last_output);

char    *readline_heredoc(char *cmd);
int	    make_heredoc(char *cmd);

int     make_all_redirections(t_token *start, t_token *end);
int     handle_redirection_only(t_token *data);
int     fork_and_exec(t_exec *ex, t_token *current, int is_first_cmd, int has_pipe);

void	parent_process(t_exec *ex, int f_cmd, int has_pipe);
void	child_process(t_exec *ex, t_token *data, int f_cmd, int has_pipe);
int     check_if_cmd(t_token *data);
int     wait_child_process(void);


//PROTECTED functions to make other functions shorter
//int		protected_open(char *file, int flags);
int	protected_pipe(int pipefd[2]);
int	protected_close(int fd);

//PARSING commands, path, ex->env
int     parse_args(t_token *data);

//modified functions for chained list
int    check_lst(t_token *data);

//errors functions
void    print_error(int error, char *cmd);

//signals functions
void	handle_sig(int sig);
void    heredoc_signal(void);

//functions to help debug and improve my projet
void	print_node(t_token *cmd);
void	print_env(t_exec *ex);
void	print_info(t_input *input);

void	execute_command(t_token *data, t_exec *ex);
int		execute_all_commands(t_token *data, t_exec *ex);
t_token	*get_end(t_token *start);

#endif