
CFLAGS = -g -Wall
OBJDIR = obj

all: dir sepserver sepclient dup sepserver2

sepserver: $(OBJDIR)/sep_server.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/sep_server.o: sep_server.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

sepclient: $(OBJDIR)/sep_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/sep_client.o: sep_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dup: $(OBJDIR)/dup.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/dup.o: dup.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

sepserver2: $(OBJDIR)/sep_server2.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/sep_server2.o: sep_server2.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm sepserver sepclient dup sepserver2
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)