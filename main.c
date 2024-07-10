//header

#include "includes/minishell.h"

int global_signal_received = 0;

int main(int argc, char *argv[], char **envp)
{
    t_input_data    *input_data;

    input_data = NULL;
    if (init_tests_minishell(&argc, argv) == 1)
        return (1);
    // if (init_signals_minishell() == 1)
    //     return (1);
    if (malloc_inputdata(&input_data) == 1)
        return (1);
    input_data->env = &envp;
    if (show_minishell(&input_data) == 1)
    {
        clean_input_data(&input_data);
        return (1);
    }
    if (clean_input_data(&input_data) == 1)//
        return (1);//
    return (0);
}