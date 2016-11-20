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
#include "php_adf.h"
#include "php_play.h"
#include <zend_interfaces.h>

zend_class_entry *udf_ce;

static int le_udf;

int class_call_user_method(zval *retval,zend_class_entry *obj_ce,zval *obj,zval func,uint32_t params_count,zval params[]){
	HashTable *function_table;

	  if(obj) { 
                function_table = &Z_OBJCE_P(obj)->function_table;
        }else{
                function_table = (CG(function_table));
    }

	zend_fcall_info fci;
	fci.size = sizeof(fci);
	fci.function_table = function_table;
	fci.object = obj ? Z_OBJ_P(obj) : NULL;
	fci.function_name = func;
	fci.retval = retval;
	fci.param_count = params_count;
	fci.params = params;
	fci.no_separation = 1;
	fci.symbol_table = NULL;
	
	int result;
	result = zend_call_function(&fci,NULL TSRMLS_CC);
	if (result == FAILURE){
		zend_printf("error");
	}
	zend_printf("success.\n");
}

ZEND_METHOD(udf,__construct){
	RETURN_NULL();
}
// ZEND_METHOD(udf,get){

// 	// //创建类实例
// 	// zval *object_name;
// 	// //MAKE_STD_ZVAL(object_name);
// 	// //object_init_ex(object_name,adf_ce);
// 	// zval function_name;
// 	// ZVAL_STRING(&function_name,"clalladf");
// 	// zend_call_method(object_name,adf_ce,NULL,"calladf",sizeof("calladf")-1,return_value,0,NULL,NULL);
//     // RETURN_NULL();
// }

ZEND_METHOD(udf,get){
	
	zval retval;
	zval obj;
	object_init_ex(&obj,adf_ce);
	
	zval function_name;
	ZVAL_STRING(&function_name,"__construct");
    class_call_user_method(&retval,adf_ce,&obj,function_name,0,NULL);

	zval retval2;
	
	zval obj2;
	object_init_ex(&obj2,adf_ce);
  
    zval function_name2;
	ZVAL_STRING(&function_name2,"set");

	zval params[2];
	ZVAL_STRING(&params[0],"xing");
	ZVAL_STRING(&params[1],"cun");

	class_call_user_method(&retval2,adf_ce,&obj2,function_name2,2,params);

     


	// zval retval3;

	// zval obj3;
	// object_init_ex(&obj3,adf_ce);
	// zval function_name3;
	// ZVAL_STRING(&function_name3,"get");
	// class_call_user_method(&retval3,adf_ce,&obj3,function_name3,0,NULL);
}



/*PHP_MINIT_FUNCTION(udf)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
/*	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce,"udf",udf_functions);
	udf_ce = zend_register_internal_class(&ce);
	return SUCCESS;
}
*/
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
	PHP_ME(udf,get,NULL,ZEND_ACC_PUBLIC)
	PHP_FE_END	/* Must be the last line in udf_functions[] */
};

PHP_MINIT_FUNCTION(udf)
{
        /* If you have INI entries, uncomment these lines
         REGISTER_INI_ENTRIES();        */
        zend_class_entry ce;
        INIT_CLASS_ENTRY(ce, "udf", udf_functions);
	    udf_ce = zend_register_internal_class(&ce TSRMLS_CC);
        return SUCCESS;
}


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
