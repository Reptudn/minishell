/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:17:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/06 15:17:11 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_shunting_yard	*shunting_yard_create(char	**tokens);

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
		{
			while(arg_count > 0)
				free(cmd->args[--arg_count]);
			free(cmd->args);
			break ;
		}
		arg_count++;
		i++;
	}
	if (split[i] && is_operator(split[i]) != 0)
	{
		cmd->operator_type = malloc(sizeof(int));
		if (!cmd->operator_type)
			return (0);
		*(cmd->operator_type) = is_operator(split[i]);
		i++;
	}
	cmd->prev = NULL;
	cmd->next = NULL;
	return (i);
}

t_command	*make_cmds(char *line, t_shell *shell)
{
	char		**split;
	char		**split_2;
	int			i;
	t_command	*current;
	t_command	*new_cmd;
	t_command	*prev;

	line = is_valid_input(line);
	if (!line)
		return (0);
	split = ft_split_shell(line);
	if (!split)
		return (NULL);
	split_2 = filter_variables(split, shell);
	if (!split_2)
	{
		free_split(split);
		return (NULL);
	}
	free_split(split);
	shunting_yard_create(split_2);
	current = malloc(sizeof(t_command));
	if (!current)
		return (free_split(split_2));
	i = 0;
	i = allocate_cmd(current, split_2, i);
	while (split_2[i])
	{
		new_cmd = malloc(sizeof(t_command));
		if (!new_cmd)
		{
			while (current != NULL)
			{
				prev = current->prev;
				free_cmds(current);
				current = prev;
				free(split_2);
			}
			return (NULL);
		}
		i = allocate_cmd(new_cmd, split_2, i);
		current->next = new_cmd;
		new_cmd->prev = current;
		current = new_cmd;
	}
	free_split(split_2);
	return (current);
}

