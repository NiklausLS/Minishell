//header

#include "../includes/minishell.h"

void    print_input_data(t_input_data   *input_data)
{
    t_input_data    *temp_input;

    temp_input = input_data;
    printf("Structure's DATA :\n");
    while (temp_input)
    {
        printf("\n%p\nDATA: '%s' bdq: '%d' bsq: '%d'  NsNs: '%d'\n",temp_input, temp_input->data, temp_input->between_double_quotes, temp_input->between_single_quotes, temp_input->next_structure_without_space);
        printf("NDSC_id : %p\n", temp_input->next_data_same_command_id);
        printf("NC_ID : %p\n", temp_input->next_command_id);
        if (temp_input->next_data_same_command_id && temp_input->next_command_id)
        {
            printf("\nError, 2 linked lists\n");
        }
        else 
        {
            if (temp_input->next_data_same_command_id)
            {
                printf("   ndsc_id\n");
                temp_input = temp_input->next_data_same_command_id;
            }
            else //if (temp->next_command_id)
            {
                printf("   nc_id\n");
                temp_input = temp_input->next_command_id;
            }
        }
    }
    printf("END Structure DATA\n");
}