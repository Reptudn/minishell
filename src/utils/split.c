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
char	**clean_quotes(char **tmp);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		weird_shell_op(const char *str);
void	process_string_helper(t_temps *temp, const char *str, int *i);
int		**get_i(void);
char	***get_shell_op(void);

int	process_string_helper2(t_temps *temp, char **result, int *res_i,
	const char *str)
{
	int	*i;

	i = *get_i();
	if (!str_is_equal(temp->charp_i, "")
		|| !str_is_equal(temp->charp_i, " "))
		result[(*res_i)++] = temp->charp_i;
	result[(*res_i)++] = ft_substr(&str[(*i)], 0, temp->int_j);
	(*i) += temp->int_j - 1;
	temp->charp_i = ft_strdup("");
	if (!temp->charp_i)
		return (1);
	return (0);
}

int	process_string_helper3(t_temps *temp, char **result, int *res_i,
	const char *str)
{
	int	*i;

	i = *get_i();
	if (ft_isspace(str[(*i)]))
	{
		if (!str_is_equal(temp->charp_i, "")
			|| !str_is_equal(temp->charp_i, " "))
			result[(*res_i)++] = temp->charp_i;
		temp->charp_i = ft_strdup("");
		if (!temp->charp_i)
			return (420);
		return (69);
	}
	temp->charp_i = append_single_char(temp->charp_i, str[(*i)]);
	if (!temp->charp_i)
		return (420);
	return (0);
}

int	process_string_helper4(t_temps *temp, char **result, int *res_i,
	const char *str)
{
	int		*i;
	char	**shell_op;

	i = *get_i();
	shell_op = *get_shell_op();
	temp->int_j = is_shell_op((char *) &str[(*i)], shell_op, 10);
	if (temp->int_j != 0)
	{
		if (process_string_helper2(temp, result, res_i, str))
			return (69);
	}
	else
	{
		temp->int_l = process_string_helper3(temp, result, res_i, str);
		if (temp->int_l == 420)
			return (69);
		else if (temp->int_l == 69)
			return (420);
	}
	return (0);
}

int	process_string_helper5(const char *str, t_temps *temp,
		char **result, int **res_i)
{
	int	*i;

	i = *get_i();
	if (str[(*i)] == '"' || str[(*i)] == '\'')
		process_string_helper(temp, str, i);
	else
	{
		temp->int_k = process_string_helper4(temp, result,
				*res_i, str);
		if (temp->int_k == 69)
			return (69);
		else if (temp->int_k == 420)
			return (420);
	}
	return (0);
}

void	process_string(const char *str, char **result, int *res_i)
{
	t_temps	temp;
	char	**shell_op;
	int		i;
	char	quote;

	i = -1;
	*get_i() = &i;
	shell_op = fill_shell_op();
	*get_shell_op() = shell_op;
	temp.charp_i = NULL;
	if (weird_shell_op(str))
		(*res_i)--;
	while (str[++i])
	{
		temp.int_m = process_string_helper5(str, &temp, result, &res_i);
		if (temp.int_m == 69)
			return ;
		else if (temp.int_m == 420)
			continue ;
	}
	if (!str_is_equal(temp.charp_i, "") || !str_is_equal(temp.charp_i, " "))
		result[(*res_i)++] = temp.charp_i;
	result[(*res_i)] = NULL;
}
