dnl $Id$
dnl config.m4 for extension tipidemo02

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(tipidemo02, for tipidemo02 support,
dnl Make sure that the comment is aligned:
[  --with-tipidemo02             Include tipidemo02 support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(tipidemo02, whether to enable tipidemo02 support,
dnl Make sure that the comment is aligned:
dnl [  --enable-tipidemo02           Enable tipidemo02 support])

if test "$PHP_TIPIDEMO02" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-tipidemo02 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/tipidemo02.h"  # you most likely want to change this
  dnl if test -r $PHP_TIPIDEMO02/$SEARCH_FOR; then # path given as parameter
  dnl   TIPIDEMO02_DIR=$PHP_TIPIDEMO02
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for tipidemo02 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TIPIDEMO02_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TIPIDEMO02_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the tipidemo02 distribution])
  dnl fi

  dnl # --with-tipidemo02 -> add include path
  dnl PHP_ADD_INCLUDE($TIPIDEMO02_DIR/include)

  dnl # --with-tipidemo02 -> check for lib and symbol presence
  dnl LIBNAME=tipidemo02 # you may want to change this
  dnl LIBSYMBOL=tipidemo02 # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TIPIDEMO02_DIR/$PHP_LIBDIR, TIPIDEMO02_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TIPIDEMO02LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong tipidemo02 lib version or lib not found])
  dnl ],[
  dnl   -L$TIPIDEMO02_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TIPIDEMO02_SHARED_LIBADD)

  PHP_NEW_EXTENSION(tipidemo02, tipidemo02.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
