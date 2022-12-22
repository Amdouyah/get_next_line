/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:18:16 by amdouyah          #+#    #+#             */
/*   Updated: 2022/12/20 02:24:36 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_save(char *r)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (r[i] && r[i] != '\n')
		i++;
	if (!r[i])
	{
		free(r);
		return (0);
	}
	s = malloc(ft_str_len(r) - i);
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (r[i])
		s[j++] = r[i++];
	s[j] = '\0';
	free (r);
	return (s);
}

char	*ft_get_line(char *r)
{
	int		i;
	char	*s;

	i = 0;
	if (!r[i])
		return (NULL);
	while (r[i] && r[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (r[i] && r[i] != '\n')
	{
		s[i] = r[i];
		i++;
	}
	if (r[i] == '\n')
	{
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_read(int fd, char *r)
{
	char	*buffer;
	int		res;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	res = 1;
	while (!ft_str_chr(r, '\n') && res != 0)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res < 0)
		{
			free (buffer);
			free (r);
			return (NULL);
		}
		buffer[res] = '\0';
		r = ft_strjoin(r, buffer);
	}
	free(buffer);
	return (r);
}

char	*get_next_line(int fd)
{
	char		*ptr;
	static char	*r[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	r[fd] = ft_read(fd, r[fd]);
	if (!r[fd])
		return (NULL);
	ptr = ft_get_line(r[fd]);
	r[fd] = ft_save(r[fd]);
	return (ptr);
}
