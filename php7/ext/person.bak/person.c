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
#include "php_person.h"

/* If you declare any globals in php_person.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(person)
*/

/* True global resources - no need for thread safety here */
static int le_person;

zend_class_entry *person_ce;

PHP_METHOD(person_ce,__construct);
PHP_METHOD(person_ce,saying);
PHP_METHOD(person_ce,doing);



ZEND_BEGIN_ARG_INFO_EX(global_config_arg,0,0,1)
     ZEND_ARG_INFO(0,global_config)
ZEND_END_ARG_INFO()


ZEND_METHOD(person,__construct){
  zval *array_config;
 if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"a",&array_config)==FAILURE){
    RETURN_NULL();
 } 

  php_var_dump(array_config,1);

  zend_update_property(person_ce,getThis(),"config",sizeof("config")-1,array_config TSRMLS_CC);
  //	zval *pThis;
//	pThis = getThis();
  //    zend_printf("construct\n");
}
ZEND_METHOD(person,__destruct){
      zend_printf("destruct\n");
}
ZEND_METHOD(person,doing){
  // zend_printf("doing\n");

   zval *array_config;
   zval rv;
   array_config = zend_read_property(person_ce,getThis(),"config",sizeof("config")-1,0,&rv TSRMLS_DC);
   if (Z_TYPE_P(array_config)==IS_NULL || Z_TYPE_P(array_config)!=IS_ARRAY){
        RETURN_FALSE;
   }
  php_var_dump(array_config, 1);
  RETURN_ZVAL(array_config,1,0);
}

ZEND_METHOD(person,saying){
   zend_printf("saying\n");
}

const zend_function_entry person_functions[] = {
    ZEND_ME(person, __construct, global_config_arg, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    ZEND_ME(person,doing,NULL,ZEND_ACC_PUBLIC) ZEND_ME(person,saying,NULL,ZEND_ACC_PUBLIC)
    ZEND_ME(person,__destruct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    PHP_FE_END  /* Must be the last line in person_functions[] */
};


PHP_MINIT_FUNCTION(person)
{
        zend_class_entry ce;
        INIT_CLASS_ENTRY(ce, "person", person_functions);
        person_ce = zend_register_internal_class(&ce TSRMLS_CC); 
	zend_declare_property_null(person_ce,"saying",strlen("saying"),ZEND_ACC_PUBLIC);
	zend_declare_property_null(person_ce,"doing",strlen("doing"),ZEND_ACC_PUBLIC);	
    return SUCCESS;
}
PHP_MSHUTDOWN_FUNCTION(person)
{
	return SUCCESS;
}
PHP_RINIT_FUNCTION(person)
{
#if defined(COMPILE_DL_PERSON) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
PHP_RSHUTDOWN_FUNCTION(person)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(person)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "person support", "enabled");
	php_info_print_table_end();

}
zend_module_entry person_module_entry = {
	STANDARD_MODULE_HEADER,
	"person",
        NULL,   //	person_functions,
	PHP_MINIT(person),
	PHP_MSHUTDOWN(person),
	PHP_RINIT(person),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(person),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(person),
	PHP_PERSON_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PERSON
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(person)
#endif

