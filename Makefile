SRCDIR = src

BUILDDIR = src

SRCS = $(SRCDIR)/main.cpp \
       $(SRCDIR)/Portifolio.cpp \
       $(SRCDIR)/Stock.cpp \
       $(SRCDIR)/Market.cpp \
       $(SRCDIR)/Menus.cpp \
       $(SRCDIR)/Saver.cpp \
       $(SRCDIR)/Tick.cpp 

OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

TARGET = $(BUILDDIR)/out

CXX = g++

CXXFLAGS = -Wall -g -std=c++23

LDFLAGS =

all: $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(OBJS) $(BUILDDIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	# Se você quiser remover o diretório src inteiro na limpeza (cuidado!), descomente a linha abaixo
	# rm -rf $(BUILDDIR)

.PHONY: all clean $(BUILDDIR)
