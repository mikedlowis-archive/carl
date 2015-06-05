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

/*
 * Rune Definitions and Routines
 */
#define UTFmax    4        /*< Maximum number of bytes per rune */
#define Runesync  0x80     /*< Upper bound of a UTF sequence */
#define Runeself  0x80     /*< Upper bound of a rune sequence */
#define Runeerror 0xFFFD   /*< Decoding error */
#define Runemax   0x10FFFF /*< Maximum rune value */
#define Runemask  0x1FFFFF /*< All bits used by a rune */

/*
typedef uint32_t Rune;

int runetochar(char*, Rune*);
int chartorune(Rune*, char*);
int runelen(long);
int runenlen(Rune*, int);
int fullrune(char*, int);
int utflen(char*);
int utfnlen(char*, long);
char* utfrune(char*, long);
char* utfrrune(char*, long);
char* utfutf(char*, char*);
char* utfecpy(char*, char*, char*);

Rune* runestrcat(Rune*, Rune*);
Rune* runestrchr(Rune*, Rune);
int runestrcmp(Rune*, Rune*);
Rune* runestrcpy(Rune*, Rune*);
Rune* runestrncpy(Rune*, Rune*, long);
Rune* runestrecpy(Rune*, Rune*, Rune*);
Rune* runestrdup(Rune*);
Rune* runestrncat(Rune*, Rune*, long);
int runestrncmp(Rune*, Rune*, long);
Rune* runestrrchr(Rune*, Rune);
long  runestrlen(Rune*);
Rune* runestrstr(Rune*, Rune*);

Rune tolowerrune(Rune);
Rune totitlerune(Rune);
Rune toupperrune(Rune);
Rune tobaserune(Rune);
int isalpharune(Rune);
int isbaserune(Rune);
int isdigitrune(Rune);
int islowerrune(Rune);
int isspacerune(Rune);
int istitlerune(Rune);
int isupperrune(Rune);
*/

/*
 * I/O Routines
 */
#include <stdio.h>

#define Bsize      8*1024
#define Bungetsize 4        /* space for ungetc */
#define Bmagic     0x314159
#define Beof       -1
#define Bbad       -2
//#define Binactive  0        /* states */
//#define Bractive,
//#define Bwactive,
//#define Bracteof,
//#define Bend

//enum {
//    Bsize       = 8*1024,
//    Bungetsize  = 4,        /* space for ungetc */
//    Bmagic      = 0x314159,
//    Beof        = -1,
//    Bbad        = -2,
//
//    Binactive   = 0,        /* states */
//    Bractive,
//    Bwactive,
//    Bracteof,
//
//    Bend
//};

typedef struct Biobuf {
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
} Biobuf;

/*
#define BGETC(bp)\
        ((bp)->icount?(bp)->bbuf[(bp)->bsize+(bp)->icount++]:Bgetc((bp)))

#define BPUTC(bp,c)\
        ((bp)->ocount?(bp)->bbuf[(bp)->bsize+(bp)->ocount++]=(c),0:Bputc((bp),(c)))

#define BOFFSET(bp)\
        (((bp)->state==Bractive)?\
                (bp)->offset + (bp)->icount:\
            (((bp)->state==Bwactive)?\
                    (bp)->offset + ((bp)->bsize + (bp)->ocount):\
                    -1))

#define BLINELEN(bp)\
        (bp)->rdline

#define BFILDES(bp)\
        (bp)->fid

int Bbuffered(Biobuf*);
Biobuf* Bfdopen(int, int);
int Bfildes(Biobuf*);
int Bflush(Biobuf*);
int Bgetc(Biobuf*);
int Bgetd(Biobuf*, double*);
long Bgetrune(Biobuf*);
int Binit(Biobuf*, int, int);
int Binits(Biobuf*, int, int, unsigned char*, int);
int Blinelen(Biobuf*);
long long Boffset(Biobuf*);
Biobuf* Bopen(char*, int);
int Bprint(Biobuf*, char*, ...);
int Bputc(Biobuf*, int);
int Bputrune(Biobuf*, long);
void* Brdline(Biobuf*, int);
char* Brdstr(Biobuf*, int, int);
long Bread(Biobuf*, void*, long);
long long Bseek(Biobuf*, long long, int);
int Bterm(Biobuf*);
int Bungetc(Biobuf*);
int Bungetrune(Biobuf*);
long Bwrite(Biobuf*, void*, long);
int Bvprint(Biobuf*, char*, va_list);
*/

/*
 * New Features
 */
extern char* errstr;
void exits(char*);

/*
 * Make sure we use the built-in main which calls user_main
 */
#ifndef NO_MAIN_WRAPPER
    #define main user_main
#endif
void user_main(int, char**);

#endif /* LIBC_H */
