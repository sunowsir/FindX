CC 		= g++ 
CFLAGS 	= -g -Wall -I ../include/
VPATH 	= ../src/:../include/
RELY 	= \
		CodingSystem.o \
		BinaryTrie.o \
		FindXmain.o

FindX : ${RELY}
	@echo "[CC] [Link] FindX"
	@${CC} ${CFLAGS} ${RELY} -o FindX 

CodingSystem.o : CodingSystem.cpp CodingSystem.h
	@echo "[CC] [Build] CodingSystem.o"
	@${CC} -c ${CFLAGS} $< 

BinaryTrie.o : BinaryTrie.cpp BinaryTrie.h
	@echo "[CC] [Build] BinaryTrie.o"
	@${CC} -c ${CFLAGS} $<

FindXmain.o : FindXmain.cpp BinaryTrie.h 
	@echo "[CC] [Build] FindXmain.o"
	@${CC} -c ${CFLAGS} $<

.PHONY : clean install uninstall  
	
install : 
	@echo "[Install] install FindX to system"
	@sudo cp ./FindX /usr/bin

uninstall : 
	@echo "[Uninstall] Uninstall FindX from system"
	@sudo rm -rf /usr/bin/FindX

clean : 
	@echo "[Clean] clean up build files."
	@rm -rf ${RELY} FindX
