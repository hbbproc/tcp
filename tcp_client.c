#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define _REMOTE_PORT_ 8080

static void usage(const char* proc)
{
    printf("usage:[IP] %s\n",proc);
}

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        usage(argv[0]);
        exit(1);
    }
    const char* ip = argv[1];

    int sock = socket(AF_INET/*ipv4*/,SOCK_STREAM,0);
    if(sock == -1)
    {
        printf("%d:%s\n",errno,strerror(errno));
        exit(1);
    }

    unsigned short port = _REMOTE_PORT_;
    struct sockaddr_in remote;
    remote.sin_family = AF_INET;//ipv4
    remote.sin_port = htons(port);
    inet_aton(ip,&remote.sin_addr);

    int ret = connect(sock,(struct sockaddr*)&remote,sizeof(remote));
    if(ret<0)
    {
        perror("connect");
        exit(1);
    }
    printf("connect success\n");
    char buf[1024];
    while(1)
    {
        memset(buf,'\0',sizeof(buf));
        printf("please input:");
        gets(buf);
        ssize_t _size = write(sock,buf,sizeof(buf)-1);
        if(_size < 0)
        {
            perror("write");
            break;
        }
        memset(buf,'\0',sizeof(buf));
        size_t ret = read(sock,buf,sizeof(buf) - 1);
        if(ret < 0)
        {
            perror("read");
            break;
        }
        buf[ret] = '\0';
    }
    close(sock);
    return 0;
}
