/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:05:49 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/20 10:00:09 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	is_variable(char **arg, t_shell *shell, int status)
{
	char		*var;
	char		*a_status;
	t_env_var	*env_var;

	if (!arg || !*arg || *arg[0] != '$')
		return ;
	if (ft_strncmp(*arg, "$?", 2) == 0)
	{
		a_status = ft_itoa(status);
		if (!a_status)
			return ;
		var = ft_strjoin(a_status, (*arg) + 2);
		free(a_status);
		if (!var)
			return ;
		free(*arg);
		*arg = var;
		return ;
	}
	env_var = env_get_by_name(shell->env_vars, *arg + 1);
	if (!env_var)
		var = ft_strdup("");
	else
		var = ft_strdup(env_var->value);
	if (!var)
		return ;
	free(*arg);
	*arg = var;
	return ;
}

void	replace_variable(char **args, t_shell *shell, int status)
{
	int	i;

	i = -1;
	while (args[++i])
		is_variable(&args[i], shell, status);
}
