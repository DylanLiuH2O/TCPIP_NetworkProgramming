CFLAGS = -g -Wall
OBJDIR = obj

all: dir pipe1 pipe2 pipe3 esserver empclient

pipe1: $(OBJDIR)/pipe1.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/pipe1.o: pipe1.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@
	
pipe2: $(OBJDIR)/pipe2.o
	cc $(CFLAGS) $^ -o $@ 
$(OBJDIR)/pipe2.o: pipe2.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@ 

pipe3: $(OBJDIR)/pipe3.o
	cc $(CFLAGS) $^ -o $@ 
$(OBJDIR)/pipe3.o: pipe3.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@ 

esserver: $(OBJDIR)/echo_storeserv.o
	cc $(CFLAGS) $^ -o $@ 
$(OBJDIR)/echo_storeserv.o: echo_storeserv.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@ 

empclient: $(OBJDIR)/echo_mpclient.o
	cc $(CFLAGS) $^ -o $@ 
$(OBJDIR)/echo_mpclient.o: echo_mpclient.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@ 

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm pipe1 pipe2 pipe3 esserver empclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)
