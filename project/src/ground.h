#include "../../common/GL_utilities.h"
#include "../../common/loadobj.h"
#include "../../common/VectorUtils3.h"
#include "../../common/LoadTGA.h"


class Ground {
	private:
		GLuint tex0;
		Model *cube;

	public:
		Ground();
		void init();
		void draw(mat4 total,GLuint program);
};

