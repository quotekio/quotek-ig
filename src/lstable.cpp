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

#include "lstable.hpp"

std::vector<LSTable*> LSTable::table_list;

LSTable::LSTable(int nfields) {
  nb_fields = nfields;
}

AssocArray< std::vector<std::string> >* LSTable::getData() {
  return &data;
}

std::vector<std::string>* LSTable::getItemData(std::string item_name) {
  return &data[item_name];
}

int LSTable::appendData(std::string item_name, std::vector<std::string> item_data) {
  if ( item_data.size() != nb_fields ) return 1;
  data[item_name] = item_data;
  return 0;
}


/* STATIC METHODS */

LSTable* LSTable::getTable(int tnum) {

  if ( tnum >= LSTable::table_list.size() ) {
    return NULL;
  }
  return LSTable::table_list[tnum];
}

LSTable* LSTable::addTable(int nb_fields) {

  	LSTable* t = new LSTable(nb_fields);
  	LSTable::table_list.push_back(t);
    return t;
}

int LSTable::removeTable(int tnum) {

  if ( tnum >= LSTable::table_list.size() ) {
    return 1;
  }

  LSTable::table_list.erase(LSTable::table_list.begin() + tnum);
  return 0;
}

int LSTable::append(int tnum, int item_num, std::vector<std::string> item_data) {

  LSTable* s = LSTable::getTable(tnum);
  


}



