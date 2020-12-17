
WAL = -g -Wall

ALL:tcp_server tcp_client

tcp_server:tcp_server.cpp TcpSocket.cpp
	g++ -std=c++11 $^ -o $@ $(WAL)

tcp_client:tcp_client.cpp TcpSocket.cpp
	g++ -std=c++11 $^ -o $@ $(WAL)

.PHONY:
clean:
	-rm -rf tcp_client tcp_server
