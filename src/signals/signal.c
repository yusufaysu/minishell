/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:52 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/11 13:29:35 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint2(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	restore_sigint(t_data *data)
{
	signal(SIGINT, data->sigint_handler);
	signal(SIGQUIT, data->sigquit_handler);
}

void	sigint_dlesser(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 130;
	close(STDIN_FILENO);
}
	/*ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);*/

void	sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 1;
	rl_replace_line("", STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(t_data *data)
{
	data->sigint_handler = signal(SIGINT, sigint);
	data->sigquit_handler = signal(SIGQUIT, SIG_IGN);
}
