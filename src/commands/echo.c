/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:44:50 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/13 16:20:33 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	echo(char **args, int fdout)
{
	int		n_option;
	int		i;

	n_option = 0;
	if (get_string_arr_len(args) == 1)
	{
		write(fdout, "\n", 1);
		return ;
	}
	i = 0;
	while (args[++i] && ft_strcmp("-n", args[i]) == 0)
		n_option++;
	i = n_option;
	while (args[++i] && i < get_string_arr_len(args))
	{
		write(fdout, args[i], ft_strlen(args[i]));
		if (i + 1 < get_string_arr_len(args))
			write(fdout, " ", 1);
	}
	if (!n_option)
		write(fdout, "\n", 1);
	g_exit_status = 0;
}
