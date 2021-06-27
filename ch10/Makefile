CFLAGS = -g -Wall
OBJDIR = obj

all: dir zombie wait waitpid signal sigaction \
	 remove_zombie fork empserver empclient \
	 eclient
	
zombie: $(OBJDIR)/zombie.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/zombie.o: zombie.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

wait: $(OBJDIR)/wait.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/wait.o: wait.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

waitpid: $(OBJDIR)/waitpid.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/waitpid.o: waitpid.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

signal: $(OBJDIR)/signal.o
	cc $(CFLAGS) $^ -o $@ 
$(OBJDIR)/signal.o: signal.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@ 

sigaction: $(OBJDIR)/sigaction.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/sigaction.o: sigaction.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

remove_zombie: $(OBJDIR)/remove_zombie.o
	cc $(CFLAGS) $^ -o $@ 
$(OBJDIR)/remove_zombie.o: remove_zombie.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@ 

fork: $(OBJDIR)/fork.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/fork.o: fork.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

empserver: $(OBJDIR)/echo_mpserv.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_mpserv.o: echo_mpserv.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

empclient: $(OBJDIR)/echo_mpclient.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_mpclient.o: echo_mpclient.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

eclient: $(OBJDIR)/echo_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_client.o: echo_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm zombie wait waitpid signal sigaction \
		 remove_zombie fork empserver empclient \
		 eclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)