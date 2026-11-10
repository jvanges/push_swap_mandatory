/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:18:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/10 15:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(const char *str, int fd)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}

/* L'écriture récursive évite d'utiliser une fonction de printf externe. */
void	ft_putlong_fd(long value, int fd)
{
	char	digit;

	if (value < 0)
	{
		ft_putchar_fd('-', fd);
		value = -value;
	}
	if (value >= 10)
		ft_putlong_fd(value / 10, fd);
	digit = (char)('0' + value % 10);
	ft_putchar_fd(digit, fd);
}

void	print_error(void)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
}
