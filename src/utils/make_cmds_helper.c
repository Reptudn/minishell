/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:07:17 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/20 10:35:54 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

void	is_var(char *str, t_env_var *var)
{
	if (!str || !var)
		return ;

	char	*name;
	char	*value;
	int		i;
	int		m;

	i = 0;
	m = 0;
	name = malloc(strlen(str) + 1);
	if (!name)
		return ;
	value = malloc(strlen(str) + 1);
	if (!value)
	{
		free(name);
		return ;
	}
	while (str[i] && str[i] != '=')
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
	t_env_var	*var = NULL;
	t_env_var	*new_var;
	t_env_var	*prev;
	char		**result;
	char		**test = malloc(100 * sizeof(char *));
	int			i;

	i = 0;
	while (split[i] != NULL)
	{
		if (ft_strchr(split[i], '=') != NULL)
		{
			new_var = malloc(sizeof(t_env_var));
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
			var = malloc(sizeof(t_env_var));
			is_var(split[i], var);
			if (shell->env_vars == NULL)
				shell->env_vars = var;
			var->next = new_var;
			new_var->prev = var;
			var = new_var;
		}
		i++;
	}
	result = clean_data(split, test);
	return (result);
}
