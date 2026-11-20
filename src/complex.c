/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
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
static void	radix_pass(t_push_swap *push_swap, int current_bit)
{
	int	i;
	int	size;

	i = 0;
	size = push_swap->a.size;
	while (i < size)
	{
		if (((push_swap->a.data[0] >> current_bit) & 1) == 0)
			exec_op(push_swap, OP_PB);
		else
			exec_op(push_swap, OP_RA);
		i++;
	}
	while (push_swap->b.size > 0)
		exec_op(push_swap, OP_PA);
}

/* Le radix LSD trie n rangs en au plus log2(n) passages linéaires. */
void	sort_complex(t_push_swap *push_swap)
{
	int	current_bit;
	int	total_bits;

	total_bits = bit_count(push_swap->a.size);
	current_bit = 0;
	while (current_bit < total_bits)
	{
		radix_pass(push_swap, current_bit);
		current_bit++;
	}
}
