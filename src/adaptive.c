/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Les seuils sont ceux imposés par le sujet pour chaque régime. */
t_strategy	adaptive_strategy(double disorder)
{
	if (disorder < 0.2)
		return (SIMPLE);
	if (disorder < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}

void	run_strategy(t_ps *ps, t_strategy strategy)
{
	if (is_sorted(&ps->a))
		return ;
	if (strategy == SIMPLE)
		sort_simple(ps);
	else if (strategy == MEDIUM)
		sort_medium(ps);
	else
		sort_complex(ps);
}
