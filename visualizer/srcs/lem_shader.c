#include "lem_visual.h"

static int8_t		shad_compile_stat(GLuint *p_shad)
{
	GLint	result;
	GLint	log_len;
	GLsizei	written;
	char	*log;

	glGetShaderiv(*p_shad, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		ft_printf(F_RED "Shader compile error\n" NONE);
		glGetShaderiv(*p_shad, GL_INFO_LOG_LENGTH, &log_len);
		if (log_len > 0)
		{
			log = (char *)malloc(sizeof(char) * log_len);
			glGetShaderInfoLog(*p_shad, log_len, &written, log);
			ft_printf(F_RED "Shader log: %s\n" NONE, log);
			free(log);
		}
		return (0);
	}
	return (1);
}

int8_t				read_compile_shader(const char *filename, GLuint *p_shad,
															GLenum shader_type)
{
	int32_t	fd;
	int64_t	size;
	char	*buf;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_printf(F_RED "%s\n" NONE, strerror(errno));
		return (0);
	}
	size = lseek(fd, 0L, SEEK_END);
	lseek(fd, 0L, SEEK_SET);
	buf = (char *)malloc(size + 1);
	read(fd, buf, size);
	buf[size] = '\0';
	close(fd);
	*p_shad = glCreateShader(shader_type);
	glShaderSource(*p_shad, 1, (const GLchar**)&buf, NULL);
	glCompileShader(*p_shad);
	free(buf);
	if (!shad_compile_stat(p_shad))
		return (0);
	return (1);
}

static int8_t		prog_stat(GLuint *prog)
{
	GLint	status;
	GLint	log_len;
	GLsizei	written;
	char	*log;

	glGetProgramiv(*prog, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		ft_printf(F_RED "Shader program link error\n" NONE);
		glGetProgramiv(*prog, GL_INFO_LOG_LENGTH, &log_len);
		if (log_len > 0)
		{
			log = (char *)malloc(sizeof(char) * log_len);
			glGetProgramInfoLog(*prog, log_len, &written, log);
			ft_printf(F_RED "Program log: %s\n" NONE, log);
			free(log);
		}
		return (0);
	}
	return (1);
}

static inline void	delete_shader(GLuint vert_shad, GLuint geom_shad,
															GLuint frag_shad)
{
	glDeleteShader(vert_shad);
	glDeleteShader(frag_shad);
	if (geom_shad)
		glDeleteShader(geom_shad);
}

int8_t				set_shader(GLuint *prog, const char *vsfile,
										const char *gsfile, const char *fsfile)
{
	GLuint vert_shad;
	GLuint geom_shad;
	GLuint frag_shad;

	geom_shad = 0;
	if (!read_compile_shader(vsfile, &vert_shad, GL_VERTEX_SHADER) ||
	(gsfile && !read_compile_shader(gsfile, &geom_shad, GL_GEOMETRY_SHADER)) ||
		!read_compile_shader(fsfile, &frag_shad, GL_FRAGMENT_SHADER) ||
		!(*prog = glCreateProgram()))
		return (0);
	glAttachShader(*prog, vert_shad);
	glAttachShader(*prog, frag_shad);
	if (gsfile)
	{
		glAttachShader(*prog, geom_shad);
		glProgramParameteriEXT(*prog, GL_GEOMETRY_INPUT_TYPE_EXT, GL_LINE);
		glProgramParameteriEXT(*prog, GL_GEOMETRY_OUTPUT_TYPE_EXT,
															GL_TRIANGLE_STRIP);
		glProgramParameteriEXT(*prog, GL_GEOMETRY_VERTICES_OUT_EXT, 4);
	}
	glLinkProgram(*prog);
	delete_shader(vert_shad, geom_shad, frag_shad);
	if (!prog_stat(prog))
		return (0);
	return (1);
}
