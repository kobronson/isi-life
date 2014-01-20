CFLAGS = -g -O2 -std=gnu99 	
OBJS = life.o

LIBS = -lncurses

TARGET = life

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS) 

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
