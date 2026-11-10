/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Renvoie un code positif pour un drapeau et zéro pour une valeur. */
int	flag_code(const char *str)
{
	if (ft_streq(str, "--simple"))
		return (SIMPLE + 1);
	if (ft_streq(str, "--medium"))
		return (MEDIUM + 1);
	if (ft_streq(str, "--complex"))
		return (COMPLEX + 1);
	if (ft_streq(str, "--adaptive"))
		return (ADAPTIVE + 1);
	if (ft_streq(str, "--bench"))
		return (5);
	return (0);
}

/* Enregistre un drapeau en refusant les sélecteurs contradictoires. */
static int	apply_flag(t_config *config, int code)
{
	if (code == 5)
	{
		if (config->bench)
			return (0);
		config->bench = 1;
		return (1);
	}
	if (config->strategy_seen)
		return (0);
	config->strategy = (t_strategy)(code - 1);
	config->strategy_seen = 1;
	return (1);
}

static int	parse_first_pass(int argc, char **argv, t_config *config,
			int *count)
{
	int	i;
	int	code;

	i = 1;
	while (i < argc)
	{
		code = flag_code(argv[i]);
		if (code)
		{
			if (!apply_flag(config, code))
				return (0);
		}
		else if (parse_string(argv[i], NULL, count) < 0)
			return (0);
		i++;
	}
	return (1);
}

static void	parse_second_pass(int argc, char **argv, int *values)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		if (!flag_code(argv[i]))
			parse_string(argv[i], values, &count);
		i++;
	}
}

/* Deux passages permettent une allocation exacte sans realloc. */
int	parse_arguments(int argc, char **argv, t_config *config, int **values)
{
	int	count;

	config->strategy = ADAPTIVE;
	config->bench = 0;
	config->strategy_seen = 0;
	count = 0;
	*values = NULL;
	if (!parse_first_pass(argc, argv, config, &count))
		return (-1);
	if (count == 0)
		return (0);
	*values = malloc((size_t)count * sizeof(int));
	if (!*values)
		return (-1);
	parse_second_pass(argc, argv, *values);
	return (count);
}
