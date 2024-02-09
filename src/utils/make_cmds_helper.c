/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:07:17 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/09 16:02:08 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

void	is_var(char *str)
{
	t_variable *var;
	char	*name;
	char	*value;
	int		i;
	int		m;

	i = 0;
	m = 0;
	var = malloc(sizeof(t_variable));
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	i++;
	var->name = name;
	while (str[i])
	{
		value[m] = str[i];
		m++;
		i++;
	}
	value[m] = '\0';
	var->value = value;
	var->next = NULL;
	var->prev = NULL;
	}

char	**filter_variables(char **split)
{
	char	**temp;
	char	**result;
	int		i;

	temp = split;
	i = 0;
	while (temp[i])
	{
		if (ft_strchr(temp[i], '=') != NULL)
		{
			is_var(temp[i]);
			temp[0] = ' ';
			temp[1] = '\0';
		}
		i++;
	}
	result = malloc(sizeof(char *) * (i + 1)); // allocate memory for result
	result = clean_data(temp, result);
	return (result);
}


t_variable *is_var(char *str)
{
	t_variable *var;
	char	*name;
	char	*value;
	int		i;
	int		m;

	i = 0;
	m = 0;
	name = malloc(strlen(str) + 1);
	value = malloc(strlen(str) + 1);
	var = malloc(sizeof(t_variable));
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	i++;
	var->name = name;
	while (str[i])
	{
		value[m] = str[i];
		m++;
		i++;
	}
	value[m] = '\0';
	var->value = value;
	var->next = NULL;
	var->prev = NULL;
	return var;
}

void filter_variables(char **split)
{
	t_variable *current = NULL;
	t_variable *new_var;
	int i = 0;

	while (split[i])
	{
		if (ft_strchr(split[i], '=') != NULL)
		{
			new_var = is_var(split[i]);
			if (!new_var)
			{
				// handle error
				return;
			}
			if (current)
			{
				current->next = new_var;
				new_var->prev = current;
			}
			current = new_var;
		}
		i++;
	}
	// current now points to the last node in the linked list
	// do something with the linked list
}