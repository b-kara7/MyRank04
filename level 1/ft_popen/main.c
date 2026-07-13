#include <stdio.h>
#include <unistd.h>

int ft_popen(const char *file, char *const argv[], char type);

int main(void)
{
    char buf[1024];
    int n;

    // 'r' (okuma) testi: "ls -l" komutunun çıktısını okuyup ekrana basacağız
    char *const args[] = {"ls", "-l", NULL};
    int fd = ft_popen("ls", args, 'r');
    
    if (fd < 0)
    {
        printf("Hata olustu!\n");
        return 1;
    }

    printf("--- 'ls -l' ciktisi okunuyor ---\n");
    while ((n = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        buf[n] = '\0';
        printf("%s", buf);
    }
    close(fd);

    return 0;
}