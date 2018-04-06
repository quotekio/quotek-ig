#!/bin/bash


#Fill in the IG API username/password/key.
BROKER_ARGS='{"username":"","password":"","api_key": "", "api_url":"https://demo-api.ig.com"}'

for i in `ls|grep test_| grep -v '\.c'`; do
  ./$i "$BROKER_ARGS"
done
