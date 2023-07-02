#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

//int	main(void)
//{
//	int	fd1;
//	int	fd2;

//	fd1 = open("emp.txt", O_RDONLY);
//	fd2 = open("empty.txt", O_RDONLY);
//	printf("%d\n", fd1);
//	printf("%d\n", fd2);
//}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	memsize;
	int		i;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	memsize = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * (memsize + 1));
	if (copy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	main(void)
{
	char	*str;
	char	*dup;

	str = "";
	dup = ft_strdup(str);
	printf("%s\n", str);
	printf("%s\n", dup);
	free(dup);
	dup = NULL;

}