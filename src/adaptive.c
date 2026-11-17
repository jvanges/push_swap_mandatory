/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Les seuils sont ceux imposés par le sujet pour chaque régime. */
static t_strategy	adaptive_strategy(double disorder)
{
	if (disorder < 0.2)
		return (SIMPLE);
	if (disorder < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}

void	execute_strategy(t_ps *ps, const t_config *config, double disorder)
{
	t_strategy	strategy;

	strategy = config->strategy;
	if (strategy == ADAPTIVE)
		strategy = adaptive_strategy(disorder);
	if (!is_sorted(&ps->a))
	{
		if (strategy == SIMPLE)
			sort_simple(ps);
		else if (strategy == MEDIUM)
			sort_medium(ps);
		else
			sort_complex(ps);
	}
	if (config->bench)
		print_bench(ps, disorder, strategy, config->strategy == ADAPTIVE);
}
