/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:27:22 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 13:37:10 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_builtin_command(t_shell *shell, t_shunting_node *cmd)
{
	char	*new_path;

	new_path = NULL;
	if (str_is_equal(cmd->value, "history"))
		return (display_history());
	else if (str_is_equal(cmd->value, "exit"))
		return (ft_exit(shell, cmd));
	else if (str_is_equal(cmd->value, "echo"))
		return (ft_echo(cmd));
	else if (str_is_equal(cmd->value, "pwd"))
		return (pwd());
	else if (str_is_equal(cmd->value, "clear"))
		return (ft_clear());
	else if (str_is_equal(cmd->value, "export"))
		return (ft_export(shell, cmd));
	else if (str_is_equal(cmd->value, "env"))
		return (ft_env());
	else if (str_is_equal(cmd->value, "unset"))
		return (ft_unset(cmd, shell));
	else if (str_is_equal(cmd->value, "cd"))
		return (ft_cd(cmd, shell, new_path));
	else
		return (-1);
}

int	run_external_command(t_shell *shell, t_shunting_node *cmd)
{
	int	status;

	status = run_env_command(shell, cmd);
	if (status == -1)
	{
		status = run_path_command(shell, cmd);
		if (status == CMD_NOT_FOUND)
			print_invalid_cmd(cmd->value, "NO SUCH FILE OR DIR", CMD_NOT_FOUND);
	}
	return (status);
}

void	is_invlid_builtin_helper(char *lower, int *i, char curr, bool *changed)
{
	while (lower[++(*i)])
	{
		curr = lower[*i];
		lower[*i] = ft_tolower(lower[*i]);
		if (curr != lower[*i])
			*changed = true;
	}
}

bool	is_invlid_builtin(char *cmd)
{
	char	*lower;
	int		i;
	bool	changed;
	char	curr;

	curr = '\0';
	if (!cmd)
		return (false);
	lower = ft_strdup(cmd);
	if (!lower)
		return (false);
	i = -1;
	changed = false;
	is_invlid_builtin_helper(lower, &i, curr, &changed);
	if (changed && (str_is_equal(lower, "history")
			|| str_is_equal(lower, "exit")
			|| str_is_equal(lower, "echo") || str_is_equal(lower, "pwd")
			|| str_is_equal(lower, "clear") || str_is_equal(lower, "export")
			|| str_is_equal(lower, "env") || str_is_equal(lower, "unset")
			|| str_is_equal(lower, "cd")))
	{
		return (true);
	}
	return (false);
}

int	run_command(t_shell *shell, t_shunting_node *cmd)
{
	int	status;

	if (!cmd || !shell)
		return (CMD_FAILURE);
	replace_variable(&(cmd->value), &cmd->args);
	if (str_is_equal(cmd->value, "."))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		return (2);
	}
	status = run_builtin_command(shell, cmd);
	if (is_invlid_builtin(cmd->value) || str_is_equal(cmd->value, ""))
	{
		print_invalid_cmd(cmd->value, "FAILURE", CMD_NOT_FOUND);
		status = CMD_NOT_FOUND;
	}
	else if (status == -1)
		status = run_external_command(shell, cmd);
	if (cmd->exit_status == NULL)
		cmd->exit_status = ft_malloc(1);
	if (!cmd->update)
		return (status);
	*cmd->exit_status = status;
	*shell->exit_status = status;
	return (status);
}
