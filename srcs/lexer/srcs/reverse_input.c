/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:02:51 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/24 15:51:31 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

void	check_rev(t_reverse *rev, t_info *info)
{
	if (rev->k != 0)
	{
		remp_bef_aft_pipe(info, rev->bef_pipe, rev->aft_pipe, rev->k);
		rev->ptr = info->input;
		info->input = ft_strjoin(rev->bef_pipe, rev->word);
		free(rev->ptr);
		rev->ptr = info->input;
		info->input = ft_strjoin(info->input, rev->aft_pipe);
		free(rev->ptr);
	}
	else
	{
		rev->ptr = info->input;
		info->input = ft_strjoin(rev->word, info->input);
		free(rev->ptr);
	}
}

/* -------------------------------------------------------------------------- */

int	not_operator(t_info *info, int i)
{
	if (info->input[i] != PIPE && info->input[i] != IN && \
		info->input[i] != OUT && info->input[i] != APPEND && \
		info->input[i] != HEREDOC && info->input[i] != ' ')
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

void	init_rev(t_reverse *rev)
{
	if (!rev->word || !rev->bef_pipe || !rev->aft_pipe)
		exit(1);
	rev->i = 0;
	rev->k = 0;
	rev->start = 0;
}

/* -------------------------------------------------------------------------- */

void	reverse_input(t_info *info)
{
	t_reverse	rev;

	info->input = remove_red_in(info->input);
	rev.word = (char *)ft_calloc(100, sizeof(char));
	rev.bef_pipe = (char *)ft_calloc(500, sizeof(char));
	rev.aft_pipe = (char *)ft_calloc(500, sizeof(char));
	init_rev(&rev);
	while (info->input[rev.i])
	{
		if (info->input[rev.i] == PIPE)
			rev.k = rev.i;
		if ((info->input[rev.i] == IN || info->input[rev.i] == OUT || \
			info->input[rev.i] == APPEND || info->input[rev.i] == HEREDOC) && \
			rev.i != 0)
		{
			set_rev(&rev, info);
			check_rev(&rev, info);
			ft_bzero(rev.word, 100);
			ft_bzero(rev.bef_pipe, 500);
			ft_bzero(rev.aft_pipe, 500);
			continue ;
		}
		rev.i++;
	}
	free_reverse(&rev);
}

/* -------------------------------------------------------------------------- */
