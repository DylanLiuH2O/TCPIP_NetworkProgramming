CFLAGS = -g -Wall
OBJDIR = obj

all: dir sock_type get_buf set_buf reserver reclient

sock_type: $(OBJDIR)/sock_type.o
	cc $(CFLAGS) sock_type.c -o sock_type
$(OBJDIR)/sock_type.o: sock_type.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

get_buf: $(OBJDIR)/get_buf.o
	cc $(CFLAGS) get_buf.c -o get_buf
$(OBJDIR)/get_buf.o: get_buf.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

set_buf: $(OBJDIR)/set_buf.o
	cc $(CFLAGS) set_buf.c -o set_buf
$(OBJDIR)/set_buf.o: set_buf.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

reserver: $(OBJDIR)/reuseadr_eserver.o
	cc $(CFLAGS) reuseadr_eserver.c -o reserver
$(OBJDIR)/reuseadr_eserver.o: reuseadr_eserver.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

reclient: $(OBJDIR)/reuseadr_eclient.o
	cc $(CFLAGS) reuseadr_eclient.c -o reclient
$(OBJDIR)/reuseadr_eclient.o: reuseadr_eclient.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm sock_type get_buf set_buf reserver reclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)