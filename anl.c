
char	*read_line(int fd, int BUFFER_SIZE);
{
	char	*buffer;
	char	*temp;
	int		count;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	count = 1;
	while (count > 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			return (NULL);
		}
		temp = ft_strjoin(line, buffer);
		free(line);
		line = temp;
		if (ft_strchr(line, '\n'))
			break;
	} 
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*remain;
	char		*temp;
	static char	*line;
	int			count;
	int			w = 1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (line == 0)
		line = ft_strdup("");
	if(line == NULL)
		return (NULL);
	line = read_line(fd, BUFFER_SIZE);

}