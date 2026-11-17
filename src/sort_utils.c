/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
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

/* Amène une position au sommet par le plus court des deux sens. */
void	bring_to_top(t_ps *ps, t_stack *stack, int pos, t_op forward)
{
	t_op	reverse;

	reverse = OP_RRA;
	if (forward == OP_RB)
		reverse = OP_RRB;
	if (pos <= stack->size / 2)
	{
		while (pos-- > 0)
			exec_op(ps, forward);
	}
	else
	{
		pos = stack->size - pos;
		while (pos-- > 0)
			exec_op(ps, reverse);
	}
}
