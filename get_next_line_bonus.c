#include "get_next_line_bonus.h"

static char	*alloc_one(char *str)
{
	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

static char	*ft_strjoin_plus(char *s1, char *s2)
{
	char			*ret;
	unsigned int	i;
	unsigned int	j;
	char			*temp;

	i = -1;
	j = 0;
	temp = NULL;
	if (!s1)
		s1 = alloc_one(s1);
	temp = s1;
	ret = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (s1[++i] != '\0')
		ret[i] = s1[i];
	while (s2[j] != '\0')
		ret[i++] = s2[j++];
	ret[i] = '\0';
	free(temp);
	return (ret);
}

static char	*read_fd(int fd, char *str)
{
	char	*temp;
	int		bytes_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (!is_there_a_line(str) && bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			free(temp);
			free(str);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		str = ft_strjoin_plus(str, temp);
	}
	free(temp);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*scp[FOPEN_MAX];
	char		*line[FOPEN_MAX];

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	scp[fd] = read_fd(fd, scp[fd]);
	if (!scp[fd])
		return (NULL);
	line[fd] = take_line(scp[fd]);
	scp[fd] = free_util(scp[fd]);
	return (line[fd]);
}
