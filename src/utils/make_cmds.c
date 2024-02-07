/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:17:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/07 13:36:52 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

int allocate_cmd(t_command *cmd, char **split)
{
	int i;
	int arg_count;

	i = 0;
	arg_count = 0;

	//kopiere den ersten command
	cmd->command = ft_strdup(split[0]);
	if (!cmd->command)
		return (0);
	//solange keine shell_op weiterlaufen
	while (split[i] && is_operator(split[i]) != NONE)
	{
		i++;
		arg_count++;
	}

	//entsprechend viel platz allocieren
	cmd->args = malloc(arg_count * sizeof(char *));
	if (!cmd->args)
		return (0);

	//starte beim erste nicht command
	i = 1;
	arg_count = 0;

	//kopiert in die args solange kein shell_op
	while (split[i])
	{
		cmd->args[arg_count] = ft_strdup(split[i]);
		printf("allocate_cmds[%d]: %s\n", arg_count, cmd->args[arg_count]);
		if (!cmd->args[arg_count])
			break;
		arg_count++;
		i++;
	}
	cmd->args[arg_count] = NULL;

	//wenn es ein shell_op gibt dann reinkopieren
	if (split[i] && is_operator(split[i]))
	{
		cmd->operator_type = malloc(sizeof(int));
		if (!cmd->operator_type)
			return(0);
		*(cmd->operator_type) = is_operator(split[i]);
		i++;
	}

	//nur gegen segfaults
	cmd->prev = NULL;
	cmd->next = NULL;
	return (i);
}

t_command *make_cmds(char *line, t_shell *shell)
{
	char 		**split;
	int			i;
	t_command	*first;
	// int arg_count;

	split = ft_split_shell(line);
	if (!split)
		return (0);
	first = malloc(sizeof(t_command));
	if (!first)
		return (free_split(split));
	i = allocate_cmd(first, split);
	for (int j = 0; first->args[j]; j++)
	{
		printf("make_cmds[%d]: %s\n", j, first->args[j]);
	}
	// while (split[++i])
	// {
	// 	if (!cmd)
	// 		return (0);
	// 	cmd->command = split[i];
	// 	arg_count = 0;
	// 	while (split[i] && is_operator(split[i]) != NONE)
	// 	{
	// 		cmd->args[arg_count] = ft_strdup(split[i]);
	// 		if (!cmd->args[arg_count])
	// 			break;
	// 		arg_count++;
	// 		i++;
	// 	}
	// 	if (split[i] && is_operator(split[i]))
	// 	{
	// 		cmd->operator_type = malloc(sizeof(int));
	// 		if (!cmd->operator_type)
	// 			break;
	// 		*(cmd->operator_type) = is_operator(split[i]);
	// 		i++;
	// 	}
	// 	cmd->args = malloc(arg_count * sizeof(char *));
	// 	if (!cmd->args)
	// 		break;
	// }
	free_split(split);
	return(first);
}
