 # Usage of CDK Matrix
 #
 # File:   example1.cc
 # Author: Ricardo Ramirez
 # Email:  rjr170030@utdallas.edu
 # Course: CS3377
 
CXX = g++
CXXFLAGS = -Wall -g
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 



PROJECTNAME = Program6
# This should not contain spaces or special characters

EXECFILE = cdkexample

OBJS = cdkexample.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDINAME:= rjr170030-RicardoRamirez)
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDINAME) 2> /dev/null
	@echo 600 $(MKBKUPNAME)
	@echo
	@echo Done!
