%{
#include <stdio.h>
int bytes         = 0, /* or chars, if you will*/
    lines         = 0,
    words         = 0,
    strings       = 0,
    strlength     = 0, /* length of the current string begin scanned */
    strlength_agg = 0; /* aggregate length of valid strings */
%}

%x STRING

%%

<<EOF>>    { return EOF; }

\"         { BEGIN STRING; bytes++; }
<STRING>{
    \"     { /* end of string */
             BEGIN INITIAL;
             strlength_agg+=strlength; /* valid string, add length to aggregate */
             strlength = 0;            /* reset character count inside current string */
             bytes++;
             strings++;
           }

    \n+    { /* newline, invalid string*/
             BEGIN INITIAL;
             strlength = 0; /* reset character count inside current string */
             bytes+=yyleng;
             words++;
             lines+=yyleng;
           }

    [ \t]+ { strlength+=yyleng; bytes+=yyleng; words++; } /* whitespace, word delimiter */
    .      { strlength++;       bytes++;                } /* anything else */
}

^[ \t]+    { bytes+=yyleng;                             } /* leading whitespace(s)*/
[ \t]+     { bytes+=yyleng; words++;                    } /* non-leading whitespace(s), word delimiter */
^\n+       { bytes+=yyleng;          lines+=yyleng;     } /* blank-line(s) */
\n+        { bytes+=yyleng; words++; lines+=yyleng;     } /* newline(s), word delimiter */
.          { bytes++;                                   } /* anything else */

%%

int main(void) {
    while (yylex() != EOF)
        ;

    /* `wc`-like alignment */
    int width, tmp = bytes;
    for (width=1; tmp > 9;tmp /= 10, width++)
        ;

    /* treating the average length of the strings as an integer */
    int avg_strlength = strings > 0 ? strlength_agg/strings : 0;

    /* `wc`-like printing: lines words bytes strings average */
    printf("%2$*1$d %3$*1$d %4$*1$d %5$*1$d %6$*1$d\n", width, lines, words, bytes, strings, avg_strlength);
    return 0;
}

