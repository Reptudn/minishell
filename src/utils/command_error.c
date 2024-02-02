/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:58:11 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/02 14:00:16 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_invalid_cmd(char *command)
{
	char	**args;
	int		i;

	args = ft_split(command, ' ');
	i = -1;
	printf("%scommand not found: %s%s\n%s", COLOR_RED,
		COLOR_MAGENTA, args[0], COLOR_RESET);
	while (args[++i])
		free(args[i]);
	free(args);
}
