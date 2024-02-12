/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:07:17 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/12 17:19:03 by jkauker          ###   ########.fr       */
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

char	**filter_variables(char **split)
{
	t_variable	*var;
	t_variable	*new_var;
	t_variable	*prev;
	char		**result;
	int			i;

	i = 0;
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
			split[i][0] = ' ';
			split[i][1] = '\0';		//idk koennte ein leak sein who knows?
			var->next = new_var;
			new_var->prev = var;
			var = new_var;
		} //sonst wird anscheinend alles richtig eingelesen, das Problem ist nur
		//dass ich es nicht testen kann, weil clean_data() drunterliegt!
		i++;
	}
	result = (char **)malloc(10000); //here is the segfault
	return (NULL);
	result = clean_data(split, result);
	return (result);
}


// t_variable *is_var(char *str)
// {
// 	t_variable *var;
// 	char	*name;
// 	char	*value;
// 	int		i;
// 	int		m;

// 	i = 0;
// 	m = 0;
// 	name = malloc(strlen(str) + 1);
// 	value = malloc(strlen(str) + 1);
// 	var = malloc(sizeof(t_variable));
// 	while (str[i] != '=')
// 	{
// 		name[i] = str[i];
// 		i++;
// 	}
// 	name[i] = '\0';
// 	i++;
// 	var->name = name;
// 	while (str[i])
// 	{
// 		value[m] = str[i];
// 		m++;
// 		i++;
// 	}
// 	value[m] = '\0';
// 	var->value = value;
// 	var->next = NULL;
// 	var->prev = NULL;
// 	return var;
// }

// void filter_variables(char **split)
// {
// 	t_variable *current = NULL;
// 	t_variable *new_var;
// 	int i = 0;

// 	while (split[i])
// 	{
// 		if (ft_strchr(split[i], '=') != NULL)
// 		{
// 			new_var = is_var(split[i]);
// 			if (!new_var)
// 			{
// 				// handle error
// 				return;
// 			}
// 			if (current)
// 			{
// 				current->next = new_var;
// 				new_var->prev = current;
// 			}
// 			current = new_var;
// 		}
// 		i++;
// 	}
// 	// current now points to the last node in the linked list
// 	// do something with the linked list
// }