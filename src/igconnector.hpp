/*
IG api C++ Connector v1.0
Copyright(c) 2015 Clément Gamé.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES LOSS 
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
THE USE OF THIS SOFTWARE,EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef IGCONNECTOR_H
#define IGCONNECTOR_H

#include "broker.hpp"
#include "utils.hpp"
#include "assoc.hpp"
#include "lsclient.hpp"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_UPTIME 42000

#define LS_STREAM_TIMEOUT 10


class igConnector : public broker {
public:

    bool requires_indices_list;

    igConnector();
    igConnector(string, bool, bool, string);
    virtual int initialize(string, bool, bool, string);
    virtual int requiresIndicesList();
    virtual int setIndicesList(vector<string>);
    virtual int connect();
    virtual void setMode(string);
    virtual string getMode();
    virtual vector<bvex> getValues();
    virtual vector<bpex> getPositions();
    virtual bpex openPos(string,string,int,float,float);
    virtual string closePos(string, int size);
    virtual int initPushService();
    virtual std::vector<brokerError*>* getErrors();

    LSClient* getLSClient();


private:

  brokerError* addError(int, string, string);

  bpex confirmOpenDeal(std::string dealref);
  string confirmCloseDeal(std::string dealref);

  string cst;
  string security_token;
  string client_id;
  AssocArray<string> currencies_map;
  
  int uptime_s;
  LSClient* ls_client;
  string ls_endpoint;
  vector<string> ls_subscriptions;

  inline curl_slist* addHeaders();
  static void* staticUptimeLoop(void* p);
  void* uptimeLoop(void*);
  void loadCurrenciesMap();

  vector<bvex> getValues_push();
  vector<bvex> getValues_poll();

};

#endif