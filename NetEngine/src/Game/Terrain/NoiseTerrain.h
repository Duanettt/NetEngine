#pragma once

#include <vector>
#include <noise/noise.h>
#include "../../Renderer/Mesh.h"

#define COUNT 500

class NoiseTerrain : public Mesh
{
public:
	NoiseTerrain();

	void GenerateHeightMapPlane();

	void DrawTerrain(Shader& shader, glm::mat4 projection, glm::mat4& view);

	double GenerateNoise(double x, double y, double z);

private:
	Mesh* noiseTerrainMesh;
	noise::module::Perlin myNoise;
	std::vector<Vertex> noiseTerrainVertices;
	std::vector<unsigned int> noiseTerrainIndices;

};

