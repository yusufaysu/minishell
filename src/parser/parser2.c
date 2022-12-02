/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:04:10 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/13 17:37:05 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	dlesser_write(char *line, int fd[2])
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
}

void	dlesser_child(t_data *data, int i, int fd[2])
{
	char	*line;

	close(fd[0]);
	g_exit_status = 0;
	signal(SIGINT, sigint_dlesser);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_exit_status == 130)
				free_all_exit(data);
			else
			{
				print_error("warning: delimited by end-of-files", data, 0, 0);
				break ;
			}
		}
		if (ft_strcmp(line, data->cmd_line[i + 1]) == 0)
			break ;
		dlesser_write(line, fd);
		free(line);
	}
	close(fd[1]);
	free_all_exit(data);
}

int	dlesser(t_data *data, int *i, int *cmd_i)
{
	int	pid;
	int	fd[2];
	int	es;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		dlesser_child(data, *i, fd);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	wait(&es);
	signal(SIGINT, sigint);
	es = WEXITSTATUS(es);
	if (es == 130)
		return (free_on_error(data, 3));
	data->command[*cmd_i].descriptor.in = fd[0];
	return (1);
}

int	lesser(t_data *data, int *i, int *cmd_i)
{
	if (data->command[*cmd_i].descriptor.in != STDIN_FILENO)
		close(data->command[*cmd_i].descriptor.in);
	data->command[*cmd_i].descriptor.in
		= open(data->cmd_line[*i + 1], O_RDONLY);
	if (data->command[*cmd_i].descriptor.in == -1)
		return (print_error("no such file or directory", data, 1, 3));
	return (1);
}

int	greater(t_data *data, int *i, int *cmd_i, int ind)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (data->command[*cmd_i].descriptor.out != STDOUT_FILENO)
		close(data->command[*cmd_i].descriptor.out);
	if (ind == 1)
	{
		data->command[*cmd_i].descriptor.out
			= open(data->cmd_line[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, mode);
	}
	if (ind == 2)
	{
		data->command[*cmd_i].descriptor.out
			= open(data->cmd_line[*i + 1], O_WRONLY | O_CREAT | O_APPEND, mode);
	}
	if (data->command[*cmd_i].descriptor.out == -1)
		return (print_error("invalid file descriptor.", data, 1, 3));
	return (1);
}
