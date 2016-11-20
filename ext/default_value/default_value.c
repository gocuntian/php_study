/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_default_value.h"

/* If you declare any globals in php_default_value.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(default_value)
*/

/* True global resources - no need for thread safety here */
static int le_default_value;


PHP_MINIT_FUNCTION(default_value)
{
	return SUCCESS;
}
PHP_MSHUTDOWN_FUNCTION(default_value)
{
	return SUCCESS;
}
PHP_RINIT_FUNCTION(default_value)
{
#if defined(COMPILE_DL_DEFAULT_VALUE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
PHP_RSHUTDOWN_FUNCTION(default_value)
{
	return SUCCESS;
}
PHP_MINFO_FUNCTION(default_value)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "default_value support", "enabled");
	php_info_print_table_end();

}


const zend_function_entry default_value_functions[] = {
	PHP_FE(xingcuntian_type,	NULL)	
	PHP_FE_END	
};

PHP_FUNCTION(xingcuntian_type){
    zend_string *type;
    zval        *value=NULL;
#ifndef FAST_ZPP
     if(zend_parse_parameters(ZEND_NUM_ARGS(),"S|z",&type,&value)==FAILURE){
              return;
     }
#else
    ZEND_PARSE_PARAMETERS_START(1,2)
      Z_PARAM_STR(type)
      Z_PARAM_OPTIONAL
      Z_PARAM_ZVAL_EX(value,0,1)
    ZEND_PARSE_PARAMETERS_END();
#endif
   if(ZSTR_LEN(type) == 3&& strncmp(ZSTR_VAL(type),"int",3)==0&& value ==NULL){
    RETURN_LONG(0);
}else if(ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type),"int",3)==0 && value!=NULL){
    RETURN_ZVAL(value,0,1);
}else if(ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type),"bool",4) ==0 && value==NULL){
   RETURN_FALSE;
}else if(ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type),"bool",4) ==0 && value !=NULL){
   RETURN_ZVAL(value,0,1);
}else if(ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type),"str",3) == 0 && value ==NULL){
   RETURN_EMPTY_STRING();
}else if(ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type),"str",3) == 0 && value !=NULL){
   RETURN_ZVAL(value,0,1);
}
RETURN_NULL();

}
zend_module_entry default_value_module_entry = {
	STANDARD_MODULE_HEADER,
	"default_value",
	default_value_functions,
	PHP_MINIT(default_value),
	PHP_MSHUTDOWN(default_value),
	PHP_RINIT(default_value),	
	PHP_RSHUTDOWN(default_value),	
	PHP_MINFO(default_value),
	PHP_DEFAULT_VALUE_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DEFAULT_VALUE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(default_value)
#endif

