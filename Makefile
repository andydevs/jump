TARGET = jump

SHELL = /bin/bash -O globstar
CC    = g++

FLAGS = -Wall -std=c++14

INCDIR = include
LIBDIR = lib
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INSDIR = /usr/bin

INCLUDS = $(shell ls $(INCDIR)/**/*.h)
SOURCES = $(shell ls $(SRCDIR)/**/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
BINARY  = $(BINDIR)/$(TARGET)

$(BINARY): $(OBJECTS)
	@echo building $@
	@test -d $(@D) || mkdir -p $(@D)
	@$(CC) $^ -o $@ $(FLAGS) -L $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDS)
	@echo compiling $<
	@test -d $(@D) || mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(FLAGS) -I $(INCDIR)

clean:
	@echo Cleaning up...
	@rm -f -r $(OBJDIR) $(BINDIR)
	@rm -f $(TARGET).exe.stackdump

install: $(BINARY)
	@echo Installing...
	@cp $(BINARY) $(INSDIR)
	@echo Installed!

uninstall:
	@echo Uninstalling...
	@rm $(INSDIR)/$(TARGET)
	@echo Uninstalled!

run: $(BINARY)
	@echo Running...
	@echo -----------------------------------------
	@$(BINARY)
	@echo -----------------------------------------