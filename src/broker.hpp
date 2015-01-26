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


#ifndef broker_H
#define broker_H

#include <vector>
#include <string>
#include <iostream>
#include "brokerio.hpp"

using namespace std;


class brokerError  {

  public:
    brokerError(int, string, string);
    int timestamp;
    string type;
    string message;

};



class broker {

public:
    broker();
    virtual ~broker();
    virtual int initialize(string, bool, bool, string);
    virtual void setMode(string);
    virtual string getMode();
    virtual int connect();
    virtual int initPushService();
    virtual int requiresIndicesList();
    virtual int setIndicesList(vector<string>);
    virtual vector<bvex> getValues();
    virtual vector<bpex> getPositions();
    virtual string closePos(string, int size);
    virtual bpex openPos(string, string, int ,int ,int);
    virtual std::vector<brokerError*>* getErrors();

private:

protected:
    vector<string> ilist;
    vector<brokerError*> errlist;
    string username;
    string password;
    string api_key;
    string api_url;
    string connector_mode;
    int requires_indices_list;

    brokerError* addError(int, string, string);

};

// the types of the class factories
typedef broker* create_t();
typedef void destroy_t(broker*);

#endif
