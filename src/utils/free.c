/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:13:09 by yaysu             #+#    #+#             */
/*   Updated: 2022/12/02 12:23:36 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_str_array(char **arr)
{
	int	i;

	i = -1;
	while (++i < get_string_arr_len(arr))
		free(arr[i]);
	free(arr);
}

void	free_after_cmd(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		if (!data->command[i].cmd || !data->command[i].args)
			break ;
		free(data->command[i].cmd);
		free_str_array(data->command[i].args);
	}
	free(data->command);
	free(data->arg_counts);
	free(data->tokens);
	free_str_array(data->cmd_line);
}

void	free_on_exit(t_data *data)
{
	free_str_array(data->envp);
	free(data->home_path);
}

void	free_all_exit(t_data *data)
{
	free_after_cmd(data);
	free_on_exit(data);
	exit(g_exit_status);
}

int	free_on_error(t_data *data, int level)
{
	int	i;

	if (level >= 1)
	{
		free(data->tokens);
		free_str_array(data->cmd_line);
	}
	if (level >= 2)
		free(data->arg_counts);
	if (level >= 3)
	{
		i = -1;
		while (data->command[++i].cmd != NULL)
		{
			free(data->command[i].cmd);
			if (data->command[i].args)
				free_str_array(data->command[i].args);
		}
		free(data->command);
	}
	return (0);
}
