OBJ := rdk.o clazz/Object.o
LD := ld
LD_FLAGS_RELEASE := -s
LD_FLAGS_DEBUG :=
GPP := g++
GPP_FLAGS_RELEASE := -std=c++11 -I "../../RNI/"
GPP_FLAGS_DEBUG := -std=c++11 -I "../../RNI/"
ifeq ($(OS),Windows_NT)
	SHARED_GEN := -shared
	OUTPUT := RdkNative.dll
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
		SHARED_GEN := -shared
		OUTPUT := libRdkNative.so
    endif
    ifeq ($(UNAME_S),Darwin)
		SHARED_GEN := -dynamiclib
		OUTPUT := libRdkNative.dylib
    endif
endif
CONFIGER := ../configer/configer

%.o : %.cpp
	$(GPP) $(GPP_FLAGS_DEBUG) -c -fPIC -o $@ $^

$(OUTPUT): $(OBJ)
	$(GPP) $(GPP_FLAGS_DEBUG) -fPIC $(SHARED_GEN) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJ)