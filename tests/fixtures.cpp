#include "fixtures.hpp"

igConnector* get_igconnector(string broker_params) {
  return new igConnector(broker_params, false, false, "poll");
}

igConnector* get_igconnector_connected_pollmode(string broker_params) {
  igConnector* c = new igConnector(broker_params, false, false, "poll");  
  c->connect();
  return c;
}

igConnector* get_igconnector_connected_pushmode(string broker_params, std::vector<std::string> ilist) {
  igConnector* c = new igConnector(broker_params, false, false, "push");
  c->setIndicesList(ilist);  
  c->connect();
  return c;
}

igConnector* get_igconnector_connected_logging(string broker_params) {
  igConnector* c = new igConnector(broker_params, true, false, "pull");  
  c->connect();
  return c;
}

igConnector* get_igconnector_connected_profiling(string broker_params) {
  igConnector* c = new igConnector(broker_params, false, true, "pull");  
  c->connect();
  return c;
}
