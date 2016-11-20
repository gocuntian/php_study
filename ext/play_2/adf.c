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
#include "php_adf.h"
#include <zend_API.h>

/* If you declare any globals in php_adf.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(adf)
*/
zend_class_entry *adf_ce;


//新增定义
ZEND_BEGIN_ARG_INFO_EX(global_setkey_arg, 0, 0, 2)
    ZEND_ARG_INFO(0, key1)
    ZEND_ARG_INFO(0, key2)
ZEND_END_ARG_INFO()



/* True global resources - no need for thread safety here */
static int le_adf;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("adf.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_adf_globals, adf_globals)
    STD_PHP_INI_ENTRY("adf.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_adf_globals, adf_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */

ZEND_METHOD(adf,__construct){

	RETURN_NULL();
}

ZEND_METHOD(adf,set){



	zval *param1;
	zval *param2;

//	array_init(param2);

	//int zend_parse_parameters ( int num_args TSRMLS_DC, char* type_spec, ... )

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z|z",&param1,&param2) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property(adf_ce, getThis(), "param1", sizeof("param1")-1, param1 TSRMLS_CC);
	zend_update_property(adf_ce, getThis(), "param2", sizeof("param2")-1, param2 TSRMLS_CC);

	RETURN_NULL();
}


ZEND_METHOD(adf,get){

	array_init(return_value);
	
	zval  *get1;
	zval  *get2;
	
	zval  param1; //php >=7.0
	zval  param2; //php >=7.0

	get1 = zend_read_property(adf_ce, getThis(), "param1", sizeof("param1")-1, 0, &param1 TSRMLS_DC);
	get2 = zend_read_property(adf_ce, getThis(), "param2", sizeof("param2")-1, 0, &param2 TSRMLS_DC);


	add_next_index_string(return_value,Z_STRVAL_P(get1));
	add_next_index_string(return_value,Z_STRVAL_P(get2));
	//add_assoc_string(return_value, "param1", ZEND_STRL("test1"));
	//add_assoc_string(return_value, "param2", ZEND_STRL("test2"));

	RETURN_ZVAL(return_value, 1, 0);

}


ZEND_METHOD(adf,calladf){

}
/* {{{ php_adf_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_adf_init_globals(zend_adf_globals *adf_globals)
{
	adf_globals->global_value = 0;
	adf_globals->global_string = NULL;
}
*/
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(adf)
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
PHP_RINIT_FUNCTION(adf)
{
#if defined(COMPILE_DL_ADF) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(adf)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(adf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "adf support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ adf_functions[]
 *
 * Every user visible function must have an entry in adf_functions[].
 */
const zend_function_entry adf_functions[] = {

	PHP_ME(adf, __construct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(adf,set,global_setkey_arg,ZEND_ACC_PUBLIC)
	PHP_ME(adf,get,NULL,ZEND_ACC_PUBLIC)
	PHP_ME(adf,calladf,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)

	PHP_FE_END	/* Must be the last line in adf_functions[] */
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(adf)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

        zend_class_entry ce;
        INIT_CLASS_ENTRY(ce, "adf", adf_functions);
	adf_ce = zend_register_internal_class(&ce TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/* {{{ adf_module_entry
 */
zend_module_entry adf_module_entry = {
	STANDARD_MODULE_HEADER,
	"adf",
	adf_functions,
	PHP_MINIT(adf),
	PHP_MSHUTDOWN(adf),
	PHP_RINIT(adf),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(adf),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(adf),
	PHP_ADF_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ADF
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(adf)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
