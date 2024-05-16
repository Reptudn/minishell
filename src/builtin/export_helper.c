/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:55:29 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/16 12:27:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	replace_existing_val(char **split, t_env_var *env, bool append);

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

bool	is_valid_var_indentifier(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	i = 0;
	while (arg[++i])
	{
		if (arg[i] == '+' && arg[i + 1] == 0)
			return (true);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
	}
	return (true);
}

int	handle_no_equal(t_shell *shell, char *arg)
{
	t_env_var	*env;

	if (!is_valid_var_indentifier(arg))
		return (export_error(arg));
	env = env_get_by_name(shell->env_vars, arg);
	if (!env)
	{
		env = env_create_var(arg, NULL, false);
		if (!env)
			return (CMD_FAILURE);
		env_push(shell->env_vars, env);
	}
	else
	{
		// ft_free((env->value));
		env->value = NULL;
	}
	return (CMD_SUCCESS);
}

int	handle_arg_helper(char **split, t_env_var *env, bool append)
{
	replace_existing_val(split, env, append);
	return (1);
}
