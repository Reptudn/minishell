/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:49:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/24 09:50:33 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain)
{
	int	i;

	i = -1;
	printf("Command Chain:\n");
	if (!chain)
	{
		printf("  No chain\n");
		return ;
	}
	while (chain[++i])
		printf("  chain[%d]: %s\n", i, (chain[i])->value);
}
