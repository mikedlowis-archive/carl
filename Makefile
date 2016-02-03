#------------------------------------------------------------------------------
# Build Configuration
#------------------------------------------------------------------------------
# Update these variables according to your requirements.

# version
VERSION = 0.0.1

# tools
CC = c99
LD = ${CC}
AR = ar

# flags
INCS      = -Isource/ -Itests/
CPPFLAGS  = -D_XOPEN_SOURCE=700
CFLAGS   += ${INCS} ${CPPFLAGS}
LDFLAGS  += ${LIBS}
ARFLAGS   = rcs

# commands
COMPILE = @echo CC $@; ${CC} ${CFLAGS} -c -o $@ $<
LINK    = @echo LD $@; ${LD} -o $@ $^ ${LDFLAGS}
ARCHIVE = @echo AR $@; ${AR} ${ARFLAGS} $@ $^
CLEAN   = @rm -f

#------------------------------------------------------------------------------
# Build-Specific Macros
#------------------------------------------------------------------------------
# Library macros and rules
LIBNAME = carl
LIB     = lib${LIBNAME}.a
DEPS    = ${OBJS:.o=.d}
OBJS    = source/main.o                      \
          source/refcount.o                  \
          source/utf/chartorune.o            \
          source/utf/fullrune.o              \
          source/utf/runecmp.o               \
          source/utf/runeinrange.o           \
          source/utf/runelen.o               \
          source/utf/runenlen.o              \
          source/utf/runetochar.o            \
          source/utf/runetype/alphas.o       \
          source/utf/runetype/controls.o     \
          source/utf/runetype/digits.o       \
          source/utf/runetype/lowers.o       \
          source/utf/runetype/marks.o        \
          source/utf/runetype/numbers.o      \
          source/utf/runetype/other.o        \
          source/utf/runetype/otherletters.o \
          source/utf/runetype/punctuation.o  \
          source/utf/runetype/spaces.o       \
          source/utf/runetype/symbols.o      \
          source/utf/runetype/titles.o       \
          source/utf/runetype/tolower.o      \
          source/utf/runetype/totitle.o      \
          source/utf/runetype/toupper.o      \
          source/utf/runetype/uppers.o       \
          source/utf/runetype.o

# Test binary macros
TEST_BIN  = test${LIBNAME}
TEST_DEPS = ${TEST_OBJS:.o=.d}
TEST_OBJS = tests/data/bstree.o    \
            tests/data/hash.o      \
            tests/data/slist.o     \
            tests/atf.o            \
            tests/main.o           \
            tests/refcount.o       \
            tests/utf/test_runes.o \
            tests/utf/test_unicodedata.o

# Distribution dir and tarball settings
DISTDIR   = ${LIBNAME}-${VERSION}
DISTTAR   = ${DISTDIR}.tar
DISTGZ    = ${DISTTAR}.gz
DISTFILES = config.mk LICENSE.md Makefile README.md source tests tools

# load user-specific settings
-include config.mk

#------------------------------------------------------------------------------
# Phony Targets
#------------------------------------------------------------------------------
.PHONY: all options tests

all: options ${LIB} tests

options:
	@echo "Toolchain Configuration:"
	@echo "  CC       = ${CC}"
	@echo "  CFLAGS   = ${CFLAGS}"
	@echo "  LD       = ${LD}"
	@echo "  LDFLAGS  = ${LDFLAGS}"
	@echo "  AR       = ${AR}"
	@echo "  ARFLAGS  = ${ARFLAGS}"

tests: ${TEST_BIN}
	@./${TEST_BIN}

dist: clean
	@echo DIST ${DISTGZ}
	@mkdir -p ${DISTDIR}
	@cp -R ${DISTFILES} ${DISTDIR}
	@tar -cf ${DISTTAR} ${DISTDIR}
	@gzip ${DISTTAR}
	@rm -rf ${DISTDIR}

clean:
	${CLEAN} ${LIB} ${TEST_BIN} ${OBJS} ${TEST_OBJS}
	${CLEAN} ${OBJS:.o=.gcno} ${OBJS:.o=.gcda}
	${CLEAN} ${TEST_OBJS:.o=.gcno} ${TEST_OBJS:.o=.gcda}
	${CLEAN} ${DEPS} ${TEST_DEPS}
	${CLEAN} ${DISTTAR} ${DISTGZ}

#------------------------------------------------------------------------------
# Target-Specific Rules
#------------------------------------------------------------------------------
.c.o:
	${COMPILE}

${LIB}: ${OBJS}
	${ARCHIVE}

${TEST_BIN}: ${TEST_OBJS} ${LIB}
	${LINK}

# load dependency files
-include ${DEPS}
-include ${TEST_DEPS}

