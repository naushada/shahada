CC = gcc
AR = ar
YACC = bison
LEX = flex
FLAGS =  -g -Wall
AR_FLAGS =  -rc
INC = -I./ -I./inc -I./parser -I./ut/inc
LINK_LIB = 
SHAHADA_BIN = bin/shahada
SHAHADA_LIB = lib/libshahada.a
OBJS        = obj/main.o obj/shahada.o obj/shahada.tab.o obj/shahada.yy.o obj/test.o
GENERAT_SRC = parser/shahada.tab.c parser/shahada.tab.h parser/shahada.yy.c parser/shahada.yy.h

#/*Make all will be used to build everything- lib, bin.*/
all: build parser/shahada.yy.c parser/shahada.tab.c $(SHAHADA_BIN) $(SHAHADA_LIB)

#/*make lib - will be used to build the static library.*/
lib: build parser/shahada.yy.c parser/shahada.tab.c $(SHAHADA_LIB)

#/*make bin will be used to build executable.*/
bin: build parser/shahada.yy.c parser/shahada.tab.c $(SHAHADA_BIN)

.PHONY: all lib bin

# /* Creates the directory if don't exists */
build:
	@mkdir -p parser
	@mkdir -p obj
	@mkdir -p bin
	@mkdir -p lib

parser/shahada.yy.c: grammar/shahada.l
	$(LEX) --debug $^

parser/shahada.tab.c: grammar/shahada.y
	$(YACC) --debug --verbose -d -b shahada $^ -o $@

# /*Creating static library i.e. libshahada.a */
$(SHAHADA_LIB): $(OBJS)
	$(AR) $(AR_FLAGS) -o $@  $^  $(LINK_LIB)

$(SHAHADA_BIN): $(OBJS)
	$(CC) $(FLAGS) -o $@  $^  $(LINK_LIB)

# /* Creating Object files in obj directory from source files */

obj/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

obj/%.o: ut/src/%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

# /* Creating Object files from source files kept in parser directory. */

obj/%.o: parser/%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

obj/test.o        :	ut/inc/test.h
obj/main.o        : inc/shahada.h ut/inc/test.h
obj/shahada.o     : inc/shahada.h parser/shahada.tab.h parser/shahada.yy.h
obj/shahada.tab.o : parser/shahada.tab.c parser/shahada.tab.h
obj/shahada.yy.o  : parser/shahada.yy.c parser/shahada.yy.h

.PHONY: clean

clean:
	rm -f $(SHAHADA_BIN) $(OBJS) $(GENERAT_SRC) $(SHAHADA_LIB)
	@rm -fr parser
	@rm -fr obj
	@rm -fr bin
	@rm -fr lib
