#include "src/Engine.h"
#include "src/deleteutil.h"

int main(int argc, char **argv)
{
	Crescer3D::Engine* engine = Crescer3D::Engine::GetEngine();
	int result = engine->runMainLoop();
	SafeDelete(engine);
	return result;
}
