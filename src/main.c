/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	init_stacks(t_ps *push_swap, int *input_values, int stack_size)
{
	*push_swap = (t_ps){0};
	push_swap->a.data = input_values;
	push_swap->a.size = stack_size;
	push_swap->b.data = malloc((size_t)stack_size * sizeof(int));
	if (!push_swap->b.data)
		return (0);
	return (1);
}

static void	free_stacks(t_ps *push_swap)
{
	free(push_swap->a.data);
	free(push_swap->b.data);
}

static int	prepare_input(t_ps *push_swap, double *disorder_ratio)
{
	if (has_duplicates(&push_swap->a))
		return (0);
	*disorder_ratio = compute_disorder(&push_swap->a);
	if (!normalize_stack(&push_swap->a))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_ps		push_swap;
	double		disorder_ratio;
	int			stack_size;
	int			*input_values;

	if (argc == 1)
		return (0);
	stack_size = parse_arguments(argc, argv, &config, &input_values);
	if (stack_size < 0)
		return (print_error(), 1);
	if (stack_size == 0)
		return (0);
	if (!init_stacks(&push_swap, input_values, stack_size))
		return (free(input_values), print_error(), 1);
	if (!prepare_input(&push_swap, &disorder_ratio))
		return (free_stacks(&push_swap), print_error(), 1);
	execute_strategy(&push_swap, &config, disorder_ratio);
	free_stacks(&push_swap);
	return (0);
}
