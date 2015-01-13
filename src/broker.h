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
#include "brokerio.h"

using namespace std;

class broker {

public:
    broker(string params, bool use_logging, bool use_profiling ) {}
    virtual ~broker() {}
    virtual int connect() {return 0;}
    virtual int requiresIndicesList() {return 0;}
    virtual int setIndicesList(vector<string> il) { return 0;}
    virtual vector<bvex> getValues() {vector<bvex> v1; return v1; }
    virtual vector<bpex> getPositions() {vector<bpex> p1; return p1; }
    virtual string closePos(string dealid) {return "";};
    virtual string openPos(string epic,string way,int nbc,int stop,int limit) {return "";}
    
private:

protected:
    vector<string> ilist;
    string username;
    string password;
    string api_key;
    string api_url;
    int requires_indices_list;

};

// the types of the class factories
typedef broker* create_t();
typedef void destroy_t(broker*);

#endif
