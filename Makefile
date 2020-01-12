CXX = g++ 
CPPFLAGS = -Wall -Werror -o
OBJECTS = bin2csv
LDFLAGS = -lboost_filesystem

all: $(OBJECTS)

bin2csv: bin2txt_stock.cpp bin2txt_stock.h
	$(CXX) $(CPPFLAGS) bin2csv bin2txt_stock.cpp $(LDFLAGS) 

clean:
	rm -f $(OBJECTS)

