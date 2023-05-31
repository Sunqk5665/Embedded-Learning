CC=gcc
CFLAGS=-g -c -O
OBJS=merge.o main.o
a.out:$(OBJS)
	$(CC) $(OBJS) -o $@
$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@
.PHONY:clean
clean:
	rm *.o
