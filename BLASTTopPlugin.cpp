#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "BLASTTopPlugin.h"

void BLASTTopPlugin::input(std::string file) {
 inputfile = file;
}

void BLASTTopPlugin::run() {
   
}

void BLASTTopPlugin::output(std::string file) {
 // alpha_diversity.py -i filtered_otu_table.biom -m observed_species,chao1,shannon,PD_whole_tree -t rep_set.tre -o alpha.txt
   //std::string command = "samtools sort " + inputfile + " > "+file;
	std::string command = "";
	command = "awk '/Query=/{print; flag=1; next} flag && /^>/{print; flag=0} flag && /No hits found/{print; flag=0}' "+inputfile+" > temp1.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "awk 'NR%2==1{col1=$0} NR%2==0{print col1, $0}' temp1.txt > temp2.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "sed -i 's/PREDICTED: //' temp2.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "sed -i 's/\\*\\*\\*\\*\\* No hits found \\*\\*\\*\\*\\*/> No No_hits_found/g' temp2.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "awk '{print $2, $5}' temp2.txt > temp3.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "sed -i 's/ /\\t/' temp3.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "echo -e \"contig\\tTopHit\" > "+file;//TopHitBLAST.txt
	std::cout << command << std::endl;
        system(command.c_str());

command = "sort -t_ -k2n temp3.txt >> "+file;//TopHitBLAST.txt
	std::cout << command << std::endl;
        system(command.c_str());


}

PluginProxy<BLASTTopPlugin> BLASTTopPluginProxy = PluginProxy<BLASTTopPlugin>("BLASTTop", PluginManager::getInstance());
