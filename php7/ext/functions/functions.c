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
#include "php_functions.h"

/* If you declare any globals in php_functions.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(functions)
*/

/* True global resources - no need for thread safety here */
static int le_functions;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("functions.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_functions_globals, functions_globals)
    STD_PHP_INI_ENTRY("functions.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_functions_globals, functions_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_functions_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_functions_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "functions", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string self_concat(string str, int n)
    */
PHP_FUNCTION(self_concat)
{
	char *str = NULL;
	int argc = ZEND_NUM_ARGS();
	size_t str_len;
	zend_long n;
        char *result=NULL;
 	char *ptr=NULL;        
   #ifndef FAST_ZPP
	if (zend_parse_parameters(argc, "sl", &str, &str_len, &n) == FAILURE) 
		return;
   #else
	ZEND_PARSE_PARAMETERS_START(2,2)
		Z_PARAM_STRING(str,str_len)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
   #endif
	result=(char *)ecalloc(str_len * n+1,sizeof(char));
	ptr = result;
        while(n--){
            memcpy(ptr,str,str_len);
	ptr+=str_len;
	}

        *ptr='\0';
 	RETURN_STRING(result);
}


PHP_FUNCTION(str_concat){
   zend_string *prefix,*subject,*result;
   zval *string;
   if(zend_parse_parameters(ZEND_NUM_ARGS(),"Sz",&prefix,&string)== FAILURE){
      return;
   }
   //提供了zval到zend_string的转换
    subject = zval_get_string(string);
    if (zend_binary_strncmp(ZSTR_VAL(prefix), ZSTR_LEN(prefix), ZSTR_VAL(subject), ZSTR_LEN(subject), ZSTR_LEN(prefix)) == 0) {
        RETURN_STR(subject); 
    } 
   //内存操作，拼接两个zend_string
    result = zend_string_extend(prefix, ZSTR_LEN(prefix)+ZSTR_LEN(subject)+2, 0); 
    ZSTR_VAL(result)[ZSTR_LEN(prefix)+1] = ' ';
    memcpy(ZSTR_VAL(result)+ZSTR_LEN(prefix)+2, ZSTR_VAL(subject), ZSTR_LEN(subject));
    RETURN_STR(result);
}

PHP_FUNCTION(default_value)
{
    zend_string     *type;    
    zval            *value = NULL;

#ifndef FAST_ZPP
    /* Get function parameters and do error-checking. */
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S|z", &type, &value) == FAILURE) {
        return;
    }    
#else
    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STR(type)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL_EX(value, 0, 1)
    ZEND_PARSE_PARAMETERS_END();
#endif

    if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "int", 3) == 0 && value == NULL) {
        RETURN_LONG(0);
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "int", 3) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1); 
    } else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value == NULL) {
        RETURN_FALSE;
    } else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1); 
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "str", 3) == 0 && value == NULL) {
        RETURN_EMPTY_STRING();
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "str", 3) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1); 
    } 
    RETURN_NULL();
}

PHP_FUNCTION(get_size)
{
   zval *val;
   size_t size;
   char *result;
   HashTable *myht;
  if(zend_parse_parameters(ZEND_NUM_ARGS(),"z",&val) == FAILURE){
       return;
  }
  result = emalloc(1024);
  if (Z_TYPE_P(val) == IS_STRING){
       size = php_sprintf(result,"string size is %d\n",Z_STRLEN_P(val));
  }else if(Z_TYPE_P(val) == IS_ARRAY){
     myht = Z_ARRVAL_P(val);
     size = php_sprintf(result,"array size is %d\n",zend_array_count(myht));
  }else{
     size = php_sprintf(result,"can not support");
  }
  RETVAL_STRINGL(result,size);
  efree(result);
}

PHP_FUNCTION(get_cur_client_ip){
 zval *server, *field;
    zend_string *ip = NULL;

    server = zend_hash_str_find(&EG(symbol_table), "_SERVER", sizeof("_SERVER") - 1);
    if (Z_TYPE_P(server) == IS_ARRAY) {
        if ((field= zend_hash_str_find(Z_ARRVAL_P(server), "HTTP_CLIENT_IP", sizeof("HTTP_CLIENT_IP") - 1)) &&
                Z_TYPE_P(field) == IS_STRING) {
            ip = Z_STR_P(field);
        } else if ((field = zend_hash_str_find(Z_ARRVAL_P(server), "HTTP_X_FORWARDED_FOR", sizeof("HTTP_X_FORWARDED_FOR") - 1)) &&
                Z_TYPE_P(field) == IS_STRING) {
            ip = Z_STR_P(field);
        } else if ((field = zend_hash_str_find(Z_ARRVAL_P(server), "REMOTE_ADDR", sizeof("REMOTE_ADDR") - 1)) &&
                Z_TYPE_P(field) == IS_STRING) {
            ip = Z_STR_P(field);
        }
    } 
    if (ip) {
        zend_string_copy(ip);
    } else {
        ip = zend_string_init("0.0.0.0", sizeof("0.0.0.0") - 1, 0);  // 默认值
    }
 RETURN_STR(ip);
}

/* }}} */


/* {{{ php_functions_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_functions_init_globals(zend_functions_globals *functions_globals)
{
	functions_globals->global_value = 0;
	functions_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(functions)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(functions)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(functions)
{
#if defined(COMPILE_DL_FUNCTIONS) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(functions)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(functions)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "functions support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ functions_functions[]
 *
 * Every user visible function must have an entry in functions_functions[].
 */
const zend_function_entry functions_functions[] = {
	PHP_FE(confirm_functions_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(self_concat,	NULL)
	PHP_FE(str_concat,	NULL)
        PHP_FE(get_size,	NULL)
        PHP_FE(default_value,	NULL)
     //   PHP_FE(get_cur_client_ip,	NULL)
	PHP_FE_END	/* Must be the last line in functions_functions[] */
};
/* }}} */

/* {{{ functions_module_entry
 */
zend_module_entry functions_module_entry = {
	STANDARD_MODULE_HEADER,
	"functions",
	functions_functions,
	PHP_MINIT(functions),
	PHP_MSHUTDOWN(functions),
	PHP_RINIT(functions),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(functions),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(functions),
	PHP_FUNCTIONS_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FUNCTIONS
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(functions)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
