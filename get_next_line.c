/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:00:57 by mkarim            #+#    #+#             */
/*   Updated: 2021/11/30 19:33:05 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_search(char *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_line(char *s)
{
	int		i;
	char	*line;
	int		len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\n')
	{
		len = len + 1;
	}
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
char	*ft_read(char *str, int fd)
{
	char	*buf;
	int		r;

	r = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (r != 0 && ft_search(str, '\n') == 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[r] = '\0';
		if (r == 0)
		{
			break ;
		}
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*ft_save_rest(char *s)
{
	int		i;
	int		j;
	int		start;
	char	*save;

	i = 0;
	j = 0;
	start = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	if (s[i] && s[i++] == '\n')
	{
		start = i;
		while (s[i++])
			j++;
	}
	i = 0;
	save = (char *)malloc((j + 1) * sizeof(char));
	while (s[start + i])
	{
		save[i] = s[start + i];
		i++;
	}
	save[i] = '\0';
	free(s);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char	*res;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = ft_read(line, fd);
	if (!line)
		return (NULL);
	res = ft_get_line(line);
	line = ft_save_rest(line);
	return (res);
}

/*int main()
{
	int		fd;

	fd = open("test", O_CREAT | O_RDWR);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}*/
