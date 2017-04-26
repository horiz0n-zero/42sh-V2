
#include "shell.h"

static size_t		base_count(int nb, const int base)
{
	size_t 			count;

	count = 1;
	if (nb == 0)
		count++;
	if (nb < 0)
		nb = -nb;
	while (nb)
	{
		nb /= base;
		count++;
	}
	return (count);
}

int 				ft_atoi(const char *str)
{
	int 			result;

	if (!str)
		return (0);
	result = 0;
	while (*str >= '0' && *str <= '9')
		result += result * 10 + ((int)(*str++ - '0') & 0xFF);
	return (result);
}

char				*ft_itoa_base(int nb, const int base)
{
	char 			*new;
	char 			*ptr;
	int 			save;

	new = malloc(sizeof(char) * base_count(nb, base));
	if (!new)
		return (NULL);
	ptr = new;
	if (nb == 0)
		*ptr++ = '0';
	if (nb < 0)
		nb = -nb;
	save = nb;
	while (save)
		(ptr++) && (save /= base);
	*ptr = 0;
	while (nb)
	{
		*--ptr = nb % base + '0';
		nb /= base;
	}
	return (new);
}
