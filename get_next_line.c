/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/06/16 21:50:22 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*before_next(char *line)
{
	char	*before;
	int		i;
		before = (char *)malloc(sizeof(char) * ft_strlen(line));
	if (before == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		before[i++] = *(line++);
		if (*(line - 1) == '\n')
			break;
	}
	before[i] = '\0';
	return (before);
}

char	*after_next(char *line)
{
	char	*after;
	int		i;
	after = (char *)malloc(sizeof(char) * ft_strlen(line));
	if (after == NULL)
		return (NULL);
	i = 0;
	while (*line != '\0' && *(line - 1) != '\n')
		line++;
	while (*line !='\0')
	{
		after[i++] = *(line++);
	}
	after[i] = '\0';
	return (after);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*remain;
	char		*temp;
	static char	*line;
	int			count;
	int			w = 1;

	if (fd < 0 || BUFFER_SIZE <= 0)	// fd할당 잘못되었거나 버퍼사이즈가 0이하면 NULL
		return (NULL);
	if (line == 0)	// static char *line이 0초기화가 잘 되었다면
		line = ft_strdup("");	// line을 사용하기 위해 빈문자열을 만들어 주소값을 할당해준다.
	if (line == NULL)
		return (NULL);	// strdup이 실패해 NULL을 반환했다면 널가드
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));	//버퍼사이즈+1(널자리)만큼 동적할당
	if (buffer == NULL)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';		// +1한 자리에 널문자 넣어서 문자열의 끝을 알린다.
	count = 1;						// read한 문자의 갯수를 파악하기 위해 1을 넣어둔다.
	while (count != 0 && ft_strchr(line, '\n') == NULL)	// read가 EOF를 만나거나 복사된 line에 '\n'이 남아있다면 반복종료
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count <= 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[count] = '\0';	// 버퍼사이즈보다 count가 작을수도 있어서 널문자로 문자열의 끝을 알린다.
		line = ft_strjoin(line, buffer);	// line에 line + buffer
		if (line == NULL)
			return (NULL);
		if (ft_strchr(line, '\0') != NULL)
			break ;
	}
	if (count == 0)
		return (NULL);
	printf("FIRST LINE: %s\n", line);
	temp = before_next(line);
	printf("%s\n", temp);
	remain = after_next(line);				// line이 개행까지만 잘린 상태라 after 불가하다
	printf("%s\n", remain);
	line = temp;
	printf("%s\n", line);
	return (line);		// 처음 만나는 개행까지(개행포함)반환한다.
}


// line1이 개행까지 끊어서 출력되는데 계속 line1을 가지고 있음
// line1을 초기화하고 다음 개행까지 before next라인에 넣는걸 반복문 안에 넣어서 돌려야 할 것 같다.
// 버퍼사이즈가 1일때도 계속 첫줄(개행전까지)만 가지고 있음

int	main(void)
{
	int		fd;
	char	*gnl;
	int		n;

	n = 1;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		printf("error\n");
	//while (1)
	//{
	//	gnl = get_next_line(fd);
	//	if (gnl == NULL)
	//		break ;
	//	//printf("line%d: %s", n, gnl);
	//	//printf("------------------------Cycle %d DONE------------------------\n", n++);
	//	free(gnl);
	//}
	printf("MAIN LINE%d: %s\n", n++, gnl = get_next_line(fd));
	printf("MAIN LINE%d: %s\n", n++, gnl = get_next_line(fd));
	printf("MAIN LINE%d: %s\n", n++, gnl = get_next_line(fd));
	printf("MAIN LINE%d: %s\n", n++, gnl = get_next_line(fd));
	//gnl = get_next_line(fd);
	//gnl = get_next_line(fd);
	//gnl = get_next_line(fd);
	//gnl = get_next_line(fd);
	
	close(fd);
	return (0);
}
