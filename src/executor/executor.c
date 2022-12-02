/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:26:12 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/15 23:44:38 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	try_path_helper(t_data *data, int cmd_i, char *path_line, t_bool done)
{
	char	*path;
	int		i;

	i = 0;
	while (++i)
	{
		path = fill_path(path_line, i - 1);
		if (path[0] == '\0')
		{
			free(path);
			break ;
		}
		path = ft_strjoinf(path, "/");
		path = ft_strjoinf(path, data->command[cmd_i].cmd);
		if (access(path, X_OK) == 0)
		{
			done = TRUE;
			data->command[cmd_i].cmd = path;
			break ;
		}
		else
			free(path);
	}
	try_path_helper_helper(done, data, cmd_i);
}

void	try_path(t_data *data, int cmd_i)
{
	int		i;
	char	*path_line;
	t_bool	done;

	done = FALSE;
	path_line = NULL;
	i = -1;
	while (++i < get_string_arr_len(data->envp))
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			path_line = data->envp[i];
			break ;
		}
	}
	if (path_line)
		try_path_helper(data, cmd_i, path_line, done);
}

void	child_process(t_data *data, int i)
{
	restore_sigint(data);
	dup2(data->command[i].descriptor.in, STDIN_FILENO);
	dup2(data->command[i].descriptor.out, STDOUT_FILENO);
	close_all_open_fds(data, i);
	if (!ft_strcont(data->command[i].cmd, '/'))
		try_path(data, i);
	if (execve(data->command[i].cmd, data->command[i].args, data->envp)
		== -1)
	{
		if ((errno == EACCES || errno == EISDIR)
			&& ft_strcmp(data->command[i].cmd, "") == 0)
			print_error("command is not executable.", data, 126, 0);
		else
			print_error("command not found.", data, 127, 0);
	}
	close(data->command[i].descriptor.out);
	free_all_exit(data);
}

t_bool	is_buitin(char *cmd, char **args, t_data *data, int fdout)
{
	if (ft_strcmp("pwd", cmd) == 0)
		pwd(fdout);
	else if (ft_strcmp("echo", cmd) == 0)
		echo(args, fdout);
	else if (ft_strcmp("env", cmd) == 0)
		env(args, data->envp, fdout);
	else if (ft_strcmp("exit", cmd) == 0)
		exitbin(args, fdout, data);
	else if (ft_strcmp("cd", cmd) == 0)
		cd(args, data, fdout);
	else if (ft_strcmp("unset", cmd) == 0)
		unset(args, data);
	else if (ft_strcmp("export", cmd) == 0)
		export(args, data->envp, fdout, data);
	else
		return (FALSE);
	return (TRUE);
}

int	executor(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		if (data->cmd_count == 1)
			executor_helper4(data, i);
		else
			executor_helper3(data, i);
	}
	free_after_cmd(data);
	return (0);
}
