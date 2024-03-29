/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_oper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:27:49 by mnaimi            #+#    #+#             */
/*   Updated: 2022/07/03 01:21:06 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	handel_pipe(t_info *info, t_cmds *cmds)
{
	cmds->token = PIPE;
	cmds->data = NULL;
	cmds->path = NULL;
	cmds->file_fd = -1;
	cmds->cmd_flag = 0;
	add_back(&info->head, new_node(cmds));
}

/* -------------------------------------------------------------------------- */

int	handel_in(t_info *info, t_cmds *cmds, char *str)
{
	info->i++;
	scape_space(info);
	while_operator(info, str);
	if (check_file_in_access(cmds, str))
		return (1);
	cmds->token = IN;
	cmds->path = NULL;
	cmds->cmd_flag = 0;
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 500);
	return (0);
}

/* -------------------------------------------------------------------------- */

void	handel_herdoc(t_info *info, t_cmds *cmds, char *str)
{
	info->i += 2;
	scape_space(info);
	while_operator(info, str);
	if (str && *str)
		cmds->data = ft_strdup(str);
	else
		cmds->data = NULL;
	cmds->token = HEREDOC;
	cmds->path = NULL;
	cmds->file_fd = -1;
	cmds->cmd_flag = 0;
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 500);
}

/* -------------------------------------------------------------------------- */

int	handel_out(t_info *info, t_cmds *cmds, char *str)
{
	int	i;

	i = 0;
	if (info->input[info->i] == APPEND)
	{
		info->i += 2;
		i++;
	}
	else
		info->i++;
	scape_space(info);
	while_operator(info, str);
	out_check_str(str, i, cmds);
	if (print_filetype(str, 0))
		return (1);
	cmds->path = NULL;
	cmds->cmd_flag = 0;
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 500);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	handel_command(t_info *info, t_cmds *cmds, char *str)
{
	int		j;
	char	**split_cmd;

	j = 0;
	scape_space(info);
	while (info->input[info->i] && check_operator(info, 1))
		str[j++] = info->input[info->i++];
	cmds->token = COMMAND;
	cmds->file_fd = -1;
	cmds->data = ft_strdup(str);
	split_cmd = ft_split_cmd(str);
	if (check_builtins(split_cmd[0]) == 0)
		cmds->path = get_path(split_cmd[0], cmds);
	else
		cmds->path = NULL;
	free_split(split_cmd);
	add_back(&info->head, new_node(cmds));
	ft_bzero(str, 500);
	return (0);
}

/* -------------------------------------------------------------------------- */
