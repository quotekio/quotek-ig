/*
This is a Quick'n'Dirty C++ implementation of LightStreamer Client
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

#include "lsclient.hpp"
#include "http.hpp"

LSClient::LSClient(std::string url, 
    		       std::string username, 
    		       std::string password) {

  ls_endpoint = url;
  ls_username = username;
  ls_password = password;
  
}

int LSClient::connect() {

  //creates a new LS session
  http* req = new http();
  AssocArray<string> pdata;
  pdata["LS_USERNAME"] = ls_username;
  pdata["LS_PASSWORD"] = ls_password;

  std::string create_session_url = ls_endpoint + "/lightstreamer/create_session.txt";  
  std::string foo = req->post(create_session_url, pdata);
  
  cout << foo << endl;

  return 0;

}

int LSClient::addSubscription(LSSubscription* s) {
	ls_subscriptions.push_back(s);
	return 0;
}
int LSClient::remSubscription(std::string object_id) {

  for(int i=0;i<ls_subscriptions.size();i++) {
    if (ls_subscriptions[i]->getObjectId() == object_id) {
      //delete vector entry
    }
  }

  return 0;
}




