/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:55:29 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/30 10:24:20 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_export(t_env_var *env)
{
	while (env)
	{
		if (!env->value)
			printf("declare -x %s\n", env->name);
		else if (env->value[0] == '\0')
			printf("declare -x %s=\"\"\n", env->name);
		else
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
	return (CMD_SUCCESS);
}

int	export_error(char *arg)
{
	if (!arg)
	{
		ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		return (CMD_FAILURE);
	}
	ft_putstr_fd("minishell: export: `", 2);
	if (arg[0] == '-')
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': invalid option\n", 2);
		ft_putstr_fd("export: usage: export name[=value] ...\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (CMD_FAILURE);
}
