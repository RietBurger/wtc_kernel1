#include "libfts.h"

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		if (strcmp(av[1], "isalnum") == 0)
		{
			char str[] = "a45*-Z&";
			for (int i = 0; i < 7; i++)
			{
				int out = ft_isalnum(str[i]);
				printf("character: %c, result:  %d\n", str[i], out);
			}
		}
		else if (strcmp(av[1], "bzero") == 0)
		{
			char str[] = "Hello you, what is the result";
			int c[] = {3, 4, 6, 7, 1, 9};
			ft_bzero(c, 6);
			for (int i = 0; i < 6; i++)
			{
				printf("%d\n", c[i]);
			}
			ft_bzero(str, 6);
			for (int j = 0; j < 20; j++)
			{
				printf("%c\n", str[j]);
			}
		}
		else if (strcmp(av[1], "isalpha") == 0)
		{
			char str[] = "Az 345@#$ aZasdfGHJK";
			for (int i = 0; i < 20; i++)
			{
				int out = ft_isalpha(str[i]);
				printf("char: %c, result: %d \n", str[i], out);
			}
		}
		else if (strcmp(av[1], "isascii") == 0)
		{
			char str[] = {128, 127, 0, -1, 97, 123, 36};
			for (int i = 0; i < 7; i++)
			{
				int out = ft_isascii(str[i]);
				printf("char: %c, result: %d \n", str[i], out);
			}
		}
		else if (strcmp(av[1], "isdigit") == 0)
		{
			char str[] = "Az 345@#$ aZ97dfGH01";
			for (int i = 0; i < 20; i++)
			{
				int out = ft_isdigit(str[i]);
				printf("char: %c, result: %d \n", str[i], out);
			}
		}
		else if (strcmp(av[1], "isprint") == 0)
		{
				char str[] = "Az 345@#$ aZsGH~±§)+";
			for (int i = 0; i < 20; i++)
			{
				int out = ft_isprint(str[i]);
				printf("char: %c, result: %d \n", str[i], out);
			}
		}
		else if (strcmp(av[1], "memcpy") == 0)
		{
			const char src[50] = "this is my src string";
			char dest[50];
			strcpy(dest, "destination");
			printf("before memcpy dest = %s\n", dest);
			ft_memcpy(dest, src, strlen(src)+1);
			printf("after memcpy dest = %s\n", dest);

		}
		else if (strcmp(av[1], "memset") == 0)
		{
			char str[] = "my string is now like this";
			printf("str before memset: %s\n", str);
			ft_memset(str, '@', 12);
			for (int i = 0; i < 27; i++)
			{
				write(1, &str[i], 1);
			}
		}
		else if (strcmp(av[1], "puts") == 0)
		{
			ft_puts("hello world");
		}
		else if (strcmp(av[1], "strcat") == 0)
		{
			char str[] = "this is src";
			char str2[] = " this is dest";
			printf("concatonated: %s\n", ft_strcat(str, str2));
		}
		else if (strcmp(av[1], "strdup") == 0)
		{
			char *p1 = "This is me";
			char *p2;

			p2 = ft_strdup(p1);
			printf("dup string: %s\n", p2);
		}
		else if (strcmp(av[1], "strlen") == 0)
		{
			char str[] = "this is my test string";
			int ret = ft_strlen(str);
			printf("strlen is: %d\n", ret);
		}
		else if (strcmp(av[1], "tolower") == 0)
		{
			char str[] = "this IS aNoThEr TEST";
			for (int i = 0; i < 21; i++)
			{
				char c = ft_tolower(str[i]);
				printf("str char: %c, lowered char: %c\n", str[i], c);
			}
		}
		else if (strcmp(av[1], "toupper") == 0)
		{
			char str[] = "this IS aNoThEr TEST";
			for (int i = 0; i < 21; i++)
			{
				char c = ft_toupper(str[i]);
				printf("str char: %c, uppered char: %c\n", str[i], c);
			}
		}
		else if (strcmp(av[1], "cat") == 0)
		{
			ft_cat(0);
		}
	}
	else
	{
		puts("Please enter a function name");
		return (0);
	}
	return (0);
}
