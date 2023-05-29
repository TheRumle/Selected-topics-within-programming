//
// Created by rasmus on 5/29/2023.
//
#include "reaction_network/ReactionNetwork.h"
struct GraphVizShower{    
    static std::basic_ofstream<char> CreateGraphVizPicture_DotFile(ReactionNetwork& network, const std::string& path){
        std::ofstream dotfile (path);
        dotfile << network.to_graphviz_string();
        dotfile.close();
        return dotfile;
    }
    
    static void CreateGraphVizPicture(ReactionNetwork& network, const std::string& path){
        CreateGraphVizPicture_DotFile(network, path);
        std::system("dot -Tpng -o reaction_graph.png reaction_graph.dot");
    }
};