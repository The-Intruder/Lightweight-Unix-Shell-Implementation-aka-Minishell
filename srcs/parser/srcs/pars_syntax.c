/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:15:52 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/24 15:54:15 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* -------------------------------------------------------------------------- */

void	removechar(char *str, char chartoremmove)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = strlen(str);
	while (i < len)
	{
		if (str[i] == chartoremmove)
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
}

/* -------------------------------------------------------------------------- */

int	check_syntax3(char c, char check, int *count)
{
	if (c == PIPE || c == IN || c == OUT || c == APPEND || c == HEREDOC)
	{
		if (check != c && check != PIPE)
		{
			if (check == IN && c == OUT)
				return (0);
			else
				return (printf ("minishell: parse error near!\n"), 258);
		}
		if (check == c)
		{
			if (check == PIPE)
				return (printf ("minishell: parse error near!\n"), 258);
			(*count)++;
			if (*count == 2)
				return (printf ("minishell: parse error near!\n"), 258);
		}
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

void	init_syntax_data(t_syntax *synta)
{
	synta->dq = -1;
	synta->i = 0;
	synta->cout = 0;
}

/* -------------------------------------------------------------------------- */

int	detect_error(t_syntax *synta, char *str)
{
	if (str[synta->i] == HEREDOC || str[synta->i] == APPEND)
	{
		if ((unsigned long)synta->i == (ft_strlen(str) - 2))
			return (printf ("minishell: parse error near!\n"), 258);
		synta->check = str[synta->i];
		synta->i += 2;
		if (str[synta->i] && \
			check_syntax3(str[synta->i], synta->check, &synta->cout))
			return (1);
	}
	else
	{
		if ((unsigned long)synta->i == (ft_strlen(str) - 1))
			return (printf ("minishell: parse error near!\n"), 258);
		synta->check = str[synta->i++];
		if (str[synta->i] && \
			check_syntax3(str[synta->i], synta->check, &synta->cout))
			return (1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	check_syntax2(char *str)
{
	t_syntax	synta;

	init_syntax_data(&synta);
	while (str[synta.i])
	{
		if (check_oper(str, synta.i) == 1)
		{
			if (detect_error(&synta, str))
				return (258);
		}
		else
		{
			synta.cout = 0;
			synta.i++;
		}
	}
	return (0);
}

/* -------------------------------------------------------------------------- */
