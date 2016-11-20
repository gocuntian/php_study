dnl $Id$
dnl config.m4 for extension people

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(people, for people support,
dnl Make sure that the comment is aligned:
[  --with-people             Include people support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(people, whether to enable people support,
dnl Make sure that the comment is aligned:
dnl [  --enable-people           Enable people support])

if test "$PHP_PEOPLE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-people -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/people.h"  # you most likely want to change this
  dnl if test -r $PHP_PEOPLE/$SEARCH_FOR; then # path given as parameter
  dnl   PEOPLE_DIR=$PHP_PEOPLE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for people files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PEOPLE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PEOPLE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the people distribution])
  dnl fi

  dnl # --with-people -> add include path
  dnl PHP_ADD_INCLUDE($PEOPLE_DIR/include)

  dnl # --with-people -> check for lib and symbol presence
  dnl LIBNAME=people # you may want to change this
  dnl LIBSYMBOL=people # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PEOPLE_DIR/$PHP_LIBDIR, PEOPLE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PEOPLELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong people lib version or lib not found])
  dnl ],[
  dnl   -L$PEOPLE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PEOPLE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(people, people.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
