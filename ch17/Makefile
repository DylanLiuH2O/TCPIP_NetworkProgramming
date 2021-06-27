CFLAGS = -g -Wall
OBJDIR = obj

all: dir eepollserv eclient eepltserv eepetserv

eepollserv: $(OBJDIR)/echo_epollserv.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_epollserv.o: echo_epollserv.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

eclient: $(OBJDIR)/echo_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_client.o: echo_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

eepltserv: $(OBJDIR)/echo_EPLTserv.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_EPLTserv.o: echo_EPLTserv.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

eepetserv: $(OBJDIR)/echo_EPETserv.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_EPETserv.o: echo_EPETserv.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm eepollserv eclient eepltserv eepetserv
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)