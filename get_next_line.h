/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:49:39 by matoledo          #+#    #+#             */
/*   Updated: 2025/05/06 14:19:44 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
//if BUFFER_SIZE is not define on the compiler with -D
//-DDO_SOMETHING=1 - Equivalent to add to the code #define DO_SOMETHING = 1
//create the macro with 42 value
//macros normally cannot be changed, thats the main difference with global variables
//when the code is compiled the macro is changed with the value choosed
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *c);

#endif
