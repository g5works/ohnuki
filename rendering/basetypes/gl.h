struct Vertex {
    
    float position[3];
    float color[3];
    float texture[2];

};

struct IndexTri {

    unsigned int tri[3];

};


class GLVertexObject {
    
    public:
        unsigned int vao;
        unsigned int vbo;
        unsigned int cnt = 0;

        GLVertexObject(Vertex vertices[], unsigned int vs);
        void bind();
        void bindArray();
        void bindBuffer();

};

class GLIndices {

    public: 
        unsigned int ibo;
        unsigned int index;
        unsigned int cnt = 0;

        GLIndices(IndexTri indices[], unsigned int tricnt);
        void bind();

};

class GLShaders {

    public:
        unsigned int prog;
        unsigned int vert;
        unsigned int frag;

        GLShaders(std::string vertex, std::string fragment);
        void use();

    private: 
        std::string readshaderfile(std::string shaderPath);
        unsigned int compile(const std::string &shadersource, unsigned int shadertype);
        int create(const std::string &vloc, const std::string &floc);

};

class GLTexture {

    public:
        unsigned int tex;
        std::string texpath;
        int width;
        int height;
        int chans;
        int slot;

        GLTexture(std::string texpath, unsigned int slot);
        void bind(std::string suniformname, GLShaders s);

};