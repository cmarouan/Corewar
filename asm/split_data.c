#include "asm.h"

static int	words(const char *str, char c)
{
	int flag_quote;
	int index;
	int counter;

	index = 0;
	if (str[index] != c)
		index++;
	counter = index;
	flag_quote = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '"')
			flag_quote = !flag_quote;
		if (!flag_quote && str[index] != c && str[index - 1] == c)
			counter++;
		index++;
	}
	return (counter);
}

static int	ft_count_char(char *str, char c)
{
	int counter;
	int flag_quote;

	counter = 0;
	flag_quote = 0;
	while (str[counter] != '\0')
	{
		if (str[counter] == '"')
			flag_quote = !flag_quote;
		if (!flag_quote && str[counter] == c)
			break ;
		counter++;
	}
	return (counter);
}

char		**split_data(char const *s, char c)
{
	char	**tab;
	int		flag_quote;
	int		j;
	int		size;

	j = 0;
	flag_quote = 0;
	if ((tab = (char **)malloc(sizeof(char *) * (words(s, c) + 1))) == NULL)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			size = ft_count_char((char *)s, c);
			while (*s == c)
				s++;
			if (!(tab[j++] = ft_strsub(s, 0, size)))
				return (NULL);
			s = s + size;
		}
		else
			s++;
	}
	tab[j] = 0;
	return (tab);
}