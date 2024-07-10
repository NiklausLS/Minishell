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
        //rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == SIGQUIT) 
    {
        rl_on_new_line();
        rl_redisplay();
        write(1, "  \b\b  \b\b", 8);
    }
}

int handle_eof()//à utiliser en fork pendant l'execution pour detecter si appuie sur ctrl-d
{
    char    *buffer;
    ssize_t bytes_read;

    buffer = malloc(sizeof(char) * 1);
    if (!buffer)
        printf("Error malloc buffer\n");
    if (!buffer)
        return (2);
    bytes_read = read(STDIN_FILENO, buffer, 1);//0 il me semble write(1, X, Xnb) ici c'est 0 au lieu de 1 et read au lieu de write
    if (bytes_read == 0)
    {
        printf("Exiting because Ctrl-D pressed\n");
        global_signal_received = 1;
        return (1);
    }
    if (bytes_read < 0)
    {
        printf("Error reading STDIN_FILENO\n");
        if (buffer)
            free(buffer);
        return (2);
    }
    if (buffer)
        free(buffer);
    return (0);
}