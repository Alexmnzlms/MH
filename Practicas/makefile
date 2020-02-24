.SUFFIXES:
.PHONY: x

OBJ 				 := obj/
SRC				 := src/
INC    			 := include/
exe             := bin/cc_exe
units_cc        := $(wildcard $(addprefix $(SRC), *.cpp))
units_o         := $(addprefix $(OBJ), $(addsuffix .o, $(notdir $(basename $(units_cc)))))
headers         := $(wildcard $(addprefix $(INC), *.h*))
compiler        := g++
cc_flags        := -std=c++11 -g -I/usr/include -I$(INC) -DLINUX


x: $(exe)
	@echo Enlazando para: $(sistoper)
	$(exe)

$(exe): $(units_o) makefile
	$(compiler) -o $(exe) $(units_o)

$(OBJ)%.o : $(SRC)%.cc
	$(compiler) -o $@ -c $(cc_flags) $<

$(OBJ)%.o : $(SRC)%.ccp
	$(compiler) -o $@ -c $(cc_flags)

$(units_cc) : $(headers)
	touch $(units_cc)

clean:
	rm -rf obj/*.o bin/*_exe

muestra:
	@echo $(wildcard $(addprefix $(SRC), *.cpp))
	@echo $(addprefix $(OBJ), $(addsuffix .o, $(notdir $(basename $(units_cc)))))
	@echo $(wildcard $(addprefix $(INC), *.h*))
