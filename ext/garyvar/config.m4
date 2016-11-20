dnl $Id$
dnl config.m4 for extension garyvar

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(garyvar, for garyvar support,
dnl Make sure that the comment is aligned:
[  --with-garyvar             Include garyvar support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(garyvar, whether to enable garyvar support,
dnl Make sure that the comment is aligned:
dnl [  --enable-garyvar           Enable garyvar support])

if test "$PHP_GARYVAR" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-garyvar -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/garyvar.h"  # you most likely want to change this
  dnl if test -r $PHP_GARYVAR/$SEARCH_FOR; then # path given as parameter
  dnl   GARYVAR_DIR=$PHP_GARYVAR
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for garyvar files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GARYVAR_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GARYVAR_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the garyvar distribution])
  dnl fi

  dnl # --with-garyvar -> add include path
  dnl PHP_ADD_INCLUDE($GARYVAR_DIR/include)

  dnl # --with-garyvar -> check for lib and symbol presence
  dnl LIBNAME=garyvar # you may want to change this
  dnl LIBSYMBOL=garyvar # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GARYVAR_DIR/$PHP_LIBDIR, GARYVAR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GARYVARLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong garyvar lib version or lib not found])
  dnl ],[
  dnl   -L$GARYVAR_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GARYVAR_SHARED_LIBADD)

  PHP_NEW_EXTENSION(garyvar, garyvar.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
