/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:15:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/07/03 02:24:11 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

int	check_file_in_access( t_cmds *cmds, char *str)
{
	if (access(str, F_OK) != 0)
	{
		cmds->file_fd = -1;
		cmds->data = ft_strdup(str);
	}
	else if (access(str, R_OK | F_OK) == 0 || \
		(access(str, F_OK) == 0 && access(str, R_OK) != 0))
	{
		cmds->data = ft_strdup(str);
		if (access(str, F_OK) == 0 && access(str, R_OK) != 0)
			cmds->file_fd = -2;
		else if (access(str, R_OK | F_OK) == 0)
			cmds->file_fd = open(cmds->data, O_RDONLY, 00500);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

void	rm_dqsq_cmds(t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd_split[i])
	{
		node->cmd_split[i] = remove_dq_sq(node->cmd_split[i]);
		i++;
	}
}

/* -------------------------------------------------------------------------- */

t_node	*new_node(t_cmds *cmds)
{
	t_node	*node;

	node = (t_node *)calloc(1, sizeof(t_node));
	if (!node)
		exit (1);
	node->token = cmds->token;
	node->data = ft_strdup(cmds->data);
	node->path = ft_strdup(cmds->path);
	node->next = NULL;
	node->file_fd = cmds->file_fd;
	node->cmd_flag = cmds->cmd_flag;
	if (node->token == COMMAND)
	{
		node->cmd_split = ft_split_cmd(cmds->data);
		rm_dqsq_cmds(node);
	}
	else
		node->cmd_split = NULL;
	if (cmds->data)
		free(cmds->data);
	if (cmds->path)
		free(cmds->path);
	return (node);
}

/* -------------------------------------------------------------------------- */

void	add_back(t_node **lst, t_node *node)
{
	t_node	*new;

	new = *lst;
	if (!node)
		return ;
	if (!lst[0])
	{
		lst[0] = node;
		return ;
	}
	while (new->next != NULL)
		new = new->next;
	new->next = node;
}

/* -------------------------------------------------------------------------- */
