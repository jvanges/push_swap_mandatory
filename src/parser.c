/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Renvoie un code positif pour un drapeau et zéro pour une valeur. */
static int	get_flag_code(const char *str)
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
static int	apply_flag(t_config *config, int flag_code)
{
	if (flag_code == 5)
	{
		if (config->bench)
			return (0);
		config->bench = 1;
		return (1);
	}
	if (config->strategy_seen)
		return (0);
	config->strategy = (t_strategy)(flag_code - 1);
	config->strategy_seen = 1;
	return (1);
}

static int	scan_arguments(int argc, char **argv, t_config *config,
			int *number_count)
{
	int	i;
	int	flag_code;

	i = 1;
	while (i < argc)
	{
		flag_code = get_flag_code(argv[i]);
		if (flag_code)
		{
			if (!apply_flag(config, flag_code))
				return (0);
		}
		else if (parse_string(argv[i], NULL, number_count) < 0)
			return (0);
		i++;
	}
	return (1);
}

static void	fill_input_values(int argc, char **argv, int *values)
{
	int	i;
	int	number_count;

	i = 1;
	number_count = 0;
	while (i < argc)
	{
		if (!get_flag_code(argv[i]))
			parse_string(argv[i], values, &number_count);
		i++;
	}
}

/* Deux passages permettent une allocation exacte sans realloc. */
int	parse_arguments(int argc, char **argv, t_config *config, int **values)
{
	int	number_count;

	config->strategy = ADAPTIVE;
	config->bench = 0;
	config->strategy_seen = 0;
	number_count = 0;
	*values = NULL;
	if (!scan_arguments(argc, argv, config, &number_count))
		return (-1);
	if (number_count == 0)
		return (0);
	*values = malloc((size_t)number_count * sizeof(int));
	if (!*values)
		return (-1);
	fill_input_values(argc, argv, *values);
	return (number_count);
}
