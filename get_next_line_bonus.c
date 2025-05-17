/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:49:17 by matoledo          #+#    #+#             */
/*   Updated: 2025/05/17 22:12:40 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_buffer(int fd, int *bytes_read)
{
	char	*pt_buffer;

	if (fd == -1)
		return (NULL);
	pt_buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!pt_buffer)
		return (NULL);
	*bytes_read = (int)read(fd, pt_buffer, BUFFER_SIZE);
	if (*bytes_read == -1)
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

static char	*search_end_of_line(char **pt_buffer)
{
	char	*pt_aux;
	char	*pt_return;
	char	*pt_after_buffer;

	pt_aux = ft_strchr(*pt_buffer, '\n');
	if (pt_aux)
		pt_aux++;
	else
		pt_aux = ft_strchr(*pt_buffer, '\0');
	pt_return = ft_substr(*pt_buffer, 0, pt_aux - *pt_buffer);
	if (*pt_aux)
		pt_after_buffer = ft_strdup(pt_aux);
	else
		pt_after_buffer = NULL;
	free(*pt_buffer);
	*pt_buffer = pt_after_buffer;
	return (pt_return);
}

char	*get_next_line(int fd)
{
	static char	*buf[1024];
	int			bytes_read;
	char		*ret;

	bytes_read = 0;
	if (!buf[fd] || !*buf[fd])
	{
		buf[fd] = read_buffer(fd, &bytes_read);
		if (!buf[fd])
			return (NULL);
	}
	while (ft_strchr(buf[fd], '\n') == 0)
	{
		buf[fd] = increment_readed_buffer(buf[fd], fd, &bytes_read);
		if (!buf[fd])
			return (buf[fd] = NULL, NULL);
		if (bytes_read == 0)
			break ;
	}
	ret = search_end_of_line(&buf[fd]);
	if (!ret || !*ret)
		return (free(ret), free(buf[fd]), buf[fd] = NULL, NULL);
	return (ret);
}
