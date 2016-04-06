All:tcp_server tcp_client
.PHONY:All

tcp_server:tcp_server.c
	gcc -o $@ $^ -D_FUN2_
tcp_client:tcp_client.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf tcp_server tcp_client


