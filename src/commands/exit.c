/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:18:27 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/04 14:55:47 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	write_error(char *str, int exit_status)
{
	write(STDERR_FILENO, "Error: ", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	g_exit_status = exit_status;
}

void	exitbin(char **args, int fdout, t_data *data)
{
	int	i;

	write(fdout, "exit\n", 5);
	if (get_string_arr_len(args) > 2)
	{
		write_error("exit: too many arguments.", 1);
		return ;
	}
	else if (get_string_arr_len(args) == 1)
		free_all_exit(data);
	else
	{
		g_exit_status = ft_atoi(args[1]);
		i = -1;
		while (++i < (int)ft_strlen(args[1]))
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				write_error("exit: numeric argument required.", 2);
				break ;
			}
		}
		free_all_exit(data);
	}
}
