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

// TODO: echo '$ANTHING' should display $ANTHING and not the value of the variable

void	is_variable(char **arg, t_shell *shell)
{
	char		*var;
	char		*a_status;
	t_env_var	*env_var;

	if (!arg || !*arg || *arg[0] != '$' || ft_strlen(*arg) == 1)
		return ;
	if (ft_strncmp(*arg, "$?", 2) == 0)
	{
		a_status = ft_itoa(*shell->exit_status);
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
}

// FIXME: echo '"$USER"' should display "$USER" and not the value of the variable
void	replace_variable(char **args, t_shell *shell)
{
	int		i;
	char	*matching;

	i = -1;
	if (!args && *args == NULL)
		return ;
	while (args && args[++i])
	{
		is_variable(&args[i], shell);
		matching = get_matching_files(args[i]);
		if (matching)
		{
			free(args[i]);
			args[i] = matching;
		}
	}
}
