RVMD = reveal-md

.PHONY: all html clean

all: html

html: _site

_site: slides.md
	$(RVMD) $< --static $@

clean:
	-rm -f *~
	-rm -fr _site
