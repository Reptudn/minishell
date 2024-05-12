/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:28:07 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 15:29:46 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_delimiter_helper2dot1(char *temp, char *heredoc)
{
	free(temp);
	free(heredoc);
	return (1);
}

int	run_delmiter_im_crying(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	return (1);
}
