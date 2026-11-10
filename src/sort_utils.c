/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_rank_pos(const t_stack *stack, int rank)
{
	int	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->data[i] == rank)
			return (i);
		i++;
	}
	return (-1);
}

int	find_max_pos(const t_stack *stack)
{
	int	i;
	int	best;

	i = 1;
	best = 0;
	while (i < stack->size)
	{
		if (stack->data[i] > stack->data[best])
			best = i;
		i++;
	}
	return (best);
}

/* Choisit le sens de rotation le plus court dans la pile a. */
void	bring_a_to_top(t_ps *ps, int pos)
{
	if (pos <= ps->a.size / 2)
	{
		while (pos-- > 0)
			exec_op(ps, OP_RA);
	}
	else
	{
		pos = ps->a.size - pos;
		while (pos-- > 0)
			exec_op(ps, OP_RRA);
	}
}

/* Choisit le sens de rotation le plus court dans la pile b. */
void	bring_b_to_top(t_ps *ps, int pos)
{
	if (pos <= ps->b.size / 2)
	{
		while (pos-- > 0)
			exec_op(ps, OP_RB);
	}
	else
	{
		pos = ps->b.size - pos;
		while (pos-- > 0)
			exec_op(ps, OP_RRB);
	}
}
