const int INDEX_DRAW = 0;
const int VERTEX_DRAW = 1;

const int PLATFORM_MAC = 0;
const int PLATFORM_LIN = 1;

#define ASSERT(x) if (!(x)) __builtin_trap();
#define glHCheckingCall(x) glHClearErrors(); x; ASSERT(glHBreakError(__FILE__, __LINE__))

static void glHClearErrors() {
     
    while (glGetError() != 0);

}

static bool glHBreakError(const char* location, int line) {

    while (GLenum glerror = glGetError()) {

        std::cout << "!!!<OPENGL ERROR>: " << glerror << std::endl;
        std::cout << "!![FILE]: " << location << std::endl;
        std::cout << "!![LINE]: " << line << std::endl;


        return false;

    }
    return true;
}

class GLRenderer {

    public:

        GLVertexObject *vx;
        GLIndices *ix;
        GLFWwindow *win;

        unsigned int numitems;
        unsigned int drawmode;


        GLRenderer(unsigned int platform);

        void setShader(GLShaders shader);

        //VERTEX DRAW
        //vertices: the GLVertexObject you wanna draw
        void set(GLVertexObject *vertices);

        //INDEX DRAW
        //vertices: the GLVertexObject you wanna draw
        //indices: the GLIndices object you wanna use to draw
        void set(GLVertexObject *vertices, GLIndices *indices);

        //this takes no args, and renders whatever u put in the set function last
        void draw();

};