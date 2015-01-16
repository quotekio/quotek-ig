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

#include "igconnector.hpp"


igConnector::igConnector() : broker() {

}

igConnector::igConnector(string broker_params, 
                         bool use_logging, 
                         bool use_profiling, 
                         string mode) {

      initialize(broker_params, use_logging, use_profiling, mode);
}

int igConnector::initialize(string broker_params, 
                            bool use_logging, 
                            bool use_profiling, 
                            string mode ) {

      rapidjson::Document d;
      d.Parse<0>(broker_params.c_str());

      if (d.HasParseError() ) {  
        return 1;
      }
      
      username = d["username"].GetString();
      password = d["password"].GetString();
      api_key = d["api_key"].GetString();
      api_url = d["api_url"].GetString();

      connector_mode = mode;
      requires_indices_list = true;

      //creates uptime loop, to reconnect when IG session expires.
      pthread_t uptime_loop;
      pthread_create(&uptime_loop,NULL,igConnector::staticUptimeLoop, this);

      return 0;
    }

int igConnector::requiresIndicesList() {
  return requires_indices_list;
}

int igConnector::setIndicesList(vector<string> il) {
      ilist = il;
      return 0;
}
  
int igConnector::connect() {

      cst = "";
      security_token = "";

      string temp = "";
      string htemp = "";
      string pdata = "";
      struct curl_slist *headers = NULL;
      CURL* ch = curl_easy_init();

      //Adds API Key to header;
      string apikey_header = "X-IG-API-KEY: " + api_key;
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, apikey_header.c_str());

      //creates post data
      pdata = "{\"identifier\":\"" + username + "\",";
      pdata += "\"password\":\"" + password + "\" }";

      string c_url = api_url + "/gateway/deal/session";

      curl_easy_setopt(ch,CURLOPT_URL,c_url.c_str());
      curl_easy_setopt(ch,CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(ch,CURLOPT_POST,1);
      curl_easy_setopt(ch,CURLOPT_POSTFIELDS, pdata.c_str());
      curl_easy_setopt(ch,CURLOPT_WRITEFUNCTION,curl_write_handler);
      curl_easy_setopt(ch,CURLOPT_WRITEDATA,&temp);
      curl_easy_setopt(ch,CURLOPT_HEADERFUNCTION,curl_write_handler);
      curl_easy_setopt(ch,CURLOPT_HEADERDATA,&htemp);

      curl_easy_perform(ch);
      curl_easy_cleanup(ch);
      curl_slist_free_all(headers);

      rapidjson::Document d;

      d.Parse<0>(temp.c_str());
      if (d.HasParseError() ) {        
        return 1;
      }
     
      ls_endpoint = d["lightstreamerEndpoint"].GetString();
      cout << ls_endpoint << endl;
    

      vector<string> hdata = split(htemp,'\n');

      for (int i=0;i<hdata.size();i++) {

        if ( hdata[i].find("CST: ") == 0 ) {
          cst = hdata[i];
        }

        if ( hdata[i].find("X-SECURITY-TOKEN: ") == 0 ) {
          security_token = hdata[i];
        }

      }

      if ( cst == "" || security_token == "") {
        return 1;
      }

      //loads currencies map right after connect
      loadCurrenciesMap();

      return 0;
    }


/*
int igConnector::LSSetSubscribtions(vector<string>* subscribtions) {

}
*/

int igConnector::LSConnect() {

   std::string ncst = cst;
   std::string xst = security_token;

   sreplace(ncst,"CST: ","CST-");
   trim(ncst);

   sreplace(xst, "X-SECURITY-TOKEN: ", "XST-");
   trim(xst);
   
   std::string ls_password;
   ls_password = ncst + "|" + xst;
   ls_client = new LSClient(ls_endpoint, username, ls_password);
   return ls_client->connect();
}

vector<bvex> igConnector::getValues() {
   
      vector<bvex> result;

      struct curl_slist *headers = NULL;
      string epics_list = "";
      rapidjson::Document d;

      for (int i=0;i<ilist.size();i++)  {
        epics_list += ilist[i] + ",";
      }

      string c_url = api_url + "/gateway/deal/markets?epics=" + epics_list;

      headers = addHeaders();

      string temp = "";
      CURL* ch = curl_easy_init();
      curl_easy_setopt(ch,CURLOPT_URL,c_url.c_str());
      curl_easy_setopt(ch,CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(ch,CURLOPT_WRITEFUNCTION,curl_write_handler);
      curl_easy_setopt(ch,CURLOPT_WRITEDATA,&temp);
      curl_easy_perform(ch);
      curl_easy_cleanup(ch);
      curl_slist_free_all(headers);

      d.Parse<0>(temp.c_str());
      if (d.HasParseError() ) return result;

      if (d["marketDetails"].IsArray()) {
        
        for (int i=0;i<d["marketDetails"].Capacity();i++) {

          bvex ex1;
          ex1.epic = d["marketDetails"][rapidjson::SizeType(i)]["instrument"]["epic"].GetString();
          ex1.offer = d["marketDetails"][rapidjson::SizeType(i)]["snapshot"]["offer"].GetDouble();
          ex1.bid = d["marketDetails"][rapidjson::SizeType(i)]["snapshot"]["bid"].GetDouble();
          result.push_back(ex1);

        }

      }

      return result;
}

vector<bpex> igConnector::getPositions() {

      vector<bpex> result;

      string temp = "";
      CURL* ch = curl_easy_init();
      string c_url = api_url + "/gateway/deal/positions";
      curl_slist *headers = NULL;
      rapidjson::Document d;
 
      headers = addHeaders();

      curl_easy_setopt(ch,CURLOPT_URL,c_url.c_str());
      curl_easy_setopt(ch,CURLOPT_WRITEFUNCTION,curl_write_handler);
      curl_easy_setopt(ch,CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(ch,CURLOPT_WRITEDATA,&temp);
      curl_easy_perform(ch);
      curl_easy_cleanup(ch);

      curl_slist_free_all(headers);
      
      d.Parse<0>(temp.c_str());
      if (d.HasParseError() ) return result;

      if (d["positions"].IsArray()) {
        for (int i=0;i<d["positions"].Capacity();i++) {

          bpex p1;

          rapidjson::Value& jval = d["positions"][rapidjson::SizeType(i)]["position"];
          rapidjson::Value& jval_m = d["positions"][rapidjson::SizeType(i)]["market"];

          p1.size = roundint(jval["dealSize"].GetDouble()); 

          string direction = jval["direction"].GetString();

          //puts size in reverse if direction is sell.
          if ( direction == "SELL" )  {
            p1.size *= -1;
          }

          p1.dealid = jval["dealId"].GetString();
          p1.open = jval["openLevel"].GetDouble();
          p1.epic = jval_m["epic"].GetString();

          p1.stop = 0;
          
          if ( ! jval["stopLevel"].IsNull() ) {
            p1.stop = jval["stopLevel"].GetDouble();
          }

          p1.limit = 0;
          if (! jval["limitLevel"].IsNull() ) {
            p1.limit = jval["limitLevel"].GetDouble();
          }

          result.push_back(p1);
          
        }
      }

      lastpos = result;
      return result;
}
    

string igConnector::openPos(string epic,string way,int nbc,int stop,int limit) {

    string temp = "";
    string pdata = "";
    string stop_str = "";
    string limit_str = "";
    CURL* ch = curl_easy_init();
    string c_url = api_url + "/gateway/deal/positions/otc";
    curl_slist *headers = NULL;
    rapidjson::Document d;
    
    headers = addHeaders();

    if (stop == 0) {
      stop_str = "null";
    }
    else {
      stop_str = "\"" + int2string(stop) + "\"";
    }

    if (limit == 0) {
      limit_str = "null";
    }
    else  {
      limit_str = "\"" + int2string(limit) + "\"";
    }

    //build post data
    pdata = "{\n";
    pdata += "    \"epic\": \"" + epic + "\",\n";
    pdata += "    \"expiry\": \"-\",\n";
    pdata += "    \"direction\": \"" + upper(way) + "\",\n";
    pdata += "    \"size\": \"" + int2string(nbc) + "\",\n";
    pdata += "    \"orderType\": \"MARKET\",\n";
    //pdata += "    \"level\": null,\n";
    pdata += "    \"guaranteedStop\": \"false\",\n";
    pdata += "    \"stopDistance\": " + stop_str + ",\n";
    pdata += "    \"stopLevel\": null,\n";
    //pdata += "    \"trailingStop\": null,\n";
    //pdata += "    \"trailingStopIncrement\": null,\n";
    pdata += "    \"forceOpen\": \"true\",\n";
    pdata += "    \"limitDistance\": " + limit_str + ",\n";
    pdata += "    \"limitLevel\": null,\n";
    //pdata += "    \"quoteId\": null,\n";
    pdata += "    \"currencyCode\": \"" + currencies_map[epic] + "\"\n" ;
    pdata += "}"; 

    curl_easy_setopt(ch,CURLOPT_URL,c_url.c_str());
    curl_easy_setopt(ch,CURLOPT_WRITEFUNCTION,curl_write_handler);
    curl_easy_setopt(ch,CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(ch,CURLOPT_WRITEDATA,&temp);
    curl_easy_setopt(ch,CURLOPT_POST, 1);
    curl_easy_setopt(ch,CURLOPT_POSTFIELDS, pdata.c_str());
    curl_easy_perform(ch);
    curl_easy_cleanup(ch);

    curl_slist_free_all(headers);
    
    d.Parse<0>(temp.c_str());
    if (d.HasParseError() ) return "";

    string res = "ERROR: NULLREF";
    if (! d["dealReference"].IsNull() ) res = d["dealReference"].GetString();
    else if (! d["errorCode"].IsNull()) res = std::string("ERROR:") + d["errorCode"].GetString();
    return res;

  }

string igConnector::closePos(string dealid) {
  
    string temp = "";
    string c_url = api_url + "/gateway/deal/positions/otc" ;
    curl_slist *headers = NULL;
    rapidjson::Document d;
    string pdata;

    bpex pos;

    //finds position in current list
    for (int i=0;i<lastpos.size();i++) {
      if (lastpos[i].dealid == dealid) {
        pos = lastpos[i];
        break;
      }
    }

    string way = ( pos.size < 0 ) ? "BUY" : "SELL";
    int size = (pos.size < 0) ? pos.size * -1 : pos.size; 
    
    headers = addHeaders();

    //hack IG DELETE with body Issue
    headers = curl_slist_append(headers, "_METHOD: DELETE");

    pdata = "{\n";
    pdata += "    \"dealId\": \"" + dealid + "\",\n";
    pdata += "    \"expiry\": \"-\",\n";
    pdata += "    \"direction\": \"" + upper(way) + "\",\n";
    pdata += "    \"size\": \"" + int2string(size) + "\",\n";
    pdata += "    \"orderType\": \"MARKET\"\n";
    pdata += "}";

    CURL* ch = curl_easy_init();
    curl_easy_setopt(ch,CURLOPT_URL,c_url.c_str());
    curl_easy_setopt(ch,CURLOPT_WRITEFUNCTION,curl_write_handler);
    curl_easy_setopt(ch,CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(ch,CURLOPT_WRITEDATA,&temp);
    //hack IG DELETE with body Issue
    //curl_easy_setopt(ch, CURLOPT_CUSTOMREQUEST, "DELETE"); 
    curl_easy_setopt(ch,CURLOPT_POST,1);
    curl_easy_setopt(ch,CURLOPT_POSTFIELDS, pdata.c_str());
    curl_easy_perform(ch);
    curl_easy_cleanup(ch);

    curl_slist_free_all(headers);

    d.Parse<0>(temp.c_str());
    if (d.HasParseError() ) return "";


    string res = "ERROR: NULLREF";
    if (! d["dealReference"].IsNull() ) res = d["dealReference"].GetString();
    else if (! d["errorCode"].IsNull()) res = std::string("ERROR:") + d["errorCode"].GetString();
    return res;

}

curl_slist* igConnector::addHeaders() {

    curl_slist* headers = NULL;

    //Adds API Key to header;
    string apikey_header = "X-IG-API-KEY: " + api_key;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "version: 1");
    headers = curl_slist_append(headers, apikey_header.c_str());
    headers = curl_slist_append(headers, cst.c_str());
    headers = curl_slist_append(headers, security_token.c_str());
  
    return headers;

}


void* igConnector::staticUptimeLoop(void* p) {
    static_cast<igConnector*>(p)->uptimeLoop(NULL);
    return NULL;
}

void* igConnector::uptimeLoop(void*) {
    uptime_s = 0;
    while(1) {
      uptime_s++;
      if (uptime_s >= MAX_UPTIME) {
        connect();

        uptime_s =0;
      }
      sleep(1);

    }
    return NULL;
}

void igConnector::loadCurrenciesMap() {

    struct curl_slist *headers = NULL;
    string epics_list = "";
    rapidjson::Document d;

    for (int i=0;i<ilist.size();i++)  {
      epics_list += ilist[i] + ",";
    }

    string c_url = api_url + "/gateway/deal/markets?epics=" + epics_list;

    headers = addHeaders();

    string temp = "";
    CURL* ch = curl_easy_init();
    curl_easy_setopt(ch,CURLOPT_URL,c_url.c_str());
    curl_easy_setopt(ch,CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(ch,CURLOPT_WRITEFUNCTION,curl_write_handler);
    curl_easy_setopt(ch,CURLOPT_WRITEDATA,&temp);
    curl_easy_perform(ch);
    curl_easy_cleanup(ch);
    curl_slist_free_all(headers);

    
    d.Parse<0>(temp.c_str());
    if (d.HasParseError()) return ;

    if (d["marketDetails"].IsArray()) {
      
      for (int i=0;i<d["marketDetails"].Capacity();i++) {

        string epic = d["marketDetails"][rapidjson::SizeType(i)]["instrument"]["epic"].GetString();
        currencies_map[epic] = "";
        rapidjson::Value& c_array = d["marketDetails"][rapidjson::SizeType(i)]["instrument"]["currencies"];

        if (c_array.IsArray()) {

          //pick the best suite currency
          for (int j=0;j< c_array.Capacity();j++  ) {

            string c_array_code = c_array[rapidjson::SizeType(j)]["code"].GetString();

            if ( c_array_code == "EUR"  ) {
              currencies_map[epic] = "EUR";
              break; 
            }             

            else if ( c_array_code == "USD"  ) {
              currencies_map[epic] = "USD";
              break; 
            }
          }

          if (currencies_map[epic] == "")  {
            currencies_map[epic] = c_array[rapidjson::SizeType(0)]["code"].GetString();
          }

        }

      }

    }

}

// the class factories
extern "C" broker* create() {
    return new igConnector();
}

extern "C" void destroy(broker* p) {
    delete p;
}
