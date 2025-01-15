#!/usr/bin/env wolframscript

fileID = 0
numFiles = 100
numNodes = 20
numEdges = 100
Do[
	outFileStream = OpenWrite["./testdags/" <> ToString@fileID <> ".dag"];
	testGraph = EdgeList@DirectedGraph[RandomGraph[{numNodes, numEdges}], "Acyclic"];
	Map[WriteLine[outFileStream, #]&]
		@ Map[(ToString@#[[1]] <> " " <> ToString@#[[2]])&]
		@ testGraph
	;
	Close[outFileStream];
	fileID += 1;
, numFiles]
