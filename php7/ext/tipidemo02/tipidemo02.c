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
#include "php_tipidemo02.h"

/* If you declare any globals in php_tipidemo02.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(tipidemo02)
*/

/* True global resources - no need for thread safety here */
static int le_tipidemo02;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("tipidemo02.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_tipidemo02_globals, tipidemo02_globals)
    STD_PHP_INI_ENTRY("tipidemo02.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_tipidemo02_globals, tipidemo02_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_tipidemo02_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_tipidemo02_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "tipidemo02", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string tipi_hello_world(string name)
    */
PHP_FUNCTION(tipi_hello_world)
{
	char *name = NULL;
	int argc = ZEND_NUM_ARGS();
	size_t name_len;
        char *prefix="hello world, ";
	char *result=NULL;
	
	ZEND_PARSE_PARAMETERS_START(1,1)
            Z_PARAM_STRING(name,name_len)
	ZEND_PARSE_PARAMETERS_END();
	
        result=(char *) ecalloc(strlen(prefix) + name_len + 1,sizeof(char));
	strncat(result,prefix,strlen(prefix));
	strncat(result,name,name_len);
	RETURN_STRING(result);

}
/* }}} */


/* {{{ php_tipidemo02_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_tipidemo02_init_globals(zend_tipidemo02_globals *tipidemo02_globals)
{
	tipidemo02_globals->global_value = 0;
	tipidemo02_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(tipidemo02)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(tipidemo02)
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
PHP_RINIT_FUNCTION(tipidemo02)
{
#if defined(COMPILE_DL_TIPIDEMO02) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(tipidemo02)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(tipidemo02)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "tipidemo02 support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ tipidemo02_functions[]
 *
 * Every user visible function must have an entry in tipidemo02_functions[].
 */
const zend_function_entry tipidemo02_functions[] = {
	PHP_FE(confirm_tipidemo02_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(tipi_hello_world,	NULL)
	PHP_FE_END	/* Must be the last line in tipidemo02_functions[] */
};
/* }}} */

/* {{{ tipidemo02_module_entry
 */
zend_module_entry tipidemo02_module_entry = {
	STANDARD_MODULE_HEADER,
	"tipidemo02",
	tipidemo02_functions,
	PHP_MINIT(tipidemo02),
	PHP_MSHUTDOWN(tipidemo02),
	PHP_RINIT(tipidemo02),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(tipidemo02),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(tipidemo02),
	PHP_TIPIDEMO02_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TIPIDEMO02
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(tipidemo02)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
