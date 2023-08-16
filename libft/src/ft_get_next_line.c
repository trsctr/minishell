/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trsctr <trsctr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:53:15 by oandelin          #+#    #+#             */
/*   Updated: 2023/03/23 07:54:24 by trsctr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*scan_for_line(char *scan, int fd)
{
	char		*buf;
	char		*temp;
	int			bytes_read;

	bytes_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_strchr(scan, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(scan);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		temp = ft_strjoin(scan, buf);
		free(scan);
		scan = temp;
	}
	free(buf);
	return (scan);
}

static	char	*split_line(char *line, char *scan)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (scan[i] == '\0')
		return (NULL);
	while (scan[len] && scan[len] != '\n')
		len++;
	line = ft_calloc((len + 2), sizeof(char));
	while (i <= len)
	{
		line[i] = scan[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static	char	*trim_scan(char *scan)
{
	char	*scan_copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (scan[i] && scan[i] != '\n')
		i++;
	if (!scan[i])
	{
		free(scan);
		return (NULL);
	}
	scan_copy = ft_calloc((ft_strlen(scan) - i + 1), sizeof(char));
	i++;
	while (scan[i])
		scan_copy[j++] = scan[i++];
	scan_copy[j] = '\0';
	free(scan);
	return (scan_copy);
}

// get_next_line
// when called, retrieves next line from file descriptor fd
char	*get_next_line(int fd)
{
	char		*nextline;
	static char	*scan[256];

	nextline = NULL;
	if ((read(fd, 0, 0)) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!scan[fd])
	{	
		scan[fd] = ft_calloc(1, 1);
		if (!scan[fd])
			return (NULL);
		scan[fd][0] = '\0';
	}
	scan[fd] = scan_for_line(scan[fd], fd);
	nextline = split_line(nextline, scan[fd]);
	scan[fd] = trim_scan(scan[fd]);
	if (!scan[fd])
		free(scan[fd]);
	return (nextline);
}
