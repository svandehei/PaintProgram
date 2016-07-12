# CSci-3081W Project Support Code Makefile


### Definitions Section ###

# Name of the executable to create
EXECUTABLE = FlashPhoto
SOURCE_DIR = src
OBJECT_DIR = build


# Define the list of files to compile for this project. Defaults to all
# of the .cpp files in the source directory.
CPPFILES = $(wildcard $(SOURCE_DIR)/*.cpp)

# For each of the .cpp files found above, determine the name of the 
# corresponding .o file to create.
OBJFILES = $(addprefix $(OBJECT_DIR)/,  $(notdir $(CPPFILES:.cpp=.o)))


# The command to run for the C++ compiler and linker
CC = g++

# Basic C++ compiler arguments
CFLAGS = -g -c -Wall -std=gnu++0x

# Basic C++ linker arguments
LDFLAGS = -g


# We use the GLUI library for our graphical user interface.  So, we
# also need to add compiler and linker arguments for GLUI.
GLUI_PATH = ./glui
INCLUDE += -I$(GLUI_PATH)/include
LINK_LIBS +=  -L$(GLUI_PATH)/lib/ -lglui -lpthread
GLUI_LIB = $(GLUI_PATH)/lib/libglui.a

# We use the JPEG library for our graphical user interface.  So, we
# also need to add compiler and linker arguments for JPEG.
JPEG_PATH = ./jpeg-9a
INCLUDE += -I$(JPEG_PATH)/include
JPEG_LIB = $(JPEG_PATH)/.libs/libjpeg.a
LINK_LIBS +=  $(JPEG_LIB)

# We use the PNG library for our graphical user interface.  So, we
# also need to add compiler and linker arguments for PNG.
PNG_PATH = ./png
INCLUDE += -I$(PNG_PATH)/include
PNG_LIB = $(PNG_PATH)/.libs/libpng16.a
LINK_LIBS +=  $(PNG_LIB) -lz

# For graphics support, we also need to link with the Glut and OpenGL libraries.
# This is specified differently depending on whether we are on linux or OSX.
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin) # Mac OSX 
	LINK_LIBS += -framework glut -framework opengl
else # LINUX
	LINK_LIBS += -lglut -lGL -lGLU
endif

# On some lab machines the glut and opengl libraries are located in the directory
# where the nvidia graphics driver was installed rather than the default /usr/lib
# directory.  In this case, we need to tell the linker to search this nvidia directory
# for libraries as well.  Uncomment the line below.
#NVIDIA_LIB =  /usr/lib/nvidia-304  #or whichever nvidia driver number shows up in that dir
ifneq ($(NVIDIA_LIB), )
	LINK_LIBS += -L$(NVIDIA_LIB)
endif



### Rules Section ###


# Note, other than each .o depending upon a corresponding .cpp there is no automatic 
# dependency checking here.  You can add individual dependency rules for .h files
# (e.g., build/ColorData.o:  src/ColorData.h src/SomethingElse.h) by hand if you want
# or just remember to run "make rebuild" if you change a .h file.


all: setup $(EXECUTABLE)

rebuild: clean all

# Create the object_files directory only if it does not exist. 
setup: | $(OBJECT_DIR)

$(OBJECT_DIR): 
	mkdir -p $(OBJECT_DIR)

$(EXECUTABLE): $(JPEG_LIB) $(PNG_LIB) $(OBJFILES) $(GLUI_LIB)
	$(CC) $(LDFLAGS) $(OBJFILES) $(LINK_LIBS) -o $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

clean:
	\rm -rf $(OBJECT_DIR) $(EXECUTABLE)
	$(MAKE) -C $(JPEG_PATH) distclean
	$(MAKE) -C $(PNG_PATH) distclean

$(GLUI_LIB): 
	$(MAKE) -C $(GLUI_PATH) all

$(JPEG_LIB):
	cd $(JPEG_PATH); ./configure --prefix=$(abspath $(JPEG_PATH)) --enable-shared=no	
	$(MAKE) -C $(JPEG_PATH) all
	$(MAKE) -C $(JPEG_PATH) check
	$(MAKE) -C $(JPEG_PATH) install

$(PNG_LIB):
	cd $(PNG_PATH); ./configure --prefix=$(abspath $(PNG_PATH)) --enable-shared=no
	$(MAKE) -C $(PNG_PATH) all
	$(MAKE) -C $(PNG_PATH) check
	$(MAKE) -C $(PNG_PATH) install
