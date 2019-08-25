CC        = gcc
AR        = ar
FLAGS     = -g -Wall
AR_FLAGS  = rvs
INC       = -I. -Iinc
LINK_LIB  = 
LOG_LIB   = lib/liblog.a
OBJS      = obj/llog.o

#/*make lib - will be used to build the static library.*/
lib : build $(LOG_LIB)
all : lib

.PHONY: all lib

# /* Creates the directory if don't exists */
build:
	@mkdir -p obj
	@mkdir -p lib

# /*Creating static library i.e. libshahada.a */
$(LOG_LIB): $(OBJS)
	$(AR) $(AR_FLAGS) $@ $^ $(LINK_LIB)

# /* Creating Object files in obj directory from source files */

obj/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

# /* Creating Object files from source files kept in parser directory. */

obj/llog.o         : inc/llog.h

.PHONY: clean

clean:
	rm -f $(OBJS) $(LOG_LIB)
	@rm -fr obj
	@rm -fr lib
