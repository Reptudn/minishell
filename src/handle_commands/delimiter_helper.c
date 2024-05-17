/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:28:07 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/17 13:51:39 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_delimiter_helper2dot1(char *temp, char *heredoc)
{
	(void)temp;
	(void)heredoc;
	return (1);
}

int	run_delmiter_im_crying(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	return (1);
}

char	*get_input2(char *prompt)
{
	char	*line;
	char	*tmp;

	if (isatty(fileno(stdin)))
		line = readline(prompt);
	else
	{
		line = get_next_line(fileno(stdin));
		if (!line)
			return (NULL);
		tmp = ft_strtrim(line, "\n");
		ft_free(line);
		line = tmp;
	}
	if (!line)
		return (NULL);
	tmp = ft_strtrim(line, " \t");
	if (isatty(fileno(stdin)))
		free(line);
	else
		ft_free(line);
	return (tmp);
}
