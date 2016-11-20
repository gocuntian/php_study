dnl $Id$
dnl config.m4 for extension adf

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(adf, for adf support,
dnl Make sure that the comment is aligned:
[  --with-adf             Include adf support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(adf, whether to enable adf support,
dnl Make sure that the comment is aligned:
dnl [  --enable-adf           Enable adf support])

if test "$PHP_ADF" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-adf -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/adf.h"  # you most likely want to change this
  dnl if test -r $PHP_ADF/$SEARCH_FOR; then # path given as parameter
  dnl   ADF_DIR=$PHP_ADF
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for adf files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ADF_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ADF_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the adf distribution])
  dnl fi

  dnl # --with-adf -> add include path
  dnl PHP_ADD_INCLUDE($ADF_DIR/include)

  dnl # --with-adf -> check for lib and symbol presence
  dnl LIBNAME=adf # you may want to change this
  dnl LIBSYMBOL=adf # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ADF_DIR/$PHP_LIBDIR, ADF_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ADFLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong adf lib version or lib not found])
  dnl ],[
  dnl   -L$ADF_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ADF_SHARED_LIBADD)

  PHP_NEW_EXTENSION(adf, adf.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
