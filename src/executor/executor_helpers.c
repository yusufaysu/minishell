/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:47:59 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/15 14:56:22 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	executor_helper(t_data *data, int i)
{
	if (data->command[i].descriptor.out != STDOUT_FILENO)
		close(data->command[i].descriptor.out);
	if (data->command[i].descriptor.in != STDIN_FILENO)
		close(data->command[i].descriptor.in);
}

void	executor_helper2(void)
{
	signal(SIGINT, sigint2);
	while (waitpid(-1, &g_exit_status, WUNTRACED) != -1)
		continue ;
	signal(SIGINT, sigint);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else
		g_exit_status = 130;
}

void	executor_helper3(t_data *data, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!is_buitin(data->command[i].cmd, data->command[i].args,
				data, data->command[i].descriptor.out))
			child_process(data, i);
		else
			free_all_exit(data);
	}
	else if (i == data->cmd_count - 1)
	{
		executor_helper(data, i);
		executor_helper2();
	}
	else
		executor_helper(data, i);
}

void	executor_helper4(t_data	*data, int i)
{
	int	pid;

	if (!is_buitin(data->command[i].cmd, data->command[i].args,
			data, data->command[i].descriptor.out))
	{
		pid = fork();
		if (pid == 0)
			child_process(data, i);
		else if (i == data->cmd_count - 1)
		{
			executor_helper(data, i);
			executor_helper2();
		}
		else
			executor_helper(data, i);
	}
}

void	close_all_open_fds(t_data *data, int i)
{
	while (i < data->cmd_count)
	{
		if (data->command[i].descriptor.in != STDIN_FILENO)
			close(data->command[i].descriptor.in);
		if (data->command[i].descriptor.out != STDOUT_FILENO)
			close(data->command[i].descriptor.out);
		i++;
	}
}
