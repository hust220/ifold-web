SUBDIRS = src DMD-NEW

all: subdirs

subdirs:
	for dir in $(SUBDIRS); do\
	$(MAKE) -C $$dir;\
	done

clean:
	for dir in $(SUBDIRS); do\
	$(MAKE) -C $$dir clean;\
	done
