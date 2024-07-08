//header

#include "../includes/minishell.h"

int init_signals_minishell()
{
    struct sigaction sa;

    sa.sa_handler = signal_handler_input;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        printf(" Error with Sigaction SIGINT \n");
        return (1);
    }
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
    {
        printf(" Error with Sigaction SIGQUIT \n");
        return (1);
    }
    return (0);
}

void    signal_handler_input(int signal)
{
    if (signal == SIGINT)
    {
        global_signal_received = SIGINT;
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == SIGQUIT) 
    {
        rl_on_new_line();
        rl_redisplay();
        write(1, "  \b\b  \b\b", 8);
    }
}

