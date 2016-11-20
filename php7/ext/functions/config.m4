dnl $Id$
dnl config.m4 for extension functions

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(functions, for functions support,
dnl Make sure that the comment is aligned:
dnl [  --with-functions             Include functions support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(functions, whether to enable functions support,
dnl Make sure that the comment is aligned:
[  --enable-functions           Enable functions support])

if test "$PHP_FUNCTIONS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-functions -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/functions.h"  # you most likely want to change this
  dnl if test -r $PHP_FUNCTIONS/$SEARCH_FOR; then # path given as parameter
  dnl   FUNCTIONS_DIR=$PHP_FUNCTIONS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for functions files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       FUNCTIONS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$FUNCTIONS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the functions distribution])
  dnl fi

  dnl # --with-functions -> add include path
  dnl PHP_ADD_INCLUDE($FUNCTIONS_DIR/include)

  dnl # --with-functions -> check for lib and symbol presence
  dnl LIBNAME=functions # you may want to change this
  dnl LIBSYMBOL=functions # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $FUNCTIONS_DIR/$PHP_LIBDIR, FUNCTIONS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_FUNCTIONSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong functions lib version or lib not found])
  dnl ],[
  dnl   -L$FUNCTIONS_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(FUNCTIONS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(functions, functions.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
