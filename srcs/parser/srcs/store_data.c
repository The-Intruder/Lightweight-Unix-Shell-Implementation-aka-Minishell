/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:16:09 by mnaimi            #+#    #+#             */
/*   Updated: 2022/07/03 00:02:53 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

int	print_filetype(char *input, int flag)
{
	struct stat	file_stat;

	if (stat(input, &file_stat))
		return (0);
	if (S_ISREG(file_stat.st_mode) == 0 && S_ISDIR(file_stat.st_mode))
		return (printf("%s:\tIs a directory\n", input), 1);
	else if (S_ISREG(file_stat.st_mode) == 0 && S_ISDIR(file_stat.st_mode) == 0 \
		&& flag == 1)
		return (printf("no such file or directory:\t%s\n", input), 1);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	check_operator(t_info *info, int flag)
{
	if (flag == 1)
	{
		if (info->input[info->i] && info->input[info->i] != PIPE && \
		info->input[info->i] != OUT && info->input[info->i] != IN && \
		info->input[info->i] != HEREDOC && info->input[info->i] != APPEND)
			return (1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	operator_statements(t_info *info)
{
	if ((check_operator(info, 1) && info->input[info->i] != ' ') || \
		info->input[info->i] == IN || info->input[info->i] == OUT || \
		info->input[info->i] == APPEND || info->input[info->i] == HEREDOC)
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	all_operator(t_info *info, char *str, t_cmds *cmds)
{
	if (check_operator(info, 1) && info->input[info->i] != ' ')
	{
		if (handel_command(info, cmds, str))
			return (1);
		if (info->head->cmd_split && (info->head->cmd_split[0][0] == '.' || \
			info->head->cmd_split[0][0] == '/'))
		{
			if (print_filetype(info->head->cmd_split[0], 1))
				return (1);
		}
	}
	else if (info->input[info->i] == IN)
	{
		if (handel_in(info, cmds, str))
			return (1);
	}
	else if (info->input[info->i] == OUT || info->input[info->i] == APPEND)
	{
		if (handel_out(info, cmds, str))
			return (1);
	}
	else if (info->input[info->i] == HEREDOC)
		handel_herdoc(info, cmds, str);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	store_data(t_info *info)
{
	char	*str;
	t_cmds	*cmds;

	info->i = 0;
	info->head = NULL;
	str = (char *)malloc(sizeof(char) * 500);
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (!str || !cmds)
		exit(1);
	ft_bzero(str, 500);
	while (info->input[info->i])
	{
		if (operator_statements(info))
		{
			if (all_operator(info, str, cmds))
				return (1);
			continue ;
		}
		else if (info->input[info->i] == PIPE)
			handel_pipe(info, cmds);
		info->i++;
	}
	return (free(str), free(cmds), 0);
}
