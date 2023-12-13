/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 07:34:19 by lscarcel          #+#    #+#             */
/*   Updated: 2023/12/11 13:13:59 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024 
#endif

char *get_next_line(int fd)
{
	return(read_nbytes(fd, BUFFER_SIZE));
}

int main(void)
{
    char *fileName = "test.txt";
    int fd = open(fileName, O_RDONLY);

    if (fd == -1)
    {
        printf("La lecture a échoué\n");
        return 1;
    }
    else
    {
        char *line;
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("%s\n", line);
            free(line);
        }
    }
    close(fd);
    return 0;
}
