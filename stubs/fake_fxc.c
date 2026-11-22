/* fake_fxc: stands in for fxc.exe in the Firefox 115 build. It does NOT compile HLSL.
   It writes a placeholder byte array under the -Vn name to the -Fh file and prints one
   dependency line, which is the contract genshaders.py relies on. The resulting shaders are
   invalid bytecode, so any Direct3D 11 shader creation fails at run time. */
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
    const char *fh = NULL, *vn = NULL, *src = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "-Fh", 3)) fh = argv[i] + 3;
        else if (!strncmp(argv[i], "-Vn", 3)) vn = argv[i] + 3;
        else if (argv[i][0] != '-') src = argv[i];
    }
    if (!fh || !vn) { fprintf(stderr, "fake fxc: missing -Fh or -Vn\n"); return 1; }
    FILE *f = fopen(fh, "w");
    if (!f) { fprintf(stderr, "fake fxc: cannot write %s\n", fh); return 1; }
    fprintf(f, "const unsigned char %s[] = { 0x44, 0x58, 0x42, 0x43, 0x00 };\n", vn);
    fclose(f);
    if (src) printf("Resolved to [%s]\n", src);
    return 0;
}
