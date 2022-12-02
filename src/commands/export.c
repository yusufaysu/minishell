/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:13 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/04 13:36:07 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_env_var(char *str, char **envp, t_data *data)
{
	char	*key;
	int		i;
	int		key_index;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	key_index = get_key_index(key, data);
	free(key);
	if (key_index == -1)
		add_to_env(ft_strdup(str), data);
	else if (ft_strcont(str, '='))
	{
		free(envp[key_index]);
		envp[key_index] = ft_strdup(str);
	}
}

int	is_key_valid(char *str)
{
	char	*key;
	int		i;

	if (str[0] == '=' || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	i = -1;
	while (++i < (int)ft_strlen(key))
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (free_and_ret(key));
	}
	free(key);
	return (1);
}

char	*add_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	t_bool	first_eq;

	i = -1;
	first_eq = FALSE;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 3));
	j = 0;
	while (++i < (int)ft_strlen(str))
	{
		new_str[j++] = str[i];
		if (str[i] == '=' && !first_eq)
		{
			new_str[j++] = '"';
			first_eq = TRUE;
		}
	}
	new_str[j++] = '"';
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	**export_envp(char **envp)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (get_string_arr_len(envp) + 1));
	i = -1;
	while (++i < get_string_arr_len(envp))
	{
		new_envp[i] = ft_strdup("declare -x ");
		new_envp[i] = ft_strjoinf(new_envp[i], envp[i]);
		if (ft_strcont(new_envp[i], '='))
			new_envp[i] = add_quotes(new_envp[i]);
	}
	new_envp[i] = 0;
	sort_2d_str_array(new_envp);
	return (new_envp);
}

void	export(char **args, char **envp, int fdout, t_data *data)
{
	char	**exp_envp;
	int		i;

	if (get_string_arr_len(args) < 2)
	{
		exp_envp = export_envp(envp);
		i = -1;
		while (++i < get_string_arr_len(exp_envp))
		{
			write(fdout, exp_envp[i], ft_strlen(exp_envp[i]));
			write(fdout, "\n", 1);
		}
		free_str_array(exp_envp);
		return ;
	}
	i = 0;
	while (++i < get_string_arr_len(args))
	{
		if (is_key_valid(args[i]))
			add_env_var(args[i], envp, data);
		else
			print_error("export: not a valid identifier.", data, 1, 0);
	}
}
