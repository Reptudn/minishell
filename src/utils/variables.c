/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:05:49 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/08 09:40:01 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_matching_files(char *pattern);
char	*get_var_str(char *str, t_shell *shell);

void	handle_exit_status(char **arg, t_shell *shell)
{
	char	*a_status;
	char	*var;

	a_status = ft_itoa(*shell->exit_status);
	if (!a_status)
		return ;
	var = ft_strjoin(a_status, (*arg) + 2);
	free(a_status);
	if (!var)
		return ;
	free(*arg);
	*arg = var;
}

void	handle_env_var(char **arg, t_shell *shell)
{
	char		*var;
	t_env_var	*env_var;

	env_var = env_get_by_name(shell->env_vars, *arg + 1);
	if (!env_var)
		var = ft_strdup("");
	else
		var = ft_strdup(env_var->value);
	if (!var)
		return ;
	free(*arg);
	*arg = var;
}

// OBSOLETE
void	is_variable(char **arg, t_shell *shell)
{
	if (!arg || !*arg || *arg[0] != '$' || ft_strlen(*arg) == 1)
		return ;
	if (ft_strncmp(*arg, "$?", 2) == 0)
	{
		handle_exit_status(arg, shell);
		return ;
	}
	handle_env_var(arg, shell);
}

void	replace_variable(char *value, char **args, t_shell *shell)
{
	int		i;
	char	*matching;

	i = -1;
	if (!value || (!args && *args == NULL))
		return ;
	value = get_var_str(value, shell);
	while (args && args[++i])
	{
		args[i] = get_var_str(args[i], shell);
		matching = get_matching_files(args[i]);
		if (matching)
		{
			free(args[i]);
			args[i] = matching;
		}
	}
}

// TODO: update that shi- so that $T$T$T$T$T$T$T$T$T also works and expands each variable