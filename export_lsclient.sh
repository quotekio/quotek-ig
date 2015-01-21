#!/bin/sh

if [ -d ./lsclient_export/src ]; then
  rm -rf ./lsclient_export/src
fi

cp -r src ./lsclient_export/

rm ./lsclient_export/src/igconnector*
rm ./lsclient_export/src/broker.*
rm ./lsclient_export/src/brokerio.*
rm -rf ./lsclient_export/src/rapidjson

