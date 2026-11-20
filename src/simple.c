/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Extrait successivement le minimum, puis reconstruit a dans l'ordre. */
void	sort_simple(t_push_swap *push_swap)
{
	int	target_rank;
	int	minimum_position;
	int	initial_size;

	target_rank = 0;
	initial_size = push_swap->a.size;
	while (target_rank < initial_size)
	{
		minimum_position = find_rank_pos(&push_swap->a, target_rank);
		bring_to_top(push_swap, &push_swap->a, minimum_position, OP_RA);
		exec_op(push_swap, OP_PB);
		target_rank++;
	}
	while (push_swap->b.size > 0)
		exec_op(push_swap, OP_PA);
}
