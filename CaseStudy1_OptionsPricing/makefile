CC = g++
LD = g++
CFLAGS = -c -g -Ofast
LIBS = -ldl 

PROG_OBJS = calculateOptionPrice.o calculationFunctions.o constructExpintMatrix.o expint.o main.o triDiagSolver.o

TGTS = CaseStudy.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
