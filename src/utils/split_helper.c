/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:56:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/13 10:20:05 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	is_shell_op(char *str, char *shell_op[], int size)
{
	int	i;

	i = 0;
	(void)size;
	while (shell_op[i] != NULL)
	{
		if (ft_strncmp(str, shell_op[i], ft_strlen(shell_op[i])) == 0)
			return (ft_strlen(shell_op[i]));
		i++;
	}
	return (0);
}

char	**clean_data(char **temp, char **result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (temp[i][0] != 0 && !(temp[i][0] == ' ' && temp[i][1] == 0))
			result[j++] = ft_strdup(temp[i]);
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split_shell(const char *str)
{
	char	**temp;
	int		res_i;
	char	**result;
	int		k;

	res_i = 0;
	k = -1;
	if (!str)
		return (NULL);
	temp = (char **)malloc((strlen(str) + 1) * sizeof(char *));
	process_string(str, temp, &res_i);
	temp[res_i] = NULL;
	result = (char **)malloc((res_i + 1) * sizeof(char *));
	result[res_i] = NULL;
	result = clean_data(temp, result);
	free(temp);
	temp = result;
	result = clean_quotes(temp);
	while (temp[++k])
		free(temp[k]);
	free(temp);
	temp = NULL;
	return (result);
}

char	**fill_shell_op(void)
{
	char	**shell_op;

	shell_op = malloc(10 * sizeof(char *));
	shell_op[0] = ft_strdup("||");
	shell_op[1] = ft_strdup("&&");
	shell_op[2] = ft_strdup("<<");
	shell_op[3] = ft_strdup("<");
	shell_op[4] = ft_strdup(">>");
	shell_op[5] = ft_strdup(">");
	shell_op[6] = ft_strdup("(");
	shell_op[7] = ft_strdup(")");
	shell_op[8] = ft_strdup("|");
	shell_op[9] = NULL;
	return (shell_op);
}
