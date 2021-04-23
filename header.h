#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <vector>
#include <string>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

using std::vector;
using std::string;

GLuint CompileShaders();
GLuint CompileAllShaders();
namespace Engine{
    class Triangle{
        public:
            GLuint id = 0;
            GLuint shaderId = 0;
            float oPos[2] = {0,0};  //Position where triangle will be drawn.
            float zRot = 0; 	    // Rotation around center point in degrees.
            float scale = 1;        //scale factor
            void init(float v1[], float v2[], float v3[], GLenum use, GLuint shId);
            void draw(float oP, float zr, float sc);
    };
    class shaderProgram{
        public:
            GLuint id = 0;
            void init(vector<string> Shaders, std::vector<GLenum> identifier);

            //gl uniform functions
            void Uniform1f(GLfloat v0);
            void Uniform2f(GLfloat v0, GLfloat v1);
            void Uniform3f(GLfloat v0, GLfloat v1, GLfloat v2);
            void Uniform4f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

            void Uniform1i(GLint v0);
            void Uniform2i(GLint v0, GLint v1);
            void Uniform3i(GLint v0, GLint v1, GLint v2);
            void Uniform4i(GLint v0, GLint v1, GLint v2, GLint v3);

            void Uniform1ui(GLuint v0);
            void Uniform2ui(GLuint v0, GLuint v1);
            void Uniform3ui(GLuint v0, GLuint v1, GLuint v2);
            void Uniform4ui(GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    };
};