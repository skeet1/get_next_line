/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:00:57 by mkarim            #+#    #+#             */
/*   Updated: 2021/12/04 11:51:49 by karim            ###   ########.fr       */
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
		len++;
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

typedef struct variables {
	int		i;
	int		j;
	int		start;
}t_var;

char	*ft_save_rest(char *s)
{
	t_var	v;
	char	*save;

	v.i = 0;
	v.j = 0;
	v.start = 0;
	while (s[v.i] && s[v.i] != '\n')
		(v.i)++;
	if (s[v.i] == '\0' || s[v.i + 1] == '\0')
	{
		free(s);
		return (NULL);
	}
	v.start = v.i + 1;
	if (s[v.i] && s[(v.i)++] == '\n')
		while (s[(v.i)++])
			(v.j)++;
	v.i = -1;
	save = (char *)malloc((v.j + 1) * sizeof(char));
	if (!save)
		return (NULL);
	while (++(v.i) + v.start < ft_strlen(s))
		save[v.i] = s[v.start + v.i];
	save[v.i] = '\0';
	free(s);
	return (save);
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
			break ;
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read(line, fd);
	if (!line)
		return (NULL);
	res = ft_get_line(line);
	line = ft_save_rest(line);
	return (res);
}

int main()
{
	int	fd;
	int	i;

	i = 0;
	fd = open("test", O_CREAT | O_RDWR);
	while (i < 10)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
}
