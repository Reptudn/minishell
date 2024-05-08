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

char	**env_get_path(t_env_var *vars)
{
	t_env_var	*temp;

	temp = vars;
	while (temp)
	{
		if (str_is_equal(temp->name, "PATH"))
			return (ft_split(temp->value, ':'));
		temp = temp->next;
	}
	return (NULL);
}

char	**env_to_envp(t_env_var *var)
{
	char		**split;
	t_env_var	*temp;
	int			i;

	if (!var)
		return (NULL);
	temp = var;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	split = malloc((i + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[i] = NULL;
	i = 0;
	while (var)
	{
		split[i] = ft_strjoin(var->name, "=");
		split[i] = ft_strjoin(split[i], var->value);
		var = var->next;
		i++;
	}
	return (split);
}

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
	free(pop->name);
	free(pop->value);
	free(pop);
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

t_env_var	*env_get_by_name(t_env_var *vars, char *name)
{
	while (vars)
	{
		if (str_is_equal(vars->name, name))
			return (vars);
		vars = vars->next;
	}
	return (NULL);
}

t_env_var	*env_create_var(char *name, char *value, bool is_envp)
{
	t_env_var	*env_var;

	if (!name)
		return (NULL);
	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->name = ft_strdup(name);
	if (!env_var->name)
	{
		free(env_var);
		return (NULL);
	}
	if (value)
	{
		env_var->value = ft_strdup(value);
		if (!env_var->value)
		{
			free(env_var->name);
			free(env_var);
			return (NULL);
		}
	}
	else
		env_var->value = NULL;
	env_var->is_envp = is_envp;
	env_var->next = NULL;
	env_var->prev = NULL;
	return (env_var);
}

char	**split_first_occ(char *str, char c)
{
	int		i;
	char	**split;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == 0)
		return (NULL);
	split = malloc(3 * sizeof(char *));
	if (!split)
		return (NULL);
	split[2] = NULL;
	split[0] = malloc(i + 1);
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	split[0] = ft_strncpy(split[0], str, i);
	split[0][i] = 0;
	split[1] = ft_strdup(str + i + 1);
	if (!split[1])
	{
		free(split[0]);
		free(split);
		return (NULL);
	}
	return (split);
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
		if (!temp)
			return (NULL);
		if (!first)
			first = temp;
		else
		{
			current = first;
			while (current->next)
				current = current->next;
			current->next = temp;
			temp->prev = current;
		}
	}
	while (first->prev)
		first = first->prev;
	return (first);
}

char	**doublestrdup(char **str)
{
	char	**new_str;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new_str = malloc(sizeof(char *) * (i + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		new_str[i] = ft_strdup(str[i]);
		if (!new_str[i])
		{
			while (i >= 0)
				free(new_str[i--]);
			free(new_str);
			return (NULL);
		}
	}
	new_str[i] = NULL;
	return (new_str);
}
