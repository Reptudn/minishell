/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 08:55:29 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/06 09:53:58 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_make_cmd_node(char **tokens)
{
	t_ast	*ast;
	int		i;
	int		length;

	length = 0;
	i = 1;
	while (tokens[length + 1] && is_operator(tokens[length + 1]) == 0
		&& tokens[length + 1][0] != '(' && tokens[length + 1][0] != ')')
		length++;
	ast->type = COMMAND;
	ast->value = ft_strdup(tokens[0]);
	ast->args = malloc(length * sizeof(char *));
	if (!ast->args)
		return (NULL);
	while (length > 0)
	{
		ast->args[length - 1] = ft_strdup(tokens[i]);
		if (!ast->args[length - 1])
		{
			while (length > 0)
				free(ast->args[--length]);
			free(ast->args);
			free(ast->value);
			return (NULL);
		}
		length--;
	}
	for (int i = 0; i < length; i++)
		printf("args[%d]: %s\n", i, ast->args[i]);
	ast->left = NULL;
	ast->right = NULL;
	ast = malloc(sizeof(t_ast));
	return (ast);
}

t_ast	*build_ast(char **tokens)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	return (ast);
}
