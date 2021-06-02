CC=g++
CFLAGS=-Wall

TARGET=uniq-window
INSTALL_LOCATION=/usr/bin/uniq-window

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)

install:
	install $(TARGET) $(INSTALL_LOCATION)

uninstall:
	$(RM) $(INSTALL_LOCATION)
