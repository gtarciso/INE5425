g++ -c -std=c++11 -lm src/statistic.cc src/main.cpp src/tests.cc

g++ -std=c++11 statistic.o main.o tests.o

./a.out < test2.in
