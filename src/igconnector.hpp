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

#include "broker.hpp"
#include "assoc.h"
#include "utils.h"

#include <curl/curl.h>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include <stdlib.h>
#include <pthread.h>
#include "lsclient/lsclient.h"

#define MAX_UPTIME 42000


class igConnector : public broker {
public:

    bool requires_indices_list;

    igConnector();
    igConnector(string, bool, bool, string);
    virtual int initialize(string, bool, bool, string);
    virtual int requiresIndicesList();
    virtual int setIndicesList(vector<string>);
    virtual int connect();
    virtual vector<bvex> getValues();
    virtual vector<bpex> getPositions();
    virtual string openPos(string,string,int,int,int);
    virtual string closePos(string);
  
private:
  
  string cst;
  string security_token;
  AssocArray<string> currencies_map;
  vector<bpex> lastpos;
  int uptime_s;
  LSClient* ls_client;

  inline curl_slist* addHeaders();
  static void* staticUptimeLoop(void* p);
  void* uptimeLoop(void*);
  void loadCurrenciesMap();
};

// the class factories
extern "C" broker* create() {
    return new igConnector();
}

extern "C" void destroy(broker* p) {
    delete p;
}
