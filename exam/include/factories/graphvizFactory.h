//
// Created by rasmus on 5/29/2023.
//
#include "reaction_network/reactionNetwork.h"
struct GraphVizFactory
{
    GraphVizFactory(ReactionNetwork network, const std::string& path):
        network(std::move(network)), path(path){
        
    }
    
    void createGraphVizPictureDotFile() {
        std::basic_ofstream<char> dotfile{path.ends_with(".dot") ? path : path+".dot"};
        dotfile << network.to_graphviz_string();
        dotfile.close();
    }
    
    
    void createGraphVizPng(){
        createGraphVizPictureDotFile();
        std::stringstream a{};
        a << "dot -Tpng -o " << path << ".png " << path << ".dot";
        std::system(a.str().c_str());
    }
    
private:
    std::string path;
    ReactionNetwork network;
};