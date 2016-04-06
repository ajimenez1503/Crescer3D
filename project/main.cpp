#include "src/Engine.h"
#include "src/deleteutil.h"

int main(int argc, char **argv)
{
	Crescer3D::Engine* engine = new Crescer3D::Engine();
	int result = engine->runMainLoop();
	SafeDelete(engine);
	return result;
}
