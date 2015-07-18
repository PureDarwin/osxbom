NAME=lsbom
SRCROOT?=.
OBJROOT?=/tmp/$(NAME).obj
SYMROOT?=/tmp/$(NAME).sym
DSTROOT?=/tmp/$(NAME).dst

CXX=g++
MKDIR=mkdir -p
STRIP=strip
INSTALL=install

.PHONY : install pre-install lsbom

install: pre-install lsbom

pre-install: 
	@[ -d "$(SYMROOT)" ] || mkdir -p "$(SYMROOT)"
	@[ -d "$(DSTROOT)" ] || mkdir -p "$(DSTROOT)"

lsbom: lsbom.cpp
	$(CXX) $(RC_CPPFLAGS) -o "$(SYMROOT)/$@" $^
	$(MKDIR) "$(DSTROOT)/usr/bin"
	$(INSTALL) -c -m 0755 "$(SYMROOT)/$@" "$(DSTROOT)/usr/bin"
	$(STRIP) "$(DSTROOT)/usr/bin/$@"



