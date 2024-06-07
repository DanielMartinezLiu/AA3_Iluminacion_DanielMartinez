#version 440 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 scaleMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec2 uvsGeometryShader[];
in vec3 normalsGeometryShader[];

out vec2 uvsFragmentShader;
out vec3 normalsFragmentShader;
out vec3 fragmentPosition;

void main(){

	mat4 model = translationMatrix * rotationMatrix * scaleMatrix;

	for(int i = 0; i < gl_in.length(); i++){
	
		gl_Position = projectionMatrix * viewMatrix * model * gl_in[i].gl_Position;

		uvsFragmentShader = uvsGeometryShader[i];
		normalsFragmentShader = normalsGeometryShader[i];

		fragmentPosition = (model * gl_in[i].gl_Position).xyz;

		EmitVertex();
	}

	EndPrimitive();
}