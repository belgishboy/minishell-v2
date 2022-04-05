/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheymans <vheymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:50:54 by vheymans          #+#    #+#             */
/*   Updated: 2022/04/05 11:30:36 by vheymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * init cmd figures out what cmd is passed and the path
 *  0 == shell cmd; 1 == ERROR 2 == echo; 3 == cd; 4 == pwd; 5 == export
 *  6 == unset; 7 == env; 8 == exit; 9 == $?; ?9 == CTRL?
*/
int	init_cmd(t_seq *seq)
{
	if (ft_strncmp(seq->split[0], "echo", 5) == 0)
		seq->wht_cmd = 2;
	else if (ft_strncmp(seq->split[0], "cd", 3) == 0)
		seq->wht_cmd = 3;
	else if (ft_strncmp(seq->split[0], "pwd", 4) == 0)
		seq->wht_cmd = 4;
	else if (ft_strncmp(seq->split[0], "export", 7) == 0)
		seq->wht_cmd = 5;
	else if (ft_strncmp(seq->split[0], "unset", 6) == 0)
		seq->wht_cmd = 6;
	else if (ft_strncmp(seq->split[0], "env", 4) == 0)
		seq->wht_cmd = 7;
	else if (ft_strncmp(seq->split[0], "exit", 5) == 0)
		seq->wht_cmd = 8;
	else if (ft_strncmp(seq->split[0], "$?", 3) == 0)
		seq->wht_cmd = 9;
	else
		seq->wht_cmd = 1;
	return (0);
}

int	count_args(char **split)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (split[i])
	{
		if (is_split(split[i][0]) != 3)
			count ++;
		i ++;
	}
	return (count);
}

/**
 * @param split [char **] char array to be worked on
 * @param seq	[t_seq *] sequance to be worked on
 * @return [int] 0 if succesful, 1 if malloc error
*/
int	arg_parsing(char **split, t_seq *seq)
{
	//printf("arg_parsing cmds\n");
	int	i;
	int	x;
	int	arg_cnt;

	arg_cnt = count_args(split);
	seq->cmd_args = ft_calloc(arg_cnt + 1, sizeof (char *));
	if (!seq->cmd_args)
		return (1);
	i = 0;
	x = 0;
	//printf("arg_cnt = [%d]\n", arg_cnt);//DELETE
	while (i < arg_cnt)
	{
		while (is_split(split[x][0]) == 3)
		{
			split[x] = rmv_quotes(split[x], 1);
			x ++;
		}
		seq->cmd_args[i] = rmv_quotes(split[x], 0);
		i ++;
		x ++;
	}
	//printf("done arg_parsing cmds\n");
	return (0);
}

/**
 * @param seq [t_seq *] seq to be initilized
*/
void	init_seq(t_seq *seq)
{
	seq->split = NULL;
	seq->cmd_args = NULL;
	seq->fd[0] = STDIN_FILENO;
	seq->fd[1] = STDOUT_FILENO;
	seq->wht_cmd = 1;
	seq->nbr_arg = -1;
}

/**
 * initializes the sequence and parses the arguent to extract usefull args
 * @param sh [t_shell *] shell struct
 * @return 0 if successful, # of what seq[#] if fail
*/
int	parse(t_shell *sh)//clean
{
	//printf("parsing cmds\n");
	int	i;

	i = 0;
	while (sh->seq[i])
	{
		init_seq(sh->seq[i]);
		arg_split(sh->seq[i]->seq, sh->seq[i], 0, 0);
		if (arg_parsing(sh->seq[i]->split, sh->seq[i]))
			return ((i + 1) * -1);
		init_fd(sh->seq[i], sh->seq[i]->split);// need to take out the '>'
		init_cmd(sh->seq[i]);
		if (sh->seq[i]->wht_cmd == 1)
			sh->seq[i]->path_cmd = ft_get_path(sh->seq[i]->cmd_args, ft_path());
		//printf("path_cmd = %s\n\n\n", sh->seq[i]->path_cmd);
		i ++;
	}
	//printf("done parsing cmds\n");
	return (0);
}
