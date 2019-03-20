#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *key, char *text, size_t size);
void decrypt(char *key, char *text, size_t size);

void print_value(char *value, size_t size)
{
	size_t index;

	index = 0;
	while (index < size)
	{
		printf("%02x", (unsigned char)value[index]);
		index += 1;
	}
	printf("\n");
}

void generate_key(char *key)
{
	unsigned int first;
	unsigned int second;
	unsigned int third;
	unsigned int fourth;

	first = rand();
	second = rand();
	third = rand();
	fourth = rand();
	memcpy(key, &first, sizeof(int));
	memcpy(key + 4, &second, sizeof(int));
	memcpy(key + 8, &second, sizeof(int));
	memcpy(key + 12, &second, sizeof(int));
	return ;
}

char *get_value(char *str, size_t *len)
{
	char *rslt;
	size_t old_len;

	*len = strlen(str);
	old_len = *len;
	*len = (*len + 16 - 1) / 16 * 16;
	rslt = malloc(*len);
	if (!rslt)
		return NULL;
	bzero(rslt, *len);
	memcpy(rslt, str, old_len);
	return rslt;
}


int main(int argc, char **argv)
{
	char	key[16];
	char	*value;
	size_t	len;

	srand(time(NULL));
	if (argc < 2)
	{
		dprintf(2, "Usage: %s [data to encrypt]\n", argv[0]);
		return (1);
	}
	value = get_value(argv[1], &len);
	if (!value)
	{
		dprintf(2, "Malloc error\n");
		return (1);
	}
	generate_key(key);
	printf("Key       : ");
	print_value(key, 16);
	printf("value     : ");
	print_value(value, len);
	encrypt(key, value, len);
	printf("encrypted : ");
	print_value(value, len);
	decrypt(key, value, len);
	printf("decrypted : ");
	print_value(value, len);
	free(value);
	return (0);
}
