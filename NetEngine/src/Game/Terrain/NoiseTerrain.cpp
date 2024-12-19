#include "NoiseTerrain.h"

NoiseTerrain::NoiseTerrain()
{
	myNoise.SetFrequency(0.2);
	myNoise.SetOctaveCount(4);
	myNoise.SetPersistence(0.2);
	myNoise.SetLacunarity(1.2);

	GenerateHeightMapPlane();

	noiseTerrainMesh = new Mesh(noiseTerrainVertices);

	noiseTerrainMesh->setupMesh();
}

void NoiseTerrain::GenerateHeightMapPlane()
{
    int count = COUNT;  // Using COUNT directly for clarity
    int vSize = 10;

    // Generate vertices (same as before)
    for (int x = 0; x < count; x++)
    {
        for (int z = 0; z < count; z++)
        {
            Vertex v;

            float xPos = (float)x / ((float)(count - 1) * vSize);
            float yPos = 0;  // or use noise for height
            float zPos = (float)z / ((float)(count - 1) * vSize);

            v.Position = glm::vec3(xPos, yPos, zPos);
            v.Normal = glm::vec3(0, 1, 0);  // Compute normals later

            noiseTerrainVertices.push_back(v);
        }
    }

    // Generate indices (for triangle strip)
    std::vector<unsigned int> indices;

    for (int x = 0; x < count - 1; x++)  // Skip last row and column to avoid overflow
    {
        for (int z = 0; z < count - 1; z++)
        {
            // Top-left vertex
            int topLeft = x * count + z;
            // Top-right vertex
            int topRight = (x + 1) * count + z;
            // Bottom-left vertex
            int bottomLeft = x * count + (z + 1);
            // Bottom-right vertex
            int bottomRight = (x + 1) * count + (z + 1);

            // First triangle (top-left, top-right, bottom-left)
            noiseTerrainIndices.push_back(topLeft);
            noiseTerrainIndices.push_back(topRight);
            noiseTerrainIndices.push_back(bottomLeft);


            // Second triangle (top-right, bottom-right, bottom-left)
            noiseTerrainIndices.push_back(topRight);
            noiseTerrainIndices.push_back(bottomRight);
            noiseTerrainIndices.push_back(bottomLeft);
        }
    }

}


void NoiseTerrain::DrawTerrain(Shader& shader, glm::mat4 projection, glm::mat4& view)
{
	shader.use();

	// Pass projection and view matrices to the shader
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	// Model matrix (identity since we aren't transforming the whole terrain)
	glm::mat4 model = glm::mat4(1.0f);
	shader.setMat4("model", model);

	// Draw the terrain
	noiseTerrainMesh->Draw(shader, GL_TRIANGLES);
}


double NoiseTerrain::GenerateNoise(double x, double y, double z)
{
	// Assuming y is 0 since we're sampling in 2D
	return myNoise.GetValue(x * 0.1, 0.0, z * 0.1); // Scale x and z for a better distribution
}
