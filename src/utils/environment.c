/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:51:01 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 13:41:11 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_var	*env_get_by_name(t_env_var *vars, char *name);

void	env_pop(t_env_var *vars, t_env_var *pop)
{
	if (!pop)
		return ;
	if (pop->prev)
		pop->prev->next = pop->next;
	if (pop->next)
		pop->next->prev = pop->prev;
	if (pop == vars)
		vars = pop->next;
	ft_free(pop->name);
	ft_free(pop->value);
	ft_free(pop);
}

void	env_push(t_env_var *vars, t_env_var *new_var)
{
	t_env_var	*temp;

	if (!new_var)
		return ;
	if (!vars)
	{
		vars = new_var;
		return ;
	}
	temp = vars;
	while (temp->next)
		temp = temp->next;
	temp->next = new_var;
	new_var->prev = temp;
}

t_env_var	*env_create_var(char *name, char *value, bool is_envp)
{
	t_env_var	*env_var;

	if (!name)
		return (NULL);
	env_var = ft_malloc(sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->name = ft_strdup(name);
	if (value)
		env_var->value = ft_strdup(value);
	else
		env_var->value = NULL;
	env_var->is_envp = is_envp;
	env_var->next = NULL;
	env_var->prev = NULL;
	return (env_var);
}

int	env_make_vars_helper(t_env_var **temp,
		t_env_var **first, t_env_var **current)
{
	if (!(*temp))
		return (1);
	if (!(*first))
		(*first) = (*temp);
	else
	{
		(*current) = (*first);
		while ((*current)->next)
			(*current) = (*current)->next;
		(*current)->next = (*temp);
		(*temp)->prev = (*current);
	}
	return (0);
}

t_env_var	*env_make_vars(char **envp)
{
	t_env_var	*first;
	t_env_var	*temp;
	t_env_var	*current;
	int			i;
	char		**split;

	i = -1;
	first = NULL;
	if (!(*envp))
		return (NULL);
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '=') == NULL)
			continue ;
		split = split_first_occ(envp[i], '=');
		if (!split)
			return (NULL);
		temp = env_create_var(split[0], split[1], true);
		free_split(split);
		if (env_make_vars_helper(&temp, &first, &current))
			return (NULL);
	}
	while (first->prev)
		first = first->prev;
	return (first);
}
