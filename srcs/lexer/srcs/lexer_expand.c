/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:14:56 by mnaimi            #+#    #+#             */
/*   Updated: 2022/07/03 02:25:28 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

void	expanding(t_expand *expd, char *s, char *old, char *new)
{
	while (*s)
	{
		if (ft_strstr(s, old) == s && expd->check == 0)
		{
			ft_strcpy(&expd->result[expd->i], new);
			expd->i += expd->newlen;
			s += expd->oldlen;
			expd->check += 1;
		}
		else
		expd->result[expd->i++] = *s++;
	}
	expd->result[expd->i] = '\0';
}

/* -------------------------------------------------------------------------- */

int	check_expand(char *input, int i)
{
	if (input[i] && \
		(ft_isalnum(input[i]) || input[i] == '_') \
		&& input[i] != ' ' && \
		input[i] != DQ && input[i] != SQ \
		&& input[i] != PIPE && input[i] != OUT \
		&& input[i] != IN && input[i] != EXPAND \
		&& input[i] != HEREDOC && \
		input[i] != APPEND)
		return (1);
	else
		return (0);
}

/* -------------------------------------------------------------------------- */

void	get_expand_env(char *input, int *i, t_expand *expd)
{
	char	*ptr;

	expd->i = 0;
	input[*i] = '$';
	expd->str[expd->i] = '$';
	expd->i++;
	(*i)++;
	if (check_expand(input, *i))
	{
		while (check_expand(input, *i))
			expd->str[expd->i++] = input[(*i)++];
	}
	expd->ptr = input;
	ptr = ft_strtrim(expd->str, "$");
	expd->result = ft_strdup(get_env(ptr, *g_glob.env_head));
	free(ptr);
}

/* -------------------------------------------------------------------------- */

void	ft_expand_bzero(t_expand *expd, int *i)
{
	*i = 0;
	ft_bzero(expd->str, 100);
}

/* -------------------------------------------------------------------------- */

char	*input_expand(char *input)
{
	t_expand	expd;

	expd.j = 0;
	expd.str = (char *)ft_calloc(100, sizeof(char));
	if (!expd.str)
		exit (1);
	while (input[expd.j])
	{
		if (input[expd.j] == EXPAND)
		{
			get_expand_env(input, &expd.j, &expd);
			if (expd.result == NULL)
			{
				input = replaceword(input, expd.str, "");
				ft_expand_bzero(&expd, &expd.j);
				continue ;
			}
			input = replaceword(input, expd.str, expd.result);
			ft_expand_bzero(&expd, &expd.j);
			free(expd.result);
			continue ;
		}
		expd.j++;
	}
	return (free (expd.str), input);
}

/* -------------------------------------------------------------------------- */
