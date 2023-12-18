/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 07:34:12 by lscarcel          #+#    #+#             */
/*   Updated: 2023/12/18 11:26:13 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *buf, char c)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		a;
	char	*str;

	if (!str1)
		return (0);
	i = ft_strlen(str1);
	a = ft_strlen(str2);
	str = malloc(sizeof(char) * ((i + a) + 1));
	if (!str)
		return (0);
	i = 0;
	a = 0;
	while (str1[i])
	{
		str[a++] = str1[i++];
	}
	i = 0;
	while (str2[i])
	{
		str[a++] = str2[i++];
	}
	str[a] = '\0';
	free(str1);
	return (str);
}

void	free_buffers(char *buffer1, char *buffer2)
{
	free(buffer1);
	free(buffer2);
}
