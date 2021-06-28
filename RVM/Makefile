OBJ := main.o reader/reader.o executer/class.o executer/value.o executer/instruction.o \
	executer/executer.o utils/bytehelper.o utils/stringhelper.o utils/rni_util.o
GPP := g++
GPP_FLAGS_RELEASE := -s
GPP_FLAGS := -std=c++11 -I "../RNI/"
GPP_LIBS :=
ifneq ($(OS),Windows_NT)
	GPP_LIBS += -ldl
endif
OUTPUT := rain
CONFIGER := ../configer/configer

%.o : %.cpp
	$(CONFIGER) -f ../configer/configer.config -e debug true $(GPP) $(GPP_FLAGS) -c -o $@ $^ $(GPP_LIBS) $$ $(GPP) $(GPP_FLAGS) $(GPP_FLAGS_RELEASE) -c -o $@ $^ $$

$(OUTPUT): $(OBJ)
	$(CONFIGER) -f ../configer/configer.config -e debug true $(GPP) $(GPP_FLAGS) -o $@ $^ $(GPP_LIBS) $$ $(GPP) $(GPP_FLAGS) $(GPP_FLAGS_RELEASE) -o $@ $^ $$

.PHONY: clean
clean:
	$(RM) $(OBJ)