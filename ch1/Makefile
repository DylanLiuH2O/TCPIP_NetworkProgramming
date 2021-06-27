CFLAGS = -g -Wall
OBJDIR = obj

all: dir hserver hclient

hserver: $(OBJDIR)/hello_server.o
	cc $(CFLAGS) $^ -o $@ 
$(OBJDIR)/hello_server.o: hello_server.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

hclient: $(OBJDIR)/hello_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/hello_client.o: hello_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm hserver hclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)