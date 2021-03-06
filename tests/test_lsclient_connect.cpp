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

  cout << "[TEST BROKER] LSClient Connection.." ;
  igConnector* c = get_igconnector(argv[1]);
  
  assert(c->connect() == 0); 
  assert(c->initPushService() == 0);
  LSClient* lsc = c->getLSClient();

  int ctimeout = 10;
  int i=0;
  while(i < ctimeout)  {
    
    if ( lsc->getStatus() == LS_STATUS_CONNECTED ) {
      cout << "[OK]" << endl;
      exit(0);
    }

    i++;
    sleep(1);
  }

  cout << "[ERROR]" << endl;
  exit(1);


}