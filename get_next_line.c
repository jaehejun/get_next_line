/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/07/04 17:57:13 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//void	free_memory(char *str)
//{
//	free(str);
//	str = NULL;
//}

char	*make_line(char *line)
{
	char	*new_line;
	int		len;
	int		i;

	len = 0;
	while (line[len] != '\0')
	{
		if (line[len] == '\n')
		{
			len++;
			break;
		}
		len++;
	}
	new_line = (char *)malloc(sizeof(char) * (len + 1));
	if (new_line == NULL)
		return (NULL);
	new_line[len] = '\0';
	i = 0;
	while (len-- > 0)
	{
		new_line[i] = line[i];
		i++;
	}
	printf("MAKE_LINE : %s\n", new_line);
	return (new_line);
}

char	*make_remain(char *remain)
{
	char	*new_remain;
	int		i;

	i = 0;
	while (remain[i] != '\0')
	{
		if (remain[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	//if (remain[i] == '\0')	// remain에 \n이 없을때 remain 그대로 반환
	//	return (remain);
	new_remain = ft_strdup(&remain[i + 1]);
	if (new_remain == NULL)
		return (NULL);
	printf("MAKE_REMAIN : %s\n", new_remain);
	return (new_remain);
}

char	*read_line(int fd, char *buffer, char *remain)
{
	int		count;	// read의 반환값 저장(읽은 바이트 수, EOF : 0, 에러 : -1)
	char	*temp;	// remain에 strjoin할때 임시로 저장하고 free 대신해줄 변수
	
	if (remain == NULL)		// 첫 호출시 static remain은 NULL로 초기화되어있음
		remain = ft_strdup("");	// remain에 빈문자열 넣어서 주소값 할당
	if (remain == NULL)	// ft_strdup 실패시 NULL 반환
		return (NULL);
	printf("REMAIN 빈문자열 초기화\n");
	count = 1;	// count 초기화해서 while문 진입
	while (count != 0 && strchr(remain, '\n') == NULL)	// read한게 있고 remain에 \n나올때까지 반복
	{
		count = read(fd, buffer, BUFFER_SIZE);	// buffer에 read한 문자열 저장하고 count에 read한 바이트수 저장
		if (count == -1)	// read 실패시 NULL 반환 - remain : free해줘야함, buffer : free해줘야함
		{
			free(remain);
			//free(buffer);	// buffer free는 get_next_line에서 해줘야함
			return (NULL);
		}
		else if (count == 0)	// EOF일때 remain 반환 - remain : free해줘야함
		{
			break;
			//free(buffer);	// buffer free는 get_next_line에서 해줘야함
			//return (remain);		// remain : ""(첫호출) 또는 파일의 마지막 문자열(n번째호출)로 초기화되어있음
		}
		else	// (count > 0) : 1byte이상 read 성공시
		{
			buffer[count] = '\0';	// buffer에 read한 문자열 마지막에 '\0' 넣어줌
			temp = remain;	// remain의 original 주소값을 temp에 저장 -> remain에 다른 주소값 할당시 free(remain)위해
			remain = ft_strjoin(remain, buffer);	// remain에 read한 문자열 붙여줌
			if (remain == NULL)	// ft_strjoin 실패시 NULL 반환 - remain : free해줘야함, temp : free해줘야함
			{
				free(temp);
				//free(buffer);	// buffer free는 get_next_line에서 해줘야함
				return (NULL);
			}
		}
		free(temp);	// remain orignial 주소값 free
	}
	printf("REMAIN : %s\n", remain);
	return (remain);	// remain : '\n'이나 '\0'이 포함된 문자열
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;
	char		*buffer;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)	// fd가 음수거나 BUFFER_SIZE가 0이하면 에러
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));	// buffer malloc
	if (buffer == NULL)
		return (NULL);		// buffer malloc 실패시 NULL 반환
	line = read_line(fd, buffer, remain);	// (fd > 0, buffer : malloc, remain : 첫호출시 NULL)
	printf("LINE : %s\n", line);
	printf("LINE   : %p\n", line);
	if (line == NULL)	// read_line 실패시 NULL 반환
	{
		free(buffer);	// malloc한 buffer free
		return (NULL);
	}
	if (line[0] == '\0')	// line이 빈문자열 -> empty file
	{
		free(buffer);	// malloc한 buffer free
		//free(remain);	// remain free
		return (NULL);
	}
	free(buffer);	// malloc한 buffer free
	// line = read_line() == remain
	temp = line;	// line의 original 주소값을 temp에 저장 -> line에 다른 주소값 할당시 free(line)위해
	line = make_line(line);	// remain에서 \n전까지의 문자열만 line에 저장
	printf("TEMP     : %p\n", temp);
	printf("NEW LINE : %p\n", line);
	printf("NEW LINE : %s\n", line);
	printf("REMAIN : %p\n", remain);
	if (line == NULL)	// make_line 실패시 NULL 반환
	{
		//free(remain);	// remain free : remain은 line의 orignial 주소값을 가지고 있음 -> 아님
		free(temp);	// line original 주소값 free
		return (NULL);
	}
	//temp = remain;	// remain의 original 주소값을 temp에 저장 -> remain에 다른 주소값 할당시 free(remain)위해
	printf("TEMP   : %p\n", temp);
	printf("TEMP : %s\n", temp);
	remain = make_remain(temp);	// temp에서 \n뒤의 문자열만 remain에 저장
	printf("NEW REMAIN : %s\n", remain);
	if (remain == NULL)
	{
		free(line);	// new_line free
		free(temp);	// line 의 original 주소값 free
		return (NULL);
	}
	free(temp);	// line original 주소값 free
	temp = NULL;
	printf("---------------------------------------FREE CHECKING---------------------------------------\n");
	printf("RETURN LINE : %p\n", line);
	printf("RETURN LINE : %s\n", line);
	printf("REMAIN : %p\n", remain);
	printf("REMAIN : %s\n", remain);
	printf("TEMP(OG LINE) : %p\n", temp);
	printf("TEMP(OG LINE) : %s\n", temp);
	return (line);	// line : \n 까지의 문자열
}

int	main(void)
{
	int		fd;
	char	*line;
	int	i = 1;
	
	fd = open("test.txt", O_RDONLY);
	printf("----------------------------------1st GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------2nd GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------3rd GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------4th GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------5th GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------6th GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------7th GNL-------------------------------------\n");
	return 0;
}