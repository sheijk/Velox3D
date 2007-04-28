#ifndef GEOMCLIPTERRAIN_SHADER_H_INCLUDE
#define GEOMCLIPTERRAIN_SHADER_H_INCLUDE

#include "Types.h"
#include "OpenGL.h"

namespace geomclip {
    
    class Shader {
    public:
        Shader();
        /**
         * Reads vertex/fragment shaders from name.vert/name.frag
         */
        Shader(const std::string& name);
        Shader(const std::string& vertexFile, const std::string& fragmentFile);

        virtual ~Shader();

        void bind();
        void unbind();
        
        void loadFiles(const std::string& vertexFile, const std::string& fragmentFile);
		void setSource(const std::string& vertexSource, const std::string& fragmentSource);

        GLuint program() const { return program_; }
        GLuint vertexShader() const { return vertexShader_; }
        GLuint fragmentShader() const { return fragmentShader_; }
    private:
        GLuint program_;
        GLuint vertexShader_;
        GLuint fragmentShader_;
    };
    
} // namespace
#endif
