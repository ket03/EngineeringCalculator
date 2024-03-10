.PHONY: all install uninstall dist test clean
CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17

all: test clean

test: clean
	$(CC) $(CFLAGS) calc/Model/test.cc calc/Model/model.cc -o test -lgtest
	./test

install: uninstall
	make clean
	mkdir build
	cd calc && qmake && make && make clean && rm Makefile && cd ../ && mv calc/calc.app build

uninstall:
	rm -rf build*

dvi:
	open README.md

dist: install
	rm -rf Dist_SmartCalc/
	mkdir Dist_SmartCalc/
	mkdir Dist_SmartCalc/src
	mv ./build/calc.app Dist_SmartCalc/src/
	tar cvzf Dist_SmartCalc.tgz Dist_SmartCalc/
	rm -rf Dist_SmartCalc/
	rmdir build

clean:
	rm -rf test
	cd calc && rm -rf *.a && rm -rf *.o  && rm -rf *.dSYM && rm -rf *.out && rm -rf $(EXECUTABLE) && rm -rf gcov_report && rm -rf report && rm -rf CPPLINT.cfg && rm -rf *.gcda 
	cd calc && rm -rf *.gcno && rm -rf *.info && rm -rf test && rm -rf Dist_SmartCalc && rm -rf *tgz && rm -rf build && rm -rf SC_test && rm -rf gcov_test && rm -rf .qmake.stash
