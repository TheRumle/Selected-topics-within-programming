//
// Created by rasmus on 5/29/2023.
//
#include "reaction_network/reactionNetwork.h"
struct GraphVizShower{    
    static std::basic_ofstream<char> createGraphVizPictureDotFile(reactionNetwork& network, const std::string& path){
        std::ofstream dotfile (path);
        dotfile << network.to_graphviz_string();
        dotfile.close();
        return dotfile;
    }
    
    static void createGraphVizPng(reactionNetwork& network, const std::string& path){
        createGraphVizPictureDotFile(network, path);
        std::system("dot -Tpng -o reaction_graph.png reaction_graph.dot");
    }
};