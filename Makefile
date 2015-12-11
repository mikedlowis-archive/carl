#------------------------------------------------------------------------------
# Build Configuration
#------------------------------------------------------------------------------
# Update these variables according to your requirements.

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

#------------------------------------------------------------------------------
# Build Targets and Rules
#------------------------------------------------------------------------------
SRCS = source/data/bstree.c               \
       source/data/hash.c                 \
       source/data/list.c                 \
       source/data/slist.c                \
       source/data/vec.c                  \
       source/main.c                      \
       source/refcount.c                  \
       source/utf/chartorune.c            \
       source/utf/fullrune.c              \
       source/utf/runecmp.c               \
       source/utf/runeinrange.c           \
       source/utf/runelen.c               \
       source/utf/runenlen.c              \
       source/utf/runetochar.c            \
       source/utf/runetype/alphas.c       \
       source/utf/runetype/controls.c     \
       source/utf/runetype/digits.c       \
       source/utf/runetype/lowers.c       \
       source/utf/runetype/marks.c        \
       source/utf/runetype/numbers.c      \
       source/utf/runetype/other.c        \
       source/utf/runetype/otherletters.c \
       source/utf/runetype/punctuation.c  \
       source/utf/runetype/spaces.c       \
       source/utf/runetype/symbols.c      \
       source/utf/runetype/titles.c       \
       source/utf/runetype/tolower.c      \
       source/utf/runetype/totitle.c      \
       source/utf/runetype/toupper.c      \
       source/utf/runetype/uppers.c       \
       source/utf/runetype.c
OBJS = ${SRCS:.c=.o}

TEST_SRCS = tests/data/bstree.c    \
            tests/data/hash.c      \
            tests/data/slist.c     \
            tests/atf.c            \
            tests/main.c           \
            tests/refcount.c       \
            tests/utf/test_runes.c \
            tests/utf/test_unicodedata.c
TEST_OBJS = ${TEST_SRCS:.c=.o}

all: options libcarl.a testcarl

options:
	@echo "Toolchain Configuration:"
	@echo "  CC       = ${CC}"
	@echo "  CFLAGS   = ${CFLAGS}"
	@echo "  LD       = ${LD}"
	@echo "  LDFLAGS  = ${LDFLAGS}"
	@echo "  AR       = ${AR}"
	@echo "  ARFLAGS  = ${ARFLAGS}"

libcarl.a: ${OBJS}
	@echo AR $@
	@${AR} ${ARFLAGS} $@ ${OBJS}

testcarl: ${TEST_OBJS} libcarl.a
	@echo LD $@
	@${LD} -o $@ ${TEST_OBJS} libcarl.a ${LDFLAGS}
	-./$@

.c.o:
	@echo CC $<
	@${CC} ${CFLAGS} -c -o $@ $<

clean:
	@rm -f libcarl.a testcarl ${OBJS} ${TEST_OBJS}

.PHONY: all options

