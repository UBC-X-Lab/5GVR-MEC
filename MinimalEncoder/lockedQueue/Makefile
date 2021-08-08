CC = gcc
LDFLAGS := 
CFLAGS := -I$(HOME)/Augmented-x264/MinimalEncoder/lockedQueue

QueueTest: testforqueue.c locked_queue.c
	$(CC)  testforqueue.c locked_queue.c $(CFLAGS) -o QueueTest -lpthread
