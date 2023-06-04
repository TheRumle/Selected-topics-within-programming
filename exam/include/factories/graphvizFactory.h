#include <utility>

#include "reactionNetwork/reactionNetwork.h"

//REQ 2
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