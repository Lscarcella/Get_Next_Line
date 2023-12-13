/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 07:34:12 by lscarcel          #+#    #+#             */
/*   Updated: 2023/12/13 16:34:42 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024 
#endif


//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	p;

	p = (char)c;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == p)
			return ((char *)&s[i]);
		else
			i++;
	}
	if (s[i] == '\0' && p == '\0')
		return ((char *)&s[i]);
	return (0);
}
size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	if (!s)
		return (0);
	while (s[c] != '\0')
		c++;
	return (c);
}

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*dest;
	int		j;

	size = 0;
	if (!s1)
		return (0);
	while (s1[size] != '\0')
		size++;
	dest = malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		dest[j] = s1[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*newstring;
	size_t	i;
	size_t	newlen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (len < (slen - start))
		newlen = len;
	else
		newlen = slen - start;
	newstring = malloc(newlen + 1);
	if (newstring == NULL)
		return (NULL);
	i = 0;
	while (i < newlen)
	{
		newstring[i] = s[start + i];
		i++;
	}
	newstring[newlen] = '\0';
	return (newstring);
}

char *read_nbytes(int fd, size_t nbytes)
{
    static char *static_buffer = NULL;
    char *temp_buffer;
    size_t bytes_read;
    size_t newline_position;
	char *output_line;

    if (static_buffer == NULL)
	{
        static_buffer = malloc(BUFFER_SIZE);
        if (static_buffer == NULL)
		{
            return NULL;
        }
    }
    bytes_read = read(fd, static_buffer, nbytes);
    if (bytes_read == BUFFER_SIZE)
	{
        char *newline_ptr = ft_strchr(static_buffer, '\n');

        if (newline_ptr != NULL)
		{
            newline_position = newline_ptr - static_buffer;
            temp_buffer = ft_substr(static_buffer, newline_position + 1, BUFFER_SIZE);
			output_line = static_buffer;
			output_line[newline_position] = '\0';
			static_buffer = temp_buffer;
			return(output_line);
        }
		else
		{
            output_line = ft_strdup(static_buffer);
			free(static_buffer);
			read_nbytes(fd, nbytes);
        }
    }
	else
	{
		
    }
    return 0;
}

// char *read_nbytes(int fd, size_t nbytes)
// {q
//     static char static_buffer[BUFFER_SIZE + 1];
//     static int offset = 0;
//     ssize_t bytes_read;
//     int nl_position;

//     if ((bytes_read = read(fd, static_buffer + offset, nbytes)) > 0)
// 	{
//         static_buffer[offset + bytes_read] = '\0'; 

//         char *newline_ptr = ft_strchr(static_buffer + offset, '\n');
//         if (newline_ptr)
// 		{
//             nl_position = newline_ptr - (static_buffer + offset);
//             static_buffer[offset + nl_position] = '\0';
//             char *return_line = ft_strdup(static_buffer);
//             offset += nl_position + 1;
//             memmove(static_buffer, static_buffer + offset, BUFFER_SIZE - offset);
//             offset = ft_strlen(static_buffer);
//             return return_line;
//         }
// 		else
//             offset += bytes_read; 
//     }
//     return NULL;
// }

// char *read_nbytes(int fd, size_t nbytes)
// {
//     char *static_buffer;
//     ssize_t bytes_read;
//     char *return_line;
// 	char *temp_buffer;
// 	int nl_position;

// 	nl_position = 0;
// 	static_buffer = malloc(BUFFER_SIZE);
//     if (static_buffer == NULL)
//         return NULL;
//     while ((bytes_read = read(fd, static_buffer, nbytes)) > 0) 
// 	{
// 		if (ft_strchr(static_buffer, '\n') - static_buffer)
// 		{
// 			temp_buffer = ft_substr(static_buffer, nl_position, BUFFER_SIZE);
// 			return_line = static_buffer;
// 			return_line[nl_position] = '\0';
// 			*static_buffer = *temp_buffer;
// 			return return_line;
// 		}
// 		else
// 			return_line = ft_strdup(static_buffer);	
//     }
// 	return(0);
// }
