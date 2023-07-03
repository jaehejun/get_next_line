#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
	size_t	len;
	int		i;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);
	while (len-- > 0)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len1;
	size_t	len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (len1-- > 0)
		join[i++] = *s1++;
	while (len2-- > 0)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}

int	main(void)
{
	//char str[1];
	//str[0] = '\0';
    
    //char *duplicate1 = strdup(str);
    //char *duplicate2 = ft_strdup(str);
    
    //int result = strcmp(duplicate1, duplicate2);
    
    //if (result == 0) {
    //    printf("The duplicated strings are the same.\n");
    //} else {
    //    printf("The duplicated strings are different.\n");
    //}
    //printf("%c\n", duplicate1[0]);
	//printf("%c\n", duplicate2[0]);
    //free(duplicate1);
    //free(duplicate2);

	//printf("%p\n", "");
	//int i = strlen("");
	//int j = ft_strlen("");
	//printf("ORI LEN : %d\n", i);
	//printf("MY LEN : %d\n", j);
	//int ori = strlen(strdup(""));
	//int my = ft_strlen(ft_strdup(""));
	//printf("ORI STRDUP : %d\n", ori);
	//printf("MY STRDUP : %d\n", my);

	char *str = "Hello World";
	char *str2 = "012345";
	char *dup;

	dup = strdup("");
	dup = ft_strjoin(dup, str);
	free (dup);
	printf("%p\n", dup);
	dup = ft_strjoin(dup, str2);
	free (dup);
	printf("%p\n", dup);

}

			char *temp = remain;
			remain = ft_strjoin(remain, buffer);
			free (temp);

int main(void)
{
    char *str = "Hello World";
    char *str2 = "012345";
    char *dup;

    dup = strdup("");
    char *temp = ft_strjoin(dup, str);
    free(dup);
    dup = temp;
    printf("%p\n", dup);

    temp = ft_strjoin(dup, str2);
    free(dup);
    dup = temp;
    printf("%p\n", dup);

    free(dup);

    return 0;
}

Invalid fd          : 1.OK 2.OK 3.OK 4_LEAKS.KO
empty.txt           : 1.KO Abort
1char.txt           : 1.KO Abort
one_line_no_nl.txt  : 1.KO Abort
only_nl.txt         : 1.KO Abort
multiple_nl.txt     : 1.OK 2.OK 3.KO Abort
variable_nls.txt    : 1.OK 2.KO 3.KO 4.OK 5.KO 6.OK 7.KO Abort
lines_around_10.txt : 1.OK 2.OK 3.OK 4.OK 5.OK 6.KO Abort
giant_line.txt      : 1.KO Abort
giant_line_nl.txt   : 1.OK 2.KO Abort
read_error.txt      : 1.OK 2.OK 3.KO Abort
stdin               : 1.OK 2.OK 3.OK 4.OK 5.OK 6.KO Abort