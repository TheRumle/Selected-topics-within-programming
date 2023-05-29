//
// Created by rasmus on 5/29/2023.
//
#include <utility>

#include "reaction_network/reactionNetwork.h"
struct GraphVizFactory
{
    GraphVizFactory(ReactionNetwork network, std::string  path):
        network(std::move(network)), path(std::move(path)){
        
    }
    
    void createGraphVizPictureDotFile() {
        std::basic_ofstream<char> dotfile{path.ends_with(".dot") ? path : path+".dot"};
        dotfile << network.to_graphviz_string();
        dotfile.close();
    }
    
    
    void createGraphVizPng(){
        createGraphVizPictureDotFile();
        std::system((std::stringstream {} << "dot -Tpng -o " << path << ".png " << path << ".dot")
                        .str().c_str());
    }
    
private:
    std::string path;
    ReactionNetwork network;
};