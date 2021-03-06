#pragma once


#include <fstream>
#include <type_traits>
#include <iterator>
#include <limits>
#include <sstream>
#include "GraphRepresentation.h"
#include <string>

namespace TSP
{

	static std::string tsplib_symmetric_path = "C:\\Users\\Jakub\\source\\repos\\JakubSokolowski\\TSP\\TSP\\Benchmarks\\ProblemData\\TSPLIB\\Symmetric\\";
	static std::string tsplib_asymmetric_path = "C:\\Users\\Jakub\\source\\repos\\JakubSokolowski\\TSP\\TSP\\Benchmarks\\ProblemData\\TSPLIB\\Asymmetric\\";
	static std::string random_symmetric_path = "C:\\Users\\Jakub\\source\\repos\\JakubSokolowski\\TSP\\TSP\\Benchmarks\\ProblemData\\Random\\Symmetric\\";
	static std::string random_asymmetric_path = "C:\\Users\\Jakub\\source\\repos\\JakubSokolowski\\TSP\\TSP\\Benchmarks\\ProblemData\\Random\\Asymmetric\\";
	static std::string result_path = "C:\\Users\\Jakub\\source\\repos\\JakubSokolowski\\TSP\\TSP\\Benchmarks\\Results\\";
	static std::string genetic_result_path = "C:\\Users\\Jakub\\source\\repos\\JakubSokolowski\\TSP\\TSP\\Benchmarks\\Results\\Genetic\\";

	template<typename Graph, typename Cost>
	Graph ParseGraphFile(std::string filepath);	

	inline std::vector<Vertex> ReadCoordinates(std::fstream & stream)
	{
		uint id;
		double x, y;
		auto coordinates = std::vector<Vertex>();
		while (stream >> id >> x >> y)
			coordinates.push_back(Vertex{(uint)x, (uint)y ,id});
		return coordinates;
	}


	template <typename Cost>
	inline std::vector<std::vector<Cost>> ReadMatrix(std::fstream & stream);

	template <typename Cost>
	inline std::vector<std::vector<Cost>> ReadFullMatrix(std::fstream & stream);
	
	
	template<typename Graph, typename Cost>
	inline Graph ParseGraphFile(std::string filepath)
	{

		std::fstream file;
		file.open(filepath, std::ios_base::in);

		if (!file)
			throw std::runtime_error("Could not open the file");

		std::string file_type;
		std::getline(file, file_type);
		Graph rep;


		if (file_type == "NODE_COORD")
		{
			std::vector<Vertex> coordinates = ReadCoordinates(file);
			rep = Graph(coordinates);
		}
		else if (file_type == "MATRIX")
		{
			auto mat = ReadMatrix<Cost>(file);
			rep = Graph(mat);
		}
		else if (file_type == "FULL_MATRIX")
		{
			auto mat = ReadFullMatrix<Cost>(file);
			rep = Graph(mat);
		}

		/*else if (file_type == "EDGE_WEIGHT")	
			int y = 7'*/
		else
			throw std::runtime_error("Invlid file type identifier");

		file.close();
		return rep;
	}

	template<typename Graph, typename Cost>
	inline Graph ParseInstance(std::string name) {
		auto path = ""
		return ParseGraphFile()
	}


	template<typename Cost>
	inline std::vector<std::vector<Cost>> ReadMatrix(std::fstream & stream)
	{
		std::string line;
		auto vec = std::vector<std::vector<Cost>>();
		while (std::getline(stream, line))
		{
			std::istringstream is(line);
			vec.push_back(std::vector<int>(std::istream_iterator<int>(is), std::istream_iterator<int>()));
		}
		for (uint i = 0; i < vec.size(); i++)
			vec[i][i] = std::numeric_limits<Cost>::max();

		return vec;
	}

	template<typename Cost>
	std::vector<std::vector<Cost>> ReadFullMatrix(std::fstream & stream)
	{	
		// Read all the numbers into a vector
		auto raw_vec = std::vector<Cost>(std::istream_iterator<Cost>(stream), std::istream_iterator<Cost>());
		uint chunk = (uint)sqrt(raw_vec.size());
		uint start = 0;
		auto vec = std::vector<std::vector<Cost>>();
		for (uint i = 0; i < chunk; i++)
		{
			vec.push_back(std::vector<Cost>(raw_vec.begin() + start, raw_vec.begin() + start + chunk));
			start += chunk;
		}	

		for (uint i = 0; i < vec.size(); i++)
			vec[i][i] = std::numeric_limits<Cost>::max();

		return vec;
	}

	
	
}

