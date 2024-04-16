/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:55:29 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/15 14:56:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_export(t_env_var *env)
{
	while (env)
	{
		if (env->value[0] == '\0')
			printf("declare -x %s\n", env->name);
		else
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
	return (CMD_SUCCESS);
}

int	export_error(void)
{
	ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
	return (CMD_FAILURE);
}
