/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:15:14 by mnaimi            #+#    #+#             */
/*   Updated: 2022/07/03 02:22:31 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* -------------------------------------------------------------------------- */

void	new_quote(t_quote **quotes, int i, int on, int class)
{
	t_quote	*quote;
	t_quote	*tmp;

	quote = malloc(sizeof(t_quote) * 1);
	if (!quote)
		exit(1);
	quote->i = i;
	if (on >= 0)
		quote->on = 1;
	else
		quote->on = 0;
	quote->class = class;
	quote->next = NULL;
	if (!*quotes)
		*quotes = quote;
	else
	{
		tmp = *quotes;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = quote;
	}
}

/* -------------------------------------------------------------------------- */

int	quoted(t_quote *quotes, int i)
{
	t_quote	*tmp;

	if (quotes == NULL)
		return (0);
	tmp = quotes;
	while (tmp->next)
		tmp = tmp->next;
	if (i)
		if (tmp->on == 1 && tmp->class == 1)
			return (0);
	if (tmp->on == 0)
		return (0);
	return (1);
}

/* -------------------------------------------------------------------------- */

void	unclosed_quotes(t_quote *quotes, t_info *info)
{
	if (quoted(quotes, 0))
	{
		printf("Unclosed quotes!\n");
		info->uncqu = 1;
	}
}

/* -------------------------------------------------------------------------- */

int	check_dollar(t_info *info, int i, t_quote *quotes)
{
	int	j;

	j = i;
	while (j >= 0 && info->input[j] != PIPE && info->input[j] != IN && \
		info->input[j] != OUT && info->input[j] != APPEND && \
		info->input[j] != HEREDOC)
		j--;
	if (info->input[j] == HEREDOC)
		return (0);
	return (info->input[i] == '$' && info->input[i + 1]
		&& (ft_isalnum(info->input[i + 1]) || info->input[i + 1] != '?' \
			|| info->input[i + 1] == '_' || info->input[i + 1] == '\'' || \
			info->input[i + 1] == '\"') && !quoted(quotes, 1));
}

/* -------------------------------------------------------------------------- */

void	in_out(char *input, int *i, t_quote	*quotes)
{
	if (input[*i] == '<' && !quoted(quotes, 0))
	{
		if (input[*i + 1] == '<')
		{
			input[*i] = HEREDOC;
			(*i) += 2;
		}
		else
			input[*i] = IN;
	}
	else if (input[*i] == '>' && !quoted(quotes, 0))
	{
		if (input[*i + 1] == '>')
		{
			input[*i] = APPEND;
			(*i) += 2;
		}
		else
			input[*i] = OUT;
	}
}

/* -------------------------------------------------------------------------- */
