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
void	sort_simple(t_ps *ps)
{
	int	target;
	int	pos;
	int	size;

	target = 0;
	size = ps->a.size;
	while (target < size)
	{
		pos = find_rank_pos(&ps->a, target);
		bring_to_top(ps, &ps->a, pos, OP_RA);
		exec_op(ps, OP_PB);
		target++;
	}
	while (ps->b.size > 0)
		exec_op(ps, OP_PA);
}
