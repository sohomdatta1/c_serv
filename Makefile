CC=gcc
CFLAGS= -c -Wall -lpthread
RM=rm -rf

compile: create_server

#install: create_server
#	cp /usr/bin serv

create_server: common.o work_queue.o c_serv.o server.o thread_group.o request_parser.o
	$(CC) server.o c_serv.o work_queue.o thread_group.o common.o request_parser.o -o serv -lpthread

server.o: server.c c_serv.h
	$(CC) $(CFLAGS) server.c

work_queue.o: work_queue.c common.h
	$(CC) $(CFLAGS) work_queue.c

c_serv.o: c_serv.c common.h
	$(CC) $(CFLAGS) c_serv.c

thread_group.o: thread_group.c common.h work_queue.h
	$(CC) $(CFLAGS) thread_group.c

common.o:
	$(CC) -c -Wall -lpthread common.c

request_parser.o:
	$(CC) $(CFLAGS) request_parser.c 

clean:
	$(RM) *.o
	$(RM) serv
