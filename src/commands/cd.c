/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:37:37 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/04 14:55:26 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_old_pwd(t_data *data, int fdout)
{
	char	*env;

	env = get_env("OLDPWD", data);
	if (!env)
	{
		print_error("cd: OLDPWD not set.", data, 1, 0);
		return ;
	}
	if (chdir(env) == -1)
	{
		print_error("cd: not a directory.", data, 1, 0);
		free(env);
		return ;
	}
	write(fdout, env, ft_strlen(env));
	write(fdout, "\n", 1);
	free(env);
	g_exit_status = 0;
	return ;
}

char	*cd_change_arg(char *arg, t_data *data)
{
	char	*new_arg;
	int		i;
	int		j;

	new_arg = malloc(sizeof(char)
			* (ft_strlen(arg) + ft_strlen(data->home_path)));
	i = -1;
	while (++i < (int)ft_strlen(data->home_path))
		new_arg[i] = data->home_path[i];
	j = 1;
	while (arg[j] != '\0')
	{
		new_arg[i++] = arg[j];
		j++;
	}
	new_arg[i] = '\0';
	free(arg);
	return (new_arg);
}

void	cd_home(t_data *data)
{
	char	*env;

	env = get_env("HOME", data);
	if (!env)
	{
		print_error("cd: HOME not set!", data, 1, 0);
		return ;
	}
	if (chdir(env) == -1)
	{
		print_error("cd: not a directory.", data, 1, 0);
		free(env);
		return ;
	}
	free(env);
	g_exit_status = 0;
	return ;
}

void	cd(char **args, t_data *data, int fdout)
{
	if (get_string_arr_len(args) == 1)
	{
		cd_home(data);
		return ;
	}
	if (get_string_arr_len(args) > 2)
	{
		print_error("cd: too many arguments.", data, 1, 0);
		return ;
	}
	if (args[1][0] == '~' && (args[1][1] == '\0' || args[1][1] == '/')
		&& data->home_path != NULL)
		args[1] = cd_change_arg(args[1], data);
	if (args[1][0] == '-' && args[1][1] == '\0')
		cd_old_pwd(data, fdout);
	else if (chdir(args[1]) == -1)
	{
		print_error("cd: not a directory.", data, 1, 0);
		return ;
	}
	g_exit_status = 0;
}
