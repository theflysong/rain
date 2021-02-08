C_OBJ := main.o
LD := ld
LD_FLAGS_RELEASE := -s
LD_FLAGS_DEBUG :=
GPP := g++
GPP_FLAGS_RELEASE :=
GPP_FLAGS_DEBUG :=
OUTPUT := rain
CONFIGER := ../configer/configer

$(OUTPUT): $(C_OBJ)
	$(GPP) $(GPP_FLAGS_DEBUG) -o $@ $^

%.o : %.c
	$(GPP) -c $(GPP_FLAGS_DEBUG) -o $@ $^