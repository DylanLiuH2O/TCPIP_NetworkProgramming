CFLAGS = -g -Wall
OBJDIR = obj

all: dir bhost1 bhost2 userver uclient ucnclient

bhost1: $(OBJDIR)/bound_host1.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/bound_host1.o: bound_host1.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

bhost2: $(OBJDIR)/bound_host2.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/bound_host2.o: bound_host2.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

userver: $(OBJDIR)/uecho_server.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/uecho_server.o: uecho_server.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

uclient: $(OBJDIR)/uecho_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/uecho_client.o: uecho_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

ucnclient: $(OBJDIR)/uecho_conn_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/uecho_conn_client.o: uecho_conn_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm bhost1 bhost2 userver uclient ucnclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)