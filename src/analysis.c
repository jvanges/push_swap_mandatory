/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Compte les inversions, normalisées par le nombre total de paires. */
double	compute_disorder(const t_stack *stack)
{
	long	mistakes;
	long	total;
	int		i;
	int		j;

	mistakes = 0;
	total = 0;
	i = 0;
	while (i < stack->size)
	{
		j = i + 1;
		while (j < stack->size)
		{
			total++;
			if (stack->data[i] > stack->data[j])
				mistakes++;
			j++;
		}
		i++;
	}
	if (total == 0)
		return (0.0);
	return ((double)mistakes / (double)total);
}

int	has_duplicates(const t_stack *stack)
{
	int	i;
	int	j;

	i = 0;
	while (i < stack->size)
	{
		j = i + 1;
		while (j < stack->size)
		{
			if (stack->data[i] == stack->data[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/* Remplace chaque valeur par son rang, compris entre zéro et n - 1. */
int	normalize_stack(t_stack *stack)
{
	int	*ranks;
	int	i;
	int	j;

	ranks = malloc((size_t)stack->size * sizeof(int));
	if (!ranks)
		return (0);
	i = 0;
	while (i < stack->size)
	{
		ranks[i] = 0;
		j = 0;
		while (j < stack->size)
		{
			if (stack->data[j] < stack->data[i])
				ranks[i]++;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < stack->size)
	{
		stack->data[i] = ranks[i];
		i++;
	}
	free(ranks);
	return (1);
}

int	is_sorted(const t_stack *stack)
{
	int	i;

	i = 0;
	while (i + 1 < stack->size)
	{
		if (stack->data[i] > stack->data[i + 1])
			return (0);
		i++;
	}
	return (1);
}
