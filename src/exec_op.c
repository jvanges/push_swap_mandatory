/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
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
static void	apply_single(t_ps *ps, t_op op)
{
	if (op == OP_SA || op == OP_SS)
		stack_swap(&ps->a);
	if (op == OP_SB || op == OP_SS)
		stack_swap(&ps->b);
	if (op == OP_PA)
		stack_push(&ps->a, &ps->b);
	if (op == OP_PB)
		stack_push(&ps->b, &ps->a);
	if (op == OP_RA || op == OP_RR)
		stack_rotate(&ps->a);
	if (op == OP_RB || op == OP_RR)
		stack_rotate(&ps->b);
	if (op == OP_RRA || op == OP_RRR)
		stack_reverse(&ps->a);
	if (op == OP_RRB || op == OP_RRR)
		stack_reverse(&ps->b);
}

/* Exécute, compte puis affiche une unique instruction Push_swap. */
void	exec_op(t_ps *ps, t_op op)
{
	apply_single(ps, op);
	ps->counts[op]++;
	ps->total++;
	ft_putstr_fd(op_name(op), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}
