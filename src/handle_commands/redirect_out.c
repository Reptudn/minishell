/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/11 09:54:47 by jkauker          ###   ########.fr       */
=======
/*   Updated: 2024/03/11 09:40:57 by jkauker          ###   ########.fr       */
>>>>>>> 0561abd691d02b948ef172efeee9764ad311dacd
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

<<<<<<< HEAD
int redirect_out(t_shunting_node *cmd, t_shell *shell)
{
	// int fd;
	// int i;
	// char *buffer;

	// i = 0;
	// fd = open(cmd->next->command, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (fd == -1)
	// {
	// 	printf("minishell: %s: %s\n", cmd->next->command, strerror(errno));
	// 	return (CMD_FAILURE);
	// }
	// //buffer??
	// write (fd, buffer, ft_strlen(buffer));
	// free(buffer);
	// close(fd);
=======
int	redirect_out(t_command *cmd, t_shell *shell)
{
	int		fd;
	int		i;
	char	*buffer;

	i = 0;
	fd = open(cmd->next->command, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", cmd->next->command, strerror(errno));
		return (CMD_FAILURE);
	}
	write (fd, buffer, ft_strlen(buffer));
	free(buffer);
	close(fd);
>>>>>>> 0561abd691d02b948ef172efeee9764ad311dacd
	return (CMD_SUCCESS);
}
