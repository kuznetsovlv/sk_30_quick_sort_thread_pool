#Makefile
objects = main.o ThreadPool.o RequestHandler.o InterruptableThread.o InterruptNotificator.o quicksort.o array.o TaskMonitor.o
standard = c++20

.PHONY: all clean

all: qsort

qsort: ${objects}
	gcc -o qsort ${objects} -lstdc++

main.o: main.cpp array.h quicksort.h
	gcc -o main.o main.cpp -c -std=${standard}
ThreadPool.o: ThreadPool.cpp ThreadPool.h BlockedQueue.h BlockedQueue.cpp InterruptableThread.h InterruptNotificator.h
	gcc -o ThreadPool.o ThreadPool.cpp -c -std=${standard}
RequestHandler.o: RequestHandler.cpp RequestHandler.h ThreadPool.h
	gcc -o RequestHandler.o RequestHandler.cpp -c -std=${standard}
InterruptableThread.o: InterruptableThread.cpp InterruptableThread.h ThreadPool.h InterruptNotificator.h
	gcc -o InterruptableThread.o InterruptableThread.cpp -c -std=${standard}
InterruptNotificator.o: InterruptNotificator.cpp InterruptNotificator.h InterruptableThread.h
	gcc -o InterruptNotificator.o InterruptNotificator.cpp -c -std=${standard}
quicksort.o: quicksort.cpp quicksort.h RequestHandler.h TaskMonitor.h
	gcc -o quicksort.o quicksort.cpp -c -std=${standard}
array.o: array.cpp array.h
	gcc -o array.o array.cpp -c -std=${standard}
TaskMonitor.o: TaskMonitor.cpp TaskMonitor.h
	gcc -o TaskMonitor.o TaskMonitor.cpp -c -std=${standard}

clean:
	-rm -f qsort *.o 2>/dev/null