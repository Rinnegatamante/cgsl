#ifndef _CGSL_H_
#define _CGSL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	CGSL_TYPE_NONE,     // Invalid semantic binding type
	CGSL_TYPE_TEXCOORD, // TEXCOORD
	CGSL_TYPE_COLOR,    // COLOR
	CGSL_TYPE_FOG,      // FOGC
	CGSL_TYPE_CLIP      // CLP
} cgslSemanticType;

typedef enum {
	CGSL_MODE_SHADER_PAIR, // Shader Pair mode assumes as premise that VS+FS shader sets are given in tandem to cgsl_translate_shader
	CGSL_MODE_GLOBAL       // Global mode has no assumptions on input but is less accurate since shares a semantic bindings table globally
} cgslSemanticMode;

typedef enum {
	CGSL_VERTEX_SHADER,
	CGSL_FRAGMENT_SHADER
} cgslShaderType;

// Add a new forced semantic binding for CGSL_MODE_GLOBAL mode
void cgsl_add_semantic_binding(char *varying, int index, cgslSemanticType type);

// Translate a single shader
char *cgsl_translate_shader(char *shader_body, cgslShaderType type, cgslSemanticMode glsl_sema_mode, uint8_t use_low_precision);

#ifdef __cplusplus
}
#endif


#endif
