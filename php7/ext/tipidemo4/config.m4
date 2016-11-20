dnl $Id$
dnl config.m4 for extension tipidemo4

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(tipidemo4, for tipidemo4 support,
dnl Make sure that the comment is aligned:
dnl [  --with-tipidemo4             Include tipidemo4 support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(tipidemo4, whether to enable tipidemo4 support,
dnl Make sure that the comment is aligned:
dnl [  --enable-tipidemo4           Enable tipidemo4 support])

if test "$PHP_TIPIDEMO4" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-tipidemo4 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/tipidemo4.h"  # you most likely want to change this
  dnl if test -r $PHP_TIPIDEMO4/$SEARCH_FOR; then # path given as parameter
  dnl   TIPIDEMO4_DIR=$PHP_TIPIDEMO4
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for tipidemo4 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TIPIDEMO4_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TIPIDEMO4_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the tipidemo4 distribution])
  dnl fi

  dnl # --with-tipidemo4 -> add include path
  dnl PHP_ADD_INCLUDE($TIPIDEMO4_DIR/include)

  dnl # --with-tipidemo4 -> check for lib and symbol presence
  dnl LIBNAME=tipidemo4 # you may want to change this
  dnl LIBSYMBOL=tipidemo4 # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TIPIDEMO4_DIR/$PHP_LIBDIR, TIPIDEMO4_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TIPIDEMO4LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong tipidemo4 lib version or lib not found])
  dnl ],[
  dnl   -L$TIPIDEMO4_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TIPIDEMO4_SHARED_LIBADD)

  PHP_NEW_EXTENSION(tipidemo4, tipidemo4.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
