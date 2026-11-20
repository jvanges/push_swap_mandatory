/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Affiche le pourcentage avec deux décimales sans utiliser printf. */
static void	print_disorder(double disorder_ratio)
{
	long	scaled_percent;

	scaled_percent = (long)(disorder_ratio * 10000.0 + 0.5);
	ft_putstr_fd("[bench] disorder: ", STDERR_FILENO);
	ft_putlong_fd(scaled_percent / 100, STDERR_FILENO);
	ft_putchar_fd('.', STDERR_FILENO);
	if (scaled_percent % 100 < 10)
		ft_putchar_fd('0', STDERR_FILENO);
	ft_putlong_fd(scaled_percent % 100, STDERR_FILENO);
	ft_putstr_fd("%\n", STDERR_FILENO);
}

static void	print_strategy(t_strategy selected_strategy, int is_adaptive)
{
	ft_putstr_fd("[bench] strategy: ", STDERR_FILENO);
	if (is_adaptive)
		ft_putstr_fd("Adaptive -> ", STDERR_FILENO);
	if (selected_strategy == SIMPLE)
		ft_putstr_fd("Simple (O(n^2))", STDERR_FILENO);
	else if (selected_strategy == MEDIUM)
		ft_putstr_fd("Medium (O(n*sqrt(n)))", STDERR_FILENO);
	else
		ft_putstr_fd("Complex (O(n*log(n)))", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	print_bench(const t_push_swap *push_swap, double disorder_ratio,
			t_strategy selected_strategy, int is_adaptive)
{
	int	op_index;

	print_disorder(disorder_ratio);
	print_strategy(selected_strategy, is_adaptive);
	ft_putstr_fd("[bench] total operations: ", STDERR_FILENO);
	ft_putlong_fd(push_swap->total, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	op_index = 0;
	while (op_index < OP_COUNT)
	{
		ft_putstr_fd("[bench] ", STDERR_FILENO);
		ft_putstr_fd(op_name((t_operation)op_index), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putlong_fd(push_swap->counts[op_index], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		op_index++;
	}
}
