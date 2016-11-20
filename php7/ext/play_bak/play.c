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
#include "php_play.h"

/* If you declare any globals in php_play.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(play)
*/

/* True global resources - no need for thread safety here */
static int le_play;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("play.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_play_globals, play_globals)
    STD_PHP_INI_ENTRY("play.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_play_globals, play_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_play_init_globals
static void php_play_init_globals(zend_play_globals *play_globals)
{
	play_globals->global_value = 0;
	play_globals->global_string = NULL;
}
*/

PHP_MINIT_FUNCTION(play)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	ZEND_MODULE_STARTUP_N(udf) (INIT_FUNC_ARGS_PASSTHRU);
	ZEND_MODULE_STARTUP_N(adf) (INIT_FUNC_ARGS_PASSTHRU);
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(play)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_RINIT_FUNCTION(play)
{
#if defined(COMPILE_DL_PLAY) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(play)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(play)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "play support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}

const zend_function_entry play_functions[] = {

	PHP_FE_END	/* Must be the last line in play_functions[] */
};

zend_module_entry play_module_entry = {
	STANDARD_MODULE_HEADER,
	"play",
	play_functions,
	PHP_MINIT(play),
	PHP_MSHUTDOWN(play),
	PHP_RINIT(play),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(play),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(play),
	PHP_PLAY_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PLAY
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(play)
#endif
