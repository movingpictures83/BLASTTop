#ifndef BLASTTopLUGIN_H
#define BLASTTopPLUGIN_H

#include "Plugin.h"
#include "PluginProxy.h"
#include <string>
#include <vector>

class BLASTTopPlugin : public Plugin
{
public: 
 std::string toString() {return "BLASTTop";}
 void input(std::string file);
 void run();
 void output(std::string file);

private: 
 std::string inputfile;
 std::string outputfile;
};

#endif
