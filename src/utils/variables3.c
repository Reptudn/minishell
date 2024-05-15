/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:43:35 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/15 08:53:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		expand_var(char **var_str, char *str, bool trim);
char	*append_single_char(char *str, char c);

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"' || c == ' ');
}

char	*handle_single_quotes(char *str, t_temps *temp, char *var_str)
{
	temp->int_i++;
	while (str[temp->int_i] && str[temp->int_i] != '\'')
		var_str = append_single_char(var_str, str[temp->int_i++]);
	return (var_str);
}

char	*handle_double_quotes(char *str, t_temps *temp, char *var_str)
{
	temp->int_i++;
	while (str[temp->int_i] && str[temp->int_i] != '\"')
	{
		if (str[temp->int_i] == '$' && str[temp->int_i + 1] != '\"')
			temp->int_i += expand_var(&var_str, str + temp->int_i, false);
		else
			var_str = append_single_char(var_str, str[temp->int_i++]);
	}
	return (var_str);
}

char	*handle_dollar_sign(char *str, t_temps *temp, char *var_str, int index)
{
	bool	trim;

	if (str[temp->int_i + 1])
	{
		trim = true;
		if (index == 0)
			trim = false;
		temp->int_i += expand_var(&var_str, str + temp->int_i, trim) - 1;
	}
	else
		var_str = append_single_char(var_str, str[temp->int_i]);
	return (var_str);
}
