OBJ := main.o reader/reader.o executer/class.o executer/value.o executer/instruction.o utils/bytehelper.o utils/tostringhelper.o
LD := ld
LD_FLAGS_RELEASE := -s
LD_FLAGS_DEBUG :=
GPP := g++
GPP_FLAGS_RELEASE := -std=c++11
GPP_FLAGS_DEBUG := -std=c++11
OUTPUT := rain
CONFIGER := ../configer/configer

%.o : %.cpp
	$(CONFIGER) -f ../configer/configer.config -e debug true $(GPP) $(GPP_FLAGS_DEBUG) -c -o $@ $^ $$ $(GPP) $(GPP_FLAGS_RELEASE) -c -o $@ $^ $$

$(OUTPUT): $(OBJ)
	$(CONFIGER) -f ../configer/configer.config -e debug true $(GPP) $(GPP_FLAGS_DEBUG) -o $@ $^ $$ $(GPP) $(GPP_FLAGS_RELEASE) -o $@ $^ $$

.PHONY: clean
clean:
	$(RM) $(OBJ)