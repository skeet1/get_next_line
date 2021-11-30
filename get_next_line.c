/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:00:57 by mkarim            #+#    #+#             */
/*   Updated: 2021/11/30 13:02:50 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_search(char *s, char c)
{
	int		i;

	i = 0;
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

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	return (line);
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
	//printf("save is : [%s]\n", save);
	return (save);
}

char	*get_next_line(int fd)
{
	int		r;
	char	*line;
	static	char	*s;
	int		d;

	d = 0;
	r = 1;
	line = NULL;
	if (BUFFER_SIZE < 0)
		return (NULL);
	s = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (r >= 0 && ft_search(s, '\n') == 0)
	{
		r = read(fd, s, BUFFER_SIZE);
		if (r == 0)
			break;
		if (r < 0)
		{
			free(s);
			return (NULL);
		}
		line = ft_strjoin(line, s);
	}
	s = ft_save_rest(line);
	line = ft_get_line(line);
	free(s);
	return (line);
}
/*
int main()
{
	int		fd;

	fd = open("test", O_CREAT | O_RDWR);
//	printf("%s\n", ft_save_rest("hello\nworld"));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
}*/
