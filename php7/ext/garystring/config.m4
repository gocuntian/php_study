dnl $Id$
dnl config.m4 for extension garystring

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(garystring, for garystring support,
dnl Make sure that the comment is aligned:
[  --with-garystring             Include garystring support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(garystring, whether to enable garystring support,
dnl Make sure that the comment is aligned:
dnl [  --enable-garystring           Enable garystring support])

if test "$PHP_GARYSTRING" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-garystring -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/garystring.h"  # you most likely want to change this
  dnl if test -r $PHP_GARYSTRING/$SEARCH_FOR; then # path given as parameter
  dnl   GARYSTRING_DIR=$PHP_GARYSTRING
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for garystring files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GARYSTRING_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GARYSTRING_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the garystring distribution])
  dnl fi

  dnl # --with-garystring -> add include path
  dnl PHP_ADD_INCLUDE($GARYSTRING_DIR/include)

  dnl # --with-garystring -> check for lib and symbol presence
  dnl LIBNAME=garystring # you may want to change this
  dnl LIBSYMBOL=garystring # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GARYSTRING_DIR/$PHP_LIBDIR, GARYSTRING_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GARYSTRINGLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong garystring lib version or lib not found])
  dnl ],[
  dnl   -L$GARYSTRING_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GARYSTRING_SHARED_LIBADD)

  PHP_NEW_EXTENSION(garystring, garystring.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
