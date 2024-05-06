#ifndef EXEC_REDIRECT_H
# define EXEC_REDIRECT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# include "../LIBFT/includes/libft.h"

//OPERATOR checkers and managers
void    split_redirection(char *str);
void    manage_redirection(char *str);

//PROTECTED functions so make other functionsmy code shorter
int	protected_open(char *file_name, int flags);

#endif