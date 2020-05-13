#include "toy_stdio.h"


int main(int argc, char *argv[]) {
	toy_printf("Hex unsigned: %x\n", -1);
	toy_printf("Octal unsigned: %o\n", -1);
	toy_printf("Unsigned value: %u\n", 15);
	toy_printf("Unsigned value: %u\n", -15);
	int integers_array[] = {-1,-2,-3,-4,-5};
	char * strings_array[] = {"This", "is", "array", "of", "strings"};
	char c_arr[] = {'a','b','c','d','e'};
	int array_size = 5;
	toy_printf("Print array of integers: %Ad\n", integers_array, array_size);
	toy_printf("Print array of integers: %Au\n", integers_array, array_size);
	toy_printf("Print array of integers: %Ab\n", integers_array, array_size);
	toy_printf("Print array of integers: %Ao\n", integers_array, array_size);
	toy_printf("Print array of integers: %Ax\n", integers_array, array_size);
	toy_printf("Print array of integers: %AX\n", integers_array, array_size);
	toy_printf("Print array of strings: %As\n", strings_array, array_size);
	toy_printf("Print array of strings: %Ac\n", c_arr, array_size);
	toy_printf("Right-padded string: %6s\n", "str");
	toy_printf("Left-added string: %-6s\n", "str");
	toy_printf("With numeric placeholders: %05d\n%006d\n%007d\n%002d\n", -1, -1978,800,0);


}
