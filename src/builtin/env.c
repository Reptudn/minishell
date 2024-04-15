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

int	ft_env(t_shell *shell)
{
	t_env_var	*env;
	int i = 0;

	env = shell->env_vars;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		else
			printf("%s=\n", env->name);
		env = env->next;
		i++;
	}
	printf("amount: %d\n", i);
	return (CMD_SUCCESS);
}
