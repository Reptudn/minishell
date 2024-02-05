/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:17:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 12:19:00 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

int is_operator(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (ft_strncmp(str, "|", 1) == 0)
			return (PIPE);
		if (ft_strncmp(str, ">", 1) == 0)
			return (REDIRECT_OUT);	
		if (ft_strncmp(str, "<", 1) == 0)
			return (REDIRECT_IN);
	}
	else if (ft_strlen(str) == 2)
	{
		if (ft_strncmp(str, "||", 1) == 0)
			return (OR);
		if (ft_strncmp(str, "&&", 1) == 0)
			return (AND);
		if (ft_strncmp(str, ">>", 1) == 0)
			return (REDIRECT_OUT_APPEND);
		if (ft_strncmp(str, "<<", 1) == 0)
			return (REDIRECT_IN_DELIMITER);
	}
	return (NONE);
}

int is_valid_input(char **split)
{

}

int allocate_cmd(t_command *cmd, char **split)
{
	int i;
	int arg_count;

	i = 0;
	arg_count = 0;
	cmd->command = ft_strdup(split[0]);
	if (!cmd->command)
		return (0);
	while (split[i] && is_operator(split[i]) != NONE)
	{
		cmd->args[arg_count] = ft_strdup(split[i]);
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
		i++;
	}
	return (i);
}

t_command *make_cmds(char *line, t_shell *shell)
{
	char 		**split;
	int 		i;
	t_command	*first;
	int arg_count;

	split = ft_split_shell(line);
	if (!split || !is_valid_input(split))
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
	i = -1;
	free_split(split);
	return(first);
}
