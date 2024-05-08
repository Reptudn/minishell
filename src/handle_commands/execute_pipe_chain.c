/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:21:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/08 14:50:46 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	yard_pop(t_shunting_node *node, t_shunting_yard *yard);

int		run_and(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
int		run_or(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
char	*run_pipe(t_shell *shell, t_shunting_node **chain);
int		redirect_in(t_shunting_node *cmd,
			t_shunting_node *cmd2, t_shell *shell);
int		redirect_out(t_shell *shell, t_shunting_node **chain,
			int redirection_amout);
int		run_append(t_shell *shell, t_shunting_node **chain, int append_amount);
char	*run_delimiter(t_shunting_node **chain, t_shell *shell);

void	yard_pop(t_shunting_node *pop, t_shunting_yard *yard);

t_shunting_node	*get_last_opeartor(t_shunting_node *node, int type)
{
	t_shunting_node	*last;
	t_shunting_node	*start;

	last = NULL;
	start = node;
	while (node && node != last && node->next
		&& (*node->type == type || *node->type == NONE))
	{
		if (node != start && node->prev && *node->prev->type == type
			&& *node->type == NONE && node->next && *node->next->type == NONE)
			break ;
		if (*node->type == type)
			last = node;
		node = node->next;
	}
	if (node && *node->type == type)
		last = node;
	return (last);
}

t_shunting_node	**fill_chain(t_shunting_node *start, t_shunting_node *last,
		int *len, int type)
{
	t_shunting_node	**chain;
	int				i;

	chain = (t_shunting_node **)malloc(sizeof(t_shunting_node *) * (*len + 1));
	if (!chain)
		return (NULL);
	chain[*len] = NULL;
	i = -1;
	while (start && start != last && start->next
		&& (*start->type == type || *start->type == NONE))
	{
		if (*start->type != type && *start->type == NONE)
			chain[++i] = start;
		start = start->next;
	}
	return (chain);
}

t_shunting_node	**get_cmd_chain(t_shunting_node *start, int *len, int *type)
{
	t_shunting_node	*node;
	t_shunting_node	*last;

	if (!start)
		return (NULL);
	node = start;
	while (node && *node->type == NONE)
		node = node->next;
	*type = *node->type;
	if (*type == NONE || *type == AND || *type == OR)
		return (NULL);
	*len = 0;
	node = start;
	last = get_last_opeartor(node, *type);
	if (!last)
		return (NULL);
	while (node && node != last && node->next
		&& (*node->type == *type || *node->type == NONE))
	{
		if (*node->type != *type)
			*len += 1;
		node = node->next;
	}
	return (fill_chain(start, last, len, *type));
}

char	**chain_out_to_arg(char *output)
{
	char	**out;

	if (!output)
		return (NULL);
	out = malloc(3 * sizeof(char *));
	if (!out)
	{
		free(output);
		return (NULL);
	}
	out[2] = NULL;
	out[1] = ft_strdup(output);
	out[0] = ft_strdup("-n");
	if (!out[0])
	{
		free(output);
		free(out);
		return (NULL);
	}
	free(output);
	return (out);
}

int	execute_cmd_chain_helper(int len, t_shunting_node **chain,
		t_shell *shell, int type)
{
	int		i;
	int		exit_code;
	char	**args;

	i = -1;
	exit_code = 0;
	while (++i < len && chain[i] && type != REDIRECT_IN_DELIMITER)
		replace_variable(&(chain[i]->value), &chain[i]->args);
	if (type == PIPE)
	{
		args = chain_out_to_arg(run_pipe(shell, chain));
		free_split(chain[0]->args);
		chain[0]->args = args;
	}
	else if (type == REDIRECT_IN)
		exit_code = redirect_in(chain[0], chain[1], shell);
	else if (type == REDIRECT_OUT)
		exit_code = redirect_out(shell, chain, len);
	else if (type == REDIRECT_OUT_APPEND)
		exit_code = run_append(shell, chain, len);
	else if (type == REDIRECT_IN_DELIMITER)
	{
		args = chain_out_to_arg(run_delimiter(chain,shell));
		free_split(chain[0]->args);
		chain[0]->args = args;
	}
	return (exit_code);
}

int	execute_cmd_chain(t_shell *shell, t_shunting_node *start,
		t_shunting_yard *yard)
{
	t_shunting_node	**chain;
	int				len;
	int				type;
	int				exit_code;
	char			**args;

	chain = get_cmd_chain(start, &len, &type);
	if (!chain)
		return (-1);
	exit_code = execute_cmd_chain_helper(len, chain, shell, type);
	if (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == REDIRECT_OUT_APPEND)
	{
		args = ft_split("-n ", ' ');
		free_split(chain[0]->args);
		chain[0]->args = args;
	}
	if (!(*chain)->args)
		return (CMD_FAILURE);
	free(chain[0]->value);
	chain[0]->value = ft_strdup("echo");
	chain[0]->update = 0;
	pop_cmd_chain(yard, chain, len, type);
	free(chain);
	if (exit_code != 0)
		return (exit_code);
	return (CMD_SUCCESS);
}
