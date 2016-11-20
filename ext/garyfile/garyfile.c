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
#include "php_garyfile.h"

/* If you declare any globals in php_garyfile.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(garyfile)
*/

/* True global resources - no need for thread safety here */
static int le_garyfile;
#define GARY_FILE_TYPE "gary_file"
/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("garyfile.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_garyfile_globals, garyfile_globals)
    STD_PHP_INI_ENTRY("garyfile.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_garyfile_globals, garyfile_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_garyfile_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_garyfile_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "garyfile", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/
//资源释放回调函数
static void garyfile_dtor(zend_resource *rsrc TSRMLS_DC){
	FILE *fp = (FILE *)rsrc->ptr;
	fclose(fp);
}
/* {{{ proto resource file_open(string filename, string mode)
    */
PHP_FUNCTION(file_open)
{
	char *filename = NULL;
	char *mode = NULL;
	int argc = ZEND_NUM_ARGS();
	size_t filename_len;
	size_t mode_len;

	if (zend_parse_parameters(argc, "ss", &filename, &filename_len, &mode, &mode_len) == FAILURE) 
		return;
	FILE *fp = VCWD_FOPEN(filename,mode);
	if (fp == NULL){
	 RETURN_FALSE;
	}
	RETURN_RES(zend_register_resource(fp,le_garyfile));
}
/* }}} */

/* {{{ proto string file_read(resource filehandle, int size)
    */
PHP_FUNCTION(file_read)
{
	int argc = ZEND_NUM_ARGS();
	int filehandle_id = -1;
	zend_long size;
	zval *filehandle = NULL;
	FILE *fp = NULL;
	char *result;
	size_t bytes_read;

	if (zend_parse_parameters(argc, "rl", &filehandle, &size) == FAILURE) 
		return;


	if((fp = (FILE *)zend_fetch_resource(Z_RES_P(filehandle),GARY_FILE_TYPE,le_garyfile))==NULL){
	 RETURN_FALSE;
	}
	result = (char *)emalloc(size+1);
	bytes_read = fread(result,1,size,fp);
	result[bytes_read] = '\0';
	RETURN_STRING(result);
}	
/* }}} */

/* {{{ proto bool file_write(resource filehandle, string buffer)
    */
PHP_FUNCTION(file_write)
{
	char *buffer = NULL;
	int argc = ZEND_NUM_ARGS();
	int filehandle_id = -1;
	size_t buffer_len;
	zval *filehandle = NULL;
	FILE *fp = NULL;

	if (zend_parse_parameters(argc, "rs", &filehandle, &buffer, &buffer_len) == FAILURE) 
		return;

	if((fp = (FILE *)zend_fetch_resource(Z_RES_P(filehandle),GARY_FILE_TYPE,le_garyfile))==NULL){
	 RETURN_FALSE;
	}
	if(fwrite(buffer,1,buffer_len,fp)!=buffer_len){
	 RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool file_close(resource filehandle)
    */
PHP_FUNCTION(file_close)
{
	int argc = ZEND_NUM_ARGS();
	int filehandle_id = -1;
	zval *filehandle = NULL;

	if (zend_parse_parameters(argc, "r", &filehandle) == FAILURE) 
		return;
	zend_list_close(Z_RES_P(filehandle));
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool file_eof(resource filehandle)
    */
/*PHP_FUNCTION(file_eof)
{
	int argc = ZEND_NUM_ARGS();
	int filehandle_id = -1;
	zval *filehandle = NULL;

	if (zend_parse_parameters(argc, "r", &filehandle) == FAILURE) 
		return;

	if (filehandle) {
		ZEND_FETCH_RESOURCE(???, ???, filehandle, filehandle_id, "???", ???_rsrc_id);
	}

	php_error(E_WARNING, "file_eof: not yet implemented");
}
*/
/* }}} */


/* {{{ php_garyfile_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_garyfile_init_globals(zend_garyfile_globals *garyfile_globals)
{
	garyfile_globals->global_value = 0;
	garyfile_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(garyfile)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	le_garyfile=zend_register_list_destructors_ex(garyfile_dtor,NULL,GARY_FILE_TYPE,module_number);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(garyfile)
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
PHP_RINIT_FUNCTION(garyfile)
{
#if defined(COMPILE_DL_GARYFILE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(garyfile)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(garyfile)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "garyfile support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ garyfile_functions[]
 *
 * Every user visible function must have an entry in garyfile_functions[].
 */
const zend_function_entry garyfile_functions[] = {
	PHP_FE(confirm_garyfile_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(file_open,	NULL)
	PHP_FE(file_read,	NULL)
	PHP_FE(file_write,	NULL)
	PHP_FE(file_close,	NULL)
//	PHP_FE(file_eof,	NULL)
	PHP_FE_END	/* Must be the last line in garyfile_functions[] */
};
/* }}} */

/* {{{ garyfile_module_entry
 */
zend_module_entry garyfile_module_entry = {
	STANDARD_MODULE_HEADER,
	"garyfile",
	garyfile_functions,
	PHP_MINIT(garyfile),
	PHP_MSHUTDOWN(garyfile),
	PHP_RINIT(garyfile),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(garyfile),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(garyfile),
	PHP_GARYFILE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GARYFILE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(garyfile)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
