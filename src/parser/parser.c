/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:44:15 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/14 17:15:22 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	argument(t_data *data, int *i, int *j, int *cmd_i)
{
	data->command[*cmd_i].args[(*j)++] = ft_strdup(data->cmd_line[*i]);
	data->command[*cmd_i].args[*j] = 0;
	return (1);
}

void	create_pipe(t_data *data, int cmd_i)
{
	int	fd[2];

	if (cmd_i == data->cmd_count - 1)
	{
		data->command[cmd_i].descriptor.in = data->pipe_holder;
		data->command[cmd_i].descriptor.out = STDOUT_FILENO;
		data->command[cmd_i].descriptor.err = STDERR_FILENO;
	}
	else
	{
		pipe(fd);
		data->command[cmd_i].descriptor.in = data->pipe_holder;
		data->command[cmd_i].descriptor.out = fd[1];
		data->command[cmd_i].descriptor.err = STDERR_FILENO;
		data->pipe_holder = fd[0];
	}
}

int	command(t_data *data, int *i, int *j, int *cmd_i)
{
	*j = 0;
	data->command[++(*cmd_i)].cmd = ft_strdup(data->cmd_line[*i]);
	data->command[*cmd_i + 1].cmd = 0;
	data->command[*cmd_i].args = malloc(sizeof(char *)
			* (data->arg_counts[*cmd_i] + 1));
	if (!data->command[*cmd_i].args)
		return (print_error("Allocation error.", data, 1, 3));
	data->command[*cmd_i].args[(*j)++] = ft_strdup(data->cmd_line[*i]);
	data->command[*cmd_i].args[*j] = 0;
	create_pipe(data, *cmd_i);
	return (1);
}

int	token_operations(t_data *data, int *i, int *j, int *cmd_i)
{
	if (data->tokens[*i] == COMMAND)
		return (command(data, i, j, cmd_i));
	else if (data->tokens[*i] == ARGUMENT)
		return (argument(data, i, j, cmd_i));
	else if (data->tokens[*i] == GREATER)
		return (greater(data, i, cmd_i, 1));
	else if (data->tokens[*i] == DGREATER)
		return (greater(data, i, cmd_i, 2));
	else if (data->tokens[*i] == LESSER)
		return (lesser(data, i, cmd_i));
	else if (data->tokens[*i] == DLESSER)
		return (dlesser(data, i, cmd_i));
	return (1);
}

int	parser(t_data *data)
{
	int	i;
	int	j;
	int	cmd_i;

	data->pipe_holder = STDIN_FILENO;
	data->command = malloc(sizeof(t_command) * (data->cmd_count + 1));
	if (!data->command)
		return (print_error("Allocation error.", data, 1, 2));
	i = -1;
	cmd_i = -1;
	while (++i < data->token_count)
	{
		if (!token_operations(data, &i, &j, &cmd_i))
			return (0);
	}
	return (1);
}
