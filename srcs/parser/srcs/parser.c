/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 04:31:53 by mnaimi            #+#    #+#             */
/*   Updated: 2022/07/03 00:41:25 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

int	check_oper(char *str, int i)
{
	if (str[i] == PIPE || str[i] == HEREDOC || str[i] == IN || \
		str[i] == OUT || str[i] == APPEND)
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	check_beginning(char *str, int i)
{
	if (str[i] && check_oper(str, i) == 1 && i == 0)
	{
		if (str[i] == PIPE)
			return (printf ("minishell: parse error near!\n"), 258);
		else if (str[i + 1] == '\0' && str[i] != APPEND && str[i] != HEREDOC)
			return (printf ("minishell: parse error near!\n"), 258);
		else if ((str[i] == APPEND || str[i] == HEREDOC) && str[i + 2] == '\0')
			return (printf ("minishell: parse error near!\n"), 258);
		else if (str[i] && ft_strlen(str) == 1)
			return (printf ("minishell: parse error near!\n"), 258);
	}
	if (str[i] && str[i] == PIPE && str[i + 1] && str[i + 1] == ' ')
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == PIPE)
			return (printf ("minishell: parse error near!\n"), 258);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	parse_error(char *str, unsigned long *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (check_oper(str, *i) == 1)
		return (printf ("minishell: parse error near!\n"), 258);
	return (0);
}

/* -------------------------------------------------------------------------- */

int	check_syntax1(char *str)
{
	unsigned long	i;

	i = 0;
	while (str[i])
	{
		if (check_beginning(str, i))
			return (258);
		if (check_oper(str, i) == 1 && str[i] != PIPE && \
			str[i + 1] == ' ')
		{
			i++;
			if (parse_error(str, &i))
				return (258);
		}
		else if ((str[i] == HEREDOC || str[i] == APPEND) && \
			str[i + 2] && str[i + 2] == ' ')
		{
			i += 2;
			if (parse_error(str, &i))
				return (258);
		}
		else
			i++;
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	parcer(t_info *info)
{
	int	i;

	i = check_syntax1(info->input1);
	if (i || !ft_strcmp(info->input1, "\0"))
	{
		g_glob.exit = i;
		return (1);
	}
	i = check_syntax2(info->input1);
	if (i || !ft_strcmp(info->input1, "\0"))
	{
		g_glob.exit = i;
		return (1);
	}
	if (store_data(info))
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */
