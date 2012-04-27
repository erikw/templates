#define VERSION "1.2"
/* 
   Version 1.2 (06 Apr 1994)
   
   
   untex.c: Copyright Michael Staats (michael@hal6000.thp.uni-duisburg.de)
   This source can be freely distributed according to the GNU Public
   license, which is available via ftp at many anon ftp servers. 
   
   Warning: I give no warranty whatever. Please note, that this is
   one of the first versions of untex, there might be bugs. I haven't
   tested it completely.

   06 Apr 94: bugfix for -m (\$ wasn't recognized as escaped),
              thanks to mazumdar@ringer.cs.utsa.edu (Subhasish Mazumdar),
	      also for hints for previous improvements.

   30 Mar 94: rewrite of Umlaut processing
   	      Added -i option, better support for environments.
              Michael Staats (michael@hal6000.thp.uni-duisburg.de)
	         
   4  Oct 92: modified for conversation of "a -> ae etc.: 
	      Denis Endisch (denis@smoky.ikf.physik.uni-frankfurt.de)
	     
*/


/* untex.c:     remove all (?) LaTeX commands from input,
                Options:
		-i process \input and \include files
		-o remove options to commands
		-a remove arguments 
		-u replace all \"a (etc.) with ibm characters
		-g also replace all "a (etc.) with ibm characters (german.sty)
		-e remove environment names
		-m remove all math
		-  read from stdin (no ioctl call to determine piped input,
		                    this program is intended to be portable)
		
		-g implies -u, -a implies -o
*/


#include <stddef.h>
#include <stdio.h>
#include <ctype.h>


#define MAXCMDLEN 80
#define MAXFILENAMELEN 255
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
    
#define GET(c) if (((c)=getc(inf)) == EOF ) return    
int nomath 	= FALSE;
int noenv 	= FALSE;
int inputs	= FALSE;
int germ 	= FALSE;
int uml 	= FALSE;
int iso		= FALSE;
int ascii	= FALSE;
int noarg 	= FALSE;
int noopt 	= FALSE;
int inarray	= FALSE;


void usage();
void untex(FILE *inf);
char *umlaut(int c);
int parsecmd(FILE *inf);
int skipcomment(FILE *inf, int *c);
int skip(FILE *inf, int c);

int main(int argc, char *argv[])
{
    int i;
    FILE *inf;
    
    if (argc <= 1) usage();
    
    i = 1;
    inf = NULL;
    while (i < argc && argv[i][0]=='-') switch(argv[i++][1]) {
      case 'i':inputs = TRUE;
	break;
      case 'm':nomath = TRUE;
	break;
      case 'a':noarg = TRUE;   /* no break here! */
      case 'o':noopt = TRUE;
	break;
      case 'e':noenv = TRUE;
	break;
      case 'g':germ = TRUE;   /* no break here ! */
      case 'u':uml = TRUE;
	iso = !strcmp(&argv[i-1][2], "iso");
	ascii = !strcmp(&argv[i-1][2], "ascii");
	break;
      default:
	if (!strcmp(argv[i-1],"-")) inf = stdin;
	else usage();
	break;
    }
    
    if (i >= argc && inf == NULL) usage();
    
    if (inf == NULL) for (;i<argc;i++) {
	if ((inf = fopen(argv[i],"r"))==NULL) perror(argv[i]);
	else untex(inf);
	fclose(inf);
    } else untex(inf);
    
    exit(0);
}

void usage()
{
    fprintf(stderr,"untex version %s\n", VERSION);
    fprintf(stderr,"usage:\n   untex [-i] [-o] [-a] [-m] [-e] [-u[iso,ascii]] [-g[iso,ascii]] files ...\n");
    fprintf(stderr,"or:\n   untex [-i] [-o] [-a] [-m] [-e] [-u[iso,ascii]] [-g[iso,ascii]] -\n");
    fprintf(stderr,"Options:   - : read from stdin\n");
    fprintf(stderr,"          -m : remove all math code\n");
    fprintf(stderr,"          -o : remove options to commands\n");
    fprintf(stderr,"          -i : process \\include and \\input\n");
    fprintf(stderr,"          -u : replace all \\\"a (etc.) with ibm (CP 850) characters\n");
    fprintf(stderr,"          -g : also replace all \"a (etc.) with ibm (CP 850) characters (german.sty)\n");
    fprintf(stderr,"       -uiso : replace all \\\"a (etc.) with iso characters\n");
    fprintf(stderr,"       -giso : also replace all \"a (etc.) with iso characters (german.sty)\n");
    fprintf(stderr,"     -uascii : replace all \\\"a (etc.) with ascii characters (ae, ss, ...)\n");
    fprintf(stderr,"     -gascii : also replace all \"a (etc.) with ascii characters (german.sty)\n");
    fprintf(stderr,"          -e : remove environment names\n");
    fprintf(stderr,"          -a : remove arguments of commands\n");
    fprintf(stderr,"          -g implies -u, -a implies -o\n");
    fprintf(stderr,"          output is written to stdout\n");
    
    exit(1);
}

void untex(FILE *inf)
{
    int c, c1;
    
    while ( (c=getc(inf)) != EOF ) {
	switch (c) {
	  case '\\':
	    GET(c);
	    switch (c) {
		/*****************************************/
		/* following code treats chars preceeded
		   by a backslash */
		
	      case '|':  /* print escaped special chars */
	      case '$':
	      case '&':
	      case '%':
	      case '#':
	      case '_':
	      case '{':
	      case '}':
		putchar(c);
		break;
		
	      case ' ': /* print space instead of these */
	      case '`':
	      case '\'':
	      case '+':
	      case '/':
	      case ':':
	      case ';':
	      case ',':
	      case '<':
	      case '>':
	      case '@':
		putchar(' ');
		break;
		
	      case '-': /* ignore these */
	      case '=':
	      case '!':			      
	      case '^':
	      case '~':
	      case '.':
		break;
		
	      case '(': /* if -m is set, ignore math */
	      case '[':
		c1 = (c == '(') ? ')' : ']';
		if (!nomath) putchar(c);
		while (nomath && c != c1) {
		    while ( (c=getc(inf)) != EOF &&
			   skipcomment(inf, &c) &&
			   c != '\\' );
		    GET(c);
		}
		break;
		
	      case '3':
		if (germ) fputs(umlaut('s'), stdout);
		break;
						
	      case '\"':
		GET(c);
		if (uml) fputs(umlaut(c), stdout);
		break;
		
	      case '\\':putchar('\n');  
		GET(c);
		if (c == '[') 
		  while ((c=getc(inf)) != EOF  &&
			 skipcomment(inf, &c) &&
			 c != ']');
		else ungetc(c, inf);
		break;
		
	      default:
		ungetc(c, inf);
		if ((c=parsecmd(inf)) == EOF) return;
		if (c=='\n') putchar(c); else putchar(' ');
		break;
	    }
	    break; 
	    /*****************************************/
	  case '%':while ((c=getc(inf)) != EOF && c != '\n');
	    break; 
	    
	  case '{':
	  case '}':
	  case '~':
	  case '_':
	    putchar(' ');
	    break;
	    
	  case '\"':
	    if (germ) {
		GET(c);
		fputs(umlaut(c), stdout);
	    } else putchar(c);
	    break;
	    
	  case '$':
	    GET(c);
	    if (c != '$') ungetc(c, inf);
	    if (nomath) {
		int bs = (c == '\\');
		while ((c=getc(inf)) != EOF && 
		       skipcomment(inf, &c) &&
		       !(c == '$' && !bs)) bs = (c == '\\');
		if (c == EOF) return;
		GET(c);
		if (c != '$') ungetc(c, inf);
	    }
	    break;
	    
	  case '&':
	    if (inarray) putchar(' '); else putchar('&');
	    break;
	    
	  default:putchar(c);
	    break;
	}
	if (c == EOF) return;
    }
    return;
}


int skipcomment(FILE *inf, int *c)
{
    static int oldc = 0;
    
    while (oldc != '\\' && *c == '%') {
	while ((*c=getc(inf)) != EOF && *c != '\n');
	*c = getc(inf);
    }
    oldc = *c;
    return((*c != EOF));
}

int skip(FILE *inf, int c)
{
    int cc, ec, openb, closeb;
    switch (c) {
      case '{':ec='}'; break;
      case '(':ec=')'; break;
      case '[':ec=']'; break;
      case '<':ec='>'; break;
    }
    cc = getc(inf);
    if (cc != c) {
	ungetc(cc, inf);
	return(cc != EOF);
    }
    openb  = 1;
    closeb = 0;
    while (openb > closeb && cc != EOF) {
	cc = getc(inf);
	if (cc == c) openb++;
	if (cc == ec) closeb++;
    }
}
	
    
	


char *umlaut(int c)
{
    static char rv[2];
    switch (c) {
      case 'a':return(ascii ? "ae" : (iso ? "\344" : "\204"));
      case 'A':return(ascii ? "Ae" : (iso ? "\304" : "\216"));
      case 'o':return(ascii ? "oe" : (iso ? "\366" : "\224"));
      case 'O':return(ascii ? "Oe" : (iso ? "\326" : "\231"));
      case 'u':return(ascii ? "ue" : (iso ? "\374" : "\201"));
      case 'U':return(ascii ? "Ue" : (iso ? "\334" : "\232"));
      case 's':return(ascii ? "ss" : (iso ? "\337" : "\341"));
    }
    rv[0]=c;
    rv[1]=0;
    return(rv);
}


int parsecmd(FILE *inf)
{
    int c, ce;
    char cmd[MAXCMDLEN], env[MAXCMDLEN], envtst[MAXCMDLEN];
    int fnc, cmdc, envc, i, openb, closeb;
    int proceed;
    char fname[MAXFILENAMELEN];
    
    fnc = envc = cmdc = 0;
    c = getc(inf);
    
    while (c != EOF &&  (isalnum(c) || c == '@' || c == '*' )) {
	cmd[cmdc++] = c;
	if (cmdc >= MAXCMDLEN - 1) cmdc--;
	c = getc(inf);
    }
    cmd[cmdc] = 0;
    if (c == EOF) return(c);
    
    if (noopt && c == '[') {
	while ((c=getc(inf)) != EOF && c != ']');
	if ((c = getc(inf)) == EOF) return(c);
    }
    
    if (noarg && c == '{' && 
	strcmp(cmd,"begin") && strcmp(cmd,"end") && 
	((strcmp(cmd,"include") && strcmp(cmd,"input"))||!inputs)
	) {
	openb = 1;
	closeb = 0;
	while ((c = getc(inf)) != EOF && skipcomment(inf, &c) &&
	       closeb != openb) 
	  if (c =='{') openb++; else if (c == '}') closeb++;
	ungetc(c, inf);
	return(c);
    }
    
    if (inputs && (!strcmp(cmd, "input") || !strcmp(cmd,"include"))) {
	FILE *incfile;
	if (!(c == '{' || ( c == ' ' && !strcmp(cmd,"input")))
	      || c == EOF) {
	    ungetc(c, inf);
	    return(c);
	}
	fnc = 0;
	if (c == '{') ce = '}'; else { c = '{'; ce = '\n'; }
    	while (c != EOF && c != ce && !isspace(c)) {
	    c = getc(inf);
	    fname[fnc++] = c;
	    if (fnc >= MAXFILENAMELEN - 4) fnc--;
	}
	fname[fnc-1] = 0;
	if (strncmp(fname+fnc-5, ".tex", 4)) strcat(fname,".tex");
	if ((incfile = fopen(fname,"r"))==NULL) perror(fname);
	else untex(incfile);
	fclose(incfile);
	return(c);
    }
	
    if (!strcmp(cmd,"begin") || !strcmp(cmd,"end")) {
	if ((c != '{' || c == EOF)) {
	    ungetc(c, inf);
	    return(c);
	}
	envc = 0;
	while (c != EOF && c != '}') {
	    c = getc(inf);
	    env[envc++] = c;
	    if (envc >= MAXCMDLEN - 1) envc--;
	}
	env[envc-1] = 0;
	if (!noenv) printf(env);
	envtst[0] = 0;
	
	
	/* special treatment of some environments */
	
	/* thebibiliography */
	if (noenv && !strcmp(cmd, "begin")  && !strcmp(env,"thebibliography"))
	  skip(inf, '{');

	/* table, figure */
	if (noenv && !strcmp(cmd, "begin")  && 
	    (!strcmp(env, "table")  ||
	     !strcmp(env, "table*")  ||
	     !strcmp(env, "figure")  ||
	     !strcmp(env, "figure*")
	     )) skip(inf, '[');
	
	/* documentstyle, minipage */
	if (noenv && !strcmp(cmd, "begin") && !strcmp(env, "minipage")) {
	    skip(inf, '[');
	    skip(inf, '{');
	}
	
	/* tabular, array, eqnarray */
	if (!strcmp(cmd, "begin")  && 
	    (!strcmp(env, "tabular")  ||
	     !strcmp(env, "eqnarray") ||
	     !strcmp(env, "eqnarray*") ||
	     !strcmp(env, "array")
	     )) {
	    inarray++;
	    if (noenv && env[0] != 'e') {
		skip(inf, '[');
		skip(inf, '{');
	    }
	}
	if (!strcmp(cmd,  "end")  && 
	    (!strcmp(env, "tabular")  ||
	     !strcmp(env, "eqnarray") ||
	     !strcmp(env, "eqnarray*") ||
	     !strcmp(env, "array")
	     )) if (--inarray < 0) inarray = 0;
	
	
	/* displaymath, equation, eqnarray */
	
	
	if (nomath && !strcmp(cmd,"begin") &&
	    (!strcmp(env,"displaymath") ||
	     !strcmp(env,"equation") ||
	     !strcmp(env,"eqnarray") ||
	     !strcmp(env,"equation*") ||
	     !strcmp(env,"eqnarray*")
	     )
	    ) { 
	    putchar('\n');
	    while (strcmp(envtst, env)) {
		while ((c=getc(inf)) != EOF &&
		       skipcomment(inf, &c) &&
		       c != '\\');
		if (getc(inf) == 'e' &&
		    getc(inf) == 'n' &&
		    getc(inf) == 'd' &&
		    getc(inf) == '{') {
		    i = 0;
		    while ((c=getc(inf)) != EOF &&
			   c != '}') {
			envtst[i++] = c;
			if (i >= MAXCMDLEN - 1) i--;
		    }
		    envtst[i] = 0;
		}
	    }
	    if (!noenv) printf(envtst);
	}
    }
    ungetc(c, inf);
    return(c);
}

