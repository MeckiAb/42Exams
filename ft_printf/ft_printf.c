/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:07:06 by labderra          #+#    #+#             */
/*   Updated: 2024/08/09 14:21:15 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

void	print_str(char *str, int *i)
{
	if (!str)
	{
		write(1, "(null)", 6);
		*i += 6;
		return ;
	}
	while (*str)
	{
		write(1, str, 1);
		*i += 1;
		str += 1;
	}
}

void	print_nbr(int nbr, int *i)
{
	char	c;

	if (nbr == INT_MIN)
	{
		write(1, "-2147483648", 11);
		*i += 11;
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		*i += 1;
		print_nbr(-nbr, i);
	}
	else if (nbr > 9)
	{
		print_nbr(nbr / 10, i);
		c = '0' + nbr % 10;
		write(1, &c, 1);
		*i += 1;
	}
	else
	{
		c = '0' + nbr;
		write(1, &c, 1);
		*i += 1;
	}
}

void	print_hex(unsigned int nbr, int *i)
{
	char c;

	if (nbr > 15)
	{
		print_hex(nbr / 16, i);
		if (nbr % 16 > 9)
			c = 'a' + nbr % 16 - 10;
		else
			c = '0' + nbr % 16;
	}
	else
	{
		if (nbr > 9)
			c = 'a' + nbr - 10;
		else
			c = '0' + nbr;
	}
	write(1, &c, 1);
	*i += 1;
}

int	ft_printf(char const *format, ...)
{
	int 	i;
	va_list	ap;

	i = 0;
	va_start(ap, format);
	while (i >=0 && *format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			i++;
		}
		else
		{
			if (*(++format) == 's')
				print_str(va_arg(ap, char *), &i);
			else if (*format == 'x')
				print_hex(va_arg(ap, unsigned int), &i);
			else if (*format == 'd')
				print_nbr(va_arg(ap, int), &i);
			else
				return (-1);
		}
		format++;
	}
	va_end(ap);
	return (i);
}
