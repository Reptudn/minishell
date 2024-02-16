/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:07:17 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/16 09:36:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

void	is_var(char *str, t_variable *var)
{
	char	*name;
	char	*value;
	int		i;
	int		m;

	i = 0;
	m = 0;
	name = malloc(strlen(str) + 1);
	value = malloc(strlen(str) + 1);
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	var->name = name;
	i++;
	while (str[i])
	{
		value[m] = str[i];
		m++;
		i++;
	}
	value[m] = '\0';
	var->value = value;
	var->prev = NULL;
	var->next = NULL;
}

char	**filter_variables(char **split, t_shell *shell)
{
	t_variable	*var;
	t_variable	*new_var;
	t_variable	*prev;
	char		**result;
	char		**test = malloc(100 * sizeof(char *));
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (split[i] != NULL)
	{
		if (ft_strchr(split[i], '=') != NULL)
		{
			new_var = malloc(sizeof(t_variable));
			if (!new_var)
			{
				while (var != NULL)
				{
					prev = var->prev;
					free_cmds_helper(var);
					var = prev;
				}
				return (NULL);
			}
			is_var(split[i], var);
			if (shell->variables == NULL)
				shell->variables = var;
			var->next = new_var;
			new_var->prev = var;
			var = new_var;
		}
		i++;
	}
	result = clean_data(split, test);
	// for (i = 0; result[i] != NULL; i++)
	// 	printf("(makecmds) result[%d] = %s\n", i, result[i]);
	return (result);
}
