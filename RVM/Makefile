OBJ := main.o reader/reader.o
LD := ld
LD_FLAGS_RELEASE := -s
LD_FLAGS_DEBUG :=
GPP := g++
GPP_FLAGS_RELEASE := -std=c++11
GPP_FLAGS_DEBUG := -std=c++11
OUTPUT := rain
CONFIGER := ../configer/configer

$(OUTPUT): $(OBJ)
	$(GPP) $(GPP_FLAGS_DEBUG) -o $@ $^

%.o : %.c
	$(GPP) $(GPP_FLAGS_DEBUG) -c  -o $@ $^