cmake_minimum_required(VERSION 3.15)
project(exam CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

enable_testing()

add_subdirectory(src)


set(GRAPHVIZ_INCLUDE_DIR "C:/Program Files/Graphviz/include")
set(GRAPHVIZ_LIBRARY_DIR "C:/Program Files/Graphviz/lib")

# Add Graphviz directories
include_directories(${GRAPHVIZ_INCLUDE_DIR})
link_directories(${GRAPHVIZ_LIBRARY_DIR})


add_executable(main src/main.cpp include/symbol_table include/reaction/agents.h include/reaction/constructionRules.h include/reaction/reaction.cpp include/reaction/reaction.h include/reaction_network/reactionNetwork.h include/reaction_network/reactionNetworkSimulator.cpp include/reaction_network/reactionNetworkSimulator.h include/factories/graphvizFactory.h include/factories/csvFactory.h include/reaction/agentOperations.h)
add_executable(simple src/simple.cpp include/symbol_table include/reaction/agents.h include/reaction/constructionRules.h include/reaction/reaction.cpp include/reaction/reaction.h include/reaction_network/reactionNetwork.h  include/reaction_network/reactionNetworkSimulator.cpp include/reaction_network/reactionNetworkSimulator.h include/reaction/agentOperations.h)
add_executable(circadian src/circadian.cpp include/symbol_table include/reaction/agents.h include/reaction/constructionRules.h include/reaction/reaction.cpp include/reaction/reaction.h include/reaction_network/reactionNetwork.h include/reaction_network/reactionNetworkSimulator.cpp include/reaction_network/reactionNetworkSimulator.h include/reaction/agentOperations.h)
add_executable(figure3 src/covid.cpp include/symbol_table include/reaction/agents.h include/reaction/constructionRules.h include/reaction/reaction.cpp include/reaction/reaction.h include/reaction_network/reactionNetwork.h  include/reaction_network/reactionNetworkSimulator.cpp include/reaction_network/reactionNetworkSimulator.h include/reaction/agentOperations.h)
