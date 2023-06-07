CC := g++ 
STDNAME_ASS 	    := Examples/AssembleTxtFile
STDNAME_DUNGEON_CPU := Examples/TestCPU

CFLAGS  :=  -Wall -g -Wextra -Wpedantic -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
		#-save-temps 
#clean: 
	#@rm -rf ./Examples
	 
SRCDIR_ASS := Asm/src ATC/Log ATC/Buffer ATC/Additional 
SRC_ASS    := $(wildcard $(addsuffix /*.cpp, $(SRCDIR_ASS)) )

 
SRCDIR_DUNGEON_CPU := SoftCPU/src ATC/SuperStack  ATC/Log ATC/Buffer ATC/Additional 
SRC_DUNGEON_CPU    := $(wildcard $(addsuffix /*.cpp, $(SRCDIR_DUNGEON_CPU)) )

DUNGEON_OBG_DIR :=   SoftCPU/build
DUNGEON_CPU_ODJ    := $(patsubst %.cpp, $(DUNGEON_OBG_DIR)/%.o, $(notdir $(SRC_DUNGEON_CPU)) )



INCDIR_ASS   := Asm/headers  Arch ATC/Log ATC/Buffer ATC/Additional SoftCPU/headers  Arch ATC/SuperStack ./
INCLUDES_ASS := $(addprefix -I, $(INCDIR_ASS)) 

OBJDIR_ASS := Asm/build
OBJ_ASS    := $(patsubst %.cpp, $(OBJDIR_ASS)/%.o, $(notdir $(SRC_ASS)) )

ARGV_ASS   := ../TEST/test0



VPATH  := $(SRCDIR_ASS) $(SRCDIR_DUNGEON_CPU)

print:
	#@echo $(SRC_ASS) \ $(SRCDIR_ASS) \ $(INCLUDES_ASS)
	@echo  $(DUNGEON_OBG_DIR) \ $(DUNGEON_CPU_ODJ)

run: run_ASS run_DUNGEON_CPU
	

$(STDNAME_ASS): $(OBJ_ASS)
	@$(CC) $(OBJ_ASS) -o $@

./$(OBJDIR_ASS)/%.o: %.cpp
	@$(CC) -c $(INCLUDES_ASS) $(CFLAGS) $< -o $@

run_ASS: clean_ASS $(STDNAME_ASS)
	@./$(STDNAME_ASS) $(ARGV_ASS)

clean_ASS:
	@rm -rf $(OBJ_ASS) $(STDNAME_ASS)



ARGV_DUNGEON_CPU   := ../TEST/test0.ars 


$(STDNAME_DUNGEON_CPU): $(DUNGEON_CPU_ODJ)
	@$(CC) $(DUNGEON_CPU_ODJ) -lm -o $@

./$(DUNGEON_OBG_DIR)/%.o: %.cpp
	@$(CC) -c $(INCLUDES_ASS) $(CFLAGS) $< -o $@ 

run_DUNGEON_CPU: clean_DUNGEON_CPU $(STDNAME_DUNGEON_CPU)
	@./$(STDNAME_DUNGEON_CPU) $(ARGV_DUNGEON_CPU)

clean_DUNGEON_CPU:
	@rm -f $(DUNGEON_CPU_ODJ) $(STDNAME_DUNGEON_CPU)
