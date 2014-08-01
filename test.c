int main()
{
	char *video = 0xB8000;

	char msg[] = "Hello Kernel in C, Hey man";
	int i, j;

	for (i = 0, j = 0; msg[i]; ++i, j += 2) {
		video[j] = msg[i];
	}

	return 0;
}