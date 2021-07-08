OBJ := main.o
LD := ld
LD_FLAGS_RELEASE := -s
LD_FLAGS_DEBUG :=
GPP := g++
GPP_FLAGS_RELEASE := -std=c++14 -s
GPP_FLAGS_DEBUG := -std=c++14
OUTPUT := rainc
CONFIGER := ../configer/configer

%.o : %.cpp
	$(CONFIGER) -f ../configer/configer.config -e debug true $(GPP) $(GPP_FLAGS_DEBUG) -c -o $@ $^ $$ $(GPP) $(GPP_FLAGS_RELEASE) -c -o $@ $^ $$

%.c.o : %.c
	$(GPP) $(GPP_FLAGS_DEBUG) -c -o $@ $^

$(OUTPUT): $(OBJ)
	$(CONFIGER) -f ../configer/configer.config -e debug true $(GPP) $(GPP_FLAGS_DEBUG) -o $@ $^ $$ $(GPP) $(GPP_FLAGS_RELEASE) -o $@ $^ $$

.PHONY: clean
clean:
	$(RM) $(OBJ)