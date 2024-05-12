/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:11:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 09:25:30 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_shell_depth_helper(t_env_var *depth, char *new_val, int *lvl)
{
	if (arg_is_numerical(depth->value) && ft_atoi(depth->value) > 0)
	{
		*lvl = ft_atoi(depth->value);
		if (*lvl > 999)
			*lvl = 0;
		else if (*lvl < 0)
			*lvl = -1;
		new_val = ft_itoa(*lvl + 1);
	}
	else
		new_val = ft_strdup("1");
	free(depth->value);
	depth->value = new_val;
}

int	handle_shell_depth(t_shell *shell)
{
	t_env_var	*depth;
	char		*new_val;
	int			lvl;

	depth = env_get_by_name(shell->env_vars, "SHLVL");
	if (!depth)
	{
		depth = env_create_var("SHLVL", "1", true);
		if (!depth)
			return (CMD_FAILURE);
		else if (!shell->env_vars)
			shell->env_vars = depth;
		else
			env_push(shell->env_vars, depth);
	}
	else
		handle_shell_depth_helper(depth, new_val, &lvl);
	return (CMD_SUCCESS);
}

void	welcome_user(void)
{
	char	*user;

	user = getenv("USER");
	if (user)
	{
		printf("\n%sWelcome %s✨ %s ✨%s\n\n", color_magenta(), color_green(),
			user, color_reset());
		return ;
	}
	printf("\n%sWelcome %s✨ user ✨ %sthat didn't set the USER var 😡%s\n\n",
		color_magenta(), color_green(), color_red(), color_reset());
}

void	print_start_logo(void)
{
	printf("\033[H\033[J%s", color_magenta());
	printf(" __    __     __     __   __     __     "
		"______     __  __     ______     __         __ \n");
	printf("/\\ '-./  \\   /\\ \\   /\\ '-.\\ \\   /"
		"\\ \\   /\\  ___\\   /\\ \\_\\ \\   /\\  ___\\   /\\ \\"
		"       /\\ \\       \n");
	printf("\\ \\ \\-./\\ \\  \\ \\ \\  \\ \\ \\-.  "
		"\\  \\ \\ \\  \\ \\___  \\  \\ \\  __ \\  \\ \\  __\\   "
		"\\ \\ \\____  \\ \\ \\____  \n");
	printf(" \\ \\_\\ \\ \\_\\  \\ \\_\\  \\ \\_\\\\'"
		"\\_\\  \\ \\_\\  \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ "
		"\\_____\\  \\ \\_____\\ \n");
	printf("  \\/_/  \\/_/   \\/_/   \\/_/ \\/_/   "
		"\\/_/   \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   "
		"\\/_____/ \n\n");
	printf("                                 "
		"by %s\033]8;;https://profile.intra.42.fr/users/jkauker\ajkauker\033]8;"
		";\a%s and "
		"%s\033]8;;https://profile.intra.42.fr/users/nsabia\ansabia\033]8;"
		";\a%s\n\n",
		color_red(), color_magenta(), color_red(), color_reset());
	printf("%s", color_reset());
	welcome_user();
}

void	env_destroy(t_env_var *env)
{
	t_env_var	*temp;

	if (!env)
		return ;
	while (env)
	{
		free(env->name);
		free(env->value);
		temp = env->next;
		free(env);
		env = temp;
	}
}
