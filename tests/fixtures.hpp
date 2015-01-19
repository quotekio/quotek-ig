#ifndef FIXTURES_H
#define FIXTURES_H
#include <igconnector/igconnector.hpp>
#include <assert.h>

igConnector* get_igconnector(string);
igConnector* get_igconnector_connected_pollmode(string);
igConnector* get_igconnector_connected_pushmode(string, std::vector<std::string>);
igConnector* get_igconnector_connected_logging(string);
igConnector* get_igconnector_connected_profiling(string);

#endif


