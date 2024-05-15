/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:07:17 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:22:08 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

void	is_var(char *str, t_env_var *var)
{
	char	*name;
	char	*value;
	int		i;
	int		m;

	i = 0;
	m = 0;
	if (!str || !var)
		return ;
	name = ft_malloc(ft_strlen(str) + 1);
	value = ft_malloc(ft_strlen(str) + 1);
	while (str[++i] && str[i] != '=')
		name[i] = str[i];
	name[i] = '\0';
	var->name = name;
	while (str[++i])
	{
		value[m] = str[i];
		m++;
	}
	value[m] = '\0';
	var->value = value;
	var->prev = NULL;
	var->next = NULL;
}
