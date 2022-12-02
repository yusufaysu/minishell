/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:40:33 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/15 17:04:06 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	free_and_ret(char *var)
{
	free(var);
	return (0);
}

void	add_to_env(char *line, t_data *data)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (get_string_arr_len(data->envp) + 2));
	i = -1;
	while (++i < get_string_arr_len(data->envp))
		new_envp[i] = data->envp[i];
	new_envp[i++] = line;
	new_envp[i] = 0;
	free(data->envp);
	data->envp = new_envp;
}

int	get_key_index(char *env, t_data *data)
{
	int	i;

	i = -1;
	while (++i < get_string_arr_len(data->envp))
	{
		if (ft_strncmpf(data->envp[i], env, ft_strlen(env)) == 0)
			return (i);
	}
	return (-1);
}

void	try_path_helper_helper(t_bool done, t_data *data, int cmd_i)
{
	if (!done)
	{
		free(data->command[cmd_i].cmd);
		data->command[cmd_i].cmd = ft_strdup("");
	}
}

void	skip_all_redirs(char *str, int *j)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '>' && (i + 1 >= (int)ft_strlen(str)
					|| str[i + 1] == '>')) || \
			(str[i] == '<' && (i + 1 >= (int)ft_strlen(str)
					|| str[i + 1] == '<')))
			(*j)++;
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			(*j)++;
	}
}
