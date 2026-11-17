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
static void	extract_chunk(t_ps *ps, int low, int high, int remaining)
{
	int	i;
	int	rank;

	i = 0;
	while (i < remaining)
	{
		rank = ps->a.data[0];
		if (rank >= low && rank <= high)
			exec_op(ps, OP_PB);
		else
			exec_op(ps, OP_RA);
		i++;
	}
}

/* Trie le bloc par extraction des maxima et le place sous les précédents. */
static void	place_chunk(t_ps *ps, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		bring_to_top(ps, &ps->b, find_max_pos(&ps->b), OP_RB);
		exec_op(ps, OP_PA);
		i++;
	}
	i = 0;
	while (i < amount)
	{
		exec_op(ps, OP_RA);
		i++;
	}
}

/* Les blocs croissants sont concaténés sans extraction globale en O(n²). */
void	sort_medium(t_ps *ps)
{
	int	size;
	int	chunk;
	int	completed;
	int	amount;

	size = ps->a.size;
	chunk = integer_sqrt(size) * 5 / 2;
	if (chunk < 1)
		chunk = 1;
	completed = 0;
	while (completed < size)
	{
		amount = chunk;
		if (amount > size - completed)
			amount = size - completed;
		extract_chunk(ps, completed, completed + amount - 1,
			size - completed);
		bring_to_top(ps, &ps->a, completed, OP_RA);
		place_chunk(ps, amount);
		completed += amount;
	}
}
