/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:03:12 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/14 13:51:04 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_surrounding_doubleq(char *str, int *changed);
char	*handle_single_quotes(char *str, t_temps *temp, char *var_str);
char	*handle_double_quotes(char *str, t_temps *temp, char *var_str);
char	*handle_dollar_sign(char *str, t_temps *temp, char *var_str);
int		expand_var(char **var_str, char *str);

void	insert_str_on_pos_w_len(char **str, char *insert, int pos, int len)
{
	char	*new_str;
	int		i;
	int		k;

	new_str = malloc((ft_strlen(*str) + ft_strlen(insert) - len + 1)
			* sizeof(char));
	if (!new_str)
		return ;
	i = -1;
	k = 0;
	while ((*str)[++i])
	{
		if (i == pos)
			while (*insert)
				new_str[k++] = *insert++;
		if (i < pos || i >= pos + len)
			new_str[k++] = (*str)[i];
	}
	new_str[k] = '\0';
	free(*str);
	*str = new_str;
}

char	*append_single_char(char *str, char c)
{
	int		len;
	char	*out;

	if (!str)
	{
		out = malloc(2 * sizeof(char));
		if (!out)
			return (NULL);
		out[0] = c;
		out[1] = '\0';
	}
	else
	{
		len = ft_strlen(str);
		out = ft_realloc(str, (len + 2) * sizeof(char));
		if (!out)
			return (NULL);
		out[len] = c;
		out[len + 1] = '\0';
	}
	return (out);
}

char	*get_var_str(char *str)
{
	t_temps	temp;
	char	*var_str;

	temp.int_i = -1;
	if (!str)
		return (NULL);
	var_str = NULL;
	while (str && str[++temp.int_i])
	{
		if (str[temp.int_i] == '\'')
			var_str = handle_single_quotes(str, &temp, var_str);
		else if (str[temp.int_i] == '\"')
			var_str = handle_double_quotes(str, &temp, var_str);
		else if (str[temp.int_i] == '$')
			var_str = handle_dollar_sign(str, &temp, var_str);
		else
			var_str = append_single_char(var_str, str[temp.int_i]);
	}
	if (str)
		free(str);
	return (var_str);
}
