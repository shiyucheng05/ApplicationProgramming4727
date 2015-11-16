CC = g++
LD = g++
CFLAGS = -c -g -Ofast
LIBS = -ldl 

PROG_OBJS = main.o gamrand.o invNormal.o ran2_mod.o calcOptionPremium.o

TGTS = CaseStudy2.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
