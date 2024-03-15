/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:30:33 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/15 11:00:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <dirent.h>

bool	wildcard_match(char *pattern, char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (true);

	if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')
		return (false);

	if (*pattern == '?' || *pattern == *str)
		return (wildcard_match(pattern + 1, str + 1));

	if (*pattern == '*')
		return (wildcard_match(pattern + 1, str)
			|| wildcard_match(pattern, str + 1));

	return (false);
}

char	*get_matching_files(char *pattern)
{
	DIR				*d;
	struct dirent	*dir;
	char			*match;
	char			*temp;

	if (!pattern || ft_strchr(pattern, '*') == NULL)
		return (NULL);
	d = opendir(".");
	match = malloc(sizeof(char));
	match[0] = '\0';
	if (d && match)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (wildcard_match(pattern, dir->d_name))
			{
				temp = match;
				match = ft_strjoin(match, " ");
				if (!match)
					return (free(temp), NULL);
				free(temp);
				temp = match;
				match = ft_strjoin(match, dir->d_name);
				if (!match)
					return (free(temp), NULL);
			}
			dir = readdir(d);
		}
		closedir(d);
	}
	return (match);
}
