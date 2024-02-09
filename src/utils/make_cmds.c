/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:17:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/09 13:16:28 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

int allocate_cmd(t_command *cmd, char **split, int i)
{
	int arg_count;

	arg_count = 0;
	cmd->command = ft_strdup(split[i]);
	i++;
	if (!cmd->command)
		return (0);
	while (split[i] && is_operator(split[i]) != NONE)
	{
		i++;
		arg_count++;
	}
	cmd->args = malloc(arg_count * sizeof(char *));
	if (!cmd->args)
		return (0);
	arg_count = 0;
	i = i - arg_count;
	while (split[i] && is_operator(split[i]) == 0)
	{
		cmd->args[arg_count] = ft_strdup(split[i]);
		if (!cmd->args[arg_count])
			break;
		arg_count++;
		i++;
		// printf("cmd->args[%d] = %s\n", arg_count, cmd->args[arg_count]);
	}
	// printf("cmd->args[0] = %s\n", cmd->args[0]);
	cmd->args[arg_count] = NULL;
	if (split[i] && is_operator(split[i]) != 0)
	{
		cmd->operator_type = malloc(sizeof(int));
		if (!cmd->operator_type)
			return(0);
		*(cmd->operator_type) = is_operator(split[i]);
		i++;
	}
	cmd->prev = NULL;
	cmd->next = NULL;
	return (i);
}

t_command *make_cmds(char *line, t_shell *shell)
{
	char		**split;
	int			i;
	t_command	*first;
	t_command	*current;
	t_command	*new_cmd;

	split = ft_split_shell(line);
	if (!split)
		return (0);
	first = malloc(sizeof(t_command));
	if (!first)
		return (free_split(split));
	i = 0;
	i = allocate_cmd(first, split, i);
	current = first;
	while (split[i])
	{
		new_cmd = malloc(sizeof(t_command));
		if (!new_cmd)
		{
			t_command *prev;
			while (current != NULL)
			{
				prev = current->prev;
				free_cmds(current);
				current = prev;
			}
			return (NULL);
		}
		i = allocate_cmd(new_cmd, split, i);
		current->next = new_cmd;
		new_cmd->prev = current;
		current = new_cmd;
	}
	free_split(split);
	return(first);
}









// t_command *make_cmds(char *line, t_shell *shell)
// {
// 	char 		**split;
// 	int			i;
// 	t_command	*first;
// 	// int arg_count;

// 	split = ft_split_shell(line);
// 	if (!split)
// 		return (0);
// 	// is_valid_input(split, line); //segfault kommen von hier
// 	first = malloc(sizeof(t_command));
// 	if (!first)
// 		return (free_split(split));
// 	i = allocate_cmd(first, split);
// 	// while (split[++i])
// 	// {
// 	// 	if (!cmd)+
// 	// 		return (0);
// 	// 	cmd->command = split[i];
// 	// 	arg_count = 0;
// 	// 	while (split[i] && is_operator(split[i]) != NONE)
// 	// 	{
// 	// 		cmd->args[arg_count] = ft_strdup(split[i]);
// 	// 		if (!cmd->args[arg_count])
// 	// 			break;
// 	// 		arg_count++;
// 	// 		i++;
// 	// 	}
// 	// 	if (split[i] && is_operator(split[i]))
// 	// 	{
// 	// 		cmd->operator_type = malloc(sizeof(int));
// 	// 		if (!cmd->operator_type)
// 	// 			break;
// 	// 		*(cmd->operator_type) = is_operator(split[i]);
// 	// 		i++;
// 	// 	}
// 	// 	cmd->args = malloc(arg_count * sizeof(char *));
// 	// 	if (!cmd->args)
// 	// 		break;
// 	// }
// 	free_split(split);
// 	return(first);
// }
