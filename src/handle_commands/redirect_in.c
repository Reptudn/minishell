/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/21 08:52:35 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	redirect_in(t_shunting_node *cmd, t_shunting_node *cmd2, t_shell *shell)
{
	int		fd;
	char	*redirect;

	// printf("cmd->value: %s\n", cmd->next->value);
	// printf("cmd->args[0]: %s\n", cmd->args[0]);
	fd = open(cmd2->value, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
		return (CMD_FAILURE);
	}

	// char *line = NULL;
	// size_t len = 0;
	// ssize_t read;

	// while ((read = getline(&line, &len, fd)) != -1)
	// 	redirect = ft_strjoin(redirect, line);

	// free(line);

	// return (CMD_SUCCESS);
	#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// ...

FILE *file = fdopen(fd, "r");
if (file == NULL)
{
    perror("fdopen");
    return (CMD_FAILURE);
}

char *line = NULL;
size_t len = 0;
ssize_t read;

while ((read = getline(&line, &len, file)) != -1)
    redirect = ft_strjoin(redirect, line);

free(line);
fclose(file);

return (CMD_SUCCESS);
}
