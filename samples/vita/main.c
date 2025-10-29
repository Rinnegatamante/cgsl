#include <vitasdk.h>
#include <cgsl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	sceClibPrintf("Loading vertex shader\n");
	FILE *f = fopen("app0:/vertex.glsl", "rb");
	fseek(f, 0, SEEK_END);
	size_t sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *vert = (char *)malloc(sz + 1);
	fread(vert, 1, sz, f);
	vert[sz] = 0;
	fclose(f);
	sceClibPrintf("Vertex shader:\n%s\n", vert);
	
	sceClibPrintf("Loading fragment shader\n");
	f = fopen("app0:/fragment.glsl", "rb");
	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *frag = (char *)malloc(sz + 1);
	fread(frag, 1, sz, f);
	frag[sz] = 0;
	fclose(f);
	sceClibPrintf("Fragment shader:\n%s\n", frag);
	
	sceClibPrintf("Translating vertex shader\n");
	char *cg_vert = cgsl_translate_shader(vert, CGSL_VERTEX_SHADER, CGSL_MODE_SHADER_PAIR, 0);
	
	sceClibPrintf("Translating fragment shader\n");
	char *cg_frag = cgsl_translate_shader(frag, CGSL_FRAGMENT_SHADER, CGSL_MODE_SHADER_PAIR, 0);
	
	sceClibPrintf("Translated shaders:\nVERTEX:\n----------------------------\n\n");
	sceClibPrintf("%s\n", cg_vert);
	sceClibPrintf("---------------------------\nFRAGMENT:\n----------------------------\n\n");
	sceClibPrintf("%s\n", cg_frag);
	
	free(cg_vert);
	free(cg_frag);
	free(vert);
	free(frag);

	return 0;
}
