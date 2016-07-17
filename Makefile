TARGET = jump

SHELL = /bin/bash -O globstar
CC    = g++

COMPILE = $(CC) -c
LINK    = $(CC)

CFLAGS = -Wall -std=c++14
LFLAGS = -Wall
INCLUD = -Iinclude
LIBRAR = -Llib

INCDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INSDIR = /usr/bin

INCLUDS = $(shell ls $(INCDIR)/**/*.h)
SOURCES = $(shell ls $(SRCDIR)/**/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
BINARY  = $(BINDIR)/$(TARGET)

$(BINARY): $(OBJECTS)
	@test -d $(@D) || mkdir -p $(@D)
	@echo building $@
	@$(LINK) $^ -o $@ $(LFLAGS) $(LIBRAR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDS)
	@test -d $(@D) || mkdir -p $(@D)
	@echo compiling $<
	@$(COMPILE) $< -o $@ $(CPPFLAGS) $(INCLUD)

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