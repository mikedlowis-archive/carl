/**
  @file libc.h
*/
#ifndef LIBC_H
#define LIBC_H

/*
 * Base Types and Definitions
 */
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <errno.h>

#ifndef nil
#define nil NULL
#endif

#ifndef nelem
#define nelem(x) (sizeof(x)/sizeof((x)[0]))
#endif

#ifndef container_of
#define container_of(obj, type, member) \
    (type*)((uintptr_t)obj - offsetof(type, member))
#endif

/*
 * Assertions
 */
#include <assert.h>

#ifndef static_assert
    #ifdef NDEBUG
        #define static_assert(expr) ((void)0)
    #else
        #define static_assert(expr) switch(0){case 0:case (expr):;}
    #endif
#endif

/*
 * Setjmp Routines
 */
#include <setjmp.h>

/*
 * Signal Routines
 */
#include <signal.h>

/*
 * Memory and String Routines
 */
#include <string.h>

/**
 * Copies contents of string from input to output compressing C-language escape
 * sequences to the equivalent character. A null byte is appended to the output.
 * The space allocated for output must be at least as large as the space
 * allocated for input.
 *
 * @return The output argument.
 **/
char* strccpy(char* output, const char* input);

/**
 * Identical to strccpy() except that it returns a pointer to the appended NULL
 * byte.
 **/
char* strcadd(char* output, const char* input);

/**
 * Copies contents of string from input to output expanding non-graphical
 * characters to their C-language escape sequences. The output argument must
 * point to a space large enough to hold the result. Worst case scenario this
 * is 4 times the space allocated for the input argument. Characters in the
 * exceptions string are not expanded.
 *
 * @return The output argument.
 **/
char* strecpy(char* output, const char* input, const char* ex);

/**
 * Identical to strecpy() except that it returns the address of the appended
 * NULL byte.
 **/
char* streadd(char* output, const char* input, const char* ex);

/**
 * Makes a dynamically allocated duplicate of the input string.
 *
 * @return dynamically allocated copy of input.
 **/
char* strdup(const char* input);

/**
 * Performs a case-insensitive comparison of two strings.
 *
 * @return The result of comparison:
 *         <0 - The first mismatched character is lower in value in str1 than str2
 *          0 - The strings are equal
 *         >0 - The first mismatched character is greater in value in str1 than str2
 **/
int cistrcmp(char* str1, char* str2);

/**
 * Performs a case-insensitive comparison of two strings up to num characters.
 *
 * @return The result of comparison:
 *         <0 - The first mismatched character is lower in value in str1 than str2
 *          0 - The strings are equal
 *         >0 - The first mismatched character is greater in value in str1 than str2
 **/
int cistrncmp(char* str1, char* str2, int num);

/**
 * Returns a pointer to the first occurrences of str2 in str1. The string
 * contents are compared case-insensitively.
 *
 * @return first occurrences of str2 in str1.
 **/
char* cistrstr(char* str1, char* str2);

/**
 * Breaks str up into tokens by replacing every whitespace character with the
 * null character. Pointers to all of the non-empty tokens are placed into the
 * args array. Processing will stop after max tokens are processed.
 *
 * @return The number of tokens processed.
 **/
int tokenize(char* str, char** args, int max);

/**
 * Allocates a reference counted block of memory.
 *
 * @return pointer to the allocated memory.
 **/
void* refallocate(size_t sz);

/**
 * Allocates a reference counted block of memory with an associated destructor
 * to be called when the memory is freed.
 *
 * @return pointer to the allocated memory.
 **/
void* refobject(size_t sz,void (*destruct)(void*));

/**
 * Increments the reference count for a block of memory by one.
 *
 * @return The obj argument.
 **/
void* refretain(void* obj);

/**
 * Decrements the reference count for a block of memory by one. If this
 * operation causes the reference count to reach 0 its associated destructor
 * is called and the memory is freed. Any pointers still referencing this
 * memory will be invalid and should no longer be used.
 **/
void refrelease(void* obj);

/**
 * Returns the current number of references to obj.
 **/
size_t refcount(void* obj);

/**
 * Replace the reference in var with the reference to val. The current value of
 * var is first replaced with val and the old value of var is then released with
 * refrelease().
 **/
void refreplace(void** var, void* val);

/*
 * Rune Definitions and Routines
 */
#define UTF_MAX   4        /*< Maximum number of bytes per rune */
#define Runesync  0x80     /*< Upper bound of a UTF sequence */
#define Runeself  0x80     /*< Upper bound of a rune sequence */
#define Runeerror 0xFFFD   /*< Decoding error */
#define Runemax   0x10FFFF /*< Maximum rune value */
#define Runemask  0x1FFFFF /*< All bits used by a rune */

typedef uint32_t Rune;

/* Single source
 *****************************************************************************/
/**
 * Copies one Rune from r to at most UTF_MAX bytes in s.
 *
 * @return The number of bytes copied.
 **/
int runetochar(char* s, Rune* r);

/**
 * Copies at most UTF_MAX bytes from s to one rune at r.
 *
 * @return The number of bytes copied.
 **/
int chartorune(Rune* r, char* s);

/**
 * Returns the number of bytes required to convert r to UTF.
 **/
int runelen(long r);

/**
 * Returns the number of bytes required to convert num runes pointed to by r
 * into UTF.
 **/
int runenlen(Rune* r, int num);

/**
 * Returns true if the string s of length n is long enough to be decoded as a
 * Rune. Returns false otherwise.
 **/
bool fullrune(char* s, int n);

/* Multiple Sources
 *****************************************************************************/
/**
 * Returns the number runes that make up the string s.
 **/
int utflen(char* s);

/**
 * Returns the number of runes that make up the first n bytes of string s.
 **/
int utfnlen(char* s, long n);

/**
 * Returns a pointer to the first occurrence of rune c in string s.
 **/
char* utfrune(char* s, Rune c);

/**
 * Returns a pointer to the last occurrence of rune c in string s.
 **/
char* utfrrune(char* s, Rune c);

/**
 * Returns a pointer to the first occurrence of str2 in str1 or NULL if none
 * found.
 **/
char* utfutf(char* str1, char* str2);

/**
 * Copies UTF sequences from str2 to str1 until a null sequence or estr1 is
 * reached.
 *
 * @return Returns str1.
 **/
char* utfecpy(char* str1, char* estr1, char* str2);

/**
 * Copies the contents of str2 to the end of str1. Returns the str1 argument.
 **/
Rune* runestrcat(Rune* str1, Rune* str2);

/**
 * Copies up to num runes from str2 to the end of str1 and returns str1.
 **/
Rune* runestrncat(Rune* str1, Rune* str2, long num);

/**
 * Returns a pointer to the first occurrence of c in str.
 **/
Rune* runestrchr(Rune* str, Rune c);

/**
 * Returns a pointer to the last occurrence of c in str.
 **/
Rune* runestrrchr(Rune*, Rune);

/**
 * Compares the contents of the two strings for equality.
 * Returns the result of comparison:
 *   <0 - The first mismatched character is lower in value in str1 than str2.
 *    0 - The two strings are equal.
 *   >0 - The first mismatched character is greater in value in str1 than str2.
 **/
int runestrcmp(Rune* str1, Rune*);

/**
 *
 * Performs a comparison of two rune strings up to num characters.
 *
 * @return The result of comparison:
 *         <0 - The first mismatched rune is lower in value in str1 than str2
 *          0 - The strings are equal
 *         >0 - The first mismatched rune is greater in value in str1 than str2
 **/
int runestrncmp(Rune* str1, Rune* str2, long num);

/**
 * Copies the contents of str2 to str1. Returns argument str1.
 **/
Rune* runestrcpy(Rune* str1, Rune* str2);

/**
 * Copies up to num runes from str2 to str1. Returns argument str1.
 **/
Rune* runestrncpy(Rune* str1, Rune* str2, long num);

/**
 * Copies contents of string from input to output compressing C-language escape
 * sequences to the equivalent rune. A null byte is appended to the output.
 * The space allocated for output must be at least as large as the space
 * allocated for input.
 *
 * @return The output argument.
 **/
Rune* runestrccpy(Rune* output, Rune* input);

/**
 * Copies contents of string from input to output expanding non-graphical
 * runes to their C-language escape sequences. The output argument must
 * point to a space large enough to hold the result. Worst case scenario this
 * is 4 times the space allocated for the input argument. Characters in the
 * exceptions string are not expanded.
 *
 * @return The output argument.
 **/
Rune* runestrecpy(Rune* output, Rune* input, Rune* ex);

/**
 * Return a new dynamically allocated copy of str.
 **/
Rune* runestrdup(Rune* str);

/**
 * Return the number of runes that make up the string str.
 **/
long runestrlen(Rune* str);

/**
 *
 * Returns a pointer to the first occurrences of str2 in str1. The string
 * contents are compared case-insensitively.
 *
 * @return first occurrences of str2 in str1.
 **/
Rune* runestrstr(Rune* str1, Rune* str2);

/* Single Source
 *****************************************************************************/
/** Convert the rune ch to lowercase. */
Rune tolowerrune(Rune ch);

/** Convert the rune ch to a title rune. */
Rune totitlerune(Rune ch);

/** Convert the rune ch to uppercase. */
Rune toupperrune(Rune ch);

/** Convert the rune ch to a base rune. */
Rune tobaserune(Rune ch);

/** Returns whether the rune is a letter. */
bool isalpharune(Rune ch);

/** Returns whether the rune is a base rune. */
bool isbaserune(Rune ch);

/** Returns whether the rune is a digit. */
bool isdigitrune(Rune ch);

/** Returns whether the rune is a lowercase rune. */
bool islowerrune(Rune ch);

/** Returns whether the rune is a whitespace rune. */
bool isspacerune(Rune ch);

/** Returns whether the rune is a title rune. */
bool istitlerune(Rune ch);

/** Returns whether the rune is a uppercase rune. */
bool isupperrune(Rune ch);

/*
 * I/O Routines
 */
#include <stdio.h>

#if 0
#define Bsize      8*1024
#define Bungetsize 4        /* space for ungetc */
#define Bmagic     0x314159
#define Beof       -1
#define Bbad       -2

typedef struct iobuf {
    int icount;     /* neg num of bytes at eob */
    int ocount;     /* num of bytes at bob */
    int rdline;     /* num of bytes after rdline */
    int runesize;   /* num of bytes of last getrune */
    int state;      /* r/w/inactive */
    int fid;        /* open file */
    int flag;       /* magic if malloc'ed */
    long long   offset;     /* offset of buffer in file */
    int bsize;      /* size of buffer */
    unsigned char*  bbuf;       /* pointer to beginning of buffer */
    unsigned char*  ebuf;       /* pointer to end of buffer */
    unsigned char*  gbuf;       /* pointer to good data in buf */
    unsigned char   b[Bungetsize+Bsize];
} iobuf;

int iobuffered(iobuf*);
iobuf* iofdopen(int, int);
int iofildes(iobuf*);
int ioflush(iobuf*);
int iogetc(iobuf*);
int iogetd(iobuf*, double*);
long iogetrune(iobuf*);
int ioinit(iobuf*, int, int);
int ioinits(iobuf*, int, int, unsigned char*, int);
int iolinelen(iobuf*);
long long iooffset(iobuf*);
iobuf* ioopen(char*, int);
int ioprint(iobuf*, char*, ...);
int ioputc(iobuf*, int);
int ioputrune(iobuf*, long);
void* iordline(iobuf*, int);
char* iordstr(iobuf*, int, int);
long ioread(iobuf*, void*, long);
long long seek(iobuf*, long long, int);
int ioterm(iobuf*);
int ioungetc(iobuf*);
int ioungetrune(iobuf*);
long iowrite(iobuf*, void*, long);
int iovprint(iobuf*, char*, va_list);
#endif

/*
 * New Features
 */
extern char* errstr;
void exits(char* str);

/*
 * Make sure we use the built-in main which calls user_main
 */
#ifndef NO_MAIN_WRAPPER
    #define main user_main
#endif
void user_main(int, char**);

#endif /* LIBC_H */
