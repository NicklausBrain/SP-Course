#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#define print_type(type, min, max, specifier)\
	printf(\
		"\n%s \n\tsize: %lli \n\tmin: "#specifier"\n\tmax: "#specifier"\n",\
		#type,\
		sizeof(type),\
		min,\
		max);

int main(void) {
	print_type(bool, false, true, % hhi);

	print_type(char, CHAR_MIN, CHAR_MAX, %d);
	print_type(signed char, SCHAR_MIN, SCHAR_MAX, %hhi);
	print_type(unsigned char, 0, UCHAR_MAX, %hhu);

	print_type(short, SHRT_MIN, SHRT_MAX, %hi); // aka signed short
	print_type(unsigned short, 0, USHRT_MAX, %hu);

	print_type(int, INT_MIN, INT_MAX, %i); // aka signed int
	print_type(unsigned int, 0, UINT_MAX, %u);

	print_type(long, LONG_MIN, LONG_MAX, %li); // aka signed long
	print_type(unsigned long, 0, ULONG_MAX, %lu);

	print_type(long long, LLONG_MIN, LLONG_MAX, %lli); // aka long long int / signed long long
	print_type(unsigned long long, (unsigned long long)0, ULLONG_MAX, %llu);

	print_type(float, FLT_MIN, FLT_MAX, %f);

	print_type(double, DBL_MIN, DBL_MAX, %lf);

	print_type(long double, LDBL_MIN, LDBL_MAX, %Lf);
}
