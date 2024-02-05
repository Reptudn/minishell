/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:17:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 14:16:40 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

int is_valid_input(char **split)
{
	if (is_operator(split[0]))
		return (0);
	if (is_operator(split[ft_strlen(split[0]) - 1]))
		return (0);
	return (1);
}

int allocate_cmd(t_command *cmd, char **split)
{
	int i;
	int arg_count;

	i = 0;
	arg_count = 0;
	cmd->command = ft_strdup(split[0]);
	printf("Command: %s\n", cmd->command);
	if (!cmd->command)
		return (0);
	while (split[i] && is_operator(split[i]) != NONE)
	{
		i++;
		arg_count++;
	}
	cmd->args = malloc(arg_count * sizeof(char *));
	i -= arg_count;
	arg_count = 0;
	while (split[i] && is_operator(split[i]) != NONE)
	{
		cmd->args[arg_count] = ft_strdup(split[i]);
		printf("Arg: %s\n", cmd->args[arg_count]);
		if (!cmd->args[arg_count])
			break;
		arg_count++;
		i++;
	}
	if (split[i] && is_operator(split[i]))
	{
		cmd->operator_type = malloc(sizeof(int));
		if (!cmd->operator_type)
			return(0);
		*(cmd->operator_type) = is_operator(split[i]);
		printf("Operator: %d\n", *cmd->operator_type);
		i++;
	}
	cmd->prev = NULL;
	cmd->next = NULL;
	return (i);
}

t_command *make_cmds(char *line, t_shell *shell)
{
	char 		**split;
	int 		i;
	t_command	*first;
	// int arg_count;

	split = ft_split_shell(line);
	for (i = 0; split[i]; i++)
		printf("Split[%d]: %s\n", i, split[i]);
	printf("--------------------\n");
	if (!split)
		return (0);
	first = malloc(sizeof(t_command));
	if (!first)
		return (free_split(split));
	i = allocate_cmd(first, split);
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
