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

int	find_rank_pos(const t_stack *stack, int target_rank)
{
	int	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->data[i] == target_rank)
			return (i);
		i++;
	}
	return (-1);
}

int	find_max_pos(const t_stack *stack)
{
	int	i;
	int	max_position;

	i = 1;
	max_position = 0;
	while (i < stack->size)
	{
		if (stack->data[i] > stack->data[max_position])
			max_position = i;
		i++;
	}
	return (max_position);
}

/* Amène une position au sommet par le plus court des deux sens. */
void	bring_to_top(t_push_swap *push_swap, t_stack *stack,
			int target_position, t_operation forward)
{
	t_operation	reverse;

	reverse = OP_RRA;
	if (forward == OP_RB)
		reverse = OP_RRB;
	if (target_position <= stack->size / 2)
	{
		while (target_position-- > 0)
			exec_op(push_swap, forward);
	}
	else
	{
		target_position = stack->size - target_position;
		while (target_position-- > 0)
			exec_op(push_swap, reverse);
	}
}
