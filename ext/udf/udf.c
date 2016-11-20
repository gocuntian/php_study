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

zend_class_entry *udf_ce;

static int le_udf;


ZEND_METHOD(udf,__construct){
	RETURN_NULL();
}
ZEND_METHOD(udf,get){
    RETURN_NULL();
}

PHP_MINIT_FUNCTION(udf)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce,"udf",udf_functions);
	udf_ce = zend_register_internal_class(&ce TSRMLS_CC);
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(udf)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_RINIT_FUNCTION(udf)
{
#if defined(COMPILE_DL_UDF) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(udf)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(udf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "udf support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}

const zend_function_entry udf_functions[] = {
	PHP_ME(udf,__construct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(udf,get,NULL,ZEND_ACC_PUBLIC);
	PHP_FE_END	/* Must be the last line in udf_functions[] */
};

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

#ifdef COMPILE_DL_UDF
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(udf)
#endif
