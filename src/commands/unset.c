/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:03:37 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/04 14:56:07 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_helper(char *var, t_data *data)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc(sizeof(char *) * (get_string_arr_len(data->envp) + 1));
	i = -1;
	j = 0;
	while (++i < get_string_arr_len(data->envp))
	{
		if (ft_strncmpf(var, data->envp[i], ft_strlen(var)) == 0)
			continue ;
		new_envp[j++] = ft_strdup(data->envp[i]);
	}
	new_envp[j] = 0;
	free_str_array(data->envp);
	data->envp = new_envp;
}

t_bool	is_it_env(char *var, t_data *data)
{
	int	i;

	i = -1;
	while (++i < get_string_arr_len(data->envp))
	{
		if (ft_strncmp(var, data->envp[i], ft_strlen(var)))
			return (TRUE);
	}
	return (FALSE);
}

void	unset(char **args, t_data *data)
{
	int	i;

	i = 0;
	while (++i < get_string_arr_len(args))
	{
		if (is_it_env(args[i], data))
			unset_helper(args[i], data);
	}
	g_exit_status = 0;
}
