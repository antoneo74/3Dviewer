CC = gcc 
FLAGS = -Wall -Werror -Wextra -std=c11
VFLAG = --leak-check=full --show-leak-kinds=all -s
SOURCES = ./load_object.c ./transform.c
HEADERS = ./load_object.h ./transform.h
FRONT_DIR = ./3DViewer_1
TESTFILE = ./tests.c
DIST_NAME = 3DViewer_1
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	ADD_LIB = -lcheck -lm -lpthread -lrt -lsubunit -D_GNU_SOURCE
	LEAKS = CK_FORK=no valgrind $(VFLAG)
else
	ADD_LIB = -lcheck
	LEAKS = CK_FORK=no leaks --atExit --
endif

all: load_submodule install 

load_submodule:
	git submodule init
	git submodule update

dvi:
ifeq ($(OS), Darwin)
	@open ./docs/documentation.html
else
	@xdg-open ./docs/documentation.html
endif

dist:
	tar --totals -czvf 3DViewer_1.tar.gz ./*
	mv 3DViewer_1.tar.gz ../

tests:
	checkmk clean_mode=1 tests.check > tests.c 
	$(CC) $(FLAGS) $(SOURCES) -lm $(TESTFILE) $(ADD_LIB) -o tests
	./tests	

gcov_report: tests
	$(CC) $(FLAGS) --coverage ${SOURCES} $(TESTFILE) $(ADD_LIB) -o tests 
	./tests
	lcov -t "tests" -o tests.info -c -d .
	genhtml -o report tests.info
ifeq ($(OS), Darwin)
	@open ./report/index.html
else
	@xdg-open ./report/index.html
endif

check: tests linter cppcheck leaks 

leaks: tests
	$(CC) $(FLAGS) $(SOURCES) -lm $(TESTFILE) $(ADD_LIB) -o tests
	$(LEAKS) ./tests
	
linter:
	cp ../materials/linters/.clang-format .
	clang-format -n $(SOURCES)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction $(SOURCES)

valgrind:
	valgrind --quiet --leak-check=full --leak-resolution=med --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./tests

clean:
	@echo "Cleanup started..."
	rm -rf *.out *.o *.a *.cfg fizz *.gc* *.info report build test RESULT_VALGRIND.txt
	rm -rf ./tests && rm -rf ./tests.c && rm -rf ./report
	rm -rf .clang-format
	rm -rf ../3DViewer_1.tar.gz
	@echo "Done."


###################
# Building QT app #
###################

QT_PROJECT_NAME = 3DViewer_1
QT_PROJECT_FOLDER = ./$(QT_PROJECT_NAME)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = Build
QT_APP_FOLDER = ../App
DIST_FOLDER_NAME = 3DViewer_1

generate_make:
	@qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
	@rm -rf .qmake.stash

install: generate_make
	@echo "Building application..."
	@cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
	@echo "Application builded."
	@echo -n "Moving application to folder \"$(QT_APP_FOLDER)\"..."
	@mkdir ./$(QT_APP_FOLDER)
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME)
	@echo " Done."
	@echo -n "Deleting build folder..."
	@rm -rf $(QT_BUILD_FOLDER)
	@echo " Done."
	@echo "Installation complete!"

uninstall:
	@echo -n "Uninstalling application..."
	@rm -rf $(QT_APP_FOLDER)
	@echo " Done."

