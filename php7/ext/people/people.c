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
#include "php_people.h"

static int le_people;

zend_class_entry *people_ce;

//PHP_METHOD(people,__contruct);
//PHP_METHOD(people,__destruct);
PHP_METHOD(people,talk);
static const zend_function_entry people_functions[] = {
    //    ZEND_ME(people,__contruct,NULL,ZEND_ACC_PUBLIC)
 //       ZEND_ME(people,__destruct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
        PHP_ME(people,talk,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};


PHP_MINIT_FUNCTION(people)
{
        zend_class_entry ce;
	INIT_CLASS_ENTRY(ce,"people",people_functions);
	people_ce=zend_register_internal_class(&ce);
	zend_declare_property_null(people_ce,"name",sizeof("name")-1,ZEND_ACC_PUBLIC);	
	zend_declare_class_constant_long(people_ce,"AGE",sizeof("AGE")-1,19 TSRMLS_DC);
	return SUCCESS;
}

ZEND_COLD ZEND_METHOD(people,__construct)
{
  php_printf("construct method\n");
}

ZEND_METHOD(people,__destruct)
{
   php_printf("destruct method\n");
}

ZEND_METHOD(people,talk)
{
  php_printf("public method talk\n");
}

PHP_MSHUTDOWN_FUNCTION(people)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(people)
{
#if defined(COMPILE_DL_PEOPLE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(people)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(people)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "people support", "enabled");
	php_info_print_table_end();

}


//const zend_function_entry people_functions[] = {
 //	PHP_ME(people,__contruct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
   //     PHP_ME(people,__destruct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
     //   PHP_ME(people,talk,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
//	PHP_FE_END
//};


zend_module_entry people_module_entry = {
	STANDARD_MODULE_HEADER,
	"people",
	people_functions,
	PHP_MINIT(people),
	PHP_MSHUTDOWN(people),
	PHP_RINIT(people),	
	PHP_RSHUTDOWN(people),	
	PHP_MINFO(people),
	PHP_PEOPLE_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PEOPLE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(people)
#endif

