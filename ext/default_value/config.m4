dnl $Id$
dnl config.m4 for extension default_value

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(default_value, for default_value support,
dnl Make sure that the comment is aligned:
[  --with-default_value             Include default_value support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(default_value, whether to enable default_value support,
dnl Make sure that the comment is aligned:
dnl [  --enable-default_value           Enable default_value support])

if test "$PHP_DEFAULT_VALUE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-default_value -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/default_value.h"  # you most likely want to change this
  dnl if test -r $PHP_DEFAULT_VALUE/$SEARCH_FOR; then # path given as parameter
  dnl   DEFAULT_VALUE_DIR=$PHP_DEFAULT_VALUE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for default_value files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DEFAULT_VALUE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DEFAULT_VALUE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the default_value distribution])
  dnl fi

  dnl # --with-default_value -> add include path
  dnl PHP_ADD_INCLUDE($DEFAULT_VALUE_DIR/include)

  dnl # --with-default_value -> check for lib and symbol presence
  dnl LIBNAME=default_value # you may want to change this
  dnl LIBSYMBOL=default_value # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DEFAULT_VALUE_DIR/$PHP_LIBDIR, DEFAULT_VALUE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DEFAULT_VALUELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong default_value lib version or lib not found])
  dnl ],[
  dnl   -L$DEFAULT_VALUE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DEFAULT_VALUE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(default_value, default_value.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
