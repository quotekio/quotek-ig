#!/bin/sh

if [ -d ./lsclient_export/src ]; then
  rm -rf ./lsclient_export/src
fi

#git clone https://github.com/Velron/doxygen-bootstrapped ./lsclient_export/doxy-bootstrap

cp -r src ./lsclient_export/

rm ./lsclient_export/src/igconnector*
rm ./lsclient_export/src/broker.*
rm ./lsclient_export/src/brokerio.*
rm -rf ./lsclient_export/src/rapidjson

#generating html doc
cd lsclient_export/doxygen
doxygen lsclient.doxy
cp ext/doxy-boot.js ../doc/html/
cd ../..
