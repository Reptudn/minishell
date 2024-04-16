/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:27:22 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/16 20:35:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*prompt_success(void)
{
	if (!isatty(STDOUT_FILENO))
		return ("");
	return (PROMPT_SUCCESS);
}

char	*prompt_failure(void)
{
	if (!isatty(STDOUT_FILENO))
		return ("");
	return (PROMPT_FAILURE);
}

char	*prompt_hello(void)
{
	if (!isatty(STDOUT_FILENO))
		return ("");
	return (PROMPT_HELLO);
}

char	*prompt_squote(void)
{
	if (!isatty(STDOUT_FILENO))
		return ("squote> ");
	return ("\033[0;31msquote> \033[0m");
}

char	*prompt_dquote(void)
{
	if (!isatty(STDOUT_FILENO))
		return ("dquote> ");
	return ("\033[0;31mdquote> \033[0m");
}
