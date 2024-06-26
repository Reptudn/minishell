/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:33:01 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/02 15:12:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "get_next_line.h"

char	*buff_to_line(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	return (temp);
}

/**
 * move pointer to next line and keep everything that
 * was alredy in the buffer from new line in memory
 */
char	*next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (NULL);
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	return (line);
}

/**
	* Extracts the content of the buffer until
	the first newline character ('\n') encountered.
 */
char	*get_line_mine(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

/**
 * read out file and put into buffer
 */
char	*fill_buffer(int fd, char *res)
{
	char	*buffer;
	size_t	byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	byte_read = read(fd, buffer, BUFFER_SIZE);
	while (byte_read > 0)
	{
		buffer[byte_read] = '\0';
		res = buff_to_line(res, buffer);
		if (ft_strchr(buffer, '\n') || byte_read == 0)
			break ;
		byte_read = (size_t)read(fd, buffer, BUFFER_SIZE);
	}
	if (byte_read <= 0 && res[0] == '\0')
		return (NULL);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		buffer = NULL;
		return (NULL);
	}
	buffer = fill_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line_mine(buffer);
	buffer = next(buffer);
	return (line);
}
