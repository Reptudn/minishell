/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:30:33 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:25:22 by jkauker          ###   ########.fr       */
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

char	*append_match(char *match, char *dir_name)
{
	char	*temp;

	temp = match;
	match = ft_strjoin(match, " ");
	if (!match)
	{
		// ft_free((temp));
		return (NULL);
	}
	// ft_free((temp));
	temp = match;
	match = ft_strjoin(match, dir_name);
	if (!match)
	{
		// ft_free((temp));
		return (NULL);
	}
	return (match);
}

char	*read_directory(DIR *d, char *pattern, char *match)
{
	struct dirent	*dir;

	dir = readdir(d);
	while (dir != NULL)
	{
		if (str_is_equal(pattern, "*") || wildcard_match(pattern, dir->d_name))
		{
			match = append_match(match, dir->d_name);
			if (!match)
				return (NULL);
		}
		dir = readdir(d);
	}
	return (match);
}

char	*get_matching_files(char *pattern)
{
	DIR		*d;
	char	*match;

	if (!pattern || ft_strchr(pattern, '*') == NULL)
		return (NULL);
	d = opendir(".");
	match = ft_malloc(1);
	match[0] = '\0';
	if (d && match)
	{
		match = read_directory(d, pattern, match);
		closedir(d);
	}
	if (str_is_equal(match, ""))
		return (ft_strdup(pattern));
	return (match);
}
