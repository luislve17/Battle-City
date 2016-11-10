int dig(int n)
{
	int i;
	int r = 1;
	for(i = 0; i < n; i++)
	{
		r *= 10;
	}
	return r;
}
int strToInt(char * s)
{
	int i = 0;
	int k = 0;
	int r = 0;
	while(s[i] != 10)
	{
		i++;
	}
	for(i = i - 1; i >= 0; i--)
	{
		r += (s[i] - 48) * dig(k);
		k++;
	}
	return r;
}

