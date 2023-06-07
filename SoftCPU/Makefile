CC := g++ 

STDNAME := SOFT_CPU

CFLAGS  := #-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE -Wall -Wextra -Wpedantic
#-fsanitize=address -lasan  
SRCDIR := src ../ATC_old_/SuperStack  ../ATC_old_/Log ../ATC_old_/Buffer ../ATC_old_/Additional 
SRC    := $(wildcard $(addsuffix /*.cpp, $(SRCDIR)) )

INCDIR   := headers ../ ../Arch ../ATC_old_/SuperStack ../ATC_old_/Log ../ATC_old_/Buffer ../ATC_old_/Additional
INCLUDES := $(addprefix -I, $(INCDIR)) 

OBJDIR := build
OBJ    := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)) )

VPATH  := $(SRCDIR)

ARGV   := ../../Translator/test.ars.ars

print:
	@echo $(SRC) \ $(SRCDIR)

$(STDNAME): $(OBJ)
	@$(CC) $(OBJ) -lm -o $@

$(OBJDIR)/%.o: %.cpp
	@$(CC) -c $(INCLUDES) $(CFLAGS) $< -o $@ 

run: clean $(STDNAME)
	@./$(STDNAME) $(ARGV)

clean:
	@rm -f $(OBJ) $(STDNAME)
