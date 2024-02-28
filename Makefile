make:
	gcc -o s-talk list.o main.c recieverThread.c inputThread.c printerThread.c pthread_helpers.c senderThread.c -lpthread
help:
	echo "Run make to builds"
clean:
	rm s-talk