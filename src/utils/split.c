/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:06:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/02 14:35:30 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

int is_shell_op(char *str, char *shell_op[], int size)
{
	int i;

	i = 0;
	while (i < size) 
	{
		if (strncmp(str, shell_op[i], strlen(shell_op[i])) == 0)
			return (strlen(shell_op[i]));
		i++;
	}
	return 0;
}

char *create_split_string(const char *str, int start, int len)
{
	char *result;
	
	result = malloc((len + 1) * sizeof(char));
	strncpy(result, &str[start], len);
	result[len] = '\0';
	return result;
}

char *create_operator_string(const char *str, int len)
{
	char *result;
	
	result = malloc((len + 1) * sizeof(char));
	strncpy(result, &str[0], len);
	result[len] = '\0';
	return result;
}

char **ft_split_shell(const char *str)
{
	char *shell_op[] = {"||", "&&", "<", "<<", ">", ">>"};
	int shell_op_size = sizeof(shell_op) / sizeof(shell_op[0]);
	char **result = malloc((strlen(str) + 1) * sizeof(char *));
	int i = 0, start = 0, res_i = 0;
	

	while (str[i] != '\0')
	{
		int op_len;
		int len;

		op_len = is_shell_op((char *) &str[i], shell_op, shell_op_size);
		if (op_len > 0)
			len = i - start;
		else if (str[i + 1] == '\0')
			len = i - start + 1;
		else
			len = 0;
		if (len > 0)
		{
			result[res_i] = create_split_string(str, start, len);
			res_i++;
		}
		if (op_len > 0)
		{
			result[res_i] = create_operator_string(&str[i], op_len);
			res_i++;
			i += op_len;
			start = i;
		}
		else if (len > 0)
		{
			i++;
			start = i;
		}
		else
			i++;
	}
	result[res_i] = NULL;
	return result;
}

#include <stdio.h>

int main() {
	char **result;
	char *str = "echo \"hel<lo\" || wc || ls || ls -la";
	int i = 0;

	result = ft_split_shell(str);
	while (result[i] != NULL) {
		printf("%s\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	return 0;
}

// bekomme string
// string durchsuchen bis man auf ein trennzeichen stoesst
// von anfang bis trennzeichen in ein eigenen String kopieren