CC = gcc
YACC = bison
LEX = flex
BIN = bin/shahada
FLAGS =  -g -Wall
INC = -I./ -I./inc -I./parser
LINK_LIB = 
OBJS        = obj/main.o obj/shahada.o obj/shahada.tab.o obj/shahada.yy.o obj/test.o
GENERAT_SRC = parser/shahada.tab.c parser/shahada.tab.h parser/shahada.yy.c parser/shahada.yy.h


all: build parser/shahada.yy.c parser/shahada.tab.c $(BIN)
.PHONY: all

# /* Creates the directory if don't exists */
build:
	@mkdir -p parser
	@mkdir -p obj
	@mkdir -p bin

parser/shahada.yy.c: grammar/shahada.l
	$(LEX) --debug $^

parser/shahada.tab.c: grammar/shahada.y
	$(YACC) --debug --verbose -d -b shahada $^ -o $@

# /*Creating Shared library i.e. libjson.so */
$(BIN): $(OBJS)
	$(CC) $(FLAGS) -o $@  $^  $(LINK_LIB)

# /* Creating Object files in obj directory from source files */

obj/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

# /* Creating Object files from source files kept in parser directory. */

obj/%.o: parser/%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

obj/test.o        :	inc/test.h
obj/main.o        : inc/shahada.h inc/test.h
obj/shahada.o        : inc/shahada.h parser/shahada.tab.h parser/shahada.yy.h
obj/http_parser.tab.o  : parser/shahada.tab.c parser/shahada.tab.h
obj/http_parser.yy.o      : parser/shahada.yy.c parser/shahada.yy.h

.PHONY: clean
clean:
	rm -f $(BIN) $(OBJS) $(GENERAT_SRC)
	@rm -fr parser
	@rm -fr obj
	@rm -fr bin	
