.SUFFIXES:
.PHONY: x

OBJ 				 := obj/
SRC				 := src/
INC    			 := include/
exe             := bin/clustering_exe
units_cc        := $(wildcard $(addprefix $(SRC), *.cpp))
units_o         := $(addprefix $(OBJ), $(addsuffix .o, $(notdir $(basename $(units_cc)))))
headers         := $(wildcard $(addprefix $(INC), *.h*))
compiler        := g++
cc_flags        := -std=c++11 -g -I/usr/include -I$(INC)


x: $(exe)
	$(exe)

$(exe): $(units_o) makefile
	$(compiler) -o $(exe) $(units_o)

$(OBJ)%.o : $(SRC)%.cpp
	$(compiler) -o $@ -c $(cc_flags) $<

$(units_cc) : $(headers)
	touch $(units_cc)

clean:
	rm -rf obj/*.o bin/*_exe
