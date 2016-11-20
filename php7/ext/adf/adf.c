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

zend_class_entry *adf_ce;

//参数定义
ZEND_BEGIN_ARG_INFO_EX(global_setkey_arg,0,0,2)
	ZEND_ARG_INFO(0,key1)
	ZEND_ARG_INFO(0,key2)
ZEND_END_ARG_INFO()

static int le_adf;

ZEND_METHOD(adf,__construct){
	RETURN_NULL();
}

ZEND_METHOD(adf,set){
   zval *param1;
   zval *param2;

   array_init(param2);
   if(zend_parse_parameters(ZEND_NUM_ARGS(),"z|z",&param1,&param2) == FAILURE){
	   RETURN_FALSE;
   }
   zend_update_property(adf_ce,getThis(),"param1",sizeof("param1")-1,param1,TSRMLS_CC);
   zend_update_property(adf_ce,getThis(),"param2",sizeof("param2")-1,param2,TSRMLS_CC);
   RETURN_NULL();
}
ZEND_METHOD(adf,get){
   array_init(return_value);

   zval *get1;
   zval *get2;
   zval param1;
   zval param2;
   get1 = zend_read_property(adf_ce,getThis(),"param1",sizeof("param1")-1,0,&param1 TSRMLS_DC);
   get2 = zend_read_property(adf_ce,getThis(),"param2",sizeof("param2")-1,0,&param2 TSRMLS_DC);
   add_next_index_string(return_value,Z_STRVAL_P(get1));
   RETURN_ZVAL(return_value,1,0);
}

PHP_MSHUTDOWN_FUNCTION(adf)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_RINIT_FUNCTION(adf)
{
#if defined(COMPILE_DL_ADF) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(adf)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(adf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "adf support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}

const zend_function_entry adf_functions[] = {
	PHP_ME(adf,__construct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(adf,set,global_setkey_arg,ZEND_ACC_PUBLIC)
	PHP_ME(adf,get,NULL,ZEND_ACC_PUBLIC)
	PHP_FE_END	
};

PHP_MINIT_FUNCTION(adf)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce,"adf",adf_functions);
	adf_ce = zend_register_internal_class(&ce TSRMLS_CC);
	return SUCCESS;
}

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


#ifdef COMPILE_DL_ADF
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(adf)
#endif

