#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*str_dup;
	int		len;
	int		i;

	len = ft_strlen(s1);
	if (!(str_dup = (char *)malloc(sizeof(char) * len + 1)))
	{
		free(str_dup);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		str_dup[i] = s1[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}
