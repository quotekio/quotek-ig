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

broker::broker() {

}

broker::~broker() {

}

int broker::initialize(string broker_params, 
                               bool use_logging, 
                               bool use_profiling, 
                               string mode) {

  return 0;
}

int broker::connect() {

  return 0;
}

int broker::initPushService() {
  return 0;
}

void broker::setMode(string) {

}

string broker::getMode() {
  return "";
}


int broker::requiresIndicesList() {

  return 0;
}

int broker::setIndicesList(vector<string> il) { 

  return 0;
}

vector<bvex> broker::getValues() {
  vector<bvex> v1; 
  return v1; 
}

vector<bpex> broker::getPositions() {
  vector<bpex> p1; 
  return p1; 
}

string broker::closePos(string dealid, int size) {

  return "";
}

bpex broker::openPos(string epic,
                       string way,
                       int nbc,
                       float stop,
                       float limit) {
  bpex p1;
  return p1;
}


std::vector<brokerError*>* broker::getErrors() {
  return &errlist;
}

brokerError* broker::addError(int timestamp, string type, string message) {

  brokerError *b = new brokerError(timestamp, type, message);
  errlist.push_back(b);
  return b;

}


brokerError::brokerError(int t, string tp, string msg) {

  timestamp = t;
  type = tp;
  message = msg;
}








