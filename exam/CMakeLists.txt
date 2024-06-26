cmake_minimum_required(VERSION 3.15)
project(exam CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(doctest.cmake)

include_directories(include)

enable_testing()

add_subdirectory(src)


set(GRAPHVIZ_INCLUDE_DIR "C:/Program Files/Graphviz/include")
set(GRAPHVIZ_LIBRARY_DIR "C:/Program Files/Graphviz/lib")

# Add Graphviz directories
include_directories(${GRAPHVIZ_INCLUDE_DIR})
link_directories(${GRAPHVIZ_LIBRARY_DIR})


add_executable(graphicsAndCsv src/graphicsAndCsv.cpp include/symbolTable include/reaction/agents.h include/reaction/reaction.cpp include/reaction/reaction.h include/reactionNetwork/reactionNetwork.h include/reactionNetwork/reactionNetworkSimulator.cpp include/reactionNetwork/reactionNetworkSimulator.h include/factories/graphvizFactory.h include/factories/csvFactory.h include/reaction/agentOperations.h include/reactionNetwork/reactionNetwork.cpp include/meta/agentConstraint.h include/reactionNetwork/monitor/monitor.cpp include/reactionNetwork/monitor/monitor.h include/meta/monitorConstraint.h include/reaction/agents.cpp)
add_executable(benchmark src/benchmarks.cpp include/symbolTable include/reaction/agents.h include/reaction/reaction.cpp include/reaction/reaction.h include/reactionNetwork/reactionNetwork.h include/reactionNetwork/reactionNetworkSimulator.cpp include/reactionNetwork/reactionNetworkSimulator.h include/factories/graphvizFactory.h include/factories/csvFactory.h include/reaction/agentOperations.h include/reactionNetwork/reactionNetwork.cpp include/meta/agentConstraint.h include/reactionNetwork/monitor/monitor.cpp include/reactionNetwork/monitor/monitor.h include/meta/monitorConstraint.h include/factories/reactionNetworkFactory.h include/benchmark/benchmark.cpp include/benchmark/benchmarkResult.cpp include/benchmark/timer.h include/benchmark/timer.cpp include/reaction/agents.cpp)
add_executable(maxcovidmonitor src/maxCovid.cpp include/symbolTable include/reaction/agents.h include/reaction/reaction.cpp include/reaction/reaction.h include/reactionNetwork/reactionNetwork.h include/reactionNetwork/reactionNetworkSimulator.cpp include/reactionNetwork/reactionNetworkSimulator.h include/factories/graphvizFactory.h include/factories/csvFactory.h include/reaction/agentOperations.h include/reactionNetwork/reactionNetwork.cpp include/meta/agentConstraint.h include/reactionNetwork/monitor/monitor.cpp include/reactionNetwork/monitor/monitor.h include/meta/monitorConstraint.h include/benchmark/benchmark.cpp include/benchmark/benchmarkResult.cpp include/benchmark/timer.h include/benchmark/timer.cpp include/reaction/agents.cpp)
add_executable(meanPeak src/meanPeak.cpp include/symbolTable include/reaction/agents.h include/reaction/reaction.cpp include/reaction/reaction.h include/reactionNetwork/reactionNetwork.h include/reactionNetwork/reactionNetworkSimulator.cpp include/reactionNetwork/reactionNetworkSimulator.h include/factories/graphvizFactory.h include/factories/csvFactory.h include/reaction/agentOperations.h include/reactionNetwork/reactionNetwork.cpp include/meta/agentConstraint.h include/reactionNetwork/monitor/monitor.cpp include/reactionNetwork/monitor/monitor.h include/meta/monitorConstraint.h include/factories/reactionNetworkFactory.h include/benchmark/benchmark.cpp include/benchmark/benchmarkResult.cpp include/benchmark/timer.h include/benchmark/timer.cpp include/reaction/agents.cpp)
