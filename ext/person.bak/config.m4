dnl $Id$
dnl config.m4 for extension person

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(person, for person support,
dnl Make sure that the comment is aligned:
[  --with-person             Include person support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(person, whether to enable person support,
dnl Make sure that the comment is aligned:
dnl [  --enable-person           Enable person support])

if test "$PHP_PERSON" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-person -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/person.h"  # you most likely want to change this
  dnl if test -r $PHP_PERSON/$SEARCH_FOR; then # path given as parameter
  dnl   PERSON_DIR=$PHP_PERSON
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for person files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PERSON_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PERSON_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the person distribution])
  dnl fi

  dnl # --with-person -> add include path
  dnl PHP_ADD_INCLUDE($PERSON_DIR/include)

  dnl # --with-person -> check for lib and symbol presence
  dnl LIBNAME=person # you may want to change this
  dnl LIBSYMBOL=person # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PERSON_DIR/$PHP_LIBDIR, PERSON_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PERSONLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong person lib version or lib not found])
  dnl ],[
  dnl   -L$PERSON_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PERSON_SHARED_LIBADD)

  PHP_NEW_EXTENSION(person, person.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
