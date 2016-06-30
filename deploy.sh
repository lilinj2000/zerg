#! /bin/sh

home_app=~/app

home_zerg=${home_app}/zerg

./configure --prefix=${home_zerg}

if test -d ${home_zerg}; then
    rm -rf ${home_zerg}
fi

make install

make distclean
