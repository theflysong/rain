C_OBJ := main.o
LD := ld
LD_FLAGS:= -s
GPP := g++
GPP_FLAGS := -std=c++14
OUTPUT := configer

$(OUTPUT): $(C_OBJ)
	$(GPP) $(GPP_FLAGS) -o $@ $^

%.o : %.c
	$(GPP) -c $(GPP_FLAGS) -o $@ $^