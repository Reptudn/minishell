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

char		*append_single_char(char *str, char c);

void	process_quote(t_process *proc)
{
	char	quote;

	proc->temp->int_j = 0;
	quote = proc->str[*proc->i];
	while (proc->str[*proc->i])
	{
		if (proc->str[*proc->i] == quote && proc->temp->int_j++ > 0)
		{
			proc->temp->charp_i = append_single_char(proc->temp->charp_i,
					proc->str[*proc->i]);
			break ;
		}
		proc->temp->charp_i = append_single_char(proc->temp->charp_i,
				proc->str[*proc->i]);
		if (!proc->temp->charp_i)
			return ;
		(*proc->i)++;
	}
}

void	process_shell_op(t_process *proc, char **result, int *res_i,
	char **shell_op)
{
	proc->temp->int_j = is_shell_op((char *) &proc->str[*proc->i],
			shell_op, 10);
	if (proc->temp->int_j != 0)
	{
		if (!str_is_equal(proc->temp->charp_i, "")
			|| !str_is_equal(proc->temp->charp_i, " "))
			result[(*res_i)++] = proc->temp->charp_i;
		result[(*res_i)++] = ft_substr(&proc->str[*proc->i], 0,
				proc->temp->int_j);
		*proc->i += proc->temp->int_j - 1;
		proc->temp->charp_i = ft_strdup("");
	}
}

void	process_space(t_process *proc, char **result, int *res_i)
{
	if (ft_isspace(proc->str[*proc->i]))
	{
		if (!str_is_equal(proc->temp->charp_i, "")
			|| !str_is_equal(proc->temp->charp_i, " "))
			result[(*res_i)++] = proc->temp->charp_i;
		proc->temp->charp_i = ft_strdup("");
	}
	else
		proc->temp->charp_i = append_single_char(proc->temp->charp_i,
				proc->str[*proc->i]);
}

void	process_string(const char *str, char **result, int *res_i)
{
	t_temps		temp;
	char		**shell_op;
	int			i;
	t_process	proc;

	i = -1;
	shell_op = fill_shell_op();
	temp.charp_i = NULL;
	proc.str = str;
	proc.i = &i;
	proc.temp = &temp;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			process_quote(&proc);
		else
		{
			process_shell_op(&proc, result, res_i, shell_op);
			process_space(&proc, result, res_i);
		}
	}
	if (!str_is_equal(temp.charp_i, "") || !str_is_equal(temp.charp_i, " "))
		result[(*res_i)++] = temp.charp_i;
	result[(*res_i)] = NULL;
	free_split(shell_op);
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
			free(result);
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
