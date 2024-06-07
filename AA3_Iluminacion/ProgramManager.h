#pragma once
#include <vector>
#include "Program.h"


#define PROGRAMS ProgramManager::Instance()

class ProgramManager
{
private:
	std::vector<GLuint> compiledPrograms;

	ProgramManager() = default;

	ProgramManager(const ProgramManager&) = delete;
	ProgramManager& operator =(const ProgramManager&) = delete;

public:
	inline static ProgramManager& Instance()
	{
		static ProgramManager manager;
		return manager;
	}

	void Compile();

	GLuint CreateProgram(const Program& shaders);

	void AddProgram(const Program& shaders);

	void DeletePrograms();
	
	inline std::vector<GLuint> GetCompiledPrograms() { return compiledPrograms; }
};