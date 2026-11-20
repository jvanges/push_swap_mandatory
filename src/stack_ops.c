/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Échange les deux premiers éléments sans toucher aux autres. */
void	stack_swap(t_stack *stack)
{
	int	tmp;

	if (stack->size < 2)
		return ;
	tmp = stack->data[0];
	stack->data[0] = stack->data[1];
	stack->data[1] = tmp;
}

/* Déplace le sommet de source vers destination en conservant leur ordre. */
void	stack_push(t_stack *destination, t_stack *source)
{
	int	i;

	if (source->size == 0)
		return ;
	i = destination->size;
	while (i > 0)
	{
		destination->data[i] = destination->data[i - 1];
		i--;
	}
	destination->data[0] = source->data[0];
	destination->size++;
	i = 0;
	while (i < source->size - 1)
	{
		source->data[i] = source->data[i + 1];
		i++;
	}
	source->size--;
}

/* Fait passer le premier élément à la dernière position. */
void	stack_rotate(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack->size < 2)
		return ;
	tmp = stack->data[0];
	i = 0;
	while (i < stack->size - 1)
	{
		stack->data[i] = stack->data[i + 1];
		i++;
	}
	stack->data[stack->size - 1] = tmp;
}

/* Fait passer le dernier élément à la première position. */
void	stack_reverse(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack->size < 2)
		return ;
	tmp = stack->data[stack->size - 1];
	i = stack->size - 1;
	while (i > 0)
	{
		stack->data[i] = stack->data[i - 1];
		i--;
	}
	stack->data[0] = tmp;
}
