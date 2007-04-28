#include "Shader.h"
#include "Utils.h"

#include <vector>

namespace geomclip {
    namespace {
        std::string getShaderInfoLog(GLuint shader) {
            GLsizei logLength = 0;
            
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

            if( logLength > 0 ) {
				std::vector<char> chr;
				chr.resize( logLength + 1 );
                GLsizei realLength = 0;
                glGetShaderInfoLog( shader, logLength, &realLength, &chr[0] );

				return std::string( chr.begin(), chr.end() );
            }
            else {
                return "";
            }
        }
        
        std::string getProgramInfoLog(GLuint shader) {
            GLsizei logLength = 0;
            
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logLength);

            if( logLength > 0 ) {
				std::vector<char> chr;
				chr.resize( logLength + 1 );
                GLsizei realLength = 0;
                glGetProgramInfoLog(shader, logLength, &realLength, &chr[0]);

				return std::string( chr.begin(), chr.end() );
            }
            else {
                return "";
            }
        }
        
        GLuint createShader(const std::string& source, GLenum type) {
            GLuint shader = glCreateShader( type );
            const char* src = source.c_str();
            glShaderSource( shader, 1, &src, NULL );
            glCompileShader( shader );

            GLint result = GL_FALSE;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

            if( result != GL_TRUE ) {
                GEOMCLIP_ERROR("could not compile GLSL shader from source:\n"
                               << source
                               << "\n\nInfo log:\n"
                               << getShaderInfoLog(shader)
                               << "\n");
            }
            
            return shader;
        }
    }

    Shader::Shader() {
        program_ = 0;
        vertexShader_ = 0;
        fragmentShader_ = 0;
    }
    
    Shader::Shader(const std::string& name) {
        loadFiles(name + ".vert", name + ".frag");
    }
    
    Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile) {
        loadFiles(vertexFile, fragmentFile);
    }

    Shader::~Shader() {
        glDetachShader(program_, vertexShader_);
        glDeleteShader(vertexShader_);
        glDetachShader(program_, fragmentShader_);
        glDeleteShader(fragmentShader_);

        glDeleteProgram(program_);
    }
    
    void Shader::loadFiles(
		const std::string& vertexFile,
        const std::string& fragmentFile)
    {
        const std::string vertexSource = loadFile(vertexFile);
        const std::string fragmentSource = loadFile(fragmentFile);

		vertexShader_ = createShader( vertexSource, GL_VERTEX_SHADER );
		fragmentShader_ = createShader( fragmentSource, GL_FRAGMENT_SHADER );

		program_ = glCreateProgram();
		glAttachShader(program_, vertexShader_);
		glAttachShader(program_, fragmentShader_);
		glLinkProgram(program_);

		GLint linkSuccess = GL_FALSE;
		glGetProgramiv(program_, GL_LINK_STATUS, &linkSuccess);
		if( linkSuccess != GL_TRUE ) {
			GEOMCLIP_ERROR("Could not link GLSL program from files "
				<< "'" << vertexFile << "' and '"
				<< fragmentFile << "'\n"
				<< "Info log:\n"
				<< getProgramInfoLog(program_)
				<< "\n\n");
		}
    }

	void Shader::setSource(const std::string& vertexSource, const std::string& fragmentSource)
	{
		vertexShader_ = createShader( vertexSource, GL_VERTEX_SHADER );
		fragmentShader_ = createShader( fragmentSource, GL_FRAGMENT_SHADER );

		program_ = glCreateProgram();
		glAttachShader(program_, vertexShader_);
		glAttachShader(program_, fragmentShader_);
		glLinkProgram(program_);

		GLint linkSuccess = GL_FALSE;
		glGetProgramiv(program_, GL_LINK_STATUS, &linkSuccess);
		if( linkSuccess != GL_TRUE ) {
			GEOMCLIP_ERROR("Could not link GLSL program from source"
				<< "\n=== Vertex shader ===\n'" << vertexSource 
				<< "\n=== Fragment shader===\n" << fragmentSource
				<< "\n=== Info log===\n"
				<< getProgramInfoLog(program_)
				<< "\n\n");
		}
	}
    
    void Shader::bind() {
        glUseProgram(program_);
    }
    
    void Shader::unbind() {
        glUseProgram(0);
    }
    
}
