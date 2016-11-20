dnl $Id$
dnl config.m4 for extension udf

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(udf, for udf support,
dnl Make sure that the comment is aligned:
[  --with-udf             Include udf support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(udf, whether to enable udf support,
dnl Make sure that the comment is aligned:
dnl [  --enable-udf           Enable udf support])

if test "$PHP_UDF" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-udf -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/udf.h"  # you most likely want to change this
  dnl if test -r $PHP_UDF/$SEARCH_FOR; then # path given as parameter
  dnl   UDF_DIR=$PHP_UDF
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for udf files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       UDF_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$UDF_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the udf distribution])
  dnl fi

  dnl # --with-udf -> add include path
  dnl PHP_ADD_INCLUDE($UDF_DIR/include)

  dnl # --with-udf -> check for lib and symbol presence
  dnl LIBNAME=udf # you may want to change this
  dnl LIBSYMBOL=udf # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $UDF_DIR/$PHP_LIBDIR, UDF_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_UDFLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong udf lib version or lib not found])
  dnl ],[
  dnl   -L$UDF_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(UDF_SHARED_LIBADD)

  PHP_NEW_EXTENSION(udf, udf.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
