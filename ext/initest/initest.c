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
#include "php_initest.h"


ZEND_DECLARE_MODULE_GLOBALS(initest)

/* True global resources - no need for thread safety here */
//static int le_initest;


PHP_INI_BEGIN()
   STD_PHP_INI_ENTRY("initest.userage",   "42", PHP_INI_ALL, OnUpdateLong, userage, zend_initest_globals, initest_globals)
    STD_PHP_INI_ENTRY("initest.username", "foobar", PHP_INI_ALL, OnUpdateString, username, zend_initest_globals, initest_globals)
PHP_INI_END()

static void php_initest_init_globals(zend_initest_globals *initest_globals)
{
	// initest_globals->userage = 20;
	// initest_globals->username = "xincuntian";
}

PHP_MINIT_FUNCTION(initest)
{

	 ZEND_INIT_MODULE_GLOBALS(initest, php_initest_init_globals, NULL);
	 REGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(initest)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_FUNCTION(ini_echo){

	php_printf("username:%s\n",INITEST_G(username));
	php_printf("userage:%d\n",INITEST_G(userage));
}


PHP_RINIT_FUNCTION(initest)
{
#if defined(COMPILE_DL_INITEST) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(initest)
{
	return SUCCESS;
}
PHP_MINFO_FUNCTION(initest)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "initest support", "enabled");
	php_info_print_table_end();


	DISPLAY_INI_ENTRIES();
}

const zend_function_entry initest_functions[] = {
	PHP_FE(ini_echo,	NULL)
	PHP_FE_END	/* Must be the last line in initest_functions[] */
};

zend_module_entry initest_module_entry = {
	STANDARD_MODULE_HEADER,
	"initest",
	initest_functions,
	PHP_MINIT(initest),
	PHP_MSHUTDOWN(initest),
	PHP_RINIT(initest),		
	PHP_RSHUTDOWN(initest),	
	PHP_MINFO(initest),
	PHP_INITEST_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_INITEST
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(initest)
#endif