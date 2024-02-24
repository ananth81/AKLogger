
OUTPUT_FOLDER:=out
DEPDIR := $(OUTPUT_FOLDER)/.deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
OBJ=$(OUTPUT_FOLDER)/main.o      \
    $(OUTPUT_FOLDER)/loggerApp.o \
    $(OUTPUT_FOLDER)/loggerGUI.o \


all: $(OUTPUT_FOLDER) $(OUTPUT_FOLDER)/AKLogger

$(OUTPUT_FOLDER)/AKLogger:$(OBJ)
	@echo Linking $(OBJ) for $@
	@g++ -o $(OUTPUT_FOLDER)/AKLogger $(OBJ) `pkg-config --libs gtkmm-3.0`

$(OUTPUT_FOLDER)/%.o:%.cpp
	 @echo compiling $<
	@g++ -D_GNU_SOURCE $(DEPFLAGS) -Wall -c `pkg-config --cflags gtkmm-3.0` $< -o $@


.PHONY:clean
clean:
	rm $(OUTPUT_FOLDER)/*


$(OUTPUT_FOLDER):
	@echo Creating Output Directory $@
	mkdir -p $(OUTPUT_FOLDER)
	mkdir -p $(DEPDIR)


include $(wildcard $(DEPDIR)/*.d)

