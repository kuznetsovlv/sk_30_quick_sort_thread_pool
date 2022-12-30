#Makefile
objects = main.o ThreadPool.o RequestHandler.o InterruptableThread.o InterruptNotificator.o
standard = c++20

.PHONY: all clean

all: thread_pool

thread_pool: ${objects}
	gcc -o thread_pool ${objects} -lstdc++

main.o: main.cpp RequestHandler.h InterruptableThread.h ThreadPool.h
	gcc -o main.o main.cpp -c -std=${standard}
ThreadPool.o: ThreadPool.cpp ThreadPool.h BlockedQueue.h BlockedQueue.cpp InterruptableThread.h InterruptNotificator.h
	gcc -o ThreadPool.o ThreadPool.cpp -c -std=${standard}
RequestHandler.o: RequestHandler.cpp RequestHandler.h ThreadPool.h
	gcc -o RequestHandler.o RequestHandler.cpp -c -std=${standard}
InterruptableThread.o: InterruptableThread.cpp InterruptableThread.h ThreadPool.h InterruptNotificator.h
	gcc -o InterruptableThread.o InterruptableThread.cpp -c -std=${standard}
InterruptNotificator.o: InterruptNotificator.cpp InterruptNotificator.h InterruptableThread.h
	gcc -o InterruptNotificator.o InterruptNotificator.cpp -c -std=${standard}

clean:
	-rm -f thread_pool *.o 2>/dev/null