/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:02:12 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/13 15:02:41 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
