CC=g++
mounter: main.o dialog.o mounter.o
	$(CC) main.o dialog.o mounter.o -lncurses -o ../mounter
main.o: main.cpp dialog.h mounter.cpp
	$(CC) -c main.cpp -lncurses
mounter.o: mounter.cpp mounter.h dialog.cpp
	$(CC) -c mounter.cpp -lncurses
dialog.o: dialog.cpp dialog.h
	$(CC) -c dialog.cpp -lncurses
clean:
	rm main.o mounter.o dialog.o
