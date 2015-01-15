#ifndef FIXTURES_H
#define FIXTURES_H
#include <igconnector/igconnector.hpp>
#include <assert.h>

igConnector* get_igconnector(string);
igConnector* get_igconnector_connected_pullmode(string);
igConnector* get_igconnector_connected_pushmode(string);
igConnector* get_igconnector_connected_logging(string);
igConnector* get_igconnector_connected_profiling(string);

#endif


