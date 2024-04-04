/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:21:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 15:05:36 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	yard_pop(t_shunting_node *node, t_shunting_yard *yard);

int		run_and(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
int		run_or(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
char	*run_pipe(t_shell *shell, t_shunting_node **chain, int counter, int pipe_amount, char *str);
int		redirect_in(t_shunting_node *cmd, t_shunting_node *cmd2, t_shell *shell);
int		redirect_out(t_shell *shell, t_shunting_node **chain, int redirection_amout);
int		run_append(t_shell *shell, t_shunting_node **chain, int append_amount);
int		run_delimiter(t_shell *shell, t_shunting_node *cmd1,
			t_shunting_node *cmd2);

void	replace_variable(char **args, t_shell *shell, int status);

void	yard_pop(t_shunting_node *pop, t_shunting_yard *yard);

t_shunting_node	*get_last_opeartor(t_shunting_node *node, int type)
{
	t_shunting_node	*last;

	while (node)
	{
		if (*node->type == type)
			last = node;
		else if (*node->type != type && *node->type != NONE)
			return (last);
		node = node->next;
	}
	return (last);
}

// TODO it is not correctly adding the pointers in the chain
t_shunting_node	**get_cmd_chain(t_shunting_node *start, int *len, int *type)
{
	t_shunting_node	**chain;
	t_shunting_node	*node;
	t_shunting_node	*last;
	int				i;

	if (!start)
		return (NULL);
	node = start;
	while (node && *node->type == NONE)
		node = node->next;
	*type = *node->type;
	*len = 0;
	printf("type: %d\n", *type);
	node = start;
	last = get_last_opeartor(node, *type);
	while (node && node->prev != last && node->next)
	{
		if (*node->type == *type)
			*len += 1;
		node = node->next;
	}
	while (node && node->prev)
		node = node->prev;
	*len += 2; // TODO: this is sus and i might need to fix the while loop above
	chain = (t_shunting_node **)malloc(sizeof(t_shunting_node *) * (*len + 1));
	if (!chain)
		return (NULL);
	chain[*len] = NULL;
	printf("start: %s\n", start->value);
	i = -1;
	while (node && node->prev != last && node->next)
	{
		printf("Node is %s\n", node->value);
		if (*node->type != *type && *node->type == NONE)
		{
			chain[++i] = node;
			printf(" added chain[%d]: %s\n", i, node->value);
		}
		else printf("skipped: %s\n", node->value);
		node = node->next;
	}
	return (chain);
}

// after calling this the first one of the chain can still be used as echo and save
// the output there
void	pop_cmd_chain(t_shunting_yard *yard, t_shunting_node **chain, int len)
{
	while (len-- > 1)
		yard_pop(chain[len], yard);
}

void	print_cmd_chain(t_shunting_node **chain)
{
	int	i;

	i = -1;
	printf("Command Chain:\n");
	if (!chain)
	{
		printf("  No chain\n");
		return ;
	}
	while (chain[++i])
		printf("  chain[%d]: %s\n", i, (chain[i])->value);
}

int execute_cmd_chain(t_shell *shell, t_shunting_node *start, t_shunting_yard *yard, int *status)
{
	t_shunting_node	**chain;
	int				len;
	int				type;
	int				i;
	char			*out;

	out = ft_strdup("");
	chain = get_cmd_chain(start, &len, &type);
	i = -1;
	print_cmd_chain(chain);
	if (!chain)
		return (CMD_FAILURE);
	while (++i < len && chain[i])
		replace_variable(chain[i]->args, shell, *status);
	if (type == PIPE)
	{
		printf("-> PIPE\n");
		run_pipe(shell, chain, 0, len, out);
		printf("out: %s\n", out);
	}
	else if (type == REDIRECT_IN)
	{
		printf("REDIRECT_IN\n");
	}
	else if (type == REDIRECT_OUT)
	{
		redirect_out(shell, chain, len);
	}
	else if (type == REDIRECT_OUT_APPEND)
	{
		run_append(shell, chain, len);
	}
	else if (type == REDIRECT_IN_DELIMITER)
	{
		printf("DELIMITER\n");
	}
	else
	{
		printf("no chain needed\n");
		pop_cmd_chain(yard, chain, len);
		yard_pop(*chain, yard);
		free(chain);
	}
	pop_cmd_chain(yard, chain, len);
	free(chain);
	return (CMD_SUCCESS);
}
