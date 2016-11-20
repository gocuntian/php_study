#include <stdarg.h>
#include <stdio.h>

int zend_parse_parameters(int num_args,const char *type_spec,...);

int main(){
	zend_parse_parameters(4,"abcde",1,2,3,4,5);
	return 0;
}
int zend_parse_parameters(int num_args,const char *type_spec,...){
	va_list va;
	const char *spec_walk;
	char c;
	
	va_start(va,type_spec);
	for (spec_walk = type_spec;*spec_walk;spec_walk++){
           c=*spec_walk;
	   printf("参数类型为 %c 值为: %d\n",c,va_arg(va,int));
	}
	va_end(va);
	return 0;
}
