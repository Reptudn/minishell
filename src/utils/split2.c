/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:09 by nsabia            #+#    #+#             */
/*   Updated: 2024/05/17 11:57:32 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*append_single_char(char *str, char c);

int	weird_shell_op(const char *str)
{
	char	**shell_op;
	char	*first_two_chars;
	int		i;

	shell_op = fill_shell_op();
	first_two_chars = ft_malloc(3);
	i = -1;
	first_two_chars = ft_strncpy(first_two_chars, str, 2);
	while (shell_op[++i])
	{
		if (str[0] == *shell_op[i] || first_two_chars == shell_op[i])
			return (1);
	}
	return (0);
}

void	process_string_helper(t_temps *temp, const char *str, int *i)
{
	char	quote;

	temp->int_j = 0;
	quote = str[(*i)];
	while (str[(*i)])
	{
		if (str[(*i)] == quote && temp->int_j++ > 0)
		{
			temp->charp_i = append_single_char(temp->charp_i, str[(*i)]);
			break ;
		}
		temp->charp_i = append_single_char(temp->charp_i, str[(*i)]);
		if (!temp->charp_i)
			return ;
		(*i)++;
	}
}

int	**get_i(void)
{
	static int	*i;

	return (&i);
}

char	***get_shell_op(void)
{
	static char	**ops;

	return (&ops);
}
