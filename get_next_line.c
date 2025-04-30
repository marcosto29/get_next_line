/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:49:17 by matoledo          #+#    #+#             */
/*   Updated: 2025/04/30 15:35:21 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

char	*search_end_of_line(char *pt_buffer, int bytes_read)
{
	char	*pt_aux;
	char	*pt_return;

	if (bytes_read == 0)
		pt_aux = ft_strchr(pt_buffer, '\0');
	else
		pt_aux = ft_strchr(pt_buffer, '\n');
	pt_return = ft_calloc(sizeof(char), (pt_aux - pt_buffer) + 2);
	if (!pt_return)
		return (0);
	ft_memcpy(pt_return, pt_buffer, pt_aux - pt_buffer + 1);
	return (pt_return);
}

char	*read_buffer(int fd, int *bytes_read)
{
	char	*pt_buffer;

	pt_buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!pt_buffer)
		return (0);
	*bytes_read = (int)read(fd, pt_buffer, BUFFER_SIZE);
	if (*bytes_read == -1)
		return (0);
	return (pt_buffer);
}

//add more characters from the file to the buffer
//uses auxiliar pointers to manage the memory correctly
char	*increment_readed_buffer(char *pt_buffer, int fd, int *bytes_read)
{
	char		*pt_aux;
	char		*pt_read;

	pt_read = read_buffer(fd, bytes_read);
	if (*bytes_read == -1 || !pt_read)
		return (0);
	pt_aux = ft_strdup(pt_buffer);
	if (!pt_aux)
	{
		free(pt_read);
		return (0);
	}
	free(pt_buffer);
	pt_buffer = ft_calloc(sizeof(char), ft_strlen(pt_aux) + BUFFER_SIZE + 1);
	if (!pt_buffer)
	{
		free(pt_aux);
		free(pt_read);
		return (0);
	}
	ft_memcpy(pt_buffer, pt_aux, ft_strlen(pt_aux));
	ft_memcpy((pt_buffer + ft_strlen(pt_aux)), pt_read, ft_strlen(pt_read));
	free(pt_aux);
	free(pt_read);
	return (pt_buffer);
}

char	*readjust_buffer(char *pt_buffer)
{
	char *pt_aux;
	char *pt_return;

	pt_aux = ft_strchr(pt_buffer, '\n');
	if (!pt_aux)
		return (0);
	pt_return = ft_strdup(pt_aux + 1);
	free(pt_buffer);

	return (pt_return);
}

char	*get_next_line(int fd)
{
	static char	*pt_buffer;
	char		*pt_return;
	int			bytes_read;

	if (fd == -1)
		return (0);
	if (!pt_buffer || !*pt_buffer)
		pt_buffer = read_buffer(fd, &bytes_read);
	while (ft_strchr(pt_buffer, '\n') == 0 && bytes_read != 0)
	{
		pt_buffer = increment_readed_buffer(pt_buffer, fd, &bytes_read);
		if (!pt_buffer)
			return (0);
	}
	pt_return = search_end_of_line(pt_buffer, bytes_read);
	if (!pt_return || !*pt_return)
	{
		free(pt_buffer);
		pt_buffer = NULL;
		return (0);
	}
	pt_buffer = readjust_buffer(pt_buffer);
	return (pt_return);
}

int	main(void)
{
	char	*line;
	int		fd;

	printf("Test01\n");
	fd = open("test01.txt", O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	fd = open("test02.txt", O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	fd = open("test03.txt", O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	fd = open("test04.txt", O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	fd = open("test05.txt", O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}
