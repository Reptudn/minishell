/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:35:39 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 09:36:22 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	printf("ABSOLUTE: %s\n", path);
	printf("RELATIVE: %s\n", path + ft_strlen(getenv("HOME")));
	free(path);
	return (1);
}
