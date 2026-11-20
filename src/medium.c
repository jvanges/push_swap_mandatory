/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Calcule une racine entière sans dépendre de la bibliothèque mathématique. */
static int	integer_sqrt(int value)
{
	int	root;

	root = 0;
	while (root + 1 <= value / (root + 1))
		root++;
	return (root);
}

/* Isole un bloc en parcourant exactement les valeurs encore non triées. */
static void	extract_chunk(t_push_swap *push_swap, int min_rank, int max_rank,
			int remaining_count)
{
	int	scanned_count;
	int	current_rank;

	scanned_count = 0;
	while (scanned_count < remaining_count)
	{
		current_rank = push_swap->a.data[0];
		if (current_rank >= min_rank && current_rank <= max_rank)
			exec_op(push_swap, OP_PB);
		else
			exec_op(push_swap, OP_RA);
		scanned_count++;
	}
}

/* Trie le bloc par extraction des maxima et le place sous les précédents. */
static void	place_chunk(t_push_swap *push_swap, int current_chunk_size)
{
	int	moved_count;

	moved_count = 0;
	while (moved_count < current_chunk_size)
	{
		bring_to_top(push_swap, &push_swap->b,
			find_max_pos(&push_swap->b), OP_RB);
		exec_op(push_swap, OP_PA);
		moved_count++;
	}
	moved_count = 0;
	while (moved_count < current_chunk_size)
	{
		exec_op(push_swap, OP_RA);
		moved_count++;
	}
}

/* Les blocs croissants sont concaténés sans extraction globale en O(n²). */
void	sort_medium(t_push_swap *push_swap)
{
	int	size;
	int	chunk_size;
	int	completed_count;
	int	current_chunk_size;

	size = push_swap->a.size;
	chunk_size = integer_sqrt(size) * 5 / 2;
	if (chunk_size < 1)
		chunk_size = 1;
	completed_count = 0;
	while (completed_count < size)
	{
		current_chunk_size = chunk_size;
		if (current_chunk_size > size - completed_count)
			current_chunk_size = size - completed_count;
		extract_chunk(push_swap, completed_count,
			completed_count + current_chunk_size - 1,
			size - completed_count);
		bring_to_top(push_swap, &push_swap->a, completed_count, OP_RA);
		place_chunk(push_swap, current_chunk_size);
		completed_count += current_chunk_size;
	}
}
