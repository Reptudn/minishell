/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:03:12 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/19 13:11:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	insert_str_on_pos_w_len(char **str, char *insert, int pos, int len)
{
	char	*new_str;
	int		i;
	int		k;

	new_str = malloc((ft_strlen(*str) + ft_strlen(insert) - len + 1)
			* sizeof(char));
	if (!new_str)
		return ;
	i = -1;
	k = 0;
	while ((*str)[++i])
	{
		if (i == pos)
		{
			while (*insert)
				new_str[k++] = *insert++;
		}
		if (i < pos || i >= pos + len)
			new_str[k++] = (*str)[i];
	}
	new_str[k] = '\0';
	free(*str);
	*str = new_str;
}

// TODO: it works kinda but its not returngin the correct str
char	*get_var_str(char *str, t_shell *shell)
{
	t_env_var	*env_var;
	char		*var_str;
	char		*insert;
	int			i;
	int			k;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '$' || !str[i + 1])
			continue ;
		if (str[i + 1] == '?')
		{
			insert = ft_itoa(*shell->exit_status);
			if (!insert)
				return (NULL);
			insert_str_on_pos_w_len(&str, insert, i, 2);
		}
		else
		{
			k = 1;
			while (str[i + k] && ft_isalnum(str[i + k]))
				k++;
			insert = ft_substr(str, i, k);
			if (!insert)
				return (NULL);
			env_var = env_get_by_name(shell->env_vars, insert + 1);
			if (env_var)
			{
				var_str = ft_strdup(env_var->value);
				if (!var_str)
					return (NULL);
				insert_str_on_pos_w_len(&str, var_str, i, k);
			}
			i += k - 1;
		}
	}
	return (str);
}
