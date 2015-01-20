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

  cout << "[TEST BROKER] pushmode getvalues.." ;

  std::vector<std::string> ilist;
  ilist.push_back("IX.D.CAC.IMF.IP");
  ilist.push_back("IX.D.DAX.IMF.IP");

  igConnector* c = get_igconnector_connected_pushmode(argv[1], ilist);
  



  sleep(10);

  vector<bvex> vals = c->getValues();

  for (int i=0;i< vals.size();i++) {

    cout << "EPIC:" << vals[i].epic << endl;
    cout << "BID:" << vals[i].bid << endl;
    cout << "OFFER:" << vals[i].offer << endl;
  }

  sleep(2);

  vals = c->getValues();

  for (int i=0;i< vals.size();i++) {

    cout << "EPIC:" << vals[i].epic << endl;
    cout << "BID:" << vals[i].bid << endl;
    cout << "OFFER:" << vals[i].offer << endl;
  }



}

