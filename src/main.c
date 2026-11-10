/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_counters(t_ps *ps)
{
	int	i;

	ps->total = 0;
	i = 0;
	while (i < OP_COUNT)
	{
		ps->counts[i] = 0;
		i++;
	}
}

static int	init_stacks(t_ps *ps, int *values, int size)
{
	ps->a.data = values;
	ps->a.size = size;
	ps->a.capacity = size;
	ps->b.data = malloc((size_t)size * sizeof(int));
	if (!ps->b.data)
		return (0);
	ps->b.size = 0;
	ps->b.capacity = size;
	init_counters(ps);
	return (1);
}

static void	free_stacks(t_ps *ps)
{
	free(ps->a.data);
	free(ps->b.data);
}

static int	prepare_input(t_ps *ps, double *disorder)
{
	if (has_duplicates(&ps->a))
		return (0);
	*disorder = compute_disorder(&ps->a);
	if (!normalize_stack(&ps->a))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_ps		ps;
	t_strategy	strategy;
	double		disorder;
	int			size;
	int			*values;

	if (argc == 1)
		return (0);
	size = parse_arguments(argc, argv, &config, &values);
	if (size < 0)
		return (print_error(), 1);
	if (size == 0)
		return (0);
	if (!init_stacks(&ps, values, size))
		return (free(values), print_error(), 1);
	if (!prepare_input(&ps, &disorder))
		return (free_stacks(&ps), print_error(), 1);
	strategy = config.strategy;
	if (strategy == ADAPTIVE)
		strategy = adaptive_strategy(disorder);
	run_strategy(&ps, strategy);
	if (config.bench)
		print_bench(&ps, disorder, strategy, config.strategy == ADAPTIVE);
	free_stacks(&ps);
	return (0);
}
