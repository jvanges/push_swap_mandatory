/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_streq(const char *left, const char *right)
{
	int	i;

	i = 0;
	while (left[i] && left[i] == right[i])
		i++;
	return (left[i] == right[i]);
}

/* Convertit un entier sans jamais dépasser les limites d'un int. */
static int	convert_digits(const char *str, int *cursor, int sign,
			int *value)
{
	long	number;
	long	limit;

	number = 0;
	limit = INT_MAX;
	if (sign == -1)
		limit++;
	while (str[*cursor] >= '0' && str[*cursor] <= '9')
	{
		if (number > (limit - (str[*cursor] - '0')) / 10)
			return (0);
		number = number * 10 + (str[*cursor] - '0');
		(*cursor)++;
	}
	if (str[*cursor] && !ft_isspace(str[*cursor]))
		return (0);
	if (value)
		*value = (int)(number * sign);
	return (1);
}

int	parse_number(const char *str, int *cursor, int *value)
{
	int	sign;

	sign = 1;
	if (str[*cursor] == '+' || str[*cursor] == '-')
	{
		if (str[*cursor] == '-')
			sign = -1;
		(*cursor)++;
	}
	if (str[*cursor] < '0' || str[*cursor] > '9')
		return (0);
	return (convert_digits(str, cursor, sign, value));
}

/* Accepte aussi plusieurs nombres dans un argument entre guillemets. */
int	parse_string(const char *str, int *values, int *count)
{
	int	cursor;
	int	found;
	int	value;

	cursor = 0;
	found = 0;
	while (str[cursor])
	{
		while (str[cursor] && ft_isspace(str[cursor]))
			cursor++;
		if (!str[cursor])
			break ;
		if (!parse_number(str, &cursor, &value))
			return (-1);
		if (values)
			values[*count] = value;
		(*count)++;
		found = 1;
	}
	if (!found)
		return (-1);
	return (0);
}
