/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:51:32 by matoledo          #+#    #+#             */
/*   Updated: 2025/05/11 13:43:14 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	char	*pt_call;
	char	*pt_aux;

	total = nmemb * size;
	pt_call = malloc(total);
	if (!pt_call)
		return (0);
	pt_aux = pt_call;
	while (total--)
	{
		*pt_aux++ = '\0';
	}
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pt_return;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	pt_return = ft_calloc(sizeof(char), len_s1 + len_s2 + 1);
	if (!pt_return)
		return (0);
	ft_memcpy(pt_return, s1, len_s1);
	ft_memcpy(pt_return + len_s1, s2, len_s2);
	return (pt_return);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pt_return;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	pt_return = ft_calloc(sizeof(char), len + 1);
	if (!pt_return)
		return (0);
	ft_memcpy(pt_return, s + start, len);
	return (pt_return);
}
