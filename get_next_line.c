#include "get_next_line.h"

size_t ft_strichr(char *mem)
{
	size_t i;

	i = 0;
	while (mem[i] && mem[i] != '\n')
		i++;
	return (i);
}

char *find_line(char **buffer, char *read_result, int fd)
{
	int read_bytes;
	char *mem;

	mem = NULL;
	while (!(ft_strchr(read_result, '\n')))
	{
		read_bytes = read(fd, read_result, BUFFER_SIZE);
		if (read_bytes == 0)
		{
			if (!mem)
			{
				free(*buffer);
				return (NULL);
			}
			return (mem);
		}
		if (read_bytes == -1)
			return (NULL);
		read_result[read_bytes] = '\0';
		free(mem);
		mem = ft_strjoin(*buffer, read_result);
		free(*buffer);
		*buffer = ft_strdup(mem);
	}
	free(*buffer);
	*buffer = ft_substr(mem, ft_strichr(mem) + 1, ft_strlen(mem) - ft_strichr(mem));
	return (mem);
}

char	*get_next_line(int fd)
{
	static char *buffer;
	char *read_result;
	char *line;
	int i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	if (!buffer)
		buffer = NULL;
	read_result = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (i < BUFFER_SIZE)
	{
		read_result[i] = 'a';
		i++;
	}
	read_result[i] = '\0';
	if (!read_result)
		return (0);
	line = find_line(&buffer, read_result, fd);
	free(read_result);
	return (line);
}
