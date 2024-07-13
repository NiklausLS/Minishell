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


/*typedef struct s_commands
{
    char    **args;
    char    *path;
    //char    **env;
    //char    *cmd;
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
    int     arg_type;
} t_input_data;*/

typedef struct s_exec {
    int		pipefd[2];
    int		prev_pipe;
    char	**env;
} t_exec;

typedef struct s_input_data
{
    char	**args;
    char	*path;
    //char    **env;
    //char    *cmd;
    int		input_type;
    char	*input;
    int		output_type;
    char	*output;
    int		pipe_type;
    char	*heredoc_delim;
    int		file_type;
    int		cmd_type;
    int		exec_fail;
    //struct	s_commands *next;
    int		error;
    int		arg_type;
    char	***env;
    int		between_double_quotes;
    int		between_single_quotes;
    int     quotes;//
    int		next_structure_without_space;
    char	*data;
    struct	s_input_data *next_data_same_command_id;
    struct	s_input_data *next_command_id;
    struct  s_input_data *next;
}   t_input_data;

typedef struct s_split_data
{
    int				i;
    int				new_struct;
    int				end_word;
    char			*input_line;
    t_input_data	*temp_last;
    t_input_data	*temp_new_struct;
}   t_split_data;

/*typedef struct s_data {
    t_input_data	*cmd_lst;
    //int             can_exec;
    //char            **env;
    //t_redirection   *redir_lst;
} t_data;*/

int     make_env(char **envp);
//int get_path(t_exec *ex, t_input_data *data);
int make_path(t_exec *ex, t_input_data *data);
//int get_path(t_exec ex, t_input_data data);
//int check_and_set_path(t_input_data *data);

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
//int     get_index(t_exec *ex, char *var);
int     make_export(t_input_data *cmd, t_exec *ex);
char    *add_quotes(char *var);
void	update_env_loop(t_exec *ex, char **up_env, char *quote_var, int i);
int     make_unset(t_input_data *cmd, t_exec *ex);

int	exec_command(t_input_data *data, t_exec *ex);

//EXECUTION functions
int	make_path(t_exec *ex, t_input_data *data);
//void    make_child(t_data *data, char **env);
int	exec_command_lst(t_input_data *cmd, t_exec *ex);
//void	exec_only_cmd(t_data *data);
//void   make_child(t_input_data *cmd, int prev_pipe, int pipefd[2], t_exec *ex);
int    make_child(t_input_data *cmd, t_exec *ex);

//OPERATOR checkers and managers
void    split_redirection(char *str, t_input_data *data);
int     check_redirection(char *str);
//void    make_redirection(char *str);
int		check_pipe(char *str);
//int     check_before_after(char *str, t_data *data);

int     open_input(t_input_data *cmd);
int     open_output(t_input_data *cmd);
//void	make_heredoc(int fd, char *delim);
int	make_all_redirections(t_input_data *start, t_input_data *end);
//int     make_one_redirection(t_redirection *redir);
//int     make_redirections_lst(t_input_data *cmd);
//void	open_all(t_input_data *cmd);
void    make_pipe(t_input_data *cmd, int *prev_pipe, int pipefd[2]);
void    close_pipe(t_input_data *cmd, int *prev_pipe, int pipefd[2]);
int	exec_all(t_input_data *cmd, t_exec *ex);
int	exec_only_command(t_input_data *cmd, t_exec *ex);
int exec_pipe_commands(t_input_data *start, t_input_data *end, t_exec *ex);

t_input_data  *parse_input(char *input);

//char *find_command(char **paths, char *cmd);



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
//void    check_lst(t_data *data);
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


int structure_builtins_echo(t_input_data *structure);
//int structure_builtins_echo2(t_input_data *structure, t_input_data **temp, int *no_newline);


int init_tests_minishell(int *argc, char *argv[]);
int init_signals_minishell();
int malloc_inputdata(t_input_data **input_data);
int malloc_inputdata_and_data(t_input_data **input_data);
int clean_input_data2(t_input_data **temp_input, t_input_data **temp_next);
int clean_input_data(t_input_data **input_data);
int clean_input_data_reallocate(t_input_data **input_data, int malloc_data);
int ft_len(char *string_input, char end_char);
int add_string_to_string(char *data, char **line);
int ft_strcmp(char *s1, char *s2);
int execution_minishell(t_input_data *input_data, t_exec *ex);
int malloc_splitdata(t_split_data **split_data, t_input_data **structure, char *input_line);
int add_char_to_data(t_input_data *structure, char data);
int add_char_and_new_struct(t_split_data *split_data, char data, int no);
int replace_dollar(t_split_data *split_data, char *input_line, int *i);
int split_1(t_split_data **split_data, int *i, char *input_line);
int split_2(t_split_data **split_data, int *i, char *input_line);
int split_3(t_split_data **split_data, int *i, char *input_line);
int split_4_1(t_split_data **split_data, int *i, char *input_line);
int split_4(t_split_data **split_data, int *i, char *input_line);
int split_5_1(t_split_data **split_data, int *i, char *input_line);
int split_5_2(t_split_data **split_data, int *i, char *input_line);
int split_5_3(t_split_data **split_data, int *i, char *input_line);
int split_5(t_split_data **split_data, int *i, char *input_line);
int split_6(t_split_data **split_data, int *i, char *input_line);
int final_split_new_char(t_split_data *split_data, int *i, char *input_line);
int fill_structure(char *input_line, t_input_data **input_data);
int parsing_minishell(t_input_data **input_data);
int show_minishell(t_input_data **input_data, t_exec *ex);
int main(int argc, char *argv[], char **envp);
char    *read_line_moi();
char    *add_char_to_string(char **string, char new_char);
void    signal_handler_input(int signal);
void    output_line(char **line);
void    print_input_data(t_input_data   *input_data);




#endif