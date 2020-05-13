/* toy-io.c
 * Limited versions of printf and scanf
 *
 * Programmer: Mayer Goldberg, 2018
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* the states in the printf state-machine */


#define MAX_NUMBER_LENGTH 64
#define is_octal_char(ch) ('0' <= (ch) && (ch) <= '7')


int toy_printf(char *fs, ...);
int print_int_helper1(int n, int radix, const char *digit);
unsigned int print_int_helper(unsigned int n, int radix, const char *digit);
int print_int1(int n, int radix, const char * digit);
int print_int(int n, int radix, const char * digit);

const char *digit = "0123456789abcdef";
const char *DIGIT = "0123456789ABCDEF";

enum printf_state {
  st_printf_init=0,
  st_printf_percent=1,
  st_printf_octal2,
  st_printf_octal3
};



typedef struct  {
  int printed_chars;
  enum printf_state next_state;
}state_result;




typedef struct  {
  char* fs;
 enum printf_state state;
  int chars_printed;
  int int_value;
  char *string_value;
  char char_value;
  //char octal_char;
  int arr_length;
  int* int_arr;
  char** s_arr;
  char* c_arr;
  int left;
  int char_counter;
  int width_val;
  int str_len;
  int tmp_value;

}state_args;


void percent_char_handler(va_list args,int* out_printed_chars, state_args* state){
	state->state = st_printf_percent;
}

void another_handler(va_list args,int* out_printed_chars, state_args* state){
	putchar(*state->fs);
	++state->chars_printed;
}


state_result init_handler(va_list args,int* out_printed_chars, state_args* state){
 	
	void (*func_ptr_arr2[128])(va_list args,int* out_printed_chars, state_args* state);
	for(int i=0;i<128;i++){
		func_ptr_arr2[i]=another_handler;
	}
	func_ptr_arr2[37]=percent_char_handler;
	(*func_ptr_arr2[*state->fs])(state,out_printed_chars,state);
      
}

void percent2_handler(va_list args,int* out_printed_chars, state_args* state){
	putchar('%');
	++state->chars_printed;
	state->state = st_printf_init;
}


void d_handler(va_list args,int* out_printed_chars, state_args* state){
state->int_value = va_arg(args, int);
	state->chars_printed += print_int1(state->int_value, 10, digit);
	state->state = st_printf_init;
}


void u_handler(va_list args,int* out_printed_chars, state_args* state){
state->int_value = va_arg(args, int);
	state->chars_printed += print_int(state->int_value, 10, digit);
	state->state = st_printf_init;
}


void b_handler(va_list args,int* out_printed_chars, state_args* state){
state->int_value = va_arg(args, int);
	state->chars_printed += print_int(state->int_value, 2, digit);
	state->state = st_printf_init;
}


void o_handler(va_list args,int* out_printed_chars, state_args* state){
state->int_value = va_arg(args, int);
	state->chars_printed += print_int(state->int_value, 8, digit);
	state->state = st_printf_init;
}


void x_handler(va_list args,int* out_printed_chars, state_args* state){
state->int_value = va_arg(args, int);
	state->chars_printed += print_int(state->int_value, 16, digit);
	state->state = st_printf_init;
}


void X_handler(va_list args,int* out_printed_chars, state_args* state){
state->int_value = va_arg(args, int);
	state->chars_printed += print_int(state->int_value, 16, DIGIT);
	state->state = st_printf_init;
}


void s_handler(va_list args,int* out_printed_chars, state_args* state){
state->string_value = va_arg(args, char *);
	while(*state->string_value){
		state->chars_printed++;
		putchar(*state->string_value);
		state->string_value++;
	}
	state->state = st_printf_init;
}


void c_handler(va_list args,int* out_printed_chars, state_args* state){
state->char_value = (char)va_arg(args, int);
	putchar(state->char_value);
	++state->chars_printed;
	state->state = st_printf_init;
}







void Ad_handler(va_list args,int* out_printed_chars, state_args* state){
	toy_printf("{", *state->fs);
	  state->int_arr=va_arg(args, int*);
	  state->arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<state->arr_length ; i++){
	  	state->chars_printed += print_int1(state->int_arr[i], 10, digit);
	  	if(i<state->arr_length-1)
	  		toy_printf(", ", *state->fs);
	  }
	  toy_printf("}", *state->fs);
}


void Au_handler(va_list args,int* out_printed_chars, state_args* state){
state->int_arr=va_arg(args, int*);
	  toy_printf("{", *state->fs);
	  state->arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<state->arr_length ; i++){
	  	state->chars_printed += print_int(state->int_arr[i], 10, digit);
	  	if(i<state->arr_length-1)
	  		toy_printf(", ", *state->fs);
	  }
	  toy_printf("}", *state->fs);
}



void Ab_handler(va_list args,int* out_printed_chars, state_args* state){
toy_printf("{", *state->fs);
	  state->int_arr=va_arg(args, int*);
	  state->arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<state->arr_length ; i++){
	  	state->chars_printed += print_int(state->int_arr[i], 2, digit);
	  	if(i<state->arr_length-1)
	  		toy_printf(", ", *state->fs);
	  }
	  toy_printf("}", *state->fs);
}


void Ao_handler(va_list args,int* out_printed_chars, state_args* state){
toy_printf("{", *state->fs);
	  state->int_arr=va_arg(args, int*);
	  state->arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<state->arr_length ; i++){
	  	state->chars_printed += print_int(state->int_arr[i], 8, digit);
	  	if(i<state->arr_length-1)
	  		toy_printf(", ", *state->fs);
	  }
	  toy_printf("}", *state->fs);
}


void Ax_handler(va_list args,int* out_printed_chars, state_args* state){
toy_printf("{", *state->fs);
	  state->int_arr=va_arg(args, int*);
	  state->arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<state->arr_length ; i++){
	  	state->chars_printed += print_int(state->int_arr[i], 16, digit);
	  	if(i<state->arr_length-1)
	  		toy_printf(", ", *state->fs);
	  }
	  toy_printf("}", *state->fs);}


void AX_handler(va_list args,int* out_printed_chars, state_args* state){
  toy_printf("{", *state->fs);
	  state->int_arr=va_arg(args, int*);
	  state->arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<state->arr_length ; i++){
	  	state->chars_printed += print_int(state->int_arr[i], 16, digit);
	  	if(i<state->arr_length-1)
	  		toy_printf(", ", *state->fs);
	  }
	  toy_printf("}", *state->fs);
}


void As_handler(va_list args,int* out_printed_chars, state_args* state){
toy_printf("{", *state->fs);
	  state->s_arr=va_arg(args, char**);
	  state->arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<state->arr_length ; i++){
		toy_printf("\"");
	  	state->chars_printed += toy_printf(state->s_arr[i]);
		toy_printf("\"");
	  	if(i<state->arr_length-1)
	  		toy_printf(", ", *state->fs);
	  }
	  toy_printf("}", *state->fs);
}


void Ac_handler(va_list args,int* out_printed_chars, state_args* state){
toy_printf("{", *state->fs);
	  state->c_arr=va_arg(args, char*);
	  state->arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<state->arr_length ; i++){
		toy_printf("'");
		putchar(state->c_arr[i]);
		toy_printf("'");
		++state->chars_printed;
	  	if(i<state->arr_length-1)
	  		toy_printf(", ", *state->fs);
	  }
	  toy_printf("}", *state->fs);
}


void another_A_handler(va_list args,int* out_printed_chars, state_args* state){
toy_printf("Unhandled format %%A%c...\n", *state->fs);
	  exit(-1);
}














void A_handler(va_list args,int* out_printed_chars, state_args* state){

	if(*state->fs != '\0')
	 ++state->fs;
 	void (*func_ptr_arr3[128])(va_list args,int* out_printed_chars, state_args* state);
		for(int i=0;i<128;i++){
			func_ptr_arr3[i]=another_A_handler;
		}	
		func_ptr_arr3[100]=Ad_handler;
		func_ptr_arr3[98]=Ab_handler;
		func_ptr_arr3[111]=Ao_handler;
		func_ptr_arr3[88]=AX_handler;
		func_ptr_arr3[120]=AX_handler;
		func_ptr_arr3[115]=As_handler;
		func_ptr_arr3[99]=Ac_handler;
		func_ptr_arr3[117]=Au_handler;
		func_ptr_arr3[65]=AX_handler;
		(*func_ptr_arr3[*state->fs])(args,out_printed_chars,state);
	++state->chars_printed;
	state->state = st_printf_init;
	
}





void another2d_handler(va_list args,int* out_printed_chars, state_args* state){
state->int_value = va_arg(args, int);
			  if(state->int_value==0)
				++state->str_len;
			  else{
				  state->tmp_value=state->int_value;
	 			  if(state->int_value<0){
					++state->str_len;
					putchar('-');
					++state->chars_printed;
				  }
				  while(state->tmp_value!=0){
					state->tmp_value /= 10;
					++state->str_len;
				  }
			  }
			  for (int i = 0; i<(state->width_val-state->str_len); ++i) {
					toy_printf("0");
					++state->chars_printed;
					
				}
			  state->int_value=abs(state->int_value);
			  state->chars_printed += print_int1(state->int_value, 10, digit);
		 	  state->state = st_printf_init;
			  state->left = 0;
 			  state->char_counter=0;
			  state->width_val=0;
  			  state->str_len=0;
 			  state->tmp_value=0; 
}




void another2s_handler(va_list args,int* out_printed_chars, state_args* state){
state->string_value = va_arg(args, char *);
			state->str_len=strlen(state->string_value);
			if(state->left){
				for (int i = 0; i<(state->width_val-state->str_len); ++i) {
					toy_printf(" ");
					++state->chars_printed;
					
				}
				
				while(*state->string_value){
					state->chars_printed++;
					putchar(*state->string_value);
					state->string_value++;
				}
			state->state = st_printf_init;
			state->left = 0;
  			state->char_counter=0;
  			state->width_val=0;
			state->str_len=0;
			}
			else{
				while(*state->string_value){
					state->chars_printed++;
					putchar(*state->string_value);
					state->string_value++;
				}
				
				for (int i = 0; i<state->width_val-state->str_len; ++i) {
					toy_printf(" ");
					++state->chars_printed;
				}
				toy_printf("#");
		
			state->state = st_printf_init;
			state->left = 0;
  			state->char_counter=0;
  			state->width_val=0;
			state->str_len=0;
			}
}

void another2_another_handler(va_list args,int* out_printed_chars, state_args* state){
	toy_printf("Unhandled format");
	exit(-1);
}


void another2_handler(va_list args,int* out_printed_chars, state_args* state){

	if(*state->fs=='-'){
		state->left=1;
		++state->fs;
	}
	if(isdigit(*state->fs)){
		for (; isdigit(*state->fs); ++state->fs) {
			++state->char_counter;
		}
		char num_arr[state->char_counter+1];
		state->fs=state->fs-state->char_counter;
		for (int i = 0; i<state->char_counter; ++i) {
			num_arr[i]=*state->fs;
			if(i != state->char_counter-1)
			++state->fs;
		}
		num_arr[state->char_counter]='\0';
		state->width_val = atoi(num_arr);
		
		if(*state->fs=='\0'){
			toy_printf("Unhandled format", *state->fs);
			exit(-1);
		}else ++state->fs;
		



		void (*func_ptr_arr4[128])(va_list args,int* out_printed_chars, state_args* state);
		for(int i=0;i<128;i++){
			func_ptr_arr4[i]=another2_another_handler;
		}	
		func_ptr_arr4[100]=another2d_handler;
		func_ptr_arr4[115]=another2s_handler;

		(*func_ptr_arr4[*state->fs])(args,out_printed_chars,state);

	}
	

	else{
	toy_printf("Unhandled format %%%c...\n", *state->fs);
	exit(-1);
	}
}





state_result percent_handler(va_list args,int* out_printed_chars, state_args* state){
	void (*func_ptr_arr2[128])(va_list args,int* out_printed_chars, state_args* state);
		for(int i=0;i<128;i++){
			func_ptr_arr2[i]=another2_handler;
		}
		func_ptr_arr2[37]=percent2_handler;		
		func_ptr_arr2[100]=d_handler;
		func_ptr_arr2[98]=b_handler;
		func_ptr_arr2[111]=o_handler;
		func_ptr_arr2[88]=X_handler;
		func_ptr_arr2[120]=X_handler;
		func_ptr_arr2[115]=s_handler;
		func_ptr_arr2[99]=c_handler;
		func_ptr_arr2[117]=u_handler;
		func_ptr_arr2[65]=A_handler;
		(*func_ptr_arr2[*state->fs])(args,out_printed_chars,state);

}











int print_int_helper1(int n, int radix, const char *digit) {
  int result;

  if (n < radix) {
    putchar(digit[n]);
    return 1;
  }
  else {
    result = print_int_helper(n / radix, radix, digit);
    putchar(digit[n % radix]);
    return 1 + result;
  }
}

unsigned int print_int_helper(unsigned int n, int radix, const char *digit) {
  	int result;
	
	

  if (n < radix) {
    putchar(digit[n]);
    return 1;
  }
  else {
    result = print_int_helper(n / radix, radix, digit);
    putchar(digit[n % radix]);
    return 1 + result;
  }
}

int print_int1(int n, int radix, const char * digit) {
  if (radix < 2 || radix > 16) {
    toy_printf("Radix must be in [2..16]: Not %d\n", radix);
    exit(-1);
  }

  if (n > 0) {
    return print_int_helper1(n, radix, digit);
  }
  if (n == 0) {
    putchar('0');
    return 1;
  }
  else {
    putchar('-');
    return 1 + print_int_helper1(-n, radix, digit);
  }
}


int print_int(int n, int radix, const char * digit) {
  if (radix < 2 || radix > 16) {
    toy_printf("Radix must be in [2..16]: Not %d\n", radix);
    exit(-1);
  }

  if (n > 0) {
    return print_int_helper(n, radix, digit);
  }
  if (n == 0) {
    putchar('0');
    return 1;
  }
  else {
	unsigned int tmp;
  	tmp = n;
    return print_int_helper(tmp, radix, digit);
  }
}

/* SUPPORTED:
 *   %b, %d, %o, %x, %X -- 
 *     integers in binary, decimal, octal, hex, and HEX
 *   %s -- strings
 */

/* SUPPORTED:
 *   %b, %d, %o, %x, %X -- 
 *     integers in binary, decimal, octal, hex, and HEX
 *   %s -- strings
 */

int toy_printf(char *fs, ...) {
  state_args* state_a=malloc(sizeof(state_args));
  va_list args;
  state_a->fs=fs;
  state_a->chars_printed = 0;
  state_a->int_value = 0;
  state_a->arr_length = 0;
  state_a->left = 0;
  state_a->char_counter=0;
  state_a->width_val=0;
  state_a->str_len=0;
  state_a->tmp_value=0;	
  state_result (*func_ptr_arr[])(va_list args,int* out_printed_chars, state_args* state)={init_handler,percent_handler};
  state_result* sr=malloc(sizeof(state_result));;
  int* out_printed_chars;
  va_start(args, state_a->fs);
  state_a->state = st_printf_init; 
 

  for (; *state_a->fs != '\0'; ++state_a->fs) {
	 
	(*sr)=(*func_ptr_arr[state_a->state])(args,out_printed_chars,state_a);
	
  }

  va_end(args);
  free(state_a);
  free(sr);
  return state_a->chars_printed;
  
}


