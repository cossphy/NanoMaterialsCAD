#include "stdafx.h"

#include "JGN_Build.h"
#include "VSystem.h"

void BuildLammps(char* NewPC)
{
	time_t now = time(0);
	char* dt = ctime(&now);

	for (int i = 0; i < 100; i++)
	{
		if (NewPC[i] == '(')
		{
			NewPC[i] = NULL;
			i = 100;
		}
	}
	//if (nanotube)
	//{


	//	NewPC[0] = '\0';
	//	std::strcat(NewPC, PCtype);
	//	std::strcat(NewPC, "_NIKOULIS_NT.lmp");


	//	FILE *NewPCF = fopen(NewPC, "w");
	//	FILE *uc_file = fopen(inpf, "r");


	//	char* s;
	//	char* token;
	//	s = (char*)malloc(sizeof(char) * SBYTES);


	//	/// line 1

	//	std::fgets(s, SBYTES, uc_file);
	//	std::fprintf(NewPCF, s);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fprintf(NewPCF, s);

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}
	//	/// line 2
	//	for (ole1 = 0; ole1 < a; ole1++)
	//	{
	//		new_num_atoms[ole1] = 0;
	//		atomscc = 0;


	//	}

	//	float xlo = fl_max, xhi = fl_min,
	//		ylo = fl_max, yhi = fl_min,
	//		zlo = fl_max, zhi = fl_min;

	//	for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//	{
	//		if (crystal[2 + 5 * ole] > xhi)
	//		{
	//			xhi = crystal[2 + 5 * ole];
	//		}
	//		else if (crystal[2 + 5 * ole] < xlo)
	//		{
	//			xlo = crystal[2 + 5 * ole];
	//		}
	//		if (crystal[3 + 5 * ole] > yhi)
	//		{
	//			yhi = crystal[3 + 5 * ole];
	//		}
	//		else if (crystal[3 + 5 * ole] < ylo)
	//		{
	//			ylo = crystal[3 + 5 * ole];
	//		}
	//		if (crystal[4 + 5 * ole] > zhi)
	//		{
	//			zhi = crystal[4 + 5 * ole];
	//		}
	//		else if (crystal[4 + 5 * ole] < zlo)
	//		{
	//			zlo = crystal[4 + 5 * ole];
	//		}
	//		new_num_atoms[0] = new_num_atoms[0] + 1;
	//		atomscc++;


	//	}
	//	xhi = ijk[0][0] * sized[0] + xlo;
	//	yhi = ijk[1][1] * sized[1] + ylo;
	//	zhi = ijk[2][2] * sized[2] + zlo;

	//	std::fprintf(NewPCF, "\n%d atoms\n", new_num_atoms[0]);

	//	std::fprintf(NewPCF, "\n%d atom types\n", a);




	//	/// line 3
	//	std::fprintf(NewPCF, "\n%.*f  %.*f xlo xhi\n", printformat, xlo, printformat, xhi);


	//	/// line 4
	//	std::fprintf(NewPCF, "%.*f  %.*f ylo yhi\n", printformat, ylo, printformat, yhi);

	//	/// line 5
	//	std::fprintf(NewPCF, "%.*f  %.*f zlo zhi\n", printformat, zlo, printformat, zhi);

	//	/// line 6
	//	std::fclose(uc_file);

	//	std::fprintf(NewPCF, "\nMasses\n\n");

	//	for (ole = 0; ole < a; ole++)
	//	{
	//		std::fprintf(NewPCF, "%d\t%.*f\n", ole + 1, printformat, aweights[ole]);
	//	}

	//	std::fprintf(NewPCF, "\nAtoms\n\n");

	//	if (sized[0] / 2 != sized[0] / 2.0)
	//	{
	//		xexe[0] = 1;
	//	}

	//	if (sized[1] / 2 != sized[1] / 2.0)
	//	{
	//		xexe[1] = 1;
	//	}

	//	if (sized[2] / 2 != sized[2] / 2.0)
	//	{
	//		xexe[2] = 1;
	//	}

	//	int omg = 0;


	//	for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2 + xexe[2]; ole4++) {
	//		for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2 + xexe[1]; ole2++) {
	//			for (ole = -sized[0] / 2; ole < sized[0] / 2 + xexe[0]; ole++) {
	//				for (ole3 = 0; ole3 < t; ole3++) {

	//					omg++;
	//					for (int ii = 0; ii < a; ii++)
	//					{
	//						if (crystal[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == aweights[ii])
	//						{
	//							std::fprintf(NewPCF, "%d\t%d\t", omg, ii + 1);

	//							for (ole1 = 0; ole1 < 3; ole1++) {

	//								std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
	//							}
	//							std::fprintf(NewPCF, "\n");
	//							ii = 90000;
	//						}
	//					}



	//				}
	//			}
	//		}
	//		full = 1;
	//	}



	//	std::fclose(NewPCF);

	//	delete(s);

	//	return;


	//}
	//else if (CustomSurfacesOn)
	//{
		NewPC[0] = '\0';
		std::strcat(NewPC, PCtype);
		std::strcat(NewPC, "_NIKOULIS.lmp");


		FILE *NewPCF = fopen(NewPC, "w");
		FILE *uc_file = fopen(inpf, "r");


		char* s;
		char* token;
		s = (char*)malloc(sizeof(char) * SBYTES);


		/// line 1

		std::fgets(s, SBYTES, uc_file);
		std::fprintf(NewPCF, s);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fprintf(NewPCF, s);

			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}

		/// line 2
		for (ole1 = 0; ole1 < a; ole1++)
		{
			new_num_atoms[ole1] = 0;
			atomscc = 0;


		}

		float xlo = 0, xhi = vs.group[vs._isimulationBox].primitiveVec[0].abs(),
			ylo = 0, yhi = vs.group[vs._isimulationBox].primitiveVec[1].abs(),
			zlo = 0, zhi = vs.group[vs._isimulationBox].primitiveVec[2].abs();


		int inttoprint = 0;
		for (int i = 0; i < vs.N_types; i++)
		{
			inttoprint += vs.N_atoms_per_type[i];
		}
		std::fprintf(NewPCF, "\n%d atoms\n", inttoprint);

		std::fprintf(NewPCF, "\n%d atom types\n", vs.N_types);

		/// line 3
		std::fprintf(NewPCF, "\n%.*f  %.*f xlo xhi\n", printformat, xlo, printformat, xhi);


		/// line 4
		std::fprintf(NewPCF, "%.*f  %.*f ylo yhi\n", printformat, ylo, printformat, yhi);

		/// line 5
		std::fprintf(NewPCF, "%.*f  %.*f zlo zhi\n", printformat, zlo, printformat, zhi);

		//float b = sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2]);
		float b = vs.group[vs._isimulationBox].primitiveVec[1].abs();
		//float c = sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2]);
		float c = vs.group[vs._isimulationBox].primitiveVec[2].abs();
		//float xy = b * ((ijk[0][0] * ijk[1][0] + ijk[0][1] * ijk[1][1] + ijk[0][2] * ijk[1][2]) /
		//	(sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2])*
		//		sqrt(ijk[0][0] * ijk[0][0] + ijk[0][1] * ijk[0][1] + ijk[0][2] * ijk[0][2])));
		jgn::vec3* v0 = &vs.group[vs._isimulationBox].primitiveVec[0];
		jgn::vec3* v1 = &vs.group[vs._isimulationBox].primitiveVec[1];
		jgn::vec3* v2 = &vs.group[vs._isimulationBox].primitiveVec[2];
		float xy = b * (v0->x * v1->x + v0->y * v1->y + v0->z * v1->z) /
			(b*vs.group[vs._isimulationBox].primitiveVec[0].abs());

		//float xz = c * ((ijk[0][0] * ijk[2][0] + ijk[0][1] * ijk[2][1] + ijk[0][2] * ijk[2][2]) /
		//	(sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2])*
		//		sqrt(ijk[0][0] * ijk[0][0] + ijk[0][1] * ijk[0][1] + ijk[0][2] * ijk[0][2])));
		float xz = c * ((v0->x * v2->x + v0->y * v2->y + v0->z * v2->z) /
			(c*vs.group[vs._isimulationBox].primitiveVec[0].abs()));

		//float yz = (b*c*((ijk[1][0] * ijk[2][0] + ijk[1][1] * ijk[2][1] + ijk[1][2] * ijk[2][2]) /
		//	(sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2])*
		//		sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2]))) - xy * xz)
		//	/ (sqrt(b*b - xy * xy));
		float yz = (b*c*((v1->x * v2->x + v1->y * v2->y + v1->z * v2->z) /
			(c*b)) - xy * xz)/ (sqrt(b*b - xy * xy));

		//xy = xy * (xhi - xlo) / ijk[0][0];
		xy = xy * (xhi - xlo) / v0->x;
		//xz = xz * (xhi - xlo) / ijk[0][0];
		xz = xz * (xhi - xlo) / v0->x;
		//yz = yz * (yhi - ylo) / ijk[1][1];
		yz = yz * (yhi - ylo) / v1->y;
		std::fprintf(NewPCF, "%.*f  %.*f  %.*f xy xz yz\n", printformat, xy, printformat, xz, printformat, yz);

		/// line 6
		std::fclose(uc_file);

		std::fprintf(NewPCF, "\nMasses\n\n");

		
		for (int i = 0; i < vs.N_types; i++)
		{
			std::fprintf(NewPCF, "%d\t%.*f\n", i + 1, printformat, vs.weight_per_type[i]);
		}

		std::fprintf(NewPCF, "\nAtoms\n\n");



		atomscc = 0;
		for (int g = 0; g < vs.N_groups; g++)
		{
			for (int i = 0; i < vs.group[g].N_atoms; i++)
			{
				if (!vs.group[g].isdeleted[i] && !vs.group[g].iscut[i])
				{
					atomscc++;
					int atype = 0;
					for (int j = 0; j < vs.group[g]._N_types; j++)
					{
						if (vs.group[g].weight[i] == vs.group[g].weight_per_type[j])
						{
							atype = j + 1;
							j = 1000;
						}
					}
					std::fprintf(NewPCF, "%d\t%d\t", atomscc, atype);

					std::fprintf(NewPCF, "%.*f ", printformat, vs.group[g].position[i].x);
					std::fprintf(NewPCF, "%.*f ", printformat, vs.group[g].position[i].y);
					std::fprintf(NewPCF, "%.*f ", printformat, vs.group[g].position[i].z);

					std::fprintf(NewPCF, "\n");
				}

			}
		}
		//if (sized[0] / 2 != sized[0] / 2.0)
		//{
		//	xexe[0] = 1;
		//}

		//if (sized[1] / 2 != sized[1] / 2.0)
		//{
		//	xexe[1] = 1;
		//}

		//if (sized[2] / 2 != sized[2] / 2.0)
		//{
		//	xexe[2] = 1;
		//}

		//for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2 + xexe[2]; ole4++) {
		//	for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2 + xexe[1]; ole2++) {
		//		for (ole = -sized[0] / 2; ole < sized[0] / 2 + xexe[0]; ole++) {
		//			for (ole3 = 0; ole3 < t; ole3++) {
		//				float p[3];
		//				ole1 = 0;
		//				p[0] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
		//				ole1 = 1;
		//				p[1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
		//				ole1 = 2;
		//				p[2] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

		//				for (i = 0; i < CustomSurfacesCount; i++)
		//				{
		//					if (CustomSurfaces[i][0] * (p[0] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (p[1] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (p[2] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
		//					{

		//					}
		//					else
		//					{
		//						i = 1000;
		//					}

		//				}

		//				if (i == CustomSurfacesCount)
		//				{
		//					for (int ii = 0; ii < a; ii++)
		//					{
		//						if (crystal[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == aweights[ii])
		//						{
		//							atomscc++;
		//							std::fprintf(NewPCF, "%d\t%d\t", atomscc, ii + 1);
		//							for (ole1 = 0; ole1 < 3; ole1++) {

		//								std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
		//							}
		//							std::fprintf(NewPCF, "\n");
		//						}
		//					}
		//				}

		//			}
		//		}
		//	}
		//	full = 1;
		//}



		std::fclose(NewPCF);

		delete(s);

		return;



	//}
	//else if (Rod_like == -1)
	//{
	//	NewPC[0] = '\0';
	//	std::strcat(NewPC, PCtype);
	//	std::strcat(NewPC, "_NIKOULIS");
	//	char S[50];
	//	std::strcat(NewPC, "(Rod_like)");
	//	if (S1v >= S2v || S1v >= S3v)
	//	{

	//	}
	//	else
	//	{
	//		itoa(S1v, S, 10);
	//		std::strcat(NewPC, "(100");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}

	//	if (S2v >= 2 * S1v || S3v <= S2v)
	//	{

	//	}
	//	else
	//	{
	//		itoa(S2v, S, 10);
	//		std::strcat(NewPC, "(110");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}

	//	itoa(S3v, S, 10);
	//	std::strcat(NewPC, "(111");
	//	std::strcat(NewPC, S);
	//	std::strcat(NewPC, ")");
	//	std::strcat(NewPC, ".lmp");
	//	FILE *NewPCF = fopen(NewPC, "w");
	//	FILE *uc_file = fopen(inpf, "r");


	//	char* s;
	//	char* token;
	//	s = (char*)malloc(sizeof(char) * SBYTES);



	//	/// line 1

	//	std::fgets(s, SBYTES, uc_file);
	//	std::fprintf(NewPCF, s);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fprintf(NewPCF, s);

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}


	//	/// line 2
	//	for (ole1 = 0; ole1 < a; ole1++)
	//	{
	//		new_num_atoms[ole1] = 0;
	//		atomscc = 0;


	//	}

	//	float xlo = fl_max, xhi = fl_min,
	//		ylo = fl_max, yhi = fl_min,
	//		zlo = fl_max, zhi = fl_min;

	//	for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//	{
	//		float p[3];
	//		ole2 = 0;
	//		p[0] = crystal[ole2 + 2 + 5 * (ole)];
	//		ole2 = 1;
	//		p[1] = crystal[ole2 + 2 + 5 * ole];
	//		ole2 = 2;
	//		p[2] = crystal[ole2 + 2 + 5 * ole];

	//		if (vacuum ^ ((S1i[0] * abs(crystal[2 + 0 + 5 * ole]) <= S1v) && (S1i[0] * Right_Hexagonal*Rod_like* abs(crystal[2 + 1 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[2 + 2 + 5 * ole]) <= S1v) && Rod_like*(S2i[0] * abs(crystal[2 + 0 + 5 * ole]) + S2i[0] * Right_Hexagonal* abs(crystal[2 + 1 + 5 * ole])) <= S2v && S2i[0] * abs(crystal[2 + 0 + 5 * ole]) + S2i[0] * abs(crystal[2 + 2 + 5 * ole]) <= S2v && Rod_like*(S2i[0] * Right_Hexagonal* abs(crystal[2 + 1 + 5 * ole]) + S2i[0] * abs(crystal[2 + 2 + 5 * ole])) <= S2v && Right_Hexagonal*(S3i[0] * abs(crystal[2 + 0 + 5 * ole]) + S3i[1] * abs(crystal[2 + 1 + 5 * ole]) + S3i[2] * abs(crystal[2 + 2 + 5 * ole])) <= S3v))
	//		{
	//			for (i = 0; i < CustomSurfacesCount; i++)
	//			{
	//				if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//				{

	//				}
	//				else
	//				{
	//					i = 1000;
	//				}

	//			}

	//			if (i == CustomSurfacesCount)
	//			{
	//				if (crystal[2 + 5 * ole] > xhi)
	//				{
	//					xhi = crystal[2 + 5 * ole];
	//				}
	//				else if (crystal[2 + 5 * ole] < xlo)
	//				{
	//					xlo = crystal[2 + 5 * ole];
	//				}
	//				if (crystal[3 + 5 * ole] > yhi)
	//				{
	//					yhi = crystal[3 + 5 * ole];
	//				}
	//				else if (crystal[3 + 5 * ole] < ylo)
	//				{
	//					ylo = crystal[3 + 5 * ole];
	//				}
	//				if (crystal[4 + 5 * ole] > zhi)
	//				{
	//					zhi = crystal[4 + 5 * ole];
	//				}
	//				else if (crystal[4 + 5 * ole] < zlo)
	//				{
	//					zlo = crystal[4 + 5 * ole];
	//				}
	//				new_num_atoms[0] = new_num_atoms[0] + 1;
	//				atomscc++;
	//			}
	//		}
	//	}

	//	xhi = ijk[0][0] * sized[0] + xlo;
	//	yhi = ijk[1][1] * sized[1] + ylo;
	//	zhi = ijk[2][2] * sized[2] + zlo;


	//	std::fprintf(NewPCF, "\n%d atoms\n", new_num_atoms[0]);

	//	std::fprintf(NewPCF, "\n%d atom types\n", a);

	//	/// line 3
	//	std::fprintf(NewPCF, "\n%.*f  %.*f xlo xhi\n", printformat, xlo, printformat, xhi);


	//	/// line 4
	//	std::fprintf(NewPCF, "%.*f  %.*f ylo yhi\n", printformat, ylo, printformat, yhi);

	//	/// line 5
	//	std::fprintf(NewPCF, "%.*f  %.*f zlo zhi\n", printformat, zlo, printformat, zhi);

	//	//float b = sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2]);
	//	//float c = sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2]);
	//	//float xy = b * ((ijk[0][0] * ijk[1][0] + ijk[0][1] * ijk[1][1] + ijk[0][2] * ijk[1][2]) /
	//	//	(sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2])*
	//	//		sqrt(ijk[0][0] * ijk[0][0] + ijk[0][1] * ijk[0][1] + ijk[0][2] * ijk[0][2])));
	//	//float xz = c * ((ijk[0][0] * ijk[2][0] + ijk[0][1] * ijk[2][1] + ijk[0][2] * ijk[2][2]) /
	//	//	(sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2])*
	//	//		sqrt(ijk[0][0] * ijk[0][0] + ijk[0][1] * ijk[0][1] + ijk[0][2] * ijk[0][2])));
	//	//float yz = (b*c*((ijk[1][0] * ijk[2][0] + ijk[1][1] * ijk[2][1] + ijk[1][2] * ijk[2][2]) /
	//	//	(sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2])*
	//	//		sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2]))) - xy * xz)
	//	//	/ (sqrt(b*b - xy * xy));
	//	//std::fprintf(NewPCF, "%.*f  %.*f  %.*f xy xz yz\n", printformat, xy, printformat, xz, printformat, yz);

	//	/// line 6
	//	std::fclose(uc_file);

	//	std::fprintf(NewPCF, "\nMasses\n\n");

	//	for (ole = 0; ole < a; ole++)
	//	{
	//		std::fprintf(NewPCF, "%d\t%.*f\n", ole + 1, printformat, aweights[ole]);
	//	}

	//	std::fprintf(NewPCF, "\nAtoms\n\n");



	//	if (sized[0] / 2 != sized[0] / 2.0)
	//	{
	//		xexe[0] = 1;
	//	}

	//	if (sized[1] / 2 != sized[1] / 2.0)
	//	{
	//		xexe[1] = 1;
	//	}

	//	if (sized[2] / 2 != sized[2] / 2.0)
	//	{
	//		xexe[2] = 1;
	//	}


	//	atomscc = 0;
	//	for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2 + xexe[2]; ole4++) {
	//		for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2 + xexe[1]; ole2++) {
	//			for (ole = -sized[0] / 2; ole < sized[0] / 2 + xexe[0]; ole++) {
	//				for (ole3 = 0; ole3 < t; ole3++) {
	//					if (vacuum ^ ((S1i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * Right_Hexagonal*Rod_like* abs(crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && Rod_like*(S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[0] * Right_Hexagonal* abs(crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))])) <= S2v && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && Rod_like*(S2i[0] * Right_Hexagonal* abs(crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))])) <= S2v && Right_Hexagonal*(S3i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[2] * abs(crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))])) <= S3v))

	//					{
	//						for (i = 0; i < CustomSurfacesCount; i++)
	//						{
	//							if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//							{

	//							}
	//							else
	//							{
	//								i = 1000;
	//							}

	//						}

	//						if (i == CustomSurfacesCount)
	//						{
	//							for (int ii = 0; ii < a; ii++)
	//							{
	//								if (crystal[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == aweights[ii])
	//								{
	//									atomscc++;
	//									std::fprintf(NewPCF, "%d\t%d\t", atomscc, ii + 1);
	//									for (ole1 = 0; ole1 < 3; ole1++) {

	//										std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
	//									}
	//									std::fprintf(NewPCF, "\n");
	//								}
	//							}
	//						}


	//					}

	//				}
	//			}
	//		}
	//		full = 1;
	//	}



	//	std::fclose(NewPCF);

	//	delete(s);

	//}
	//else if (Right_Hexagonal == -1)
	//{
	//	NewPC[0] = '\0';
	//	std::strcat(NewPC, PCtype);
	//	std::strcat(NewPC, "_NIKOULIS");
	//	char S[50];
	//	std::strcat(NewPC, "(Hexagonal)");
	//	itoa(Right_Hexagonal_height, S, 10);
	//	std::strcat(NewPC, "(0001");
	//	std::strcat(NewPC, S);
	//	std::strcat(NewPC, ")");
	//	if (float(S1v) / float(S2v) > 1.14814814815)
	//	{

	//	}
	//	else
	//	{
	//		itoa(S1v, S, 10);
	//		std::strcat(NewPC, "(10-10");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}
	//	if (float(S1v) / float(S2v) < 0.86842105263)
	//	{

	//	}
	//	else
	//	{
	//		itoa(S2v, S, 10);
	//		std::strcat(NewPC, "(11-20");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}
	//	std::strcat(NewPC, ".lmp");

	//	FILE *NewPCF = fopen(NewPC, "w");
	//	FILE *uc_file = fopen(inpf, "r");


	//	char* s;
	//	char* token;
	//	s = (char*)malloc(sizeof(char) * SBYTES);



	//	/// line 1

	//	std::fgets(s, SBYTES, uc_file);
	//	std::fprintf(NewPCF, s);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fprintf(NewPCF, s);

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	/// line 2
	//	for (ole1 = 0; ole1 < a; ole1++)
	//	{
	//		new_num_atoms[ole1] = 0;
	//		atomscc = 0;


	//	}

	//	float xlo = fl_max, xhi = fl_min,
	//		ylo = fl_max, yhi = fl_min,
	//		zlo = fl_max, zhi = fl_min;

	//	for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//	{
	//		float p[3];
	//		ole2 = 0;
	//		p[0] = crystal[ole2 + 2 + 5 * (ole)];
	//		ole2 = 1;
	//		p[1] = crystal[ole2 + 2 + 5 * ole];
	//		ole2 = 2;
	//		p[2] = crystal[ole2 + 2 + 5 * ole];


	//		{
	//			if (vacuum ^ ((abs(crystal[4 + 5 * ole]) < Right_Hexagonal_height) && (S1i[0] * abs(crystal[2 + 5 * ole]) <= S2v * 0.866025404) && S2i[0] * abs(crystal[2 + 5 * ole]) / 1.73205 + S2i[0] * figure_1 * abs(crystal[2 + 1 + 5 * ole]) <= S2v &&
	//				(S1i[0] * figure_1*abs(crystal[2 + 1 + 5 * ole]) <= S1v * 0.866025404) && S2i[0] * figure_1 * abs(crystal[2 + 0 + 5 * ole]) + S1i[0] * figure_1 * abs(crystal[2 + 1 + 5 * ole]) / 1.73205 <= S1v))
	//			{

	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{

	//					if (crystal[2 + 5 * ole] > xhi)
	//					{
	//						xhi = crystal[2 + 5 * ole];
	//					}
	//					else if (crystal[2 + 5 * ole] < xlo)
	//					{
	//						xlo = crystal[2 + 5 * ole];
	//					}
	//					if (crystal[3 + 5 * ole] > yhi)
	//					{
	//						yhi = crystal[3 + 5 * ole];
	//					}
	//					else if (crystal[3 + 5 * ole] < ylo)
	//					{
	//						ylo = crystal[3 + 5 * ole];
	//					}
	//					if (crystal[4 + 5 * ole] > zhi)
	//					{
	//						zhi = crystal[4 + 5 * ole];
	//					}
	//					else if (crystal[4 + 5 * ole] < zlo)
	//					{
	//						zlo = crystal[4 + 5 * ole];
	//					}
	//					new_num_atoms[0] = new_num_atoms[0] + 1;
	//					atomscc++;
	//				}
	//			}
	//		}

	//	}
	//	xhi = ijk[0][0] * sized[0] + xlo;
	//	yhi = ijk[1][1] * sized[1] + ylo;
	//	zhi = ijk[2][2] * sized[2] + zlo;



	//	std::fprintf(NewPCF, "\n%d atoms\n", new_num_atoms[0]);

	//	std::fprintf(NewPCF, "\n%d atom types\n", a);

	//	/// line 3
	//	std::fprintf(NewPCF, "\n%.*f  %.*f xlo xhi\n", printformat, xlo, printformat, xhi);


	//	/// line 4
	//	std::fprintf(NewPCF, "%.*f  %.*f ylo yhi\n", printformat, ylo, printformat, yhi);

	//	/// line 5
	//	std::fprintf(NewPCF, "%.*f  %.*f zlo zhi\n", printformat, zlo, printformat, zhi);

	//	float b = sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2]);
	//	float c = sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2]);
	//	float xy = b * ((ijk[0][0] * ijk[1][0] + ijk[0][1] * ijk[1][1] + ijk[0][2] * ijk[1][2]) /
	//		(sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2])*
	//			sqrt(ijk[0][0] * ijk[0][0] + ijk[0][1] * ijk[0][1] + ijk[0][2] * ijk[0][2])));
	//	float xz = c * ((ijk[0][0] * ijk[2][0] + ijk[0][1] * ijk[2][1] + ijk[0][2] * ijk[2][2]) /
	//		(sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2])*
	//			sqrt(ijk[0][0] * ijk[0][0] + ijk[0][1] * ijk[0][1] + ijk[0][2] * ijk[0][2])));
	//	float yz = (b*c*((ijk[1][0] * ijk[2][0] + ijk[1][1] * ijk[2][1] + ijk[1][2] * ijk[2][2]) /
	//		(sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2])*
	//			sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2]))) - xy * xz)
	//		/ (sqrt(b*b - xy * xy));
	//	xy = xy * (xhi - xlo) / ijk[0][0];
	//	xz = xz * (xhi - xlo) / ijk[0][0];
	//	yz = yz * (yhi - ylo) / ijk[1][1];
	//	std::fprintf(NewPCF, "%.*f  %.*f  %.*f xy xz yz\n", printformat, xy, printformat, xz, printformat, yz);

	//	/// line 6
	//	std::fclose(uc_file);

	//	std::fprintf(NewPCF, "\nMasses\n\n");

	//	for (ole = 0; ole < a; ole++)
	//	{
	//		std::fprintf(NewPCF, "%d\t%.*f\n", ole + 1, printformat, aweights[ole]);
	//	}

	//	std::fprintf(NewPCF, "\nAtoms\n\n");




	//	atomscc = 0;
	//	for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//	{

	//		{
	//			if (vacuum ^ ((abs(crystal[4 + 5 * ole]) < Right_Hexagonal_height) && (S1i[0] * abs(crystal[2 + 5 * ole]) <= S2v * 0.866025404) && S2i[0] * abs(crystal[2 + 5 * ole]) / 1.73205 + S2i[0] * figure_1 * abs(crystal[2 + 1 + 5 * ole]) <= S2v &&
	//				(S1i[0] * figure_1*abs(crystal[2 + 1 + 5 * ole]) <= S1v * 0.866025404) && S2i[0] * figure_1 * abs(crystal[2 + 0 + 5 * ole]) + S1i[0] * figure_1 * abs(crystal[2 + 1 + 5 * ole]) / 1.73205 <= S1v))
	//			{
	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{

	//					for (int ii = 0; ii < a; ii++)
	//					{
	//						if (crystal[1 + 5 * ole] == aweights[ii])
	//						{
	//							atomscc++;
	//							std::fprintf(NewPCF, "%d\t%d\t", atomscc, ii + 1);
	//							for (ole1 = 0; ole1 < 3; ole1++) {

	//								std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * ole]);
	//							}
	//							std::fprintf(NewPCF, "\n");
	//						}
	//					}
	//				}


	//			}
	//		}

	//	}


	//	std::fclose(NewPCF);

	//	delete(s);
	//	return;

	//}
	//else
	//{
	//	if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
	//	{
	//		NewPC[0] = '\0';
	//		std::strcat(NewPC, PCtype);
	//		std::strcat(NewPC, "_NIKOULIS");
	//		char S[50];
	//		itoa(rad, S, 10);
	//		std::strcat(NewPC, "(sphere");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//		std::strcat(NewPC, ".lmp");

	//	}
	//	else
	//	{
	//		NewPC[0] = '\0';
	//		std::strcat(NewPC, PCtype);
	//		std::strcat(NewPC, "_NIKOULIS");
	//		char S[50];
	//		if (Scase == 1 || Scase == 2 || Scase == 3 || Scase == 4)
	//		{
	//			itoa(S1v, S, 10);
	//			std::strcat(NewPC, "(100");
	//			std::strcat(NewPC, S);
	//			std::strcat(NewPC, ")");
	//		}
	//		if (Scase == 1 || Scase == 2 || Scase == 5 || Scase == 6)
	//		{
	//			itoa(S2v, S, 10);
	//			std::strcat(NewPC, "(110");
	//			std::strcat(NewPC, S);
	//			std::strcat(NewPC, ")");
	//		}
	//		if (Scase == 1 || Scase == 3 || Scase == 5 || Scase == 7)
	//		{
	//			itoa(S3v, S, 10);
	//			std::strcat(NewPC, "(111");
	//			std::strcat(NewPC, S);
	//			std::strcat(NewPC, ")");
	//		}
	//		std::strcat(NewPC, ".lmp");
	//	}

	//	FILE *NewPCF = fopen(NewPC, "w");
	//	FILE *uc_file = fopen(inpf, "r");

	//	char* s;
	//	char* token;
	//	s = (char*)malloc(sizeof(char) * SBYTES);



	//	/// line 1

	//	std::fgets(s, SBYTES, uc_file);
	//	std::fprintf(NewPCF, s);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fprintf(NewPCF, s);

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}


	//	/// line 2
	//	for (ole1 = 0; ole1 < a; ole1++)
	//	{
	//		new_num_atoms[ole1] = 0;
	//		atomscc = 0;


	//	}

	//	float xlo = fl_max, xhi = fl_min,
	//		ylo = fl_max, yhi = fl_min,
	//		zlo = fl_max, zhi = fl_min;

	//	for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//	{
	//		float p[3];
	//		ole2 = 0;
	//		p[0] = crystal[ole2 + 2 + 5 * (ole)];
	//		ole2 = 1;
	//		p[1] = crystal[ole2 + 2 + 5 * ole];
	//		ole2 = 2;
	//		p[2] = crystal[ole2 + 2 + 5 * ole];

	//		if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
	//		{
	//			if (vacuum ^ (sqrt(crystal[2 + 5 * ole] * crystal[2 + 5 * ole] + crystal[3 + 5 * ole] * crystal[3 + 5 * ole] + crystal[4 + 5 * ole] * crystal[4 + 5 * ole]) <= rad))
	//			{
	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{
	//					if (crystal[2 + 5 * ole] > xhi)
	//					{
	//						xhi = crystal[2 + 5 * ole];
	//					}
	//					else if (crystal[2 + 5 * ole] < xlo)
	//					{
	//						xlo = crystal[2 + 5 * ole];
	//					}
	//					if (crystal[3 + 5 * ole] > yhi)
	//					{
	//						yhi = crystal[3 + 5 * ole];
	//					}
	//					else if (crystal[3 + 5 * ole] < ylo)
	//					{
	//						ylo = crystal[3 + 5 * ole];
	//					}
	//					if (crystal[4 + 5 * ole] > zhi)
	//					{
	//						zhi = crystal[4 + 5 * ole];
	//					}
	//					else if (crystal[4 + 5 * ole] < zlo)
	//					{
	//						zlo = crystal[4 + 5 * ole];
	//					}
	//					new_num_atoms[0] = new_num_atoms[0] + 1;
	//					atomscc++;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			if (vacuum ^ ((S1i[0] * abs(crystal[2 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[3 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[4 + 5 * ole]) <= S1v) && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[0] * abs(crystal[3 + 5 * ole]) <= S2v && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[0] * abs(crystal[4 + 5 * ole]) <= S2v && S2i[0] * abs(crystal[3 + 5 * ole]) + S2i[0] * abs(crystal[4 + 5 * ole]) <= S2v && S3i[0] * abs(crystal[2 + 5 * ole]) + S3i[1] * abs(crystal[3 + 5 * ole]) + S3i[2] * abs(crystal[4 + 5 * ole]) <= S3v))
	//			{
	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{
	//					if (crystal[2 + 5 * ole] > xhi)
	//					{
	//						xhi = crystal[2 + 5 * ole];
	//					}
	//					else if (crystal[2 + 5 * ole] < xlo)
	//					{
	//						xlo = crystal[2 + 5 * ole];
	//					}
	//					if (crystal[3 + 5 * ole] > yhi)
	//					{
	//						yhi = crystal[3 + 5 * ole];
	//					}
	//					else if (crystal[3 + 5 * ole] < ylo)
	//					{
	//						ylo = crystal[3 + 5 * ole];
	//					}
	//					if (crystal[4 + 5 * ole] > zhi)
	//					{
	//						zhi = crystal[4 + 5 * ole];
	//					}
	//					else if (crystal[4 + 5 * ole] < zlo)
	//					{
	//						zlo = crystal[4 + 5 * ole];
	//					}
	//					new_num_atoms[0] = new_num_atoms[0] + 1;
	//					atomscc++;
	//				}
	//			}
	//		}
	//	}



	//	xhi = ijk[0][0] * sized[0] + xlo;
	//	yhi = ijk[1][1] * sized[1] + ylo;
	//	zhi = ijk[2][2] * sized[2] + zlo;






	//	std::fprintf(NewPCF, "\n%d atoms\n", new_num_atoms[0]);

	//	std::fprintf(NewPCF, "\n%d atom types\n", a);

	//	/// line 3
	//	std::fprintf(NewPCF, "\n%.*f  %.*f xlo xhi\n", printformat, xlo, printformat, xhi);


	//	/// line 4
	//	std::fprintf(NewPCF, "%.*f  %.*f ylo yhi\n", printformat, ylo, printformat, yhi);

	//	/// line 5
	//	std::fprintf(NewPCF, "%.*f  %.*f zlo zhi\n", printformat, zlo, printformat, zhi);

	//	//float b = sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2]);
	//	//float c = sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2]);
	//	//float xy = b * ((ijk[0][0] * ijk[1][0] + ijk[0][1] * ijk[1][1] + ijk[0][2] * ijk[1][2]) /
	//	//	(sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2])*
	//	//		sqrt(ijk[0][0] * ijk[0][0] + ijk[0][1] * ijk[0][1] + ijk[0][2] * ijk[0][2])));
	//	//float xz = c * ((ijk[0][0] * ijk[2][0] + ijk[0][1] * ijk[2][1] + ijk[0][2] * ijk[2][2]) /
	//	//	(sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2])*
	//	//		sqrt(ijk[0][0] * ijk[0][0] + ijk[0][1] * ijk[0][1] + ijk[0][2] * ijk[0][2])));
	//	//float yz = (b*c*((ijk[1][0] * ijk[2][0] + ijk[1][1] * ijk[2][1] + ijk[1][2] * ijk[2][2]) /
	//	//	(sqrt(ijk[2][0] * ijk[2][0] + ijk[2][1] * ijk[2][1] + ijk[2][2] * ijk[2][2])*
	//	//		sqrt(ijk[1][0] * ijk[1][0] + ijk[1][1] * ijk[1][1] + ijk[1][2] * ijk[1][2]))) - xy * xz)
	//	//	/ (sqrt(b*b - xy * xy));
	//	//xy = xy * (xhi - xlo) / ijk[0][0];
	//	//xz = xz * (xhi - xlo) / ijk[0][0];
	//	//yz = yz * (yhi - ylo) / ijk[1][1];
	//	//std::fprintf(NewPCF, "%.*f  %.*f  %.*f xy xz yz\n", printformat, xy, printformat, xz, printformat, yz);

	//	/// line 6
	//	std::fclose(uc_file);

	//	std::fprintf(NewPCF, "\nMasses\n\n");

	//	for (ole = 0; ole < a; ole++)
	//	{
	//		std::fprintf(NewPCF, "%d\t%.*f\n", ole + 1, printformat, aweights[ole]);
	//	}

	//	std::fprintf(NewPCF, "\nAtoms\n\n");




	//	atomscc = 0;
	//	if (want_cyrcle[0] == 'y') {


	//		int ajklsdfl = t * (sized[0])*(sized[1])*(sized[2]);
	//		for (ole3 = 0; ole3 < ajklsdfl; ole3++)
	//		{
	//			if (vacuum ^ (rad >= sqrt(crystal[0 + 2 + 5 * (ole3)] * crystal[0 + 2 + 5 * (ole3)] + crystal[1 + 2 + 5 * (ole3)] * crystal[1 + 2 + 5 * (ole3)] + crystal[2 + 2 + 5 * (ole3)] * crystal[2 + 2 + 5 * (ole3)])))
	//			{
	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * ole3] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * ole3] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * ole3] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{
	//					for (int ii = 0; ii < a; ii++)
	//					{
	//						if (crystal[1 + 5 * ole3] == aweights[ii])
	//						{
	//							atomscc++;
	//							std::fprintf(NewPCF, "%d\t%d\t", atomscc, ii + 1);
	//							for (ole1 = 0; ole1 < 3; ole1++) {

	//								std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * ole3]);
	//							}
	//							std::fprintf(NewPCF, "\n");
	//						}
	//					}
	//				}

	//			}
	//		}


	//	}
	//	else {

	//		int ajklsdfl = t * (sized[0])*(sized[1])*(sized[2]);
	//		for (ole3 = 0; ole3 < ajklsdfl; ole3++)
	//		{
	//			if (vacuum ^ ((S1i[0] * figure_1*abs(crystal[2 + 5 * ole3]) <= S1v) && (S1i[0] * Right_Hexagonal*Rod_like* abs(crystal[4 + 5 * ole3]) <= S1v) && (S1i[0] * figure_1*abs(crystal[3 + 5 * ole3]) <= S1v) && Rod_like*(S2i[0] * abs(crystal[2 + 5 * ole3]) + S2i[0] * Right_Hexagonal* abs(crystal[4 + 5 * ole3])) <= S2v && S2i[0] * figure_1* abs(crystal[2 + 5 * ole3]) + S2i[0] * figure_1* abs(crystal[3 + 5 * ole3]) <= S2v && Rod_like*(S2i[0] * Right_Hexagonal* abs(crystal[4 + 5 * ole3]) + S2i[0] * abs(crystal[3 + 5 * ole3])) <= S2v && Right_Hexagonal*(S3i[0] * abs(crystal[2 + 5 * ole3]) + S3i[1] * abs(crystal[4 + 5 * ole3]) + S3i[2] * abs(crystal[3 + 5 * ole3])) <= S3v))
	//			{
	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * ole3] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * ole3] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * ole3] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{
	//					for (int ii = 0; ii < a; ii++)
	//					{
	//						if (crystal[1 + 5 * ole3] == aweights[ii])
	//						{
	//							atomscc++;
	//							std::fprintf(NewPCF, "%d\t%d\t", atomscc, ii + 1);
	//							for (ole1 = 0; ole1 < 3; ole1++) {

	//								std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * ole3]);
	//							}
	//							std::fprintf(NewPCF, "\n");
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//	free(s);


	//	std::fclose(NewPCF);
	//	return;
	//}
	//return;
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BuildPoscar(char* NewPC)
{
	time_t now = time(0);
	char* dt = ctime(&now);


	for (int i = 0; i < 100; i++)
	{
		if (NewPC[i] == '(')
		{
			NewPC[i] = NULL;
			i = 100;
		}
	}
	//if (false)
	//{


	//	std::strcat(NewPC, "_NT");
	//	//std::strcat(NewPC, dt);
	//	//std::strcat(NewPC, ")");

	//	FILE *NewPCF = fopen(NewPC, "w");
	//	FILE *uc_file = fopen(inpf, "r");


	//	char* s;
	//	char* token;
	//	s = (char*)malloc(sizeof(char) * SBYTES);


	//	/// line 1

	//	std::fgets(s, SBYTES, uc_file);
	//	std::fprintf(NewPCF, s);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fprintf(NewPCF, s);

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}


	//	/// line 2
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}
	//	std::fprintf(NewPCF, jgn::ftoa(actor));
	//	std::fprintf(NewPCF, "\n");



	//	/// line 3
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	//std::fprintf(NewPCF, "%.*f", printformat, ijk[0][0] * sized[0] / actor);
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[0].x / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	//std::fprintf(NewPCF, "%.*f", printformat, ijk[0][1] * sized[0] / actor);
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[0].y / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	//std::fprintf(NewPCF, "%.*f\n", printformat, ijk[0][2] * sized[0] / actor);
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[0].z / actor);


	//	/// line 4
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	//std::fprintf(NewPCF, "%.*f", printformat, ijk[1][0] * sized[1] / actor);
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[1].x / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	//std::fprintf(NewPCF, "%.*f", printformat, ijk[1][1] * sized[1] / actor);
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[1].y / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	//std::fprintf(NewPCF, "%.*f\n", printformat, ijk[1][2] * sized[1] / actor);
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[1].z / actor);

	//	/// line 5
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	//std::fprintf(NewPCF, "%.*f", printformat, ijk[2][0] * sized[2] / actor);
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[2].x / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	//std::fprintf(NewPCF, "%.*f", printformat, ijk[2][1] * sized[2] / actor);
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[2].y / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	//std::fprintf(NewPCF, "%.*f\n", printformat, ijk[2][2] * sized[2]) / actor;
	//	std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[2].z / actor);

	//	/// line 6
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}


	//	std::fprintf(NewPCF, atoms);
	//	std::fprintf(NewPCF, "\n");




	//	for (ole1 = 0; ole1 < a; ole1++)
	//	{
	//		new_num_atoms[ole1] = 0;
	//		atomscc = 0;


	//	}


	//	for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//	{

	//		for (ole1 = 0; ole1 < a; ole1++)
	//		{
	//			if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
	//			{

	//				new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
	//				atomscc++;


	//			}

	//		}




	//	}


	//	for (ole = 0; ole < a; ole++)
	//	{
	//		std::fprintf(NewPCF, "%d ", new_num_atoms[ole]);

	//	}
	//	std::fprintf(NewPCF, "\n");



	//	std::fclose(uc_file);


	//	if (selective_dynamics_bool)
	//		std::fprintf(NewPCF, "Selective Dynamics\n");

	//	std::fprintf(NewPCF, "Cartesian\n");


	//	if (sized[0] / 2 != sized[0] / 2.0)
	//	{
	//		xexe[0] = 1;
	//	}

	//	if (sized[1] / 2 != sized[1] / 2.0)
	//	{
	//		xexe[1] = 1;
	//	}

	//	if (sized[2] / 2 != sized[2] / 2.0)
	//	{
	//		xexe[2] = 1;
	//	}


	//	for (ole5 = 0; ole5 < a; ole5++) {
	//		for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2 + xexe[2]; ole4++) {
	//			for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2 + xexe[1]; ole2++) {
	//				for (ole = -sized[0] / 2; ole < sized[0] / 2 + xexe[0]; ole++) {
	//					for (ole3 = 0; ole3 < t; ole3++) {

	//						if (crystal[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
	//						{

	//							for (ole1 = 0; ole1 < 3; ole1++) {

	//								std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
	//							}
	//							if (selective_dynamics_bool)
	//							{
	//								for (ole1 = 0; ole1 < 3; ole1++) {

	//									std::fprintf(NewPCF, "%c ", selective_dynamics[ole1 + 3 * (ole3)]);
	//								}
	//							}
	//							std::fprintf(NewPCF, "\n");




	//						}

	//					}
	//				}
	//			}
	//			full = 1;
	//		}

	//	}

	//	std::fclose(NewPCF);

	//	delete(s);

	//	return;


	//}
	//else if (true)
	//{

		//std::strcat(NewPC, "(");
		//std::strcat(NewPC, dt);
		//std::strcat(NewPC, ")");

		FILE *NewPCF = fopen(NewPC, "w");
		FILE *uc_file = fopen(inpf, "r");


		char* s;
		char* token;
		s = (char*)malloc(sizeof(char) * SBYTES);


		/// line 1

		std::fgets(s, SBYTES, uc_file);
		//std::fprintf(NewPCF, s);
		std::fprintf(NewPCF, "poscar file by\n");
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			//std::fprintf(NewPCF, s);

			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}


		/// line 2
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{

			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		std::fprintf(NewPCF, jgn::ftoa(actor));
		std::fprintf(NewPCF, "\n");



		/// line 3
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}

		//std::fprintf(NewPCF, "%.*f", printformat, ijk[0][0] * sized[0] / actor);
		std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[0].x / actor);
		std::fprintf(NewPCF, " ");
		token = strtok(NULL, "\t ");

		//std::fprintf(NewPCF, "%.*f", printformat, ijk[0][1] * sized[0] / actor);
		std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[0].y / actor);
		std::fprintf(NewPCF, " ");
		token = strtok(NULL, "\t ");

		//std::fprintf(NewPCF, "%.*f\n", printformat, ijk[0][2] * sized[0] / actor);
		std::fprintf(NewPCF, "%.*f\n", printformat, vs.group[vs._isimulationBox].primitiveVec[0].z / actor);


		/// line 4
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}

		//std::fprintf(NewPCF, "%.*f", printformat, ijk[1][0] * sized[1] / actor);
		std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[1].x / actor);
		std::fprintf(NewPCF, " ");
		token = strtok(NULL, "\t ");

		//std::fprintf(NewPCF, "%.*f", printformat, ijk[1][1] * sized[1] / actor);
		std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[1].y / actor);
		std::fprintf(NewPCF, " ");
		token = strtok(NULL, "\t ");

		//std::fprintf(NewPCF, "%.*f\n", printformat, ijk[1][2] * sized[1] / actor);
		std::fprintf(NewPCF, "%.*f\n", printformat, vs.group[vs._isimulationBox].primitiveVec[1].z / actor);

		/// line 5
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}

		//std::fprintf(NewPCF, "%.*f", printformat, ijk[2][0] * sized[2] / actor);
		std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[2].x / actor);
		std::fprintf(NewPCF, " ");
		token = strtok(NULL, "\t ");

		//std::fprintf(NewPCF, "%.*f", printformat, ijk[2][1] * sized[2] / actor);
		std::fprintf(NewPCF, "%.*f", printformat, vs.group[vs._isimulationBox].primitiveVec[2].y / actor);
		std::fprintf(NewPCF, " ");
		token = strtok(NULL, "\t ");

		//std::fprintf(NewPCF, "%.*f\n", printformat, ijk[2][2] * sized[2]) / actor;
		std::fprintf(NewPCF, "%.*f\n", printformat, vs.group[vs._isimulationBox].primitiveVec[2].z / actor);

		/// line 6
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{

			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}




		//std::fprintf(NewPCF, atoms);
		for (int i = 0; i < vs.N_types; i++)
		{
			std::fprintf(NewPCF, vs.types[i].c_str());
			std::fprintf(NewPCF, " ");
		}
		std::fprintf(NewPCF, "\n");




		for (ole1 = 0; ole1 < a; ole1++)
		{
			new_num_atoms[ole1] = 0;
			atomscc = 0;


		}


		for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
		{

			for (ole1 = 0; ole1 < a; ole1++)
			{
				if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
				{
					double p[3];
					ole2 = 0;
					p[0] = crystal[ole2 + 2 + 5 * (ole)];
					ole2 = 1;
					p[1] = crystal[ole2 + 2 + 5 * ole];
					ole2 = 2;
					p[2] = crystal[ole2 + 2 + 5 * ole];

					for (i = 0; i < CustomSurfacesCount; i++)
					{
						if (CustomSurfaces[i][0] * (p[0] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (p[1] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (p[2] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
						{

						}
						else
						{
							i = 1000;
						}

					}

					if (i == CustomSurfacesCount)
					{
						new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
						atomscc++;
					}

				}

			}




		}


		//for (ole = 0; ole < a; ole++)
		//{
		//	std::fprintf(NewPCF, "%d ", new_num_atoms[ole]);

		//}
		for (int i = 0; i < vs.N_types; i++)
		{
			std::fprintf(NewPCF, "%d ", vs.N_atoms_per_type[i]);
		}
		std::fprintf(NewPCF, "\n");



		std::fclose(uc_file);


		//if (selective_dynamics_bool)
			//std::fprintf(NewPCF, "Selective Dynamics\n");
		std::fprintf(NewPCF, "Selective dynamics\n");
		std::fprintf(NewPCF, "Cartesian\n");

		for (int t = 0; t < vs.N_types; t++)
		{
			for (int g = 0; g < vs.N_groups; g++)
			{
				for (int i = 0; i < vs.group[g].N_atoms; i++)
				{
					if (!vs.group[g].isdeleted[i] && !vs.group[g].iscut[i])
					{
						if (vs.types[t].compare(vs.group[g].type[i]) == 0)
						{
							std::fprintf(NewPCF, "%.*f ", printformat, vs.group[g].position[i].x);
							std::fprintf(NewPCF, "%.*f ", printformat, vs.group[g].position[i].y);
							std::fprintf(NewPCF, "%.*f   ", printformat, vs.group[g].position[i].z);
							std::fprintf(NewPCF, "%c ", vs.group[g].selective_dynamics[i].c_str()[0]);
							std::fprintf(NewPCF, "%c ", vs.group[g].selective_dynamics[i].c_str()[1]);
							std::fprintf(NewPCF, "%c", vs.group[g].selective_dynamics[i].c_str()[2]);
							std::fprintf(NewPCF, "\n");
						}
					}
				}
			}
		}

		if (sized[0] / 2 != sized[0] / 2.0)
		{
			xexe[0] = 1;
		}

		if (sized[1] / 2 != sized[1] / 2.0)
		{
			xexe[1] = 1;
		}

		if (sized[2] / 2 != sized[2] / 2.0)
		{
			xexe[2] = 1;
		}


		std::fclose(NewPCF);

		delete(s);

		return;



	//}
	//else if (Rod_like == -1)
	//{
	//	char S[50];
	//	std::strcat(NewPC, "(Rod_like)");
	//	if (S1v >= S2v || S1v >= S3v)
	//	{

	//	}
	//	else
	//	{
	//		itoa(S1v, S, 10);
	//		std::strcat(NewPC, "(100");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}

	//	if (S2v >= 2 * S1v || S3v <= S2v)
	//	{

	//	}
	//	else
	//	{
	//		itoa(S2v, S, 10);
	//		std::strcat(NewPC, "(110");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}

	//	itoa(S3v, S, 10);
	//	std::strcat(NewPC, "(111");
	//	std::strcat(NewPC, S);
	//	std::strcat(NewPC, ")");
	//	FILE *NewPCF = fopen(NewPC, "w");
	//	FILE *uc_file = fopen(inpf, "r");


	//	char* s;
	//	char* token;
	//	s = (char*)malloc(sizeof(char) * SBYTES);



	//	/// line 1

	//	std::fgets(s, SBYTES, uc_file);
	//	std::fprintf(NewPCF, s);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fprintf(NewPCF, s);

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}


	//	/// line 2
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}
	//	std::fprintf(NewPCF, jgn::ftoa(actor));
	//	std::fprintf(NewPCF, "\n");



	//	/// line 3
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[0][0] * sized[0] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[0][1] * sized[0] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[0][2] * sized[0] / actor);


	//	/// line 4
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[1][0] * sized[1] / actor);
	//	std::fprintf(NewPCF, " ");


	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[1][1] * sized[1] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[1][2] * sized[1] / actor);

	//	/// line 5
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[2][0] * sized[2] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[2][1] * sized[2] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[2][2] * sized[2]) / actor;

	//	/// line 6
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, atoms);
	//	std::fprintf(NewPCF, "\n");




	//	for (ole1 = 0; ole1 < a; ole1++)
	//	{
	//		new_num_atoms[ole1] = 0;
	//		atomscc = 0;


	//	}


	//	for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//	{
	//		if (vacuum ^ ((S1i[0] * abs(crystal[2 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[4 + 5 * ole]) <= S1v) && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[0] * abs(crystal[4 + 5 * ole]) <= S2v && Right_Hexagonal*(S3i[0] * abs(crystal[2 + 5 * ole]) + S3i[1] * abs(crystal[3 + 5 * ole]) + S3i[2] * abs(crystal[4 + 5 * ole])) <= S3v))
	//		{
	//			for (i = 0; i < CustomSurfacesCount; i++)
	//			{
	//				if (CustomSurfaces[i][0] * (crystal[2 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[3 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[4 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//				{

	//				}
	//				else
	//				{
	//					i = 1000;
	//				}

	//			}

	//			if (i == CustomSurfacesCount)
	//			{
	//				for (ole1 = 0; ole1 < a; ole1++)
	//				{
	//					if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
	//					{
	//						new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
	//						atomscc++;


	//					}

	//				}
	//			}

	//		}


	//	}

	//	for (ole = 0; ole < a; ole++)
	//	{
	//		std::fprintf(NewPCF, "%d ", new_num_atoms[ole]);

	//	}
	//	std::fprintf(NewPCF, "\n");



	//	std::fclose(uc_file);


	//	if (selective_dynamics_bool)
	//		std::fprintf(NewPCF, "Selective Dynamics\n");

	//	std::fprintf(NewPCF, "Cartesian\n");








	//	if (sized[0] / 2 != sized[0] / 2.0)
	//	{
	//		xexe[0] = 1;
	//	}

	//	if (sized[1] / 2 != sized[1] / 2.0)
	//	{
	//		xexe[1] = 1;
	//	}

	//	if (sized[2] / 2 != sized[2] / 2.0)
	//	{
	//		xexe[2] = 1;
	//	}


	//	for (ole5 = 0; ole5 < a; ole5++) {
	//		for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2 + xexe[2]; ole4++) {
	//			for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2 + xexe[1]; ole2++) {
	//				for (ole = -sized[0] / 2; ole < sized[0] / 2 + xexe[0]; ole++) {
	//					for (ole3 = 0; ole3 < t; ole3++) {
	//						if (vacuum ^ ((S1i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * Right_Hexagonal*Rod_like* abs(crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && Rod_like*(S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[0] * Right_Hexagonal* abs(crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))])) <= S2v && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && Rod_like*(S2i[0] * Right_Hexagonal* abs(crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))])) <= S2v && Right_Hexagonal*(S3i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[2] * abs(crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))])) <= S3v))

	//						{
	//							for (i = 0; i < CustomSurfacesCount; i++)
	//							{
	//								if (CustomSurfaces[i][0] * (crystal[2 + 0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[2 + 1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//								{

	//								}
	//								else
	//								{
	//									i = 1000;
	//								}

	//							}

	//							if (i == CustomSurfacesCount)
	//							{
	//								if (crystal[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
	//								{
	//									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
	//									for (ole1 = 0; ole1 < 3; ole1++)
	//									{
	//										std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);

	//										//std::fprintf(NewPCF, "%.*f ", -min_xyz[ole1] + crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
	//									}
	//									if (selective_dynamics_bool)
	//									{
	//										for (ole1 = 0; ole1 < 3; ole1++)
	//										{
	//											std::fprintf(NewPCF, "%c ", selective_dynamics[ole1 + 3 * (ole3)]);
	//										}
	//									}
	//									std::fprintf(NewPCF, "\n");
	//								}
	//							}

	//						}

	//					}
	//				}
	//			}
	//			full = 1;
	//		}

	//	}

	//	std::fclose(NewPCF);

	//	delete(s);

	//}
	//else if (Right_Hexagonal == -1)
	//{
	//	char S[50];
	//	std::strcat(NewPC, "(Hexagonal)");
	//	itoa(Right_Hexagonal_height, S, 10);
	//	std::strcat(NewPC, "(0001");
	//	std::strcat(NewPC, S);
	//	std::strcat(NewPC, ")");
	//	if (float(S1v) / float(S2v) > 1.14814814815)
	//	{

	//	}
	//	else
	//	{
	//		itoa(S1v, S, 10);
	//		std::strcat(NewPC, "(10-10");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}
	//	if (float(S1v) / float(S2v) < 0.86842105263)
	//	{

	//	}
	//	else
	//	{
	//		itoa(S2v, S, 10);
	//		std::strcat(NewPC, "(11-20");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}

	//	FILE *NewPCF = fopen(NewPC, "w");
	//	FILE *uc_file = fopen(inpf, "r");


	//	char* s;
	//	char* token;
	//	s = (char*)malloc(sizeof(char) * SBYTES);



	//	/// line 1

	//	std::fgets(s, SBYTES, uc_file);
	//	std::fprintf(NewPCF, s);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fprintf(NewPCF, s);

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}


	//	/// line 2
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, jgn::ftoa(actor));
	//	std::fprintf(NewPCF, "\n");



	//	/// line 3
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[0][0] * sized[0] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[0][1] * sized[0] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[0][2] * sized[0] / actor);


	//	/// line 4
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[1][0] * sized[1] / actor);
	//	std::fprintf(NewPCF, " ");


	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[1][1] * sized[1] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[1][2] * sized[1] / actor);

	//	/// line 5
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[2][0] * sized[2] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[2][1] * sized[2] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[2][2] * sized[2]) / actor;

	//	/// line 6
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, atoms);
	//	std::fprintf(NewPCF, "\n");




	//	for (ole1 = 0; ole1 < a; ole1++)
	//	{
	//		new_num_atoms[ole1] = 0;
	//		atomscc = 0;


	//	}


	//	for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//	{
	//		if (true)
	//		{
	//			if (vacuum ^ (abs(crystal[4 + 5 * ole]) < Right_Hexagonal_height && (S1i[0] * abs(crystal[2 + 5 * ole]) <= S2v * 0.866025404) && S2i[0] * abs(crystal[2 + 5 * ole]) / 1.73205 + S2i[0] * figure_1 * abs(crystal[2 + 1 + 5 * ole]) <= S2v &&
	//				(S1i[0] * figure_1*abs(crystal[2 + 1 + 5 * ole]) <= S1v * 0.866025404) && S2i[0] * figure_1 * abs(crystal[2 + 0 + 5 * ole]) + S1i[0] * figure_1 * abs(crystal[2 + 1 + 5 * ole]) / 1.73205 <= S1v))
	//			{
	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[3 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[4 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{
	//					for (ole1 = 0; ole1 < a; ole1++)
	//					{
	//						if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
	//						{
	//							new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
	//							atomscc++;


	//						}

	//					}
	//				}

	//			}
	//		}

	//	}

	//	for (ole = 0; ole < a; ole++)
	//	{
	//		std::fprintf(NewPCF, "%d ", new_num_atoms[ole]);

	//	}
	//	std::fprintf(NewPCF, "\n");



	//	std::fclose(uc_file);


	//	if (selective_dynamics_bool)
	//		std::fprintf(NewPCF, "Selective Dynamics\n");

	//	std::fprintf(NewPCF, "Cartesian\n");



	//	for (ole5 = 0; ole5 < a; ole5++) {

	//		for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//		{
	//			if (1)
	//			{
	//				if (vacuum ^ ((abs(crystal[4 + 5 * ole]) < Right_Hexagonal_height) && (S1i[0] * abs(crystal[2 + 5 * ole]) <= S2v * 0.866025404) && S2i[0] * abs(crystal[2 + 5 * ole]) / 1.73205 + S2i[0] * figure_1 * abs(crystal[2 + 1 + 5 * ole]) <= S2v &&
	//					(S1i[0] * figure_1*abs(crystal[2 + 1 + 5 * ole]) <= S1v * 0.866025404) && S2i[0] * figure_1 * abs(crystal[2 + 0 + 5 * ole]) + S1i[0] * figure_1 * abs(crystal[2 + 1 + 5 * ole]) / 1.73205 <= S1v))
	//				{

	//					for (i = 0; i < CustomSurfacesCount; i++)
	//					{
	//						if (CustomSurfaces[i][0] * (crystal[2 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[3 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[4 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//						{

	//						}
	//						else
	//						{
	//							i = 1000;
	//						}

	//					}

	//					if (i == CustomSurfacesCount)
	//					{


	//						if (crystal[0 + 5 * ole] == atomic_number[ole5])
	//						{
	//							ole1 = 0;
	//							std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * ole]);

	//							ole1 = 1;
	//							std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * ole]);

	//							ole1 = 2;
	//							std::fprintf(NewPCF, "%.*f ", printformat, crystal[ole1 + 2 + 5 * ole]);

	//							//ole1 = 0; 
	//							//std::fprintf(NewPCF, "%.*f ", printformat, -min_xyz[ole1] + crystal[ole1 + 2 + 5 * ole]);

	//							//ole1 = 1;
	//							//std::fprintf(NewPCF, "%.*f ", printformat, -min_xyz[ole1] + crystal[ole1 + 2 + 5 * ole]);

	//							//ole1 = 2;
	//							//std::fprintf(NewPCF, "%.*f ", printformat, -min_xyz[ole1] + crystal[ole1 + 2 + 5 * ole]);

	//							if (selective_dynamics_bool)
	//							{
	//								for (ole1 = 0; ole1 < 3; ole1++)
	//								{
	//									std::fprintf(NewPCF, "%c ", selective_dynamics[ole1 + 3 * (ole%t)]);
	//								}
	//							}

	//							std::fprintf(NewPCF, "\n");

	//						}
	//					}




	//				}
	//			}

	//		}
	//	}

	//	std::fclose(NewPCF);

	//	delete(s);
	//	return;

	//}
	//else
	//{
	//	if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
	//	{
	//		char S[50];
	//		itoa(rad, S, 10);
	//		std::strcat(NewPC, "(sphere");
	//		std::strcat(NewPC, S);
	//		std::strcat(NewPC, ")");
	//	}
	//	else
	//	{
	//		char S[50];
	//		if (Scase == 1 || Scase == 2 || Scase == 3 || Scase == 4)
	//		{
	//			itoa(S1v, S, 10);
	//			std::strcat(NewPC, "(100");
	//			std::strcat(NewPC, S);
	//			std::strcat(NewPC, ")");
	//		}
	//		if (Scase == 1 || Scase == 2 || Scase == 5 || Scase == 6)
	//		{
	//			itoa(S2v, S, 10);
	//			std::strcat(NewPC, "(110");
	//			std::strcat(NewPC, S);
	//			std::strcat(NewPC, ")");
	//		}
	//		if (Scase == 1 || Scase == 3 || Scase == 5 || Scase == 7)
	//		{
	//			itoa(S3v, S, 10);
	//			std::strcat(NewPC, "(111");
	//			std::strcat(NewPC, S);
	//			std::strcat(NewPC, ")");
	//		}
	//	}
	//	FILE *NewPCF = fopen(NewPC, "w");
	//	FILE *uc_file = fopen(inpf, "r");

	//	char* s;
	//	char* token;
	//	s = (char*)malloc(sizeof(char) * SBYTES);



	//	/// line 1

	//	std::fgets(s, SBYTES, uc_file);
	//	std::fprintf(NewPCF, s);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fprintf(NewPCF, s);

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}


	//	/// line 2
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, jgn::ftoa(actor));
	//	std::fprintf(NewPCF, "\n");



	//	/// line 3
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[0][0] * sized[0] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[0][1] * sized[0] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[0][2] * sized[0] / actor);


	//	/// line 4
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[1][0] * sized[1] / actor);
	//	std::fprintf(NewPCF, " ");


	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[1][1] * sized[1] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[1][2] * sized[1] / actor);

	//	/// line 5
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{
	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[2][0] * sized[2] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f", printformat, ijk[2][1] * sized[2] / actor);
	//	std::fprintf(NewPCF, " ");
	//	token = strtok(NULL, "\t ");

	//	std::fprintf(NewPCF, "%.*f\n", printformat, ijk[2][2] * sized[2]) / actor;

	//	/// line 6
	//	std::fgets(s, SBYTES, uc_file);
	//	token = strtok(s, "\t ");
	//	while (token[0] == '\n')
	//	{

	//		std::fgets(s, SBYTES, uc_file);
	//		token = strtok(s, "\t ");

	//	}

	//	std::fprintf(NewPCF, atoms);
	//	std::fprintf(NewPCF, "\n");




	//	for (ole1 = 0; ole1 < a; ole1++)
	//	{
	//		new_num_atoms[ole1] = 0;
	//		atomscc = 0;


	//	}

	//	if (want_cyrcle[0] == 'y')
	//	{

	//		for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//		{

	//			if (vacuum ^ (sqrt(crystal[2 + 5 * ole] * crystal[2 + 5 * ole] + crystal[3 + 5 * ole] * crystal[3 + 5 * ole] + crystal[4 + 5 * ole] * crystal[4 + 5 * ole]) <= rad))
	//			{
	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[3 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[4 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{
	//					for (ole1 = 0; ole1 < a; ole1++)
	//					{
	//						if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
	//						{
	//							new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
	//							atomscc++;

	//						}

	//					}
	//				}

	//			}

	//		}

	//		for (ole = 0; ole < a; ole++)
	//		{
	//			std::fprintf(NewPCF, "%d ", new_num_atoms[ole]);

	//		}
	//		std::fprintf(NewPCF, "\n");

	//	}
	//	else
	//	{


	//		for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
	//		{

	//			if (vacuum ^ ((S1i[0] * abs(crystal[2 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[3 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[4 + 5 * ole]) <= S1v) && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[0] * abs(crystal[3 + 5 * ole]) <= S2v && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[0] * abs(crystal[4 + 5 * ole]) <= S2v && S2i[0] * abs(crystal[3 + 5 * ole]) + S2i[0] * abs(crystal[4 + 5 * ole]) <= S2v && S3i[0] * abs(crystal[2 + 5 * ole]) + S3i[1] * abs(crystal[3 + 5 * ole]) + S3i[2] * abs(crystal[4 + 5 * ole]) <= S3v))
	//			{
	//				for (i = 0; i < CustomSurfacesCount; i++)
	//				{
	//					if (CustomSurfaces[i][0] * (crystal[2 + 5 * ole] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[3 + 5 * ole] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[4 + 5 * ole] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//					{

	//					}
	//					else
	//					{
	//						i = 1000;
	//					}

	//				}

	//				if (i == CustomSurfacesCount)
	//				{
	//					for (ole1 = 0; ole1 < a; ole1++)
	//					{
	//						if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
	//						{
	//							new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
	//							atomscc++;


	//						}

	//					}
	//				}

	//			}

	//		}

	//		for (ole = 0; ole < a; ole++)
	//		{
	//			std::fprintf(NewPCF, "%d ", new_num_atoms[ole]);

	//		}
	//		std::fprintf(NewPCF, "\n");


	//	}
	//	std::fclose(uc_file);

	//	if (selective_dynamics_bool)
	//		std::fprintf(NewPCF, "Selective Dynamics\n");

	//	std::fprintf(NewPCF, "Cartesian\n");




	//	if (want_cyrcle[0] == 'y') {



	//		int ajklsdfl = t * (sized[0])*(sized[1])*(sized[2]);
	//		for (ole2 = 0; ole2 < a; ole2++)
	//		{
	//			for (ole3 = 0; ole3 < ajklsdfl; ole3++)
	//			{
	//				if (vacuum ^ (rad >= sqrt(crystal[0 + 2 + 5 * (ole3)] * crystal[0 + 2 + 5 * (ole3)] + crystal[1 + 2 + 5 * (ole3)] * crystal[1 + 2 + 5 * (ole3)] + crystal[2 + 2 + 5 * (ole3)] * crystal[2 + 2 + 5 * (ole3)])))
	//				{
	//					for (i = 0; i < CustomSurfacesCount; i++)
	//					{
	//						if (CustomSurfaces[i][0] * (crystal[2 + 5 * ole3] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[3 + 5 * ole3] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[4 + 5 * ole3] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//						{

	//						}
	//						else
	//						{
	//							i = 1000;
	//						}

	//					}

	//					if (i == CustomSurfacesCount)
	//					{
	//						if (atomic_number[ole2] == (int)crystal[0 + 5 * ole3])
	//						{
	//							for (ole1 = 0; ole1 < 3; ole1++)
	//							{
	//								std::fprintf(NewPCF, "%.*f ", printformat, (crystal[ole1 + 2 + 5 * ole3]));

	//								//std::fprintf(NewPCF, "%.*f ", (-min_xyz[ole1] + crystal[ole1 + 2 + 5 * ole3]));
	//							}
	//							if (selective_dynamics_bool)
	//							{
	//								for (ole1 = 0; ole1 < 3; ole1++)
	//								{
	//									std::fprintf(NewPCF, "%c ", selective_dynamics[ole1 + 3 * (ole3%t)]);
	//								}
	//							}
	//							std::fprintf(NewPCF, "\n");
	//						}
	//					}
	//				}
	//			}
	//		}


	//	}
	//	else {

	//		int ajklsdfl = t * (sized[0])*(sized[1])*(sized[2]);
	//		for (ole2 = 0; ole2 < a; ole2++)
	//		{
	//			for (ole3 = 0; ole3 < ajklsdfl; ole3++)
	//			{
	//				if (vacuum ^ ((S1i[0] * figure_1*abs(crystal[2 + 5 * ole3]) <= S1v) && (S1i[0] * Right_Hexagonal*Rod_like* abs(crystal[4 + 5 * ole3]) <= S1v) && (S1i[0] * figure_1*abs(crystal[3 + 5 * ole3]) <= S1v) && Rod_like*(S2i[0] * abs(crystal[2 + 5 * ole3]) + S2i[0] * Right_Hexagonal* abs(crystal[4 + 5 * ole3])) <= S2v && S2i[0] * figure_1* abs(crystal[2 + 5 * ole3]) + S2i[0] * figure_1* abs(crystal[3 + 5 * ole3]) <= S2v && Rod_like*(S2i[0] * Right_Hexagonal* abs(crystal[4 + 5 * ole3]) + S2i[0] * abs(crystal[3 + 5 * ole3])) <= S2v && Right_Hexagonal*(S3i[0] * abs(crystal[2 + 5 * ole3]) + S3i[1] * abs(crystal[4 + 5 * ole3]) + S3i[2] * abs(crystal[3 + 5 * ole3])) <= S3v))
	//				{
	//					for (i = 0; i < CustomSurfacesCount; i++)
	//					{
	//						if (CustomSurfaces[i][0] * (crystal[2 + 5 * ole3] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (crystal[3 + 5 * ole3] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (crystal[4 + 5 * ole3] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
	//						{

	//						}
	//						else
	//						{
	//							i = 1000;
	//						}

	//					}

	//					if (i == CustomSurfacesCount)
	//					{
	//						if (atomic_number[ole2] == (int)crystal[0 + 5 * ole3])
	//						{
	//							for (ole1 = 0; ole1 < 3; ole1++)
	//							{
	//								std::fprintf(NewPCF, "%.*f ", printformat, (crystal[ole1 + 2 + 5 * ole3]));

	//								//std::fprintf(NewPCF, "%.*f ", (-min_xyz[ole1] + crystal[ole1 + 2 + 5 * ole3]));
	//							}
	//							if (selective_dynamics_bool)
	//							{
	//								for (ole1 = 0; ole1 < 3; ole1++)
	//								{
	//									std::fprintf(NewPCF, "%c ", selective_dynamics[ole1 + 3 * (ole3%t)]);
	//								}
	//							}
	//							std::fprintf(NewPCF, "\n");
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//	free(s);


	//	std::fclose(NewPCF);
	//	return;
	//}
	return;
}