#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <vector>
#include <string>
#include <unordered_map>

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
        private:
            int getAndSaveUniform(string var);
        public:
            GLuint id = 0;
            std::unordered_map<string, GLuint> vars;
            void init(vector<string> Shaders, std::vector<GLenum> identifier);

            //gl uniform functions
            int Uniform1f(string var, GLfloat v0);
            int Uniform2f(string var, GLfloat v0, GLfloat v1);
            int Uniform3f(string var, GLfloat v0, GLfloat v1, GLfloat v2);
            int Uniform4f(string var, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

            int Uniform1i(string var, GLint v0);
            int Uniform2i(string var, GLint v0, GLint v1);
            int Uniform3i(string var, GLint v0, GLint v1, GLint v2);
            int Uniform4i(string var, GLint v0, GLint v1, GLint v2, GLint v3);

            int Uniform1ui(string var, GLuint v0);
            int Uniform2ui(string var, GLuint v0, GLuint v1);
            int Uniform3ui(string var, GLuint v0, GLuint v1, GLuint v2);
            int Uniform4ui(string var, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    };
};