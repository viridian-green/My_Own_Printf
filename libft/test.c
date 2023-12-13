void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	p_dest = (char *)dest;
	p_src = (char *)src;
	i = 0;
	if (p_dest < p_src)
	{
		while (i++ < n)
			p_dest[i] = p_src[i];
	}
	else
	{
		while (n-- > 0)
		{
			p_dest[n] = p_src[n];
		}
	}
	return (dest);
}
