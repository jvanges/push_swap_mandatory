/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	bit_count(int size)
{
	int	bits;
	int	max_rank;

	bits = 0;
	max_rank = size - 1;
	while ((max_rank >> bits) > 0)
		bits++;
	return (bits);
}

/* Un passage stable sépare les rangs selon la valeur d'un bit. */
static void	radix_pass(t_ps *ps, int bit)
{
	int	i;
	int	size;

	i = 0;
	size = ps->a.size;
	while (i < size)
	{
		if (((ps->a.data[0] >> bit) & 1) == 0)
			exec_op(ps, OP_PB);
		else
			exec_op(ps, OP_RA);
		i++;
	}
	while (ps->b.size > 0)
		exec_op(ps, OP_PA);
}

/* Le radix LSD trie n rangs en au plus log2(n) passages linéaires. */
void	sort_complex(t_ps *ps)
{
	int	bit;
	int	bits;

	bits = bit_count(ps->a.size);
	bit = 0;
	while (bit < bits)
	{
		radix_pass(ps, bit);
		bit++;
	}
}
