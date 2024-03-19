.PHONY: install uninstall dist clean
CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17

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
	cd calc && rm -rf *.a && rm -rf *.o  && rm -rf *.dSYM && rm -rf *.out && rm -rf $(EXECUTABLE) && rm -rf CPPLINT.cfg 
	cd calc && rm -rf *.info && rm -rf Dist_SmartCalc && rm -rf *tgz && rm -rf build && rm -rf .qmake.stash
