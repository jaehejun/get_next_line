/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0703_1840.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/07/03 20:40:48 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//void	free_memory(char *str)
//{
//	free(str);
//	str = NULL;
//}

char	*make_line(char *str)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	if (str[len] == '\0')
		return (str);			// NULL? or ""?
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (line == NULL)
		return (NULL);
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	i = 0;
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*make_remain(char *str)
{
	char	*remain;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	remain = ft_strdup(&str[i + 1]);
	if (remain == NULL)
		return (NULL);
	return (remain);
}

char	*read_line(int fd, char *remain)
{
	char	*buffer;
	char	*temp;
	int		count;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(remain, '\n') == NULL)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		else if (count == 0)
		{
			free(buffer);
			buffer = NULL;
			return (remain); // remain is the last line. if remain has "" then it is EOF.
		}
		else
		{
			buffer[count] = '\0';
			temp = remain;
			remain = ft_strjoin(remain, buffer);
			if (remain == NULL)
			{
				free(buffer);
				buffer = NULL;
				return (NULL);
			}
		}
	}
	free(buffer);
	buffer = NULL;
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;
	char		*temp;

	if (fd < 0)
		return (NULL);
	if (remain == NULL)
		remain = ft_strdup("");
	if (remain == NULL)
		return (NULL);
	temp = read_line(fd, remain);
	if (temp == NULL)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	free(remain);
	remain = NULL;
	remain = ft_strdup(temp);
	if (remain == NULL)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	line = make_line(temp);
	if (line == NULL)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	remain = make_remain(remain);
	if (remain == NULL)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}
