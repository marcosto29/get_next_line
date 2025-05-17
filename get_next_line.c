/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:49:17 by matoledo          #+#    #+#             */
/*   Updated: 2025/05/11 14:17:54 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buffer(int fd, int *bytes_read)
{
	char	*pt_buffer;

	if (fd == -1)
		return (NULL);
	pt_buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!pt_buffer)
		return (NULL);
	*bytes_read = (int)read(fd, pt_buffer, BUFFER_SIZE);
	if (*bytes_read == -1 || (bytes_read == 0 && (!pt_buffer || !*pt_buffer)))
		return (free(pt_buffer), NULL);
	return (pt_buffer);
}

static char	*increment_readed_buffer(char *pt_buffer, int fd, int *bytes_read)
{
	char		*pt_read;
	char		*pt_return;

	pt_read = read_buffer(fd, bytes_read);
	if (!pt_read || *bytes_read == -1)
		return (free(pt_read), NULL);
	pt_return = ft_strjoin(pt_buffer, pt_read);
	return (free(pt_read), free(pt_buffer), pt_return);
}

static char	*search_end_of_line(char *pt_buffer)
{
	char	*pt_aux;
	char	*pt_return;

	pt_aux = ft_strchr(pt_buffer, '\n');
	if (!pt_aux)
		pt_aux = ft_strchr(pt_buffer, '\0');
	pt_return = ft_substr(pt_buffer, 0, pt_aux - pt_buffer + 1);
	return (pt_return);
}

static char	*readjust_buffer(char *pt_buffer)
{
	char	*pt_aux;
	char	*pt_return;

	pt_aux = ft_strchr(pt_buffer, '\n');
	if (!pt_aux || !*(pt_aux + 1))
		return (free(pt_buffer), NULL);
	pt_return = ft_strdup(pt_aux + 1);
	if (!pt_return)
		return (free(pt_buffer), NULL);
	return (free(pt_buffer), pt_return);
}

char	*get_next_line(int fd)
{
	static char	*pt_buffer;
	int			bytes_read;
	char		*pt_return;

	bytes_read = 0;
	if (!pt_buffer || !*pt_buffer)
	{
		pt_buffer = read_buffer(fd, &bytes_read);
		if (!pt_buffer)
			return (NULL);
	}
	while (ft_strchr(pt_buffer, '\n') == 0)
	{
		pt_buffer = increment_readed_buffer(pt_buffer, fd, &bytes_read);
		if (!pt_buffer)
			return (free(pt_buffer), pt_buffer = NULL, NULL);
		if (bytes_read == 0)
			break ;
	}
	pt_return = search_end_of_line(pt_buffer);
	if (!pt_return || !*pt_return)
		return (free(pt_return), free(pt_buffer), pt_buffer = NULL, NULL);
	pt_buffer = readjust_buffer(pt_buffer);
	return (pt_return);
}
