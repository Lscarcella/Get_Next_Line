/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 07:34:19 by lscarcel          #+#    #+#             */
/*   Updated: 2023/12/18 11:24:07 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ft_remove_line est utilisée pour supprimer la première ligne du tampon (ou mémoire tampon) stash.
// Elle cherche la première occurrence du caractère de nouvelle ligne ('\n') dans le tampon.
// Si aucun caractère de nouvelle ligne n'est trouvé, elle libère la mémoire allouée pour le tampon et retourne 0.
// Sinon, elle crée un nouveau tampon sans la première ligne et libère la mémoire du tampon initial.
char	*ft_remove_line(char *stash)
{
	char	*new_stash;
	int		i;
	int		a;
	int		len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (0);
	}
	len = ft_strlen(stash);
	new_stash = malloc((len - i + 1) * sizeof(char));
	if (!new_stash)
		return (0);
	i++;
	a = 0;
	while (stash[i])
		new_stash[a++] = stash[i++];
	new_stash[a] = '\0';
	free(stash);
	return (new_stash);
}

// ft_get_line est utilisée pour extraire la première ligne du tampon stash.
// Elle cherche la première occurrence du caractère de nouvelle ligne ('\n') dans le tampon.
// Elle alloue de la mémoire pour stocker la ligne extraite et la retourne.
// Si aucun caractère de nouvelle ligne n'est trouvé, elle retourne 0.
char	*ft_get_line(char *stash)
{
	int		i;
	int		a;
	char	*line;

	i = 0;
	if (!stash[i])
		return (0);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	a = 0;
	while (stash[a] && stash[a] != '\n')
	{
		line[a] = stash[a];
		a++;
	}
	if (stash[a] == '\n')
	{
		line[a] = stash[a];
		a++;
	}
	line [a] = '\0';
	return (line);
}

// Cette fonction lit le fichier pointé par fd et stocke son contenu dans un tampon stash.
// Elle utilise un tampon buf pour lire les données du fichier en morceaux de taille BUFFER_SIZE à la fois.
// Elle concatène les données lues dans le tampon stash jusqu'à ce qu'elle atteigne la fin du fichier ou qu'elle trouve un caractère de nouvelle ligne dans le tampon stash.
// Elle retourne le tampon stash contenant les données lues.
char	*ft_read_line(int fd, char *stash)
{
	char	*buf;
	int		bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free_buffers(buf, stash);
			return (0);
		}
		buf[bytes_read] = '\0';
		if (!stash)
		{
			stash = malloc(sizeof(char) * 1);
			stash[0] = '\0';
		}
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

// Cette fonction est appelée pour obtenir la prochaine ligne du fichier associé au descripteur de fichier fd.
// Elle vérifie d'abord si les paramètres (fd et BUFFER_SIZE) sont valides.
// Elle utilise la fonction ft_read_line pour lire le fichier et stocker son contenu dans stash.
// Ensuite, elle utilise ft_get_line pour extraire la première ligne du tampon stash.
// Après avoir obtenu la ligne, elle utilise ft_remove_line pour supprimer cette ligne du tampon stash.
// Finalement, elle retourne la ligne extraite.
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = ft_read_line(fd, stash);
	if (!stash)
		return (0);
	line = ft_get_line(stash);
	stash = ft_remove_line(stash);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// #include "get_next_line.h"

// int main()
// {
//     int fd;
//     char *line;
//     char *file_path = "test.txt";

//     fd = open(file_path, O_RDONLY);
//     if (fd == -1) {
//         perror("Erreur lors de l'ouverture du fichier");
//         return 1;
//     }
//     while ((line = get_next_line(fd)) != NULL) {
//         printf("Ligne lue : %s\n", line);
//         free(line);
//     }
//     close(fd);
//     return 0;
// }
