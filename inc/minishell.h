/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:36:43 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/15 17:03:22 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

int	g_exit_status;

typedef enum bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum token
{
	UNKNOWN,
	COMMAND,
	ARGUMENT,
	PIPE,
	GREATER,
	LESSER,
	DGREATER,
	DLESSER,
	FILENAME
}	t_token;

typedef struct descriptor
{
	int		in;
	int		out;
	int		err;
}			t_desc;

typedef struct command
{
	char	*cmd;
	char	**args;
	t_desc	descriptor;
}			t_command;

typedef struct data
{
	int			token_count;
	int			cmd_count;
	int			*arg_counts;
	t_token		*tokens;
	t_command	*command;
	char		**envp;
	void		(*sigint_handler)(int);
	void		(*sigquit_handler)(int);
	t_bool		*redir_mark;
	int			redir_len;
	int			pipe_holder;
	char		*home_path;
	char		**cmd_line;
}				t_data;

int			get_string_arr_len(char **arr);
char		**copy_str_array(char **arr);
int			print_error(char *str, t_data *data, \
				int exit_status, int free_level);
int			ft_strncmpf(const char *s1, const char *s2, size_t n);
char		*get_env(char *env, t_data *data);
void		clear(int fdout);
char		*ft_strjoinf(char *s1, char *s2);
void		free_on_exit(t_data *data);
void		free_str_array(char **arr);
int			free_on_error(t_data *data, int level);
int			lexer(t_data *data, char *line);
char		*set_exit_status(char *str, int *ind);
char		*set_env_var_digit(char *str, int *ind);
char		*set_env_var(char *str, int *ind, t_data *data);
char		*set_env_var2(char *str, int *ind, char *env_value, int key_len);
int			ft_strcmp(const char *s1, const char *s2);
void		init_int_array(int *arr, int len, int val);
void		create_the_array(char *str, t_bool quote[2], char ***array);
char		**add_to_array(char **arr, const char *str, int st, int fn);
char		**split_line(char *str, t_data *data);
int			parser(t_data *data);
int			greater(t_data *data, int *i, int *cmd_i, int ind);
int			lesser(t_data *data, int *i, int *cmd_i);
void		sigint_dlesser(int signal);
void		free_all_exit(t_data *data);
void		sigint(int signal);
int			dlesser(t_data *data, int *i, int *cmd_i);
int			ft_strcont(char *str, char c);
void		env(char **args, char **envp, int fdout);
void		pwd(int fdout);
void		exitbin(char **args, int fdout, t_data *data);
void		echo(char **args, int fdout);
int			executor(t_data *data);
void		cd(char **args, t_data *data, int fdout);
int			free_and_ret(char *var);
void		add_to_env(char *line, t_data *data);
void		sort_2d_str_array(char **arr);
void		export(char **args, char **envp, int fdout, t_data *data);
void		unset(char **args, t_data *data);
int			get_key_index(char *env, t_data *data);
void		restore_sigint(t_data *data);
void		sigint2(int signal);
void		executor_helper2(void);
void		executor_helper(t_data *data, int i);
char		*fill_path(char	*path_line, int rot);
void		free_after_cmd(t_data *data);
void		set_signals(t_data *data);
void		executor_helper3(t_data	*data, int i);
void		executor_helper4(t_data	*data, int i);
t_bool		is_buitin(char *cmd, char **args, t_data *data, int fdout);
void		child_process(t_data *data, int i);
void		close_all_open_fds(t_data *data, int i);
void		try_path_helper_helper(t_bool done, t_data *data, int cmd_i);
void		skip_all_redirs(char *str, int *j);

#endif