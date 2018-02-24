/* Copyright (C) 2011-2012 SBA Research gGmbh

   This file is part of the Slibc Library.

   The Slibc Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The Slibc library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the Slibc Library; if not, see
   <http://www.gnu.org/licenses/>.  
*/
unsigned num_digits(unsigned int n)
{
    if (n < 10) return 1;
    return 1 + num_digits(n / 10);
}




#include <limits.h>

/* Determine whether we have to handle `long long' at all.  */
#if LONG_MAX == LONG_LONG_MAX
# define need_longlong	0
#else
# define need_longlong	1
#endif

/* Determine whether we have to handle `long'.  */
#if INT_MAX == LONG_MAX
# define need_long	0
#else
# define need_long	1
#endif


#ifdef COMPILE_WSCANF
// we have no wide char support at the moment
#else
#include <ctype.h>
# define ISSPACE(Ch)	  isspace(Ch)
# define ISDIGIT(Ch)	  isdigit(Ch)
# define ISXDIGIT(Ch)	  isxdigit(Ch)
# define TOLOWER(Ch)	  tolower(Ch)
# define L_(Str)	Str
# define CHAR_T		char
# define UCHAR_T	unsigned char
# define WINT_T		int
#endif


/* Those are flags in the conversion format. */
#define LONG		0x0001	/* l: long or double */
#define LONGDBL		0x0002	/* L: long long or long double */
#define SHORT		0x0004	/* h: short */
#define SUPPRESS	0x0008	/* *: suppress assignment */
#define POINTER		0x0010	/* weird %p pointer (`fake hex') */
#define NOSKIP		0x0020	/* do not skip blanks */
#define NUMBER_SIGNED	0x0040	/* signed integer */
#define GROUP		0x0080	/* ': group numbers */
#define GNU_MALLOC	0x0100	/* a: malloc strings */
#define CHAR		0x0200	/* hh: char */
#define I18N		0x0400	/* I: use locale's digits */
#define HEXA_FLOAT	0x0800	/* hexadecimal float */
#define READ_POINTER	0x1000	/* this is a pointer value */
#define POSIX_MALLOC	0x2000	/* m: malloc strings */


// A SCANF_CONV_SPEC begins with a % and has the following format
// (%|%n$) [flags] [width] [type_modifier] conversion_specifier
// where [] means optional and | or
typedef struct 
{
	unsigned str_beg; /// the beginning of this conversion specification in the buffer parsed
	unsigned str_end; /// the end of this conversion specification in the buffer parsed
	int argpos; /// 0 if no argpos was given
	int flags;  /// a combination of the above defines
	int width;  /// -1 if no width was specified
	char type_modifier;  /// for example l for long
	char conv_specifier; /// for example s for a string, d for an int
	char *char_class;   /// something as [aaa], must be free'ed if non-null
} SCANF_CONV_SPEC;


inline int is_string_conversion(const SCANF_CONV_SPEC *spec)
{
	return (spec->conv_specifier == 'c' ||
			spec->conv_specifier == 's' ||
			spec->conv_specifier == '[' ||
			spec->conv_specifier == 'C' || // This is an alias for ‘%lc’ 
			spec->conv_specifier == 'S' // This is an alias for ‘%ls’ 
		);
}

// is this a null terminated string conversion?
inline int is_nt_string_conversion(const SCANF_CONV_SPEC *spec)
{
	return (
			spec->conv_specifier == 's' ||
			spec->conv_specifier == '[' ||
			spec->conv_specifier == 'S' // This is an alias for ‘%ls’ 
		);
}

// returns number of chars written
size_t print_conv_spec(char *buf, rsize_t buf_max, const SCANF_CONV_SPEC *spec)
{
	size_t ind = 0;
		
	if (spec->argpos)
	{
		buf[ind++] = '%';
		int ret = snprintf(buf+ind, buf_max - ind, "%d", spec->argpos); 
		if (ret < 0)
			return ind; 
		ind += ret;
		buf[ind++] = '$';
	}
	else
		buf[ind] = '%';

	// we don't have to do anything for flags

	//now the width
	if (spec->width > -1)
	{
		ind += snprintf(buf+ind, buf_max - ind, "%d", spec->width); 
	}

	if (spec->type_modifier)
		buf[ind++] = spec->type_modifier;

	if (spec->conv_specifier == '[')
	{
//		assert(spec->char_class);
		ind += snprintf(buf+ind, buf_max - ind, "%s", spec->char_class); 
	}
	else
		buf[ind++] = spec->conv_specifier;

	return ind;
}


///////////////////////////////
///	  This function extracts the conversion specifications from a scanf-format string.
///
///	  The caller needs to free conv_spec. 
///
///	  @param [in]   format         the format string
///	  @param [out]  num_conv_spec  the number of elements in conv_spec
///	  @param [out]  conv_spec      a list of conversion specifier elements
///
///	  @return 0 on success
///////////////////////////////
errno_t parse_scanf_format_string(const char * restrict format, 
								  size_t *num_conv_spec,
								  SCANF_CONV_SPEC **conv_spec)
{
	const char *f = format;

	if (!format || !num_conv_spec || !conv_spec)
		return -1;

	*num_conv_spec = 0;

	// quick check to find out how much maximum memory we will need
	unsigned max_num_spec = 0;
	while (*f != '\0')
    {
		if (*f == '%')
			max_num_spec++;
		f++;
	}
	// allocate the entire array
	*conv_spec = calloc(max_num_spec, sizeof(SCANF_CONV_SPEC));
	if (! conv_spec)
		return ENOMEM;

	// now parse the format string
	f = format;
	while (*f != '\0')
    {
		if (*f++ != '%')
			continue;

		//start of a conversion string
		unsigned str_beg = f -1 - format;
		int flags = 0;
		int argpos = 0;
		int width = 0;
		char type_modifier = '\0';

        /* Check for a positional parameter specification.  */
		if (ISDIGIT ((UCHAR_T) *f))
		{
			argpos = (UCHAR_T) *f++ - L_('0');
			while (ISDIGIT ((UCHAR_T) *f))
				argpos = argpos * 10 + ((UCHAR_T) *f++ - L_('0'));
			if (*f == L_('$'))
				++f;
			else
			{
				/* Oops; that was actually the field width.  */
				width = argpos;
				argpos = 0;
				goto got_width;
			}
		}

		/* Check for the assignment-suppressing, the number grouping flag,
		   and the signal to use the locale's digit representation.  */
		while (*f == L_('*') || *f == L_('\'') || *f == L_('I'))
			switch (*f++)
			{
			case L_('*'):
				flags |= SUPPRESS;
				break;
/* 				case L_('\''): */
/* #ifdef COMPILE_WSCANF */
/* 					if (thousands != L'\0') */
/* #else */
/* 						if (thousands != NULL) */
/* #endif */
/* 							flags |= GROUP; */
/* 					break; */
/* 				case L_('I'): */
/* 					flags |= I18N; */
/* 					break; */
			}

		/* Find the maximum field width.  */
		width = 0;
		while (ISDIGIT ((UCHAR_T) *f))
		{
			width *= 10;
			width += (UCHAR_T) *f++ - L_('0');
		}
	got_width:
		if (width == 0)
			width = -1;
		
		/* Check for type modifiers.  */
		type_modifier = *f++;
		switch (type_modifier)
		{
		case L_('h'):
			/* ints are short ints or chars.  */
			if (*f == L_('h'))
			{
				++f;
				flags |= CHAR;
			}
			else
				flags |= SHORT;
			break;
		case L_('l'):
			if (*f == L_('l'))
			{
				/* A double `l' is equivalent to an `L'.  */
				++f;
				flags |= LONGDBL | LONG;
			}
			else
				/* ints are long ints.  */
				flags |= LONG;
			break;
		case L_('q'):
		case L_('L'):
			/* doubles are long doubles, and ints are long long ints.  */
			flags |= LONGDBL | LONG;
			break;
		case L_('a'):
			/* The `a' is used as a flag only if followed by `s', `S' or
			   `['.  */
			if (*f != L_('s') && *f != L_('S') && *f != L_('['))
			{
				--f;
				break;
			}
			/* In __isoc99_*scanf %as, %aS and %a[ extension is not
			   supported at all.  */
			// we do not support the a flag
			if (1) // s->_flags2 & _IO_FLAGS2_SCANF_STD)
			{
				--f;
				break;
			}
			/* String conversions (%s, %[) take a `char **'
			   arg and fill it in with a malloc'd pointer.  */
			flags |= GNU_MALLOC;
			break;
		case L_('m'):
			flags |= POSIX_MALLOC;
			if (*f == L_('l'))
			{
				++f;
				flags |= LONG;
			}
			break;
		case L_('z'):
			if (need_longlong && sizeof (size_t) > sizeof (unsigned long int))
				flags |= LONGDBL;
			else if (sizeof (size_t) > sizeof (unsigned int))
				flags |= LONG;
			break;
		case L_('j'):
			if (need_longlong && sizeof (uintmax_t) > sizeof (unsigned long int))
				flags |= LONGDBL;
			else if (sizeof (uintmax_t) > sizeof (unsigned int))
				flags |= LONG;
			break;
		case L_('t'):
			if (need_longlong && sizeof (ptrdiff_t) > sizeof (long int))
				flags |= LONGDBL;
			else if (sizeof (ptrdiff_t) > sizeof (int))
				flags |= LONG;
			break;
		default:
			/* Not a recognized modifier.  Backup.  */
			type_modifier = '\0';
			--f;
			break;
		}

		/* End of the format string?  */
		if (__builtin_expect (*f == L_('\0'), 0))
			return -1;

		/* Find the conversion specifier.  */		
		UCHAR_T fc;
		fc = *f++;

		switch (fc)
		{
		case L_('%'):	/* Must match a literal '%'.  */
			break;
		case L_('n'):  			/* FALLTHROUGH FOR THE REST */

		case L_('c'):	/* Match characters.  */
		case L_('C'):
		case L_('s'):		/* Read a string.  */
		case L_('S'):
		case L_('x'):	/* Hexadecimal integer.  */
		case L_('X'):	/* Ditto.  */
		case L_('o'):	/* Octal integer.  */
		case L_('u'):	/* Unsigned decimal integer.  */
		case L_('d'):	/* Signed decimal integer.  */
		case L_('i'):	/* Generic number.  */
		case L_('e'):	/* Floating-point numbers.  */
		case L_('E'):
		case L_('f'):
		case L_('F'):
		case L_('g'):
		case L_('G'):
		case L_('a'):
		case L_('A'):
		case L_('['):	/* Character class.  */
		case L_('p'):	/* Generic pointer.  */
		{
			SCANF_CONV_SPEC *spec;
			spec = &( (*conv_spec)[(*num_conv_spec)++] );

			if (fc == '[')
			{
				// character classed need special handling
				// we search for the terminating ]
				// and store the set chars in char_class
				const char *beg = f - 1;

				if (*f == L']')
					++f;

				while ((fc = *f++) != L'\0' && fc != L']');

				if (__builtin_expect (fc == L'\0', 0))
					return -1;

				// change it back
				fc = '[';
				size_t charclass_sz = f - beg;
				spec->char_class = malloc(sizeof(char) * charclass_sz + 1);
				strncpy(spec->char_class, beg, charclass_sz);
				spec->char_class[charclass_sz] = '\0';
				printf("stored charclass is %s.\n", spec->char_class);
			}

			spec->str_beg = str_beg;
			spec->str_end = (f-1 - format);
			spec->argpos = argpos;
			spec->flags = flags;
			spec->width = width;
			spec->type_modifier = type_modifier;
			spec->conv_specifier = fc;

			break;
		}
		default:
			/* If this is an unknown format character punt.  */
			return -1;
		}		
	} // while (*f != '\0')

	// success

	return 0;
}

//////////////////////////////////////////////////////////////////////
/// Not fully working implementation of vfscanf_s.
///
/// The idea of this function was to let the real vfscanf do most of the
/// work and to only rewrite the format string that we pass to vfscanf in
/// the following ways:
/// 1) so that is uses Glibc's extended positional parameters
/// 2) format width specifiers for all strings to enforce the buffer size
///
/// This implementation is in the follwing state:
/// The parsing works well.
/// But the design of this function was built on the assumption that 
/// format width specifiers and _s buffer-len are equivalent.
/// This is not the case. See: http://msdn.microsoft.com/de-de/library/xdb9w69d%28v=vs.80%29.aspx
/// Consider the following example:  
///   int n; char s[5];
///   sscanf_s("hello", "%s", s, sizeof(s));
/// This should result in a matching failure because s does not have space for hello + 0-byte.
/// Thus, the return value should be 0.
/// However, 
///   sscanf("hello", "%4s", s);
/// results in a match of 4 characters. Return value is 1.
/// Additionally, scanf is supposed to stop reading as soon as a matching failure occurrs.
///
/// My idea then was to call the original scanf several times:
/// Once after each %s so that we could test whether there should be a matching failure.
/// However this does not work so well. %n specification are broken then of course.
/// There could also be other side effects of
/// calling scanf multiple times. I'm also not so sure at the moment how to handle
/// return values (EOF, 0, etc.).
///
/// That's why development here stopped. And we simply used glib'c original function.
int vfscanf_s(FILE * restrict stream,
			  const char * restrict format, va_list arg)
{
	int ret = 0;

	if(stream == NULL || format == NULL || arg == NULL)
	{
		RUNTIME_CONSTRAINT_HANDLER();
		return EOF;
	}
	if(!stream || !format || !arg)
	{
		RUNTIME_CONSTRAINT_HANDLER();
		return EOF;
	}

	va_list ap;
	va_copy(ap, arg);	

	SCANF_CONV_SPEC *conv_spec = NULL;
	size_t num_conv_spec;
	if (parse_scanf_format_string(format, &num_conv_spec, &conv_spec))
	{
		// not a valid scanf string.
		return EOF;
	}


	// Let us calculate how much space we require for storing the
	// new format string
	size_t new_sz = 0;
	size_t i;
	for(i = 0; i < num_conv_spec; i++)
	{
		new_sz += num_digits(i); //for each digit in the gnu positional para
		if (is_string_conversion(conv_spec+i))
			new_sz += num_digits(INT_MAX); // we will add a width
	}
	new_sz += num_conv_spec; // for the $ sign
	new_sz += strlen(format);
	new_sz += 1; // the trailing zero

	char *new_format_str = malloc(new_sz);
	size_t ind = 0;
	size_t gnu_pos_param = 1;
	const char *f = format;
	size_t round_beginning = 0;

	if (num_conv_spec == 0)
		strcpy(new_format_str, format);

	for(i = 0; i < num_conv_spec; i++)
	{
		// we simply copy all characters from the old format string 
        // that are no conversion specifiers
		while(ind < conv_spec[i].str_beg)
		{
			new_format_str[ind++] = *f++;
		}

		if (conv_spec[i].flags & SUPPRESS)
		{
			// there is no corrsponding variable argument
			continue;
		}

		// now we have a conversion specifier
		// we need to rewrite it

		// get the correspoinding argument of our variable argument list
		// all arguments given should be pointers
		void *p = va_arg(ap, void*); 
		rsize_t nmemb = 0;

		if (p == NULL)
		{
			RUNTIME_CONSTRAINT_HANDLER();
			return EOF;
		}

		// it is an error if the format-string already contains
		// gnu positional parameters
		if (conv_spec[i].argpos !=0 )
		{
			return EOF;
		}
		// we want gnu positional parameter in the form of %n$
		conv_spec[i].argpos = gnu_pos_param++;

		if (is_string_conversion(conv_spec+i))
		{
			nmemb = va_arg(ap, rsize_t);
			//todo: check whether
			((char*)p)[nmemb-1] = '\0';

//			if (nmemb > 0)
//				nmemb--; //the flag width excludes the null byte

			// skip the size argument because scanf does not know expect it
			gnu_pos_param++; 

			if (conv_spec[i].width > -1)
			{
				// we already have a width specification
				conv_spec[i].width = MIN(conv_spec[i].width, nmemb);
			}
			else
				conv_spec[i].width = nmemb;
		}

		ind += print_conv_spec(new_format_str+ind, new_sz - ind, conv_spec + i);
		f += (conv_spec[i].str_end + 1 - conv_spec[i].str_beg);

		// after every [ and s we call vfscanf 
		// 
		if (is_nt_string_conversion(conv_spec+i))
		{
			// temporarily, end the format string here
			new_format_str[ind] = '\0';
			int r = vfscanf(stream, new_format_str + round_beginning, arg);
			if (((char*)p)[nmemb-1] != '\0')
			{
				// should be a matching failure
				if (r > 0)
					r--;
			}
			if (r == EOF)
			{
				if (round_beginning == 0)
					return EOF;
				else if (ferror(stream))
					return EOF;
				else
					return ret; // not sure if we need this line.
			} 
			else if (r == 0)
			{
				// well if nothing was matched we can home.
				return ret;
			}
			ret += r;
			round_beginning = ind;
		}
	}
	// in case the format string does not end with a conversion spec
	// we have to copy the rest of the string
	while(*f)
		new_format_str[ind++] = *f++;
	new_format_str[ind] = '\0';

	for(i = 0; i < num_conv_spec; i++)
		free(conv_spec[i].char_class);

	free(conv_spec);
	va_end(ap);
	printf("\nold format string: %s\n\n new format string:%s\n", format, new_format_str);

	int r = vfscanf(stream, new_format_str + round_beginning, arg);
	if (r == EOF)
		ret = EOF;
	else
		ret += r;

	free(new_format_str);
	return ret;
}
