.SUFFIXES:
.PHONY: x

OBJ				:= obj/
SRC				:= src/
INC				:= include/
exe            := bin/clustering_exe
units_CCP      := $(wildcard $(addprefix $(SRC), *.cpp))
units_o        := $(addprefix $(OBJ), $(addsuffix .o, $(notdir $(basename $(units_CCP)))))
headers        := $(wildcard $(addprefix $(INC), *.h*))
compiler       := g++ -g
CCP_flags      := -std=c++11 -Wall -O3 -I/usr/include -I$(INC)

# compiler       := g++ -g
# CCP_flags      := -std=c++11 -Wall -O3 -I/usr/include -I$(INC)


x: $(exe)

$(exe): $(units_o) makefile
	$(compiler) -o $(exe) $(units_o)

$(OBJ)%.o : $(SRC)%.cpp
	$(compiler) -o $@ -c $(CCP_flags) $<

$(units_CCP) : $(headers)
	touch $(units_CCP)

clean:
	rm -rf obj/*.o bin/*_exe
