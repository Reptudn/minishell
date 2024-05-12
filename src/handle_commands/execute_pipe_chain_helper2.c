/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain_helper2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:51:53 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 15:52:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cmd_chain_helper2(char **args, t_shunting_node **chain)
{
	args = ft_split("-n ", ' ');
	free_split(chain[0]->args);
	chain[0]->args = args;
}
