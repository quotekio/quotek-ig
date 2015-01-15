#include "fixtures.hpp"

igConnector* get_igconnector(string broker_params) {
  return new igConnector(broker_params, false, false, "pull");
}

igConnector* get_igconnector_connected_pullmode(string broker_params) {
  igConnector* c = new igConnector(broker_params, false, false, "pull");  
  c->connect();
  return c;
}

igConnector* get_igconnector_connected_pushmode(string broker_params) {
  igConnector* c = new igConnector(broker_params, false, false, "push");  
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
