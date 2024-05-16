/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:06:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:23:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

char	*append_single_char(char *str, char c);

void	ft_fuck1(const char *dick1, t_process_string *dick)
{
	dick->temp.int_j = 0;
	dick->quote = dick1[dick->i];
	while (dick1[dick->i])
	{
		if (dick1[dick->i] == dick->quote && dick->temp.int_j++ > 0)
		{
			dick->temp.charp_i = append_single_char(
					dick->temp.charp_i, dick1[dick->i]);
			break ;
		}
		dick->temp.charp_i = append_single_char(dick->temp.charp_i,
				dick1[dick->i]);
		if (!dick->temp.charp_i)
			return ;
		dick->i++;
	}
}

int	ft_fuck3(const char *dick_3, t_process_string *dick1,
		char **nis_pe, int *hu_so)
{
	if (ft_isspace(dick_3[dick1->i]))
	{
		if (!str_is_equal(dick1->temp.charp_i, "")
			|| !str_is_equal(dick1->temp.charp_i, " "))
			nis_pe[(*hu_so)++] = dick1->temp.charp_i;
		dick1->temp.charp_i = ft_strdup("");
		if (!dick1->temp.charp_i)
			return (0);
		return (1);
	}
	dick1->temp.charp_i = append_single_char(dick1->temp.charp_i,
			dick_3[dick1->i]);
	if (!dick1->temp.charp_i)
		return (0);
}

int	ft_fuck2(const char *dick, t_process_string *dick2,
		char **nis_pe, int *hu_so)
{
	dick2->temp.int_j = is_shell_op((char *) &dick[dick2->i],
			dick2->shell_op, 10);
	if (dick2->temp.int_j != 0)
	{
		if (!str_is_equal(dick2->temp.charp_i, "")
			|| !str_is_equal(dick2->temp.charp_i, " "))
			nis_pe[(*hu_so)++] = dick2->temp.charp_i;
		nis_pe[(*hu_so)++] = ft_substr(&dick[dick2->i], 0,
				dick2->temp.int_j);
		dick2->i += dick2->temp.int_j - 1;
		dick2->temp.charp_i = ft_strdup("");
		if (!dick2->temp.charp_i)
			return (0);
	}
	else
		return (ft_fuck3(dick, dick2, nis_pe, hu_so));
	return (1);
}

void	process_string(const char *str, char **result, int *res_i)
{
	t_process_string	string;

	string.i = -1;
	string.shell_op = fill_shell_op();
	string.temp.charp_i = NULL;
	while (str[++(string.i)])
	{
		if (str[string.i] == '"' || str[string.i] == '\'')
			ft_fuck1(str, &string);
		else
		{
			if (ft_fuck2(str, &string, result, res_i))
				continue ;
			else
				return ;
		}
	}
	if (!str_is_equal(string.temp.charp_i, "")
		|| !str_is_equal(string.temp.charp_i, " "))
		result[(*res_i)++] = string.temp.charp_i;
	result[(*res_i)] = NULL;
	free_split(string.shell_op);
}

char	**clean_quotes(char **tmp)
{
	char	**result;
	int		i;
	int		m;

	i = 0;
	while (tmp[i])
		i++;
	result = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!tmp || !result)
	{
		if (result)
			// ft_free((result));
		return (NULL);
	}
	i = -1;
	m = -1;
	while (tmp[++i])
	{
		if (!str_is_equal(tmp[i], "(") && !str_is_equal(tmp[i], ")"))
			result[++m] = ft_strdup(tmp[i]);
	}
	result[++m] = NULL;
	return (result);
}
