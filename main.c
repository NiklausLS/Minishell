//header

#include "includes/minishell.h"

int global_signal_received = 0;

int main(int argc, char *argv[], char **envp)
{
    t_input_data    *input_data;
    t_exec  *ex;

    input_data = NULL;
    ex = malloc(sizeof(t_exec));
    if (init_tests_minishell(&argc, argv) == 1)
        return (1);
    if (init_exec_structure(ex, envp) == 1)
        return (1);
    // if (init_signals_minishell() == 1)
    //     return (1);
    if (malloc_inputdata(&input_data) == 1)
        return (1);
    input_data->env = &envp;
    if (show_minishell(&input_data, ex) == 1)
    {
        clean_input_data(&input_data);
        return (1);
    }
   /*if (clean_input_data(&input_data) == 1)//
    {
        printf("MAIN ---- USING CLEAN INPUT DATA\n");
        return (1);//
    }*/
    return (0);
}