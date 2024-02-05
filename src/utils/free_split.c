/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:05:13 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 12:10:37 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command *free_split(char **split)
{
	int	i;

	i = 0;
	while (split[++i])
		free(split[i]);
	free (split);
	return (0);
}
