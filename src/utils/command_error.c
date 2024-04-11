/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:58:11 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 13:36:58 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: print errors in std error
// FIXME: this should also print the error message when running || and the first cmd fails
void	print_invalid_cmd(char *command)
{
	char	**args;
	int		i;

	args = ft_split(command, ' ');
	if (!args)
	{
		printf("%sminishell: command not found\n%s", color_red(), color_reset());
		// ft_putstr_fd("minishell: command not found\n", 2);
		return ;
	}
	i = -1;
	printf("%sminishell: command not found: %s%s\n%s", color_red(),
		color_magenta(), args[0], color_reset());

	// ft_putstr_fd("minishell: command not found\n", 2);
	while (args[++i])
		free(args[i]);
	free(args);
}
