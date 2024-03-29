/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:47:20 by mnaimi            #+#    #+#             */
/*   Updated: 2022/07/03 00:18:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

static char	**ft_creat(char *s, char **result, int row)
{
	int				j;
	size_t			len;
	int				i;
	unsigned int	start;

	j = -1;
	i = 0;
	start = 0;
	while (++j < row)
	{
		len = 0;
		while (s[i] && s[i] != SPACE_)
		{
			len++;
			i++;
		}
		result[j] = ft_substr(s, start, len);
		while (s[i] == SPACE_)
			i++;
		start = i;
	}
	free(s);
	return (result);
}

/* -------------------------------------------------------------------------- */

static int	str_row(char *tmp)
{
	int	count;

	count = 0;
	while (*tmp)
	{
		if (*tmp == SPACE_)
		{
			count++;
			while (*tmp == SPACE_)
				tmp++;
		}
		else
			tmp++;
	}
	return (count);
}

/* -------------------------------------------------------------------------- */

void	handle_quotes1(t_quote **quotes, char *quote, int i, int *check)
{
	if (quote[i] == DQ && (*check != 0))
		d_quotes(quotes, i, check, quote);
	else if (quote[i] == SQ && (*check != 1))
		s_quotes(quotes, i, check, quote);
}

char	*ft_space(char *str)
{
	t_quote	*quotes;
	int		i;
	int		check;

	quotes = NULL;
	check = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == DQ || str[i] == SQ)
			handle_quotes1(&quotes, str, i, &check);
		else if (str[i] == ' ' && !quoted(quotes, 0))
			str[i] = SPACE_;
	}
	free_quotes(quotes);
	return (str);
}

/* -------------------------------------------------------------------------- */

char	**ft_split_cmd(char *str)
{
	char	**result ;
	char	*tmp ;
	char	*tmp1;
	int		count;

	result = NULL;
	if (!str)
		return (NULL);
	tmp1 = ft_strtrim(str, " ");
	tmp = ft_strdup(ft_space(tmp1));
	count = str_row(tmp);
	free(tmp1);
	if (*str)
		count++;
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		exit(1);
	result[count] = NULL;
	return (ft_creat(tmp, result, count));
}

/* -------------------------------------------------------------------------- */
