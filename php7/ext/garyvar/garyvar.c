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
#include "php_garyvar.h"

/* If you declare any globals in php_garyvar.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(garyvar)
*/

/* True global resources - no need for thread safety here */
static int le_garyvar;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("garyvar.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_garyvar_globals, garyvar_globals)
    STD_PHP_INI_ENTRY("garyvar.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_garyvar_globals, garyvar_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_garyvar_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_garyvar_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "garyvar", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(define_var){
   zval var_value;//变量值
   zend_string *var_name=NULL;//变量名称
   //创建整型变量
   ZVAL_LONG(&var_value,2);
   zend_set_local_var_str("lng",3,&var_value,0);//设置本地变量
   ZVAL_NULL(&var_value);

   //创建字符串变量
   zend_string *str=NULL;
   char content[4] = "abc";
   var_name = zend_string_init("str",3,0);//设置变量名称
   str=zend_string_init(content,sizeof(content)-1,0);
   ZVAL_STR(&var_value,str);//设置变量的值
   zend_set_local_var(var_name,&var_value,0);//设置本地变量
   zend_string_release(var_name);
   ZVAL_NULL(&var_value);

   //创建数组变量
   var_name = zend_string_init("arr",3,0);//设置变量名称
   array_init(&var_value);//初始化数组
   add_index_long(&var_value,0,1);
   add_assoc_stringl_ex(&var_value,"a",1,"b",2);
   zend_set_local_var(var_name,&var_value,0);//设置本地变量
   zend_string_release(var_name);
   ZVAL_NULL(&var_value);
  
   zval subarray;
   zval myobject;
   array_init(&subarray);
   var_name  =zend_string_init("arrs",4,0);
   array_init(&var_value);
  // add_index_string(&var_value,"life",42);
   add_index_bool(&var_value,123,1);
   add_next_index_string(&var_value,"gary");
   add_next_index_string(&var_value,"age");
   add_next_index_string(&var_value,"sex");
   object_init(&myobject);
   add_property_string(&myobject,"charset","utf8");
   add_property_string(&myobject,"text","xingcuntian");
   zend_hash_next_index_insert(Z_ARRVAL_P(&var_value),&myobject);
   
   add_assoc_string(&subarray, "type", "close");
   add_assoc_long(&subarray, "level", 1);
   zend_hash_next_index_insert(Z_ARRVAL_P(&var_value),&subarray);
   zend_string *sub_key;
   sub_key = zend_string_init("sub_key",7,0);
   zend_hash_add(Z_ARRVAL_P(&var_value),sub_key,&subarray);
  // zend_hash_next_index_insert_new(Z_ARRVAL_P(subarray), &var_value);
   //add_next_index_long(subarray,1);
  // add_next_index_long(subarray,20);
  // add_next_index_long(subarray,200);
  // zend_hash_next_index_insert(Z_ARRVAL_P(&var_value),subarray);

   zend_set_local_var(var_name,&var_value,0);
   zend_string_release(var_name);
   ZVAL_NULL(&var_value);
  // zend_hash_next_index_insert_new(Z_ARRVAL_P(subarray), &var_value);
 //  add_next_index_long(subarray,1);
 //  add_next_index_long(subarray,20);
 //  add_next_index_long(subarray,200);
   //object_init(&myobject);
   //add_property_string(&myobject,"charset","utf8");
   //add_property_string(&myobject,"text","xingcuntian");
   // zend_hash_next_index_insert(Z_ARRVAL_P(&var_value),&myobject);
   
 
  //创建对象
   zend_class_entry *ce;
   zend_string *class_name;
   class_name=zend_string_init("demo",4,0);
   ce = zend_fetch_class(class_name,ZEND_FETCH_CLASS_AUTO);//获取类
   zend_string_release(class_name);
   object_init_ex(&var_value,ce);
   zend_set_local_var_str("obj",3,&var_value,0);
   ZVAL_NULL(&var_value);
} 
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_garyvar_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_garyvar_init_globals(zend_garyvar_globals *garyvar_globals)
{
	garyvar_globals->global_value = 0;
	garyvar_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(garyvar)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(garyvar)
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
PHP_RINIT_FUNCTION(garyvar)
{
#if defined(COMPILE_DL_GARYVAR) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(garyvar)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(garyvar)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "garyvar support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ garyvar_functions[]
 *
 * Every user visible function must have an entry in garyvar_functions[].
 */
const zend_function_entry garyvar_functions[] = {
	PHP_FE(confirm_garyvar_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(define_var,	NULL)
	PHP_FE_END	/* Must be the last line in garyvar_functions[] */
};
/* }}} */

/* {{{ garyvar_module_entry
 */
zend_module_entry garyvar_module_entry = {
	STANDARD_MODULE_HEADER,
	"garyvar",
	garyvar_functions,
	PHP_MINIT(garyvar),
	PHP_MSHUTDOWN(garyvar),
	PHP_RINIT(garyvar),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(garyvar),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(garyvar),
	PHP_GARYVAR_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GARYVAR
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(garyvar)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
