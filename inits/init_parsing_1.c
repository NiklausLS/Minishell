//header

#include "../includes/minishell.h"

int show_minishell(t_input_data **input_data, t_exec *ex)
{
    int launch;
    int execution;

    while (42)
    {
        //en théorie doit faire rebasculer les signaux ici puisque changés dans l'execution
        launch = parsing_minishell(input_data);
        if (launch == 0)
        {
            execution = execution_minishell(*input_data, ex); //input_data
            printf("execution = %d\n", execution);
            if (execution == 1)
                return (1);
            else if (execution == 2)
                continue;
            //retour de 2 ou autres valeurs ???? par exemple si entre exit ou ctrl-d etc qui doivent terminer le shell et pas que l execution ???? et aussi shell doit continuer a tourner si erreur d execution mais pas erreur entrainant la fermeture du shell
        }
        if (launch == 1)
            return (1);
        printf("\n\n\n\n\n==============================  FINAL  ==========================\n");//
        //print_input_data(*input_data);//
        printf("==============================================================\n");//
        if (clean_input_data_reallocate(input_data, 0) == 1)
            return (1);
    }
    return (0);
}

int parsing_minishell(t_input_data **input_data)
{
    //mes signaux doivent être mis à jour après une nouvelle execution
    char    *input_line;
    int     res;//

    input_line = read_line_moi();
    if (!input_line)
    {
        printf("Exiting because Ctrl-D pressed or readline error\n");
        return (1);
    }
    res = fill_structure(input_line, input_data);//
    if (*input_line && res == 1)//
    //if (*input_line && (fill_structure(input_line, input_data) == 1))
    {
        free(input_line);
        input_line = NULL;
        return (1);
    }
    if (*input_line && res == 2)//
    {//
        free(input_line);//
        input_line = NULL;//
        //printf("ICI_0\n");//
        return (2);//
    }//
    if (input_line)
    {
        free(input_line);
        input_line = NULL;
    }
    return (0);
}

char    *read_line_moi(void)
{
    char    *input_line;

    init_signals_minishell();
    input_line = readline("Minishell> ");
    if (input_line && *input_line && global_signal_received != SIGINT)
        add_history(input_line);
    global_signal_received = 0;
    return (input_line);
}

int fill_structure(char *input_line, t_input_data **input_data)
{
    t_split_data    *split_data;
    int             res;//

    if (malloc_splitdata(&split_data, input_data, input_line) == 1)
        return (1);
    while (input_line[split_data->i] != '\0')
    {
        res = final_split_new_char(split_data, &(split_data->i), input_line);
        if (res == 1)
        //if (final_split_new_char(split_data, &(split_data->i), input_line) == 1)
        {
            if (split_data)
                free(split_data);
            return (1);
        }
        if (res == 2)//
        {//
            if (split_data)//
                free(split_data);//
            //printf("ICI_1\n");//
            return (2);//
        }//
        split_data->i++;
    }
    if (split_data)
        free(split_data);
    return (0);
}

int final_split_new_char(t_split_data *split_data, int *i, char *input_line)
{
    int res;

    res = split_1(&split_data, i, input_line);
    if (res != 2)
        return (res);
    if (res == 3)//
        return (2);//
    res = split_2(&split_data, i, input_line);
    if (res != 2 && res != 3)
        return (res);
    if (res == 3)//
        return (2);//
    res = split_3(&split_data, i, input_line);
    if (res != 2)
        return (res);
    res = split_4(&split_data, i, input_line);
    if (res != 2)
        return (res);
    res = split_5(&split_data, i, input_line);
    if (res != 2)
        return (res);
    res = split_6(&split_data, i, input_line);
    if (res != 2)
        return (res);
    return (0);
}