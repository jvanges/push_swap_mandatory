/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/* Les opérations sont aussi les indices de leurs compteurs. */
typedef enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_COUNT
}	t_op;

typedef enum e_strategy
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_strategy;

/* Le sommet de chaque pile se trouve à l'indice zéro. */
typedef struct s_stack
{
	int	*data;
	int	size;
	int	capacity;
}	t_stack;

typedef struct s_ps
{
	t_stack	a;
	t_stack	b;
	long	counts[OP_COUNT];
	long	total;
}	t_ps;

typedef struct s_config
{
	t_strategy	strategy;
	int			bench;
	int			strategy_seen;
}	t_config;

int		parse_arguments(int argc, char **argv, t_config *config,
			int **values);
int		parse_number(const char *str, int *cursor, int *value);
int		parse_string(const char *str, int *values, int *count);
int		flag_code(const char *str);
int		ft_isspace(char c);
int		ft_streq(const char *left, const char *right);

double	compute_disorder(const t_stack *stack);
int		has_duplicates(const t_stack *stack);
int		normalize_stack(t_stack *stack);
int		is_sorted(const t_stack *stack);

void	stack_swap(t_stack *stack);
void	stack_push(t_stack *dst, t_stack *src);
void	stack_rotate(t_stack *stack);
void	stack_reverse(t_stack *stack);
void	exec_op(t_ps *ps, t_op op);
const char	*op_name(t_op op);

int		find_rank_pos(const t_stack *stack, int rank);
int		find_max_pos(const t_stack *stack);
void	bring_a_to_top(t_ps *ps, int pos);
void	bring_b_to_top(t_ps *ps, int pos);

void	sort_simple(t_ps *ps);
void	sort_medium(t_ps *ps);
void	sort_complex(t_ps *ps);
void	run_strategy(t_ps *ps, t_strategy strategy);
t_strategy	adaptive_strategy(double disorder);

void	print_bench(const t_ps *ps, double disorder,
			t_strategy strategy, int adaptive);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *str, int fd);
void	ft_putlong_fd(long value, int fd);
void	print_error(void);

#endif
