#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(zerg, 0.1, lilinj2000@gmail.com)
AC_CONFIG_SRCDIR([])
#AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
LT_INIT
AC_PROG_RANLIB
# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
#AC_CHECK_HEADER_STDBOOL

AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

# Checks for library functions.
LT_RELEASE=0.1
LT_CURRENT=0
LT_REVISION=1
LT_AGE=0
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

home_3rd=~/3rd
home_libs=~/libs

if test -d /llj/3rd ; then
   home_3rd=/llj/3rd
fi

if test -d /llj/libs ; then
   home_libs=/llj/libs
fi

dnl boost lib
AC_ARG_WITH([boost],
    [AS_HELP_STRING([--with-boost],
        [home path of the boost, defaults to $home_3rd/boost])],
    [BOOST_HOME="$withval"],
    [BOOST_HOME="$home_3rd/boost"])
AC_SUBST([BOOST_HOME])

BOOST_CPPFLAGS="-I$BOOST_HOME/include -DBOOST_ALL_DYN_LINK"
BOOST_LIBADD="$BOOST_HOME/lib/libboost_log_setup.so \
              $BOOST_HOME/lib/libboost_log.so \
	      $BOOST_HOME/lib/libboost_filesystem.so \
  	      $BOOST_HOME/lib/libboost_program_options.so \
	      $BOOST_HOME/lib/libboost_regex.so \
	      $BOOST_HOME/lib/libboost_thread.so \
	      $BOOST_HOME/lib/libboost_chrono.so \
	      $BOOST_HOME/lib/libboost_date_time.so \
	      $BOOST_HOME/lib/libboost_system.so"
AC_SUBST(BOOST_CPPFLAGS)
AC_SUBST(BOOST_LIBADD)

dnl soil lib
AC_ARG_WITH([soil],
    [AS_HELP_STRING([--with-soil],
        [home path of the soil, defaults to $home_libs/soil])],
    [SOIL_HOME="$withval"],
    [SOIL_HOME="$home_libs/soil"])
AC_SUBST([SOIL_HOME])

SOIL_CPPFLAGS="-I$SOIL_HOME/include"
SOIL_LIBADD="$SOIL_HOME/lib/libsoil.la"
AC_SUBST(SOIL_CPPFLAGS)
AC_SUBST(SOIL_LIBADD)

dnl spy lib
AC_ARG_WITH([spy],
    [AS_HELP_STRING([--with-spy],
        [home path of the spy, defaults to $home_libs/spy])],
    [SPY_HOME="$withval"],
    [SPY_HOME="$home_libs/spy"])
AC_SUBST([SPY_HOME])

SPY_CPPFLAGS="-I$SPY_HOME/include"
SPY_LIBADD="$SPY_HOME/lib/libspy.la"
AC_SUBST(SPY_CPPFLAGS)
AC_SUBST(SPY_LIBADD)

dnl zebra lib
AC_ARG_WITH([zebra],
    [AS_HELP_STRING([--with-zebra],
        [home path of the zebra, defaults to $home_libs/zebra])],
    [ZEBRA_HOME="$withval"],
    [ZEBRA_HOME="$home_libs/zebra"])
AC_SUBST([ZEBRA_HOME])

ZEBRA_CPPFLAGS="-I$ZEBRA_HOME/include"
ZEBRA_LIBADD="$ZEBRA_HOME/lib/libzebra.la"
AC_SUBST(ZEBRA_CPPFLAGS)
AC_SUBST(ZEBRA_LIBADD)

dnl rapidjson lib
RAPIDJSON_HOME=$home_3rd/rapidjson
AC_ARG_WITH([rapidjson], 
    [AS_HELP_STRING([--with-rapidjson],
        [home path of the rapidjson, defaults to $RAPIDJSON_HOME])],
    [RAPIDJSON_HOME="$withval"],
    [RAPIDJSON_HOME="$RAPIDJSON_HOME"])
AC_SUBST([RAPIDJSON_HOME])

RAPIDJSON_CPPFLAGS="-I$RAPIDJSON_HOME/include"
AC_SUBST(RAPIDJSON_CPPFLAGS)

dnl json lib
AC_ARG_WITH([json],
    [AS_HELP_STRING([--with-json],
        [home path of the json, defaults to $home_libs/json])],
    [JSON_HOME="$withval"],
    [JSON_HOME="$home_libs/json"])
AC_SUBST([JSON_HOME])

JSON_CPPFLAGS="-I$JSON_HOME/include"
JSON_LIBADD="$JSON_HOME/lib/libjson.la"
AC_SUBST(JSON_CPPFLAGS)
AC_SUBST(JSON_LIBADD)

AC_OUTPUT([
	Makefile
	src/Makefile])


