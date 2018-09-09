all:
	+$(MAKE) -C libs
clean:
	rm libs/*.o
