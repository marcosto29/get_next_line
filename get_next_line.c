/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:49:17 by matoledo          #+#    #+#             */
/*   Updated: 2025/04/28 17:07:45 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//static variable needed for the "checkpoint" of where we are reading
char	*get_next_line(int fd)
{
	size_t			size = 20;
	char			buffer[size];
	static ssize_t	read_bytes;

	read_bytes = read(fd, buffer, size);
	if(read_bytes == -1)
		return (NULL);
}
