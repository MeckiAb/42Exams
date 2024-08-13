/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:40:39 by labderra          #+#    #+#             */
/*   Updated: 2024/08/09 10:36:08 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 20
#endif

int	my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	nl_pos(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '\n')
			return (i + 1);
	return (-1);
}

void	append_str(char **dst, char *src)
{
	char	*aux;
	int		i;
	int		aux_len;
	
	i = 0;
	aux = *dst;
	aux_len = my_strlen(aux);
	*dst = malloc(sizeof(char) * (aux_len + my_strlen(src) + 1));
	if (!*dst)
	{
		free(aux);
		return ;
	}
	while (aux && aux[i])
	{
		(*dst)[i] = aux[i];
		i++;
	}
	while (src && src[i - aux_len])
	{
		(*dst)[i] = src[i - aux_len];
		i++;
	}
	(*dst)[i] = '\0';
	free(aux);
}


char	*divide_str(char **str)
{
	char	*left;
	char	*right;
	int		i;
	int		pos;

	pos = nl_pos(*str);
	left = malloc(sizeof(char) * (pos + 1));
	right = malloc(sizeof(char) * (my_strlen(*str) - pos + 1));
	if (!left || !right)
		return (free(left), free(right), free(*str), *str = NULL, NULL);
	i = 0;
	while (i < pos)
	{
		left[i] = (*str)[i];
		i++;
	}
	left[i] = '\0';
	while ((*str)[i])
	{
		right[i - pos] = (*str)[i];
		i++;
	}
	right[i - pos] = '\0';
	free (*str);
	*str = right;
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buffer;
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	while (nl_pos(leftover) == -1)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(leftover), leftover = NULL, NULL);
		else if (bytes_read == 0)
			return (free(buffer), buffer = leftover, leftover = NULL, buffer);
		buffer[bytes_read] = '\0';
		append_str(&leftover, buffer);
		free(buffer);
	}
	return (divide_str(&leftover));
}
