dnl $Id$
dnl config.m4 for extension initest

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(initest, for initest support,
dnl Make sure that the comment is aligned:
[  --with-initest             Include initest support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(initest, whether to enable initest support,
dnl Make sure that the comment is aligned:
dnl [  --enable-initest           Enable initest support])

if test "$PHP_INITEST" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-initest -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/initest.h"  # you most likely want to change this
  dnl if test -r $PHP_INITEST/$SEARCH_FOR; then # path given as parameter
  dnl   INITEST_DIR=$PHP_INITEST
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for initest files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       INITEST_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$INITEST_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the initest distribution])
  dnl fi

  dnl # --with-initest -> add include path
  dnl PHP_ADD_INCLUDE($INITEST_DIR/include)

  dnl # --with-initest -> check for lib and symbol presence
  dnl LIBNAME=initest # you may want to change this
  dnl LIBSYMBOL=initest # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $INITEST_DIR/$PHP_LIBDIR, INITEST_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_INITESTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong initest lib version or lib not found])
  dnl ],[
  dnl   -L$INITEST_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(INITEST_SHARED_LIBADD)

  PHP_NEW_EXTENSION(initest, initest.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
