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
static t_strategy	adaptive_strategy(double disorder_ratio)
{
	if (disorder_ratio < 0.2)
		return (SIMPLE);
	if (disorder_ratio < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}

void	execute_strategy(t_push_swap *push_swap, const t_config *config,
			double disorder_ratio)
{
	t_strategy	selected_strategy;

	selected_strategy = config->strategy;
	if (selected_strategy == ADAPTIVE)
		selected_strategy = adaptive_strategy(disorder_ratio);
	if (!is_sorted(&push_swap->a))
	{
		if (selected_strategy == SIMPLE)
			sort_simple(push_swap);
		else if (selected_strategy == MEDIUM)
			sort_medium(push_swap);
		else
			sort_complex(push_swap);
	}
	if (config->bench)
		print_bench(push_swap, disorder_ratio, selected_strategy,
			config->strategy == ADAPTIVE);
}
