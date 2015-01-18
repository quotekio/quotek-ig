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

#include <vector>
#include <string>
#include <pthread.h>
#include "lssubscription.hpp"
#include "utils.hpp"
#include "assoc.hpp"

#define LS_STATUS_INITIALIZED 0x01
#define LS_STATUS_CONNECTED 0x02
#define LS_STATUS_RECEIVING 0x03

#define LS_STATUS_CONNECT_ERROR 0x40

class LSClient {

  public:

    //constructor
    LSClient(std::string url, 
    		     std::string username, 
    		     std::string password);


    void start();
    int connect();
    void setStatus(int);
    int getStatus();
    int addSubscription(LSSubscription*);
    int remSubscription(std::string);
    int subscribeAll();

    //callback wrappers
    static size_t streamCallbackWrapper(void*, size_t, size_t, void*);
    static void* streamThreadWrapper(void*);
    
    void setSessionId(std::string);
    void setControlEndpoint(std::string);

    AssocArray<std::vector<std::string> >* getData();
    
  private:
    
  	std::string ls_endpoint;
    std::string ls_control_endpoint;
  	std::string ls_username;
  	std::string ls_password;
    std::string ls_session_id;
  	std::vector<LSSubscription*> ls_subscriptions;
    int ls_status;
    pthread_t stream_thread;
    AssocArray<std::vector<std::string> > ls_data;

};