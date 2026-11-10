/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static const char	*strategy_name(t_strategy strategy)
{
	if (strategy == SIMPLE)
		return ("Simple");
	if (strategy == MEDIUM)
		return ("Medium");
	return ("Complex");
}

static const char	*strategy_complexity(t_strategy strategy)
{
	if (strategy == SIMPLE)
		return ("O(n^2)");
	if (strategy == MEDIUM)
		return ("O(n*sqrt(n))");
	return ("O(n*log(n))");
}

/* Affiche le pourcentage avec deux décimales sans utiliser printf. */
static void	print_disorder(double disorder)
{
	long	scaled;

	scaled = (long)(disorder * 10000.0 + 0.5);
	ft_putstr_fd("[bench] disorder: ", STDERR_FILENO);
	ft_putlong_fd(scaled / 100, STDERR_FILENO);
	ft_putchar_fd('.', STDERR_FILENO);
	if (scaled % 100 < 10)
		ft_putchar_fd('0', STDERR_FILENO);
	ft_putlong_fd(scaled % 100, STDERR_FILENO);
	ft_putstr_fd("%\n", STDERR_FILENO);
}

static void	print_strategy(t_strategy strategy, int adaptive)
{
	ft_putstr_fd("[bench] strategy: ", STDERR_FILENO);
	if (adaptive)
		ft_putstr_fd("Adaptive -> ", STDERR_FILENO);
	ft_putstr_fd(strategy_name(strategy), STDERR_FILENO);
	ft_putstr_fd(" (", STDERR_FILENO);
	ft_putstr_fd(strategy_complexity(strategy), STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
}

void	print_bench(const t_ps *ps, double disorder,
			t_strategy strategy, int adaptive)
{
	int	op;

	print_disorder(disorder);
	print_strategy(strategy, adaptive);
	ft_putstr_fd("[bench] total operations: ", STDERR_FILENO);
	ft_putlong_fd(ps->total, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	op = 0;
	while (op < OP_COUNT)
	{
		ft_putstr_fd("[bench] ", STDERR_FILENO);
		ft_putstr_fd(op_name((t_op)op), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putlong_fd(ps->counts[op], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		op++;
	}
}
