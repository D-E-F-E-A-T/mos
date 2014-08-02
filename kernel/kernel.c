
int puts(char *s)
{
	char *video = 0xB8000;

	int i, j;

	for (i = 0, j = 0; s[i]; i++, j += 2)
		video[j] = s[i];
}

int main()
{
	char msg[] = "message built from Ubuntu VM!!!!";

	puts(msg);
	
	return 0;
}

