/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:49:17 by matoledo          #+#    #+#             */
/*   Updated: 2025/05/02 13:29:52 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*search_end_of_line(char *pt_buffer)
{
	char	*pt_aux;
	char	*pt_return;

	pt_aux = ft_strchr(pt_buffer, '\n');
	if (!pt_aux)
		pt_aux = ft_strchr(pt_buffer, '\0');
	pt_return = ft_calloc(sizeof(char), (pt_aux - pt_buffer) + 2);
	if (!pt_return)
		return (NULL);
	ft_memcpy(pt_return, pt_buffer, pt_aux - pt_buffer + 1);
	return (pt_return);
}

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

//add more characters from the file to the buffer
//uses auxiliar pointers to manage the memory correctly
static char	*increment_readed_buffer(char *pt_buffer, int fd, int *bytes_read)
{
	char		*pt_aux;
	char		*pt_read;

	pt_aux = ft_strdup(pt_buffer);
	free(pt_buffer);
	pt_read = read_buffer(fd, bytes_read);
	if (!pt_read || !pt_aux || *bytes_read == -1)
		return (free(pt_aux), free(pt_read), NULL);
	pt_buffer = ft_calloc(sizeof(char), ft_strlen(pt_aux) + BUFFER_SIZE + 1);
	if (!pt_buffer)
		return (free(pt_aux), free(pt_read), NULL);
	ft_memcpy(pt_buffer, pt_aux, ft_strlen(pt_aux));
	ft_memcpy((pt_buffer + ft_strlen(pt_aux)), pt_read, ft_strlen(pt_read));
	return (free(pt_aux), free(pt_read), pt_buffer);
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
	static char	*buf[42];
	int			bytes_read;
	char		*ret;

	bytes_read = 0;
	if (!buf[fd % 42] || !*buf[fd % 42])
	{
		buf[fd % 42] = read_buffer(fd, &bytes_read);
		if (!buf[fd % 42])
			return (NULL);
	}
	while (ft_strchr(buf[fd % 42], '\n') == 0)
	{
		buf[fd] = increment_readed_buffer(buf[fd % 42], fd, &bytes_read);
		if (!buf[fd % 42])
			return (buf[fd % 42] = NULL, NULL);
		if (bytes_read == 0)
			break ;
	}
	ret = search_end_of_line(buf[fd % 42]);
	if (!ret || !*ret)
		return (free(ret), free(buf[fd % 42]), buf[fd % 42] = NULL, NULL);
	buf[fd % 42] = readjust_buffer(buf[fd % 42]);
	return (ret);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	int		fd2;

// 	printf("Test01\n");
// 	fd = open("test07.txt", O_RDONLY);
// 	fd2 = open("test02.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("%s", line);
// 	free(line);
// 	// close(fd);
// 	// fd = open("test03.txt", O_RDONLY);
// 	// while ((line = get_next_line(fd)))
// 	// {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// 	// close(fd);
// 	// fd = open("test04.txt", O_RDONLY);
// 	// while ((line = get_next_line(fd)))
// 	// {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// 	// close(fd);
// 	// fd = open("test05.txt", O_RDONLY);
// 	// while ((line = get_next_line(fd)))
// 	// {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// 	// close(fd);
// }