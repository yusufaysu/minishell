/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:40:26 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/15 17:04:21 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	lex_check(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->token_count)
	{
		if ((data->tokens[i] >= PIPE && data->tokens[i] <= DLESSER)
			&& ((i + 1 >= data->token_count)
				|| (data->tokens[i + 1] >= PIPE
					&& data->tokens[i + 1] <= DLESSER)))
		{
			return (print_error("syntax error", data, 1, 2));
		}
	}
	return (1);
}

void	set_unknowns(t_data *data, int *i, int *j)
{
	while (++(*i) < data->token_count)
	{
		if (data->tokens[*i] == UNKNOWN)
		{
			if (data->tokens[*i - 1] == COMMAND
				|| data->tokens[*i - 1] == ARGUMENT)
			{
				data->tokens[*i] = ARGUMENT;
				data->arg_counts[*j]++;
			}
			else if (data->tokens[*i - 1] >= GREATER
				&& data->tokens[*i - 1] <= DLESSER)
				data->tokens[*i] = FILENAME;
			else if (data->tokens[*i - 1] == FILENAME)
			{
				data->tokens[*i] = ARGUMENT;
				data->arg_counts[*j]++;
			}
		}
		else if (data->tokens[*i] == COMMAND)
			(*j)++;
	}
}

int	lexer2(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (++i < data->token_count)
	{
		if (data->tokens[i] == UNKNOWN && data->tokens[i - 1] == PIPE)
		{
			data->tokens[i] = COMMAND;
			data->cmd_count++;
		}
	}
	data->arg_counts = malloc(sizeof(int) * data->cmd_count);
	if (!data->arg_counts)
		return (print_error("allocation error.", data, 1, 1));
	init_int_array(data->arg_counts, data->cmd_count, 1);
	i = 0;
	j = 0;
	set_unknowns(data, &i, &j);
	return (lex_check(data));
}

void	set_tokens(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (++i < data->token_count)
	{
		if (!ft_strcmp(data->cmd_line[i], "|") && !data->redir_mark[j++])
			data->tokens[i] = PIPE;
		else if (!ft_strcmp(data->cmd_line[i], ">>") && !data->redir_mark[j++])
			data->tokens[i] = DGREATER;
		else if (!ft_strcmp(data->cmd_line[i], "<<") && !data->redir_mark[j++])
			data->tokens[i] = DLESSER;
		else if (!ft_strcmp(data->cmd_line[i], ">") && !data->redir_mark[j++])
			data->tokens[i] = GREATER;
		else if (!ft_strcmp(data->cmd_line[i], "<") && !data->redir_mark[j++])
			data->tokens[i] = LESSER;
		else
		{
			skip_all_redirs(data->cmd_line[i], &j);
			data->tokens[i] = UNKNOWN;
		}
	}
}

int	lexer(t_data *data, char *line)
{
	data->cmd_line = split_line(line, data);
	if (!data->cmd_line)
	{
		if (data->redir_len > 0)
			free(data->redir_mark);
		return (print_error("something wrong with quotes.", data, 1, 0));
	}
	data->token_count = get_string_arr_len(data->cmd_line);
	if (!data->token_count)
	{
		g_exit_status = 0;
		free_on_error(data, 0);
		free_str_array(data->cmd_line);
		return (0);
	}
	data->tokens = malloc(sizeof(t_token) * data->token_count);
	data->tokens[0] = COMMAND;
	data->cmd_count = 1;
	set_tokens(data);
	if (data->redir_len > 0)
		free(data->redir_mark);
	return (lexer2(data));
}
