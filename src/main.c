/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:03:48 by jkauker           #+#    #+#             */
/*   Updated: 2024/01/29 12:26:05 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("%sUsage: %s%s\n", COLOR_RED, argv[0], COLOR_RESET);
		return (1);
	}
	command_loop();
	return (0);
}
