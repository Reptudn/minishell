/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:35:39 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/15 08:59:52 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	// printf("ABSOLUTE: %s\n", path);
	// printf("RELATIVE: %s\n", path + ft_strlen(getenv("HOME")));
	ft_printf("%s\n", path);
	free(path);
	return (0);
}
