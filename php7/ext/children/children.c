/*                                                |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
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
#include "php_children.h"

/* If you declare any globals in php_children.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(children)
*/

/* True global resources - no need for thread safety here */
static int le_children;
//对象创建
zend_class_entry *children_ce;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("children.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_children_globals, children_globals)
    STD_PHP_INI_ENTRY("children.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_children_globals, children_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ children_functions[]
 *
 * Every user visible function must have an entry in children_functions[].
 */
 //定义方法
PHP_METHOD(children, learn);
//ZEND_BEGIN_ARG_INFO_EX

//的最后一个参数1，是传递的参数的个数。
ZEND_BEGIN_ARG_INFO_EX(arginfo_children_learn, 0, 0, 1)
   //的第一个参数0，表示是否传引用方式传递。一般默认为0即可
    ZEND_ARG_INFO(0, love)
ZEND_END_ARG_INFO()
const zend_function_entry children_methods[] = {
	PHP_ME(children, learn, arginfo_children_learn, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}	/* Must be the last line in children_functions[] */
};
/* }}} */
/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_children_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_METHOD(children, learn)
{
	char *love = NULL;
	size_t love_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &love, &love_len) == FAILURE) {
		return;
	}
    //更新属性的值
	zend_update_property_string(children_ce,  getThis(), "memory", sizeof("memory") - 1, love);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_children_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_children_init_globals(zend_children_globals *children_globals)
{
	children_globals->global_value = 0;
	children_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(children)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry ce;
	//对象命名children
	INIT_CLASS_ENTRY(ce, "children", children_methods);
   
	zend_class_entry *children_ce;
	//注册对象
	children_ce = zend_register_internal_class(&ce);
    //定义属性memory 访问类型 ZEND_ACC_PUBLIC public
	zend_declare_property_null(children_ce, "memory",       sizeof("memory") - 1, ZEND_ACC_PUBLIC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(children)
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
PHP_RINIT_FUNCTION(children)
{
#if defined(COMPILE_DL_CHILDREN) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(children)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(children)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "children support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ children_module_entry
 */
zend_module_entry children_module_entry = {
	STANDARD_MODULE_HEADER,
	"children",
	NULL,
	PHP_MINIT(children),
	PHP_MSHUTDOWN(children),
	PHP_RINIT(children),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(children),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(children),
	PHP_CHILDREN_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CHILDREN
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(children)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */


