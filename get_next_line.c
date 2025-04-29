/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:49:17 by matoledo          #+#    #+#             */
/*   Updated: 2025/04/29 20:46:25 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	char	*pt_dest;

	pt_dest = dest;
	while (n--)
	{
		*pt_dest++ = (char)c;
	}
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	char	*pt_call;

	total = nmemb * size;
	pt_call = malloc(total);
	if (!pt_call)
		return (0);
	ft_memset(pt_call, '\0', total);
	return (pt_call);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*pt_dest;
	const char	*pt_src;

	pt_src = src;
	pt_dest = dest;
	if (!src && !dest)
		return (dest);
	while (n--)
	{
		*pt_dest++ = *pt_src++;
	}
	return (dest);
}

size_t	ft_strlen(const char *c)
{
	size_t	counter;

	counter = 0;
	while (*c++)
	{
		counter++;
	}
	return (counter);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == (char) c)
		return ((char *)s);
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	allocate_memory;
	char	*pt_return;

	allocate_memory = ft_strlen(s);
	pt_return = ft_calloc(sizeof(char), allocate_memory + 1);
	if (!pt_return)
		return (0);
	ft_memcpy(pt_return, s, allocate_memory);
	return (pt_return);
}

char	*get_next_line(int fd)
{
	static char	*pt_buffer;
	char		*pt_aux;
	char		*pt_read;
	int			iteration;
	char		*pt_return;

	iteration = 1;
	if (fd == -1)
		return (0);
	if (!pt_buffer)
	{
		pt_buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (read(fd, pt_buffer, BUFFER_SIZE) == -1)
			return (0);
	}
	while (ft_strchr(pt_buffer, '\n') == 0)
	{
		pt_aux = ft_strdup(pt_buffer);
		free(pt_buffer);
		pt_buffer = ft_calloc(sizeof(char), ft_strlen(pt_aux) + BUFFER_SIZE + 1);
		pt_read = ft_calloc(sizeof(char),  BUFFER_SIZE + 1);
		if (read(fd, pt_read, BUFFER_SIZE) == -1)
			return (0);
		ft_memcpy(pt_buffer, pt_aux, ft_strlen(pt_aux));
		ft_memcpy((pt_buffer + ft_strlen(pt_aux)), pt_read, ft_strlen(pt_read));
		free(pt_aux);
		free(pt_read);
		iteration++;
	}
	pt_aux = ft_strchr(pt_buffer, '\n');
	pt_return = ft_calloc(sizeof(char), (pt_aux - pt_buffer) + 2);
	ft_memcpy(pt_return, pt_buffer, pt_aux - pt_buffer + 1);
	pt_buffer = ft_strdup(pt_buffer + (pt_aux - pt_buffer + 1));
	return (pt_return);
}

int	main(void)
{
	char	*line;
	char	*pt_aux;
	int		fd;

	fd = open("test01.txt", O_RDONLY);
	line = get_next_line(fd);
	pt_aux = line;
	while (*line)
		write(1, line++, 1);
	line = get_next_line(fd);
	while (*line)
		write(1, line++, 1);
	line = get_next_line(fd);
	while (*line)
		write(1, line++, 1);
	line = get_next_line(fd);
	while (*line)
		write(1, line++, 1);
	while (*line)
		write(1, line++, 1);
	free (pt_aux);
}
