#include "fixtures.hpp"

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

#include "fixtures.hpp"


int main(int argc, char** argv) {
  
  if (argc < 2) {
    cout << "[ERROR] Not enough arguments" << endl;
    exit(1);
  }

  cout << "[TEST BROKER] LSClient getdata.." ;
  igConnector* c = get_igconnector(argv[1]);
  
  assert(c->connect() == 0); 
  assert(c->LSStart() == 0);
  LSClient* lsc = c->getLSClient();

  int ctimeout = 10;
  int i=0;
  int connected = 0;
  while(i < ctimeout)  {

    if ( lsc->getStatus() == LS_STATUS_CONNECTED ) {
      connected = 1;
      break;
    }

    i++;
    sleep(1);
  }

  if (!connected) {
    cout << "[ERROR]" << endl;
    exit(1);
  }

  std::vector<std::string> itemlist;
  itemlist.push_back("MARKET:IX.D.CAC.IMF.IP");

  std::vector<std::string> fields;
  fields.push_back("BID");
  fields.push_back("OFFER");

  LSSubscription *s1 = new LSSubscription("MARKET", itemlist, fields);

  lsc->addSubscription(s1);

  if (lsc->subscribeAll() != 0 ) {
    cout << "[ERROR]" << endl;
    exit(1);
  }

  sleep(10);

  AssocArray<std::vector<std::string>>* lsdata = lsc->getData();

  assert( lsdata->Size() > 0);
  assert( lsdata->GetItemName(0) == "MARKET:IX.D.CAC.IMF.IP");

  float f1 = atof(lsdata->at(0)[0].c_str());
  float f2 = atof(lsdata->at(0)[1].c_str());
  
  assert(f1 > 0 && f2 > 0);
  
  cout << "[OK]" << endl;
  
  exit(0);

}