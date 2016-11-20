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
#include "php_udf.h"
#include "php_adf.h"
#include "php_play.h"
#include <zend_interfaces.h>
/* If you declare any globals in php_udf.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(udf)
*/
zend_class_entry *udf_ce;

/* True global resources - no need for thread safety here */
static int le_udf;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("udf.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_udf_globals, udf_globals)
    STD_PHP_INI_ENTRY("udf.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_udf_globals, udf_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_udf_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_udf_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "udf", arg);

	RETURN_STR(strg);
}
/* }}} */

ZEND_METHOD(udf,__construct){

	RETURN_NULL();
}

ZEND_METHOD(udf,get){

        /**
	zend_class_entry * pdo_class_entry;
	pdo_class_entry = zend_fetch_class(zend_string_init("PDO", sizeof("PDO") - 1, 0), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);

	zval * pdo_new_ce;
	object_init_ex(pdo_new_ce, pdo_class_entry);

	zval function_name;
	ZVAL_STRING(&function_name,"__construct");

	zval dsn;
	ZVAL_STRING(&dsn,"mysql:dbname=test;host=127.0.0.1;port=3306");
	

	zval user;
	ZVAL_STRING(&user,"root");
	
	
	zval pwd;
	ZVAL_STRING(&pwd,"123456");
	
	zval ret;
	int param_count=2;

	zval *params[param_count];
	params[0]=&dsn;
	params[1]=&user;
	params[2]=&pwd;


	//ZEND_API zval* zend_call_method(zval **object_pp, zend_class_entry *obj_ce, zend_function **fn_proxy, char *function_name, int function_name_len, zval **retval_ptr_ptr, int param_count, zval* arg1, zval* arg2 TSRMLS_DC);
	//zend_call_method(&pdo_new_ce,pdo_class_entry,NULL,function_name,sizeof("__construct")-1,&ret,params_len,params,NULL TSRMLS_CC);
	//RETURN_NULL();
	
        **/


    //创建类实例
    zval *object_name;
    
     //MAKE_STD_ZVAL(object_name);
    //object_init_ex(object_name,adf_ce);
	       
 
    //返回值
    //zval retval;
    //函数名i
    zval function_name;
    ZVAL_STRING(&function_name, "calladf");
 
//zend_call_method_with_0_params(object_name,adf_ce,NULL,"calladf",return_value);
    zend_call_method(object_name,adf_ce,NULL,"calladf",sizeof("calladf")-1,return_value,0,NULL,NULL);
    RETURN_NULL();
}
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_udf_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_udf_init_globals(zend_udf_globals *udf_globals)
{
	udf_globals->global_value = 0;
	udf_globals->global_string = NULL;
}
*/
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(udf)
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
PHP_RINIT_FUNCTION(udf)
{
#if defined(COMPILE_DL_UDF) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(udf)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(udf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "udf support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ udf_functions[]
 *
 * Every user visible function must have an entry in udf_functions[].
 */
const zend_function_entry udf_functions[] = {
	
	
	PHP_ME(udf, __construct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(udf,get,NULL,ZEND_ACC_PUBLIC)
	PHP_FE_END	/* Must be the last line in udf_functions[] */
};
/* }}} */




/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(udf)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

        zend_class_entry ce;
        INIT_CLASS_ENTRY(ce, "udf", udf_functions);
	udf_ce = zend_register_internal_class(&ce TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/* {{{ udf_module_entry
 */
zend_module_entry udf_module_entry = {
	STANDARD_MODULE_HEADER,
	"udf",
	udf_functions,
	PHP_MINIT(udf),
	PHP_MSHUTDOWN(udf),
	PHP_RINIT(udf),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(udf),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(udf),
	PHP_UDF_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_UDF
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(udf)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
