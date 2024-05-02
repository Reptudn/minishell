/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:34:36 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/18 10:07:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_env_vars(void)
{
	t_env_var	*env;

	env = get_shell()->env_vars;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (CMD_SUCCESS);
}

// TODO: make this a bool return and return false if it didnt work and true if it works and just make a pointer ref to the vars var in the main env func
t_env_var	*get_env_cmd_vars(char **args, int *i)
{
	t_env_var	*vars;
	t_env_var	*new;
	char		**split;

	vars = NULL;
	while (ft_strchr(args[++(*i)], '='))
	{
		split = split_first_occurence(args[*i], '=');
		if (!split)
			return (NULL);
		new = env_create_var(split[0], split[1], false);
		if (!new)
			return (NULL);
		env_push(vars, new);
		free_split(split);
	}
	return (vars);
}

int	ft_env(t_shunting_node *cmd)
{
	t_env_var	*env_env;
	int			i;

	if (!cmd)
		return (CMD_FAILURE);
	if (!cmd->args || !cmd->args[0])
		return (print_env_vars());
	i = -1;
	env_env = get_env_cmd_vars(cmd->args, &i);

	return (CMD_SUCCESS);
}
