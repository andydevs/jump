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
	@test -d $(BINDIR) || mkdir $(BINDIR)
	@test -d $(@D) || mkdir $(@D)
	@echo building $@
	@$(LINK) $^ -o $@ $(LFLAGS) $(LIBRAR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDS)
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@test -d $(@D) || mkdir $(@D)
	@echo compiling $<
	@$(COMPILE) $< -o $@ $(CPPFLAGS) $(INCLUD)

clean:
	@echo Cleaning up...
	@test -d $(OBJDIR) && rm -r $(OBJDIR)
	@test -d $(BINDIR) && rm -r $(BINDIR)
	@test $(TARGET).exe.stackdump && rm $(TARGET).exe.stackdump

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