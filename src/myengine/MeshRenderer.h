#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>

//this component is for displaying a 3D object on screen
//to do that, we need a VAO (organised information about the 3D object, like where the vertex positions, normals, texture coords...)
//Upload positions of triangle to GPU (VBO)
//Organise that data on the GPU(VAO)
//we also neeed to know what shader(s) to use when we want to display them
class VertexArray; //forward declaration, #include them in the .cpp
class ShaderProgram;

class MeshRenderer : public Component
{
public:
	void onInit(); //this will override the Components

private:
	void onDisplay();

	std::shared_ptr<VertexArray> shape;
	std::shared_ptr<ShaderProgram> shader;

};
