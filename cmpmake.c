#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <pmc.h>

glob_t gl;

int main()
{
	FILE *desc;
	FILE *orig;

	char *utemp[50];
	char temp_gl[80];
	char U_File[80], U_File2[80];
	char bufa[1024];
	char line[80];
	int ui = 0;
	int x;

	desc = fopen("description.ext", "wt");
	if (!desc)
	{
		printf("error at description.ext\n");
		exit(1);
	}

	orig = fopen("desc.original", "rt");
	if (!orig)
	{
		printf("error at desc.original\n");
		exit(1);
	}

	glob("PMC_Fury/Missions/*", 0, 0, &gl);

	fgets(line, 80, orig);

	while (!strstr(line, "<INSERT_MISSIONS_HERE_STUPID>"))
	{
		fputs(line, desc);
		fgets(line, 80, orig);
	}

	for (x = 0; x < gl.gl_pathc; x++)
	{
		bzero(temp_gl, sizeof(temp_gl));
		sprintf(temp_gl, "%s", gl.gl_pathv[x]);

		ui = splitpath(utemp, temp_gl);
		sprintf(U_File, "%s", utemp[ui]);

		sprintf(temp_gl, "%s", gl.gl_pathv[x + 1]);
		ui = splitpath(utemp, temp_gl);
		sprintf(U_File2, "%s", utemp[ui]);

		sprintf(bufa, "                class %s: MissionDefault\n                {\n", U_File);
		fputs(bufa, desc);
		sprintf(bufa, "                        end1 = %s;\n"
		        "                        end2 = ;\n"
		        "                        end3 = ;\n"
		        "                        end4 = ;\n"
		        "                        end5 = ;\n"
		        "                        end6 = ;\n", U_File2);
		fputs(bufa, desc);
		sprintf(bufa, "                        lost = %s;\n"
		        "                        template = %s;\n"
		        "                };\n", U_File, U_File);
		fputs(bufa, desc);
	}

	fgets(line, 80, orig);

	while (!feof(orig))
	{
		fputs(line, desc);
		fgets(line, 80, orig);
	}

	fclose(desc);
	fclose(orig);
	return 0;
}

/*
   <INSERT_MISSIONS_HERE_STUPID>
                class _80_silver_obelisk.abel: MissionDefault
                {
                        end1 = _81_beach_party;
                        end2 = ;
                        end3 = ;
                        end4 = ;
                        end5 = ;
                        end6 = ;
                        lost = _80_silver_obelisk;
                        template = _80_silver_obelisk.abel;
                };
        };
   };
 */
