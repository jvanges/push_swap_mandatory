/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

const char	*op_name(t_op op)
{
	if (op == OP_SA)
		return ("sa");
	if (op == OP_SB)
		return ("sb");
	if (op == OP_SS)
		return ("ss");
	if (op == OP_PA)
		return ("pa");
	if (op == OP_PB)
		return ("pb");
	if (op == OP_RA)
		return ("ra");
	if (op == OP_RB)
		return ("rb");
	if (op == OP_RR)
		return ("rr");
	if (op == OP_RRA)
		return ("rra");
	if (op == OP_RRB)
		return ("rrb");
	return ("rrr");
}

/* Applique la partie élémentaire d'une opération demandée. */
static void	apply_single(t_ps *push_swap, t_op op)
{
	if (op == OP_SA || op == OP_SS)
		stack_swap(&push_swap->a);
	if (op == OP_SB || op == OP_SS)
		stack_swap(&push_swap->b);
	if (op == OP_PA)
		stack_push(&push_swap->a, &push_swap->b);
	if (op == OP_PB)
		stack_push(&push_swap->b, &push_swap->a);
	if (op == OP_RA || op == OP_RR)
		stack_rotate(&push_swap->a);
	if (op == OP_RB || op == OP_RR)
		stack_rotate(&push_swap->b);
	if (op == OP_RRA || op == OP_RRR)
		stack_reverse(&push_swap->a);
	if (op == OP_RRB || op == OP_RRR)
		stack_reverse(&push_swap->b);
}

/* Exécute, compte puis affiche une unique instruction Push_swap. */
void	exec_op(t_ps *push_swap, t_op op)
{
	apply_single(push_swap, op);
	push_swap->counts[op]++;
	push_swap->total++;
	ft_putstr_fd(op_name(op), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}
