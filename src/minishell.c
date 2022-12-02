/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:39:30 by yaysu             #+#    #+#             */
/*   Updated: 2022/12/02 12:23:25 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ctrl_d(t_data *data)
{
	write(STDOUT_FILENO, "exit\n", 5);
	free_on_exit(data);
	exit(EXIT_SUCCESS);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	buf[256];

	getcwd(buf, 256);
	prompt = ft_strdup("\e[1;32m#minishell#\e[0;37m:\e[1;34m");
	prompt = ft_strjoinf(prompt, buf);
	prompt = ft_strjoinf(prompt, "\e[0m$ ");
	return (prompt);
}

int	start_init(t_data *data, int argc, char **argv, char **env)
{
	if (argc > 1 && argv)
		print_error("Argument error.", data, 1, 0);
	data->envp = copy_str_array(env);
	data->home_path = get_env("HOME", data);
	set_signals(data);
	clear(STDOUT_FILENO);
	return (1);
}

void	main_helper(char *line, t_data *data)
{
	add_history(line);
	if (lexer(data, line))
	{
		if (parser(data))
			executor(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	*prompt;

	if (!start_init(&data, argc, argv, envp))
		return (1);
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
			ctrl_d(&data);
		if (line[0] != '\0')
			main_helper(line, &data);
		else
			free(line);
	}
	return (0);
}

	/*
	-| To see every words tokens at the line |-
	-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-
	while (data.cmd_line[++i] != NULL)
		printf("%s\t\t-%d-\n", data.cmd_line[i], data.tokens[i]);
	*/

	/*
	-| To print new env and home_path |<
	printf("%s\n", data.home_path);
	int i = -1;
	int j;
	while (data.env[++i])
	{
		j = -1;
		printf("%s\n", data.env[i]);
	}*/
