dnl $Id$
dnl config.m4 for extension garyfile

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(garyfile, for garyfile support,
dnl Make sure that the comment is aligned:
[  --with-garyfile             Include garyfile support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(garyfile, whether to enable garyfile support,
dnl Make sure that the comment is aligned:
dnl [  --enable-garyfile           Enable garyfile support])

if test "$PHP_GARYFILE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-garyfile -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/garyfile.h"  # you most likely want to change this
  dnl if test -r $PHP_GARYFILE/$SEARCH_FOR; then # path given as parameter
  dnl   GARYFILE_DIR=$PHP_GARYFILE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for garyfile files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GARYFILE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GARYFILE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the garyfile distribution])
  dnl fi

  dnl # --with-garyfile -> add include path
  dnl PHP_ADD_INCLUDE($GARYFILE_DIR/include)

  dnl # --with-garyfile -> check for lib and symbol presence
  dnl LIBNAME=garyfile # you may want to change this
  dnl LIBSYMBOL=garyfile # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GARYFILE_DIR/$PHP_LIBDIR, GARYFILE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GARYFILELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong garyfile lib version or lib not found])
  dnl ],[
  dnl   -L$GARYFILE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GARYFILE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(garyfile, garyfile.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
