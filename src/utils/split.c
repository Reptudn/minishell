/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:06:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 11:18:16 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

char *create_split_string(const char *str, int start, int len)
{
	char *result;
	
	result = (char *)malloc((len + 1) * sizeof(char));
	ft_strncpy(result, &str[start], len);
	result[len] = '\0';
	return (result);
}

char *create_operator_string(const char *str, int len)
{
	char *result;
	
	result = malloc((len + 1) * sizeof(char));
	ft_strncpy(result, &str[0], len);
	result[len] = '\0';
	return result;
}

void update_indices(int *i, int *start, int len, int op_len)
{
	if (op_len > 0)
	{
		*i += op_len;
		*start = *i;
	}
	else if (len > 0)
	{
		(*i)++;
		*start = *i;
	}
	else
		(*i)++;
}

void process_string(const char *str, char **result, int *res_i)
{
	char *shell_op[] = {"||", "&&", "<", "<<", ">", ">>"};
	int i = 0;
	int start = 0;
	int op_len;
	int len;

	while (str[i] != '\0')
	{
		op_len = is_shell_op((char *) &str[i], shell_op, sizeof(shell_op) / sizeof(shell_op[0]));
		if (op_len > 0)
			len = i - start;
		else if (str[i + 1] == '\0')
			len = i - start + 1;
		else
			len = 0;
		if (len > 0)
		{
			result[*res_i] = create_split_string(str, start, len);
			(*res_i)++;
		}
		if (op_len > 0)
		{
			result[*res_i] = create_operator_string(&str[i], op_len);
			(*res_i)++;
		}
		update_indices(&i, &start, len, op_len);
	}
}

char **ft_split_shell(const char *str)
{
	char **result = (char **)malloc((strlen(str) + 1) * sizeof(char *));
	int res_i = 0;

	process_string(str, result, &res_i);
	result[res_i] = NULL;
	return result;
}

// #include <stdio.h>

// int main() {
// 	char **result;
// 	char *str = "echo \"hel<lo\" || wc || ls || ls -la";
// 	int i = 0;

// 	result = ft_split_shell(str);
// 	while (result[i] != NULL) {
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// 	return 0;
// }
