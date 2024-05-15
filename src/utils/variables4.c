/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:49:41 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/15 07:51:18 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*append_single_char(char *str, char c);

static int	handle_question_mark(char **var_str, char *str)
{
	char	*var;

	var = ft_itoa(*get_shell()->exit_status);
	if (!var)
		return (-1);
	*var_str = ft_strjoin(*var_str, var);
	free(var);
	if (!var_str)
		return (-1);
	return (2);
}

static int	handle_space(char **var_str)
{
	*var_str = append_single_char(*var_str, '$');
	return (1);
}

static int	handle_var(char **var_str, char *str, int len)
{
	char		*var;
	t_env_var	*env_var;

	var = ft_substr(str, 0, len);
	if (!var)
		return (-1);
	env_var = env_get_by_name(get_shell()->env_vars, var);
	if (!env_var)
	{
		free(var);
		return (len + 1);
	}
	*var_str = ft_strjoin(*var_str, env_var->value);
	free(var);
	if (!var_str)
		return (-1);
	if (len == 0)
		return (1);
	return (len + 1);
}

int	expand_var(char **var_str, char *str)
{
	int	len;

	if (*str != '$')
		return (0);
	str++;
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	if (*str == '?' && len == 0)
		return (handle_question_mark(var_str, str));
	else if (*str == ' ')
		return (handle_space(var_str));
	else
		return (handle_var(var_str, str, len));
}
