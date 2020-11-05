#pragma once


#include "stdafx.h"
#include "JGN_DropFile.h"
#include "VSystem.h"
#include "Bonds.h"


void JGN_DropFile(const char* inpf)
{
	delete s;
	s = new char[SBYTES];
	//print the droped path
	found = std::string(inpf).find(".lmp");
	if (found != std::string::npos)
	{
		ftype = 'l';
	}
	else
	{
		ftype = 'p';
	}

	//open the droped path
	uc_file = fopen(inpf, "r");



	//initialize facetes
	S1i[0] = atoi(S1) / 100;
	S1i[1] = fmod(atoi(S1) / 10, 10);
	S1i[2] = fmod(atoi(S1), 10);

	S2i[0] = atoi(S2) / 100;
	S2i[1] = fmod(atoi(S2) / 10, 10);
	S2i[2] = fmod(atoi(S2), 10);

	S3i[0] = atoi(S3) / 100;
	S3i[1] = fmod(atoi(S3) / 10, 10);
	S3i[2] = fmod(atoi(S3), 10);

	//shorting bullshit
	if (S1[3] != '\0')
	{
		//__asm {
		//	mov esi, [S1]
		//	mov[esi + 3], 0
		//}
		S1[3] = '\0';
	}
	if (S2[3] != '\0') {
		//__asm {
		//	mov esi, [S2]
		//	mov[esi + 3], 0
		//}
		S2[3] = '\0';

	}if (S3[3] != '\0')
	{
		//__asm {
		//	mov esi, [S3]
		//	mov[esi + 3], 0
		//}
		S3[3] = '\0';

	}

	//define Svmax for a proper display (zoom)
	//__asm {
	//	mov esi, [S1v]
	//	mov[Svmax], esi
	//}
	Svmax = S1v;
	//Svmax = S1v;
	if (S2v > Svmax)
	{
		/*__asm {
			mov esi, [S2v]
			mov[Svmax], esi
		}*/
		Svmax = S2v;
	}
	if (S3v > Svmax)
	{
		/*__asm {
			mov esi, [S3v]
			mov[Svmax], esi
		}*/
		Svmax = S3v;
	}
	/*__asm {
		mov esi, [Svmax]
		mov[Svmax_buckup], esi
	}*/
	Svmax_buckup = Svmax;
	if (ftype == 'p')
	{

		///line 1
		std::fgets(s, SBYTES, uc_file);
		while (strtok(s, "\t ")[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
		}

		//tsekarw posa einai ta eidi twn atomwn xrhsimopoiwdas ta kena gia na xrhsimopoihsw thn malloc
		//h malloc me voleyei giati dn kserw posa eidi atomwn exw eksarxhs



		///grammh 2
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}

		actor = std::atof(token);//pairnei thn timh sthn grammh 2



							///grammh 3
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}


		line++;		//synistwsa i


		for (p = 0; p < 3; p++)
		{
			ijk[0][p] = std::atof(token);
			ijk[0][p] = ijk[0][p] * actor;//pollaplasiazw me ton pollaplasiastiko paragoda
			token = strtok(NULL, "\t ");
		}


		///grammh 4
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;	//synistwsa j

		for (p = 0; p < 3; p++)
		{
			ijk[1][p] = std::atof(token);
			ijk[1][p] = ijk[1][p] * actor;//pollaplasiazw me ton pollaplasiastiko paragoda
			token = strtok(NULL, "\t ");
		}



		///grammh 5
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;		//synistwsa k


		for (p = 0; p < 3; p++)
		{
			ijk[2][p] = std::atof(token);
			ijk[2][p] = ijk[2][p] * actor;//pollaplasiazw me ton pollaplasiastiko paragoda
			token = strtok(NULL, "\t ");
		}





		
		///grammh 6			
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		shelp = new char[SBYTES];

		for (int i = 0; i < SBYTES; i++)
		{
			shelp[i] = s[i];
		}

		line++;		//vlepei poia einai ta stoixeia kai ta apo8ikeyei				


		a = 0;



		//a = number of atom types
		while (token != NULL) {
			if ((token[0] > 64 && token[0] < 91))
			{


				a++;
			}
			token = strtok(NULL, "\t ");


		}
		



		new_num_atoms = (int*)realloc(NULL, a * sizeof(int));
		for (int i = 0; i < a; i++)
		{
			new_num_atoms[i] = 0;
		}
		atomic_number = (int*)realloc(NULL, a * sizeof(int));
		for (int i = 0; i < a; i++)
		{
			atomic_number[i] = 0;
		}
		an_and_aw = (float*)realloc(NULL, sizeof(float)*a * 2);

		atoms = (char*)realloc(NULL, sizeof(char)*(a * 3 + 1)); atoms[0] = '\0';
		atomshelp = (char*)realloc(NULL, sizeof(char)*(a * 3 + 1)); atomshelp[0] = '\0';
		//voi8itikos
		//etsi twra borw na dilwsw tous pinakes me ta dedomena m alliws meta dn 8a borousa mesa stis if
		//ta declares mesa sta if exoune range mono mesa sto idio to if
		//3 xaraktires to poly 2 grammata gia to ka8e stoixeio + to \0
		ea = (int*)realloc(NULL, sizeof(int)*a); 		//ea: posa atoma ana eidos

		delete s;

		s = shelp;
		// remove '\0' that strtok added (if he did (a>1) )
		if (a > 1)
		{
			ole1 = 0;
			ole = 0;
			while (ole == 0)
			{
				if (s[ole1] == '\0')
				{
					s[ole1] = ' ';
					ole = 1;
				}
				ole1++;
			}
		}

		ole = 0;
		token = strtok(s, " \t");

		//save atoms in an char array
		while (token != NULL) {
			if ((token[0] > 64 && token[0] < 91))
			{  //twra kserw poia atoma symmetexoun 8a m xrhsimeysei meta poy 8a parw ta directs
				strcat(atoms, token);

				strcat(atoms, " ");
				for (ole1 = 0; ole1 < 3; ole1++) {
					if (atoms[ole1 + 3 * ole] == '\n') {
						atoms[ole1 + 3 * ole] = '\0';//giati sto teleytaio pou 8a dei sto line to atoms[ole][ole1] 8a parei thn timh \n kai oxi thn \0 poy 8elw
						ole1 = 100;
					}
				}

				ole++;
			}
			token = strtok(NULL, " \t");

		}
		strcat(atoms, "\0");



		//extra buffer for atoms char array
		for (int i = 0; i < 3 * a + 1; i++)
		{
			atomshelp[i] = atoms[i];
		}
		//atomshelp[3 * a - 1] = ' ';




		///grammh7		
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;	//posa atoma tou ka8e stoixeiou ana cell?			

		ole = 0;
		t = 0;
		while (token != NULL) {
			ea[ole] = atoi(token);
			token = strtok(NULL, "\t ");
			t = t + ea[ole];//tosa atoma ana unit cell
			ole++;
			if (ole == a) break;
		}


		//debuging print
		//#define MY_DEBUG_1
#ifdef MY_DEBUG_1
		std::cout << actor << endl;
		std::cout << ijk[0][0] << '\t' << ijk[0][1] << '\t' << ijk[0][2] << endl;
		std::cout << ijk[1][0] << '\t' << ijk[1][1] << '\t' << ijk[1][2] << endl;
		std::cout << ijk[2][0] << '\t' << ijk[2][1] << '\t' << ijk[2][2] << endl;
		for (int i = 0; i < a; i++)
		{
			std::cout << ea[i] << '\t';
		}
		std::cout << endl;
		std::cout << "yeah 1" << endl;
#endif


		///gramh 8			

		// "direct" "cartasian" or "selective dynamics" ?
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}

		//check if we have "selective dynamics"
		selective_dynamics_bool = false;
		if (token[0] == 's' || token[0] == 'S')
		{
			selective_dynamics_bool = true;
			// "direct" or "cartasian" ?
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");
			while (token[0] == '\n')
			{
				std::fgets(s, SBYTES, uc_file);
				token = strtok(s, "\t ");

			}
		}
		line++;



		my_direct = (float*)realloc(NULL, sizeof(float)*(t * 5));//t einai ola ta atoma tou unit cell.. 3 gia h,c,l kai dio gia atomiko ari8mo kai varos
		periodic_table = fopen("periodic_table.jgn", "r");
		aweights = (float*)realloc(NULL, sizeof(float)*a);
		aatoms = (int*)realloc(NULL, sizeof(int)*a);
		anumber = (int*)realloc(NULL, sizeof(int)*a);

		for (ole = 0; ole < a; ole++)
		{
			aweights[ole] = -1.;
			anumber[ole] = -1;
		}



		///gammh 9 kai meta	
		if (token[0] == 'd' || token[0] == 'D')
		{
			inptype = 'd';
		}
		else if (token[0] == 'c' || token[0] == 'C')
		{
			inptype = 'c';
		}

		ole2 = 0;
		ole3 = 0;
		token3 = strtok(atoms, " ");

		alloena = 0;
		ka8isterimenoflag = 0;
		selective_dynamics = (char*)realloc(NULL, sizeof(char)*(t * 3));
		

		for (ole = 0; ole < t; ole++) {


			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");
			while (token[0] == '\n')
			{
				std::fgets(s, SBYTES, uc_file);
				token = strtok(s, "\t ");

			}

			ole2++;


			for (ole1 = 0; ole1 < 3; ole1++) {

				my_direct[ole1 + 2 + 5 * ole] = std::atof(token);


				token = strtok(NULL, "\t ");

			}

			if (selective_dynamics_bool)
			{
				for (ole1 = 0; ole1 < 3; ole1++)
				{
					selective_dynamics[ole1 + 3 * ole] = token[0];

					token = strtok(NULL, "\t ");
				}
			}
			else
			{
				for (ole1 = 0; ole1 < 3; ole1++)
					selective_dynamics[ole1 + 3 * ole] = 'T';
			}


			ole1 = 0;

			while (ole1 == 0) {

				std::fgets(s1, 50, periodic_table);
				token1 = strtok(s1, " ");


				if (strcmp(token3, token1) == 0) {

					token1 = strtok(NULL, " ");
					my_direct[0 + 5 * ole] = std::atof(token1);
					if (alloena == 0)
					{
						an_and_aw[alloena * 2] = std::atof(token1);
						//std::cout << 1 << "\n";
					}
					else if (an_and_aw[alloena * 2 - 2] != std::atof(token1))
					{
						//std::cout << an_and_aw[alloena * 2 - 2] << " " << std::atof(token1); getchar();
						an_and_aw[alloena * 2] = std::atof(token1);
						ka8isterimenoflag = 1;

						//std::cout << 2 << "\n";

					}


					token1 = strtok(NULL, " ");
					my_direct[1 + 5 * ole] = std::atof(token1);
					for (int ii = 0; ii < a; ii++)
					{
						if (aweights[ii] == my_direct[1 + 5 * ole])
						{
							ii = 9000;
						}
						else if (aweights[ii] == -1.)
						{
							aweights[ii] = my_direct[1 + 5 * ole];
							anumber[ii] = my_direct[0 + 5 * ole];
							ii = 9000;

						}
					}
					if (alloena == 0)
					{
						an_and_aw[alloena * 2 + 1] = std::atof(token1);
						alloena++;
						//std::cout << 3 << "\n";

					}

					else if (ka8isterimenoflag == 1)
					{
						an_and_aw[alloena * 2 + 1] = std::atof(token1);
						alloena++;
						ka8isterimenoflag = 0;
						//std::cout << 4 << "\n";
					}


					ole1 = 1;

				}

			}

			if (ole2 == ea[ole3])
			{
				token3 = strtok(token3 + strlen(token3) + 1, " \n");
				ole3++;
				ole2 = 0;

			}

			rewind(periodic_table);
		}

		atoms = atomshelp;



		fclose(uc_file);


		//#define MY_DEBUG_2
#ifdef MY_DEBUG_2
		for (ole = 0; ole < t; ole++)
		{
			std::cout << selective_dynamics[0 + 3 * ole] << ' ' << selective_dynamics[1 + 3 * ole] << " " << selective_dynamics[2 + 3 * ole] << endl;
		}
		getchar();
#endif


		if (inptype == 'd')
		{
			uccartesian = (float*)realloc(NULL, sizeof(float)*(3 * t));//ta atoma toy unit cell se kartasiano

			for (int i = 0; i < t; i++)
			{
				uccartesian[i * 3 + 0] = my_direct[2 + i * 5 + 0] * ijk[0][0] + my_direct[2 + i * 5 + 1] * ijk[1][0] + my_direct[2 + i * 5 + 2] * ijk[2][0];
				uccartesian[i * 3 + 1] = my_direct[2 + i * 5 + 0] * ijk[0][1] + my_direct[2 + i * 5 + 1] * ijk[1][1] + my_direct[2 + i * 5 + 2] * ijk[2][1];
				uccartesian[i * 3 + 2] = my_direct[2 + i * 5 + 0] * ijk[0][2] + my_direct[2 + i * 5 + 1] * ijk[1][2] + my_direct[2 + i * 5 + 2] * ijk[2][2];

			}
			//#ifdef DOUBLE_MOD
			//			__asm {
			//				mov esi, [t]
			//				imul esi, 40
			//				mov ebx, 0//ole1
			//				mov ecx, 0//ole*5
			//
			//				/**/jmp loop2_b
			//				/**/loop2_s :
			//				/**/	/**/jmp loop1_b
			//					/**/	/**/loop1_s :
			//				/**/	/**/	/**/mov eax, ecx
			//					/**/	/**/	/**/mov edx, 0
			//					/**/	/**/	/**/mov edi, 5
			//					/**/	/**/	/**/div edi
			//					/**/	/**/	/**/mov edi, 3
			//					/**/	/**/	/**/mul edi//eax=ele*3+ole1
			//					/**/	/**/	/**/add eax, ebx
			//					/**/	/**/	/**/
			//					/**/	/**/	/**/movsd xmm0, [ijk + ebx]
			//					/**/	/**/	/**/mov edx, [my_direct]
			//					/**/	/**/	/**/mulsd xmm0, [edx + 16 + ecx]
			//					/**/	/**/	/**/movsd xmm1, [ijk + 24 + ebx]
			//					/**/	/**/	/**/mulsd xmm1, [edx + 24 + ecx]
			//					/**/	/**/	/**/addsd xmm0, xmm1
			//					/**/	/**/	/**/movsd xmm1, [ijk + 48 + ebx]
			//					/**/	/**/	/**/mulsd xmm1, [edx + 32 + ecx]
			//					/**/	/**/	/**/addsd xmm0, xmm1
			//					/**/	/**/	/**/mov edx, [uccartesian]
			//					/**/	/**/	/**/movsd[edx + eax], xmm0
			//					/**/	/**/	/**/
			//					/**/	/**/	/**/add ebx, 8
			//					/**/	/**/
			//					/**/	/**/loop1_b:
			//				/**/	/**/cmp ebx, 24
			//					/**/	/**/jge loop1_out
			//					/**/	/**/jmp loop1_s
			//					/**/	/**/loop1_out :
			//				/**/
			//				/**/	/**/mov ebx, 0
			//					/**/	/**/add ecx, 40
			//					/**/
			//					/**/loop2_b :
			//					/**/cmp ecx, esi
			//					/**/jge loop2_out
			//					/**/jmp loop2_s
			//					/**/loop2_out :
			//
			//
			//			}
			//#else
			//			__asm {
			//				mov esi, [t]
			//				imul esi, 20
			//				mov ebx, 0//ole1
			//				mov ecx, 0//ole*5
			//
			//				/**/jmp loop2_b
			//				/**/loop2_s :
			//				/**/	/**/jmp loop1_b
			//					/**/	/**/loop1_s :
			//				/**/	/**/	/**/mov eax, ecx
			//					/**/	/**/	/**/mov edx, 0
			//					/**/	/**/	/**/mov edi, 5
			//					/**/	/**/	/**/div edi
			//					/**/	/**/	/**/mov edi, 3
			//					/**/	/**/	/**/mul edi//eax=ele*3+ole1
			//					/**/	/**/	/**/add eax, ebx
			//					/**/	/**/	/**/
			//					/**/	/**/	/**/movss xmm0, [ijk + ebx]
			//					/**/	/**/	/**/mov edx, [my_direct]
			//					/**/	/**/	/**/mulss xmm0, [edx + 8 + ecx]
			//					/**/	/**/	/**/movss xmm1, [ijk + 12 + ebx]
			//					/**/	/**/	/**/mulss xmm1, [edx + 12 + ecx]
			//					/**/	/**/	/**/addss xmm0, xmm1
			//					/**/	/**/	/**/movss xmm1, [ijk + 24 + ebx]
			//					/**/	/**/	/**/mulss xmm1, [edx + 16 + ecx]
			//					/**/	/**/	/**/addss xmm0, xmm1
			//					/**/	/**/	/**/mov edx, [uccartesian]
			//					/**/	/**/	/**/movss[edx + eax], xmm0
			//					/**/	/**/	/**/
			//					/**/	/**/	/**/add ebx, 4
			//					/**/	/**/
			//					/**/	/**/loop1_b:
			//				/**/	/**/cmp ebx, 12
			//					/**/	/**/jge loop1_out
			//					/**/	/**/jmp loop1_s
			//					/**/	/**/loop1_out :
			//				/**/
			//				/**/	/**/mov ebx, 0
			//					/**/	/**/add ecx, 20
			//					/**/
			//					/**/loop2_b :
			//					/**/cmp ecx, esi
			//					/**/jge loop2_out
			//					/**/jmp loop2_s
			//					/**/loop2_out :
			//
			//
			//			}
			//#endif
		}
		else if (inptype == 'c')
		{
			//free(uccartesian);
			uccartesian = my_direct;
		}


		sized[0] = 1;
		sized[1] = 1;
		sized[2] = 1;
		

		jgn::heapRealloc();






		for (int i = 0; i < 500; i++)
		{
			if (lpszFile[i] == '\0')
			{
				for (int j = i; j > 0; j--)
				{
					if (lpszFile[j] == '\\')
					{
						for (k = j + 1; k < i + 1; k++)
						{
							PCtype[k - j - 1] = lpszFile[k];
						}
						j = 0;
					}
				}
				i = 1000;
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (PCtype[i] == '.')
			{
				PCtype[i] = '_';
			}
		}

		NewPC[0] = '\0';
		strcat(NewPC, PCtype);
		strcat(NewPC, "_NIKOULIS_");


		if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
		{
			char S[50];
			itoa(rad, S, 10);
			strcat(NewPC, "(sphere");
			strcat(NewPC, S);
			strcat(NewPC, ")");
		}
		else
		{
			if (S1v != 0)
			{
				char S[50];
				itoa(S1v, S, 10);
				strcat(NewPC, "(100");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
			if (S2v != 0)
			{
				char S[50];
				itoa(S2v, S, 10);
				strcat(NewPC, "(110");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
			if (S3v != 0)
			{
				char S[50];
				itoa(S3v, S, 10);
				strcat(NewPC, "(111");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
		}
		//NewPCF = fopen(NewPC, "w");




		uc_file = fopen(inpf, "r");


		for (ole4 = -sized[2] / 2.0; ole4 < sized[2] / 2.0; ole4++) {
			for (ole2 = -sized[1] / 2.0; ole2 < sized[1] / 2.0; ole2++) {
				for (ole = -sized[0] / 2.0; ole < sized[0] / 2.0; ole++) {
					for (ole3 = 0; ole3 < t; ole3++) {
						crystal[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						crystal_backup[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

																																												  //selective dynamics
						selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
						selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
						selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

						//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
						crystal[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
						crystal_backup[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

						if (inptype == 'd')
						{
							//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
							for (ole1 = 0; ole1 < 3; ole1++) {
								crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
								crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
								{
									min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
								{
									max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}

							}

						}
						else if (inptype == 'c')
						{
							for (ole1 = 0; ole1 < 3; ole1++) {
								crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
								crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
								{
									min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
								{
									max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}

							}
						}
						rewind(periodic_table);


					}

				}
			}
		}



		ole4 = 0;
		//atom. ar. twn atomwn
		for (ole5 = 0; ole5 < t; ole5++)
		{

			if (ole4 == 0)
			{
				atomic_number[ole4] = crystal[0 + 5 * ole5];
				ole4++;

			}
			else if (atomic_number[ole4] == 0 && atomic_number[ole4 - 1] != crystal[0 + 5 * ole5])
			{

				atomic_number[ole4] = crystal[0 + 5 * ole5];
				ole4++;
			}



		}


		allatoms = sized[0] * sized[1] * sized[2] * t;
		//diavazw to arxeio


		std::cout << "\n";
		std::cout << "The number of atoms are " << allatoms << "\n";




		xyz_range[0] = max_xyz[0] - min_xyz[0];//
		xyz_range[1] = max_xyz[1] - min_xyz[1];//ogos
		xyz_range[2] = max_xyz[2] - min_xyz[2];//

		std::cout << "\n";
		std::cout << "  Minimum: " << min_xyz[0]
			<< "  " << min_xyz[1]
			<< "  " << min_xyz[2] << "\n";
		std::cout << "  Maximum: " << max_xyz[0]
			<< "  " << max_xyz[1]
			<< "  " << max_xyz[2] << "\n";
		std::cout << "  Range:   " << xyz_range[0]
			<< "  " << xyz_range[1]
			<< "  " << xyz_range[2] << "\n";

		if (Svmax == 0)
		{
			Svmax = max_xyz[0];
			if (Svmax < max_xyz[1])
			{
				Svmax = max_xyz[1];
			}

			if (Svmax < max_xyz[2])
			{
				Svmax = max_xyz[2];
			}
			Svmax = Svmax * 2;
		}

		pointsize = truepointsize / (Svmax + 5);






		fclose(uc_file);



		atoms_to_print_c = 0;
		//fclose(NewPCF);

		fclose(periodic_table);




		if (S1[0] == '1')
		{
			if (S2[0] == '1')
			{
				if (S3[0] == '1') {/*100 110 111*/Scase = 1;
				if (2 * S1v <= S2v && S3v >= 3 * S1v && figure_1 != -1)
				{
					Scase = 4;
				}
				else if (S1v >= S2v && float(S3v) >= (float(S2v) * 3) / 2)
				{
					Scase = 6;
				}
				else if (S1v >= S3v && S3v <= S2v)
				{
					Scase = 7;
				}
				else if (S1v >= S2v)
				{///////
					Scase = 5;
				}
				else if ((S2v >= 2 * S1v && figure_1 != -1) || S3v <= S2v)
				{
					Scase = 3;
				}
				else if ((float(S3v) >= (float(S2v) * 3) / 2 && figure_1 != -1) || (figure_1 == -1 && S3v >= 2 * S2v))
				{

					Scase = 2;
				}

				}
				else {/* 100 110*/Scase = 2;/*done*/
				if (S1v >= S2v)
				{
					Scase = 6;
				}
				else if (S2v >= 2 * S1v)
				{
					Scase = 4;
				}


				}
			}
			else {
				if (S3[0] == '1') {/*100 111*/Scase = 3;/*done*/
				if (S1v >= S3v)
				{
					Scase = 7;
				}
				else if (S3v >= 3 * S1v)
				{
					Scase = 4;
				}

				}
				else {/* 100*/Scase = 4;/*done*/


				}
			}
		}
		else {
			if (S2[0] == '1')
			{
				if (S3[0] == '1') {/*110 111*/Scase = 5;/*done*/
				if (float(S3v) >= (float(S2v) * 3) / 2)
				{

					Scase = 6;
				}
				else if (S3v <= S2v) {
					Scase = 7;
				}
				}
				else {/*110*/Scase = 6;/*done*/


				}
			}
			else {
				if (S3[0] == '1') {/*111*/Scase = 7;/*done*/

				}
				else {/**/Scase = 0;


				}
			}
		}






		if (jgn_supercell)
		{
			was_supercell = 1;
			jgn_supercell = 1;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;

			sized[0] = jgn_supercell_xyz[0];
			sized[1] = jgn_supercell_xyz[1];
			sized[2] = jgn_supercell_xyz[2];


			periodic_table = fopen("periodic_table.jgn", "r");

			jgn::heapRealloc();




			for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
				for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
					for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
						for (ole3 = 0; ole3 < t; ole3++) {
							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
																																																										   //crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

																																																										   //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																										   //crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

																																																										   //selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							sim_box_lo[0] = fl_max;
							sim_box_lo[1] = fl_max;
							sim_box_lo[2] = fl_max;

							if (inptype == 'd')
							{

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
																																																																	//crystal_backup[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
								if (crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[0])
								{
									sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
									sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
									sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								else if (crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == sim_box_lo[0])
								{
									if (crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[1])
									{
										sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
										sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
										sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									else if (crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == sim_box_lo[1])
									{
										if (crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[2])
										{
											sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
											sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
											sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}


							}
							else if (inptype == 'c')
							{
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians


																																																																											   //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
							}	if (crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[0])
							{
								sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
								sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
								sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

							}
							else if (crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == sim_box_lo[0])
							{
								if (crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[1])
								{
									sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
									sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
									sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								else if (crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == sim_box_lo[1])
								{
									if (crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[2])
									{
										sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
										sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
										sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}

							}


							rewind(periodic_table);

						}
					}
				}
			}


			fclose(periodic_table);


		}

	}
	else if (ftype == 'l')
	{

		///line 1
		std::fgets(s, SBYTES, uc_file);
		while (strtok(s, "\t ")[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
		}

		//tsekarw posa einai ta eidi twn atomwn xrhsimopoiwdas ta kena gia na xrhsimopoihsw thn malloc
		//h malloc me voleyei giati dn kserw posa eidi atomwn exw eksarxhs



		///grammh 2 read t
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		t = atoi(token);
		actor = 1.0;


		///grammh 3
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}


		a = atoi(token);

		float xlo, xhi, ylo, yhi, zlo, zhi;
		///grammh 4 xlo xhi
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;
		xlo = std::atof(token);
		token = strtok(NULL, "\t ");
		xhi = std::atof(token);


		ijk[0][0] = xhi - xlo;
		ijk[0][1] = 0;
		ijk[0][2] = 0;


		///grammh 5 yhi ylo
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;

		ylo = std::atof(token);
		token = strtok(NULL, "\t ");
		yhi = std::atof(token);

		ijk[1][0] = 0;
		ijk[1][1] = yhi - ylo;
		ijk[1][2] = 0;


		///grammh 6 zlo zhi	
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;

		zlo = std::atof(token);
		token = strtok(NULL, "\t ");
		zhi = std::atof(token);


		ijk[2][0] = 0;
		ijk[2][1] = 0;
		ijk[2][2] = zhi - zlo;


		new_num_atoms = (int*)realloc(NULL, a * sizeof(int));
		for (int i = 0; i < a; i++)
		{
			new_num_atoms[i] = 0;
		}
		atomic_number = (int*)realloc(NULL, a * sizeof(int));
		for (int i = 0; i < a; i++)
		{
			atomic_number[i] = 0;
		}
		an_and_aw = (float*)realloc(NULL, sizeof(float)*a * 2);

		atoms = (char*)realloc(NULL, sizeof(char)*a * 3); atoms[0] = '\0';

		atomshelp = (char*)realloc(NULL, sizeof(char)*a * 3); atomshelp[0] = '\0';
		//voi8itikos
		//etsi twra borw na dilwsw tous pinakes me ta dedomena m alliws meta dn 8a borousa mesa stis if
		//ta declares mesa sta if exoune range mono mesa sto idio to if
		//3 xaraktires to poly 2 grammata gia to ka8e stoixeio + to \0
		ea = (int*)realloc(NULL, sizeof(int)*a); 		//ea: posa atoma ana eidos
		aweights = (float*)realloc(NULL, sizeof(float)*a);
		aatoms = (int*)realloc(NULL, sizeof(int)*a);
		anumber = (int*)realloc(NULL, sizeof(int)*a);
		for (int i = 0; i < a; i++)
		{
			ea[i] = 0;
		}

		///grammh 7 xy xz yz (if it exists), Masses if exist, Atoms
		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;

		if (token[0] == 'M' || token[0] == 'm')
		{

			if (token[0] == 'M' || token[0] == 'm')
			{
				periodic_table = fopen("periodic_table.jgn", "r");

				for (i = 0; i < a; i++)
				{
					found = false;
					std::fgets(s, SBYTES, uc_file);
					token = strtok(s, "\t ");
					while (token[0] == '\n')
					{
						std::fgets(s, SBYTES, uc_file);
						token = strtok(s, "\t ");

					}
					token = strtok(NULL, "\t ");
					while (!found)
					{
						std::fgets(s1, SBYTES, periodic_table);
						token1 = strtok(s1, " ");
						strcat(atoms, token1);
						strcat(atoms, " ");

						token1 = strtok(NULL, " ");
						anumber[i] = atoi(token1);

						token1 = strtok(NULL, " ");
						aweights[i] = std::atof(token1);

						if (int(10 * std::atof(token1)) == int(10 * std::atof(token)))
						{
							found = true;
							for (ole1 = 0; ole1 < 3; ole1++) {
								if (atoms[ole1 + 3 * i] == '\n') {
									atoms[ole1 + 3 * i] = '\0';//giati sto teleytaio pou 8a dei sto line to atoms[ole][ole1] 8a parei thn timh \n kai oxi thn \0 poy 8elw
									ole1 = 100;
								}
							}
						}
						else
						{
							atoms[i * 3] = '\0';
						}
					}
					rewind(periodic_table);
				}

				strcat(atoms, " ");

			}
			else
			{
				for (i = 0; i < a; i++)
				{
					itoa(i + 1, &atoms[i * 3], 10);
					atoms[1 + i * 3] = ' ';
					atoms[2 + i * 3] = ' ';
				}
				atoms[i * 3] = '\0';

			}
		}
		else
		{
			ijk[1][0] = std::atof(token);

			token = strtok(NULL, "\t ");
			ijk[2][0] = std::atof(token);

			token = strtok(NULL, "\t ");
			ijk[2][1] = std::atof(token);

			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");
			while (token[0] == '\n')
			{
				std::fgets(s, SBYTES, uc_file);
				token = strtok(s, "\t ");

			}
			line++;

			if (token[0] == 'M' || token[0] == 'm')
			{
				periodic_table = fopen("periodic_table.jgn", "r");

				for (i = 0; i < a; i++)
				{
					found = false;
					std::fgets(s, SBYTES, uc_file);
					token = strtok(s, "\t ");
					while (token[0] == '\n')
					{
						std::fgets(s, SBYTES, uc_file);
						token = strtok(s, "\t ");

					}
					token = strtok(NULL, "\t ");
					while (!found)
					{
						std::fgets(s1, SBYTES, periodic_table);
						token1 = strtok(s1, " ");
						strcat(atoms, token1);
						strcat(atoms, " ");

						token1 = strtok(NULL, " ");
						anumber[i] = atoi(token1);

						token1 = strtok(NULL, " ");
						aweights[i] = std::atof(token1);
						std::cout << atoms << std::endl;
						if (int(10 * std::atof(token1)) == int(10 * std::atof(token)))
						{
							found = true;
							for (ole1 = 0; ole1 < 3; ole1++) {
								if (atoms[ole1 + 3 * i] == '\n') {
									atoms[ole1 + 3 * i] = '\0';//giati sto teleytaio pou 8a dei sto line to atoms[ole][ole1] 8a parei thn timh \n kai oxi thn \0 poy 8elw
									ole1 = 100;
								}
							}
						}
						else
						{
							atoms[strlen(atoms) - 1] = '\0';
							if (atoms[strlen(atoms) - 1] != ' ')
								atoms[strlen(atoms) - 1] = '\0';
							if (atoms[strlen(atoms) - 1] != ' ')
								atoms[strlen(atoms) - 1] = '\0';

						}
					}
					rewind(periodic_table);
				}

				strcat(atoms, " ");
				strcat(atoms, "\0");


			}
			else
			{
				for (i = 0; i < a; i++)
				{
					itoa(i + 1, &atoms[i * 3], 10);
					atoms[1 + i * 3] = ' ';
					atoms[2 + i * 3] = ' ';
				}
				atoms[i * 3] = '\0';

			}
		}


		///////////////////



		//debuging print
		//#define MY_DEBUG_1
#ifdef MY_DEBUG_1
		std::cout << actor << endl;
		std::cout << ijk[0][0] << '\t' << ijk[0][1] << '\t' << ijk[0][2] << endl;
		std::cout << ijk[1][0] << '\t' << ijk[1][1] << '\t' << ijk[1][2] << endl;
		std::cout << ijk[2][0] << '\t' << ijk[2][1] << '\t' << ijk[2][2] << endl;
		for (int i = 0; i < a; i++)
		{
			std::cout << ea[i] << '\t';
		}
		std::cout << endl;
		std::cout << "yeah 1" << endl;
#endif
		my_direct = (float*)realloc(NULL, sizeof(float)*(t * 5));//t einai ola ta atoma tou unit cell.. 3 gia h,c,l kai dio gia atomiko ari8mo kai varos

		///gammh 9 kai meta	
		inptype = 'c';

		std::fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}


		ole2 = 0;
		ole3 = 0;
		//token3 = strtok(atoms, " ");

		alloena = 0;
		ka8isterimenoflag = 0;
		selective_dynamics = (char*)realloc(NULL, sizeof(char)*(t * 3));

		for (ole = 0; ole < t; ole++) {


			std::fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");
			while (token[0] == '\n')
			{
				std::fgets(s, SBYTES, uc_file);
				token = strtok(s, "\t ");

			}

			ole2++;

			token = strtok(NULL, "\t ");
			my_direct[0 + 5 * ole] = anumber[atoi(token) - 1];//atomicos ari8os
			my_direct[1 + 5 * ole] = aweights[atoi(token) - 1];//atomicos varos
			ea[atoi(token) - 1]++;

			token = strtok(NULL, "\t ");

			for (ole1 = 0; ole1 < 3; ole1++) {

				my_direct[ole1 + 2 + 5 * ole] = std::atof(token);


				token = strtok(NULL, "\t ");

			}


			ole1 = 0;
									
			for (ole1 = 0; ole1 < 3; ole1++)
				selective_dynamics[ole1 + 3 * ole] = true;
			
			//if (ole2 == ea[ole3])
			//{

			//	token3 = strtok(token3 + strlen(token3) + 1, " ");
			//	ole3++;
			//	ole2 = 0;
			//}

		}


		//atoms = atomshelp;


		std::fclose(uc_file);


		//#define MY_DEBUG_2
#ifdef MY_DEBUG_2
		for (ole = 0; ole < t; ole++)
		{
			std::cout << selective_dynamics[0 + 3 * ole] << ' ' << selective_dynamics[1 + 3 * ole] << " " << selective_dynamics[2 + 3 * ole] << endl;
		}
		getchar();
#endif


		if (inptype == 'd')
		{
		}
		else if (inptype == 'c')
		{
			free(uccartesian);
			uccartesian = my_direct;
		}


		sized[0] = 1;
		sized[1] = 1;
		sized[2] = 1;

		jgn::heapRealloc();







		for (int i = 0; i < 500; i++)
		{
			if (lpszFile[i] == '\0')
			{
				for (int j = i; j > 0; j--)
				{
					if (lpszFile[j] == '\\')
					{
						for (k = j + 1; k < i + 1; k++)
						{
							PCtype[k - j - 1] = lpszFile[k];
						}
						j = 0;
					}
				}
				i = 1000;
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (PCtype[i] == '.')
			{
				PCtype[i] = '_';
			}
		}

		NewPC[0] = '\0';
		strcat(NewPC, PCtype);
		strcat(NewPC, "_NIKOULIS_");


		if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
		{
			char S[50];
			itoa(rad, S, 10);
			strcat(NewPC, "(sphere");
			strcat(NewPC, S);
			strcat(NewPC, ")");
		}
		else
		{
			if (S1v != 0)
			{
				char S[50];
				itoa(S1v, S, 10);
				strcat(NewPC, "(100");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
			if (S2v != 0)
			{
				char S[50];
				itoa(S2v, S, 10);
				strcat(NewPC, "(110");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
			if (S3v != 0)
			{
				char S[50];
				itoa(S3v, S, 10);
				strcat(NewPC, "(111");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
		}
		//NewPCF = fopen(NewPC, "w");



		uc_file = fopen(inpf, "r");


		for (ole4 = -sized[2] / 2.0; ole4 < sized[2] / 2.0; ole4++) {
			for (ole2 = -sized[1] / 2.0; ole2 < sized[1] / 2.0; ole2++) {
				for (ole = -sized[0] / 2.0; ole < sized[0] / 2.0; ole++) {
					for (ole3 = 0; ole3 < t; ole3++) {
						crystal[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						crystal_backup[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

																																												  //selective dynamics
						selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
						selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
						selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

						//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
						crystal[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
						crystal_backup[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

						if (inptype == 'd')
						{
							//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
							for (ole1 = 0; ole1 < 3; ole1++) {
								crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
								crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
								{
									min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
								{
									max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}

							}

						}
						else if (inptype == 'c')
						{
							for (ole1 = 0; ole1 < 3; ole1++) {
								crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
								crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
								{
									min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
								{
									max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}

							}
						}
						rewind(periodic_table);


					}

				}
			}
		}



		ole4 = 0;
		//atom. ar. twn atomwn
		for (ole5 = 0; ole5 < t; ole5++)
		{

			if (ole4 == 0)
			{
				atomic_number[ole4] = crystal[0 + 5 * ole5];
				ole4++;

			}
			else if (atomic_number[ole4] == 0 && atomic_number[ole4 - 1] != crystal[0 + 5 * ole5])
			{

				atomic_number[ole4] = crystal[0 + 5 * ole5];
				ole4++;
			}



		}


		allatoms = sized[0] * sized[1] * sized[2] * t;
		//diavazw to arxeio


		std::cout << "\n";
		std::cout << "The number of atoms are " << allatoms << "\n";




		xyz_range[0] = max_xyz[0] - min_xyz[0];//
		xyz_range[1] = max_xyz[1] - min_xyz[1];//ogos
		xyz_range[2] = max_xyz[2] - min_xyz[2];//

		std::cout << "\n";
		std::cout << "  Minimum: " << min_xyz[0]
			<< "  " << min_xyz[1]
			<< "  " << min_xyz[2] << "\n";
		std::cout << "  Maximum: " << max_xyz[0]
			<< "  " << max_xyz[1]
			<< "  " << max_xyz[2] << "\n";
		std::cout << "  Range:   " << xyz_range[0]
			<< "  " << xyz_range[1]
			<< "  " << xyz_range[2] << "\n";

		if (Svmax == 0)
		{
			Svmax = max_xyz[0];
			if (Svmax < max_xyz[1])
			{
				Svmax = max_xyz[1];
			}

			if (Svmax < max_xyz[2])
			{
				Svmax = max_xyz[2];
			}
			Svmax = Svmax * 2;
		}

		pointsize = truepointsize / (Svmax + 5);



	


		fclose(uc_file);

		atoms_to_print_c = 0;
		//fclose(NewPCF);

		fclose(periodic_table);




		if (S1[0] == '1')
		{
			if (S2[0] == '1')
			{
				if (S3[0] == '1') {/*100 110 111*/Scase = 1;
				if (2 * S1v <= S2v && S3v >= 3 * S1v && figure_1 != -1)
				{
					Scase = 4;
				}
				else if (S1v >= S2v && float(S3v) >= (float(S2v) * 3) / 2)
				{
					Scase = 6;
				}
				else if (S1v >= S3v && S3v <= S2v)
				{
					Scase = 7;
				}
				else if (S1v >= S2v)
				{///////
					Scase = 5;
				}
				else if ((S2v >= 2 * S1v && figure_1 != -1) || S3v <= S2v)
				{
					Scase = 3;
				}
				else if ((float(S3v) >= (float(S2v) * 3) / 2 && figure_1 != -1) || (figure_1 == -1 && S3v >= 2 * S2v))
				{

					Scase = 2;
				}

				}
				else {/* 100 110*/Scase = 2;/*done*/
				if (S1v >= S2v)
				{
					Scase = 6;
				}
				else if (S2v >= 2 * S1v)
				{
					Scase = 4;
				}


				}
			}
			else {
				if (S3[0] == '1') {/*100 111*/Scase = 3;/*done*/
				if (S1v >= S3v)
				{
					Scase = 7;
				}
				else if (S3v >= 3 * S1v)
				{
					Scase = 4;
				}

				}
				else {/* 100*/Scase = 4;/*done*/


				}
			}
		}
		else {
			if (S2[0] == '1')
			{
				if (S3[0] == '1') {/*110 111*/Scase = 5;/*done*/
				if (float(S3v) >= (float(S2v) * 3) / 2)
				{

					Scase = 6;
				}
				else if (S3v <= S2v) {
					Scase = 7;
				}
				}
				else {/*110*/Scase = 6;/*done*/


				}
			}
			else {
				if (S3[0] == '1') {/*111*/Scase = 7;/*done*/

				}
				else {/**/Scase = 0;


				}
			}
		}





	}
	Group groupInit;
	//primitive vectors
	groupInit.primitiveVec[0] = jgn::vec3(ijk[0][0], ijk[0][1], ijk[0][2]);
	groupInit.primitiveVec[1] = jgn::vec3(ijk[1][0], ijk[1][1], ijk[1][2]);
	groupInit.primitiveVec[2] = jgn::vec3(ijk[2][0], ijk[2][1], ijk[2][2]);
	groupInit.primitiveBase[0] = groupInit.primitiveVec[0] / groupInit.primitiveVec[0].abs();
	groupInit.primitiveBase[1] = groupInit.primitiveVec[1] / groupInit.primitiveVec[1].abs();
	groupInit.primitiveBase[2] = groupInit.primitiveVec[2] / groupInit.primitiveVec[2].abs();
	//atoms type
	groupInit._N_types = a;
	groupInit._prev_N_types = a;
	groupInit.N_atoms_per_type.reserve(groupInit._N_types);
	groupInit.color_per_type.reserve(groupInit._N_types);
	groupInit.weight_per_type.reserve(groupInit._N_types);
	for (int i = 0; i < groupInit._N_types; i++)
	{
		groupInit.N_atoms_per_type.emplace_back(ea[i]);
		groupInit.color_per_type.emplace_back(jgn::vec3(fmod(aweights[i], 1.5), fmod(anumber[i], 0.92), fmod(100 * fmod(aweights[i], 1.5) * fmod(anumber[i], 0.92), 0.8)));
		groupInit.weight_per_type.emplace_back(aweights[i]);
	}
	//getchar();
	for (int i = 0; i < groupInit._N_types; i++)
	{
		groupInit._alltype.emplace_back(jgn::string(atoms));
		for (int j = 0; j < i; j++)
		{
			size_t sp = groupInit._alltype[i].find(" ");
			if (sp != std::string::npos)
				groupInit._alltype[i].erase(0, sp + 1);
		}
		size_t sp = groupInit._alltype[i].find(" ");
		if (sp != std::string::npos)
		groupInit._alltype[i].resize(sp + 1);

		for (int j = 0; j < groupInit._alltype[i].length(); j++)
		{
			if ((groupInit._alltype[i].c_str())[j] == ' ')
			{
				groupInit._alltype[i].erase(j, 1);
			}
		}
		
	}
	groupInit.N_atoms = t;
	groupInit._reserve(groupInit.N_atoms);
	float cosg = groupInit.primitiveVec[1].x / groupInit.primitiveVec[1].abs();
	float cosb = groupInit.primitiveVec[2].x / groupInit.primitiveVec[2].abs();
	float sing = groupInit.primitiveVec[1].y / groupInit.primitiveVec[1].abs();
	float cosa = (groupInit.primitiveVec[2].y*groupInit.primitiveVec[1].y + groupInit.primitiveVec[2].x*groupInit.primitiveVec[1].x) / (groupInit.primitiveVec[2].abs()*groupInit.primitiveVec[1].abs());
	float V = jgn::volume(groupInit.primitiveVec[0], groupInit.primitiveVec[1], groupInit.primitiveVec[2]);
	for (int i = 0; i < groupInit.N_atoms; i++)
	{
		groupInit.position.emplace_back(jgn::vec3(crystal[2 + 5 * i], crystal[3 + 5 * i], crystal[4 + 5 * i]));
groupInit.fractional.emplace_back(jgn::vec3(crystal[2 + 5 * i] / groupInit.primitiveVec[0].abs() - crystal[3 + 5 * i] * groupInit.primitiveVec[1].x / (groupInit.primitiveVec[0].abs()*groupInit.primitiveVec[1].y) + crystal[4 + 5 * i]*groupInit.primitiveVec[1].abs()*groupInit.primitiveVec[2].abs()*(((groupInit.primitiveVec[2].y*groupInit.primitiveVec[1].y+ groupInit.primitiveVec[2].x*groupInit.primitiveVec[1].x)*groupInit.primitiveVec[1].x)/ (groupInit.primitiveVec[2].abs()*groupInit.primitiveVec[1].abs()*groupInit.primitiveVec[1].abs()) - groupInit.primitiveVec[2].x/ groupInit.primitiveVec[2].abs())/(jgn::volume(groupInit.primitiveVec[0], groupInit.primitiveVec[1], groupInit.primitiveVec[2])*groupInit.primitiveVec[1].y/ groupInit.primitiveVec[1].abs())
			, crystal[3 + 5 * i]/ groupInit.primitiveVec[1].y+ crystal[4 + 5 * i]* groupInit.primitiveVec[0].abs()*groupInit.primitiveVec[2].abs()*(cosb*cosg-cosa)/(V*sing)
			, crystal[4 + 5 * i] * groupInit.primitiveVec[0].abs()*groupInit.primitiveVec[1].abs()*sing / V));
		jgn::string s;
		s.push_back(selective_dynamics[3 * i]);
		s.push_back(selective_dynamics[1 + 3 * i]);
		s.push_back(selective_dynamics[2 + 3 * i]);
		if (!(s[0] == 'T' || s[0] == 't' || s[0] == 'f' || s[0] == 'F'))
		{
			s[0] = 'T';
			s[1] = 'T';
			s[2] = 'T';
		}
		groupInit.selective_dynamics.emplace_back(s);
		groupInit.number.emplace_back( crystal[5 * i]);
		groupInit.weight.emplace_back(crystal[1 + 5 * i]);
		groupInit.isdeleted.emplace_back(false);
		groupInit.isSelected.emplace_back(false);
		groupInit.ishovered.emplace_back(false);
		groupInit.iscut.emplace_back(false);
		for (int ii = 0; ii < groupInit._N_types; ii++)
		{
			if (groupInit.number[i] == anumber[ii])
			{
				groupInit.type.emplace_back(groupInit._alltype[ii]);
			}
		}
		groupInit.radius.emplace_back(1);
		groupInit.color.emplace_back(jgn::vec3(fmod(groupInit.weight[i], 1.5), fmod(groupInit.number[i], 0.92), fmod(100 * fmod(groupInit.weight[i], 1.5) * fmod(groupInit.number[i], 0.92), 0.8)));
	}
	///////////push new group to vs and vs.original
	vs.group.push_back(groupInit);
	vs.N_groups++;
	vs.original->group.push_back(groupInit);
	vs.original->N_groups++;
	///////////sellect the simulation box with the biggest volume for the vs and vs.original
	if (vs.N_groups == 1)
	{
		vs.setSimulationBox(vs.N_groups - 1);
	}
	else if (jgn::volume(vs.group[vs.N_groups - 1].primitiveVec[0], vs.group[vs.N_groups - 1].primitiveVec[1], vs.group[vs.N_groups - 1].primitiveVec[2]) > vs.simulationboxVolume)
	{
		vs.setSimulationBox(vs.N_groups-1);
	}
	if (vs.original->N_groups == 1)
	{
		vs.original->setSimulationBox(vs.original->N_groups - 1);
	}
	else if (jgn::volume(vs.original->group[vs.original->N_groups - 1].primitiveVec[0], vs.original->group[vs.original->N_groups - 1].primitiveVec[1], vs.original->group[vs.original->N_groups - 1].primitiveVec[2]) > vs.original->simulationboxVolume)
	{
		vs.original->setSimulationBox(vs.N_groups - 1);
	}
	/////////////////// for vs
	vs.N_atoms += vs.group[vs.N_groups - 1].N_atoms;
	if (vs.N_types == 0)
	{
		vs.N_types = vs.group[vs.N_groups - 1]._N_types;
		vs.types.reserve(vs.N_types);
		vs.N_atoms_per_type.reserve(vs.N_types);
		for (int i = 0; i < vs.N_types; i++)
		{
			vs.types.emplace_back(vs.group[vs.N_groups - 1]._alltype[i]);
			vs.N_atoms_per_type.emplace_back(vs.group[vs.N_groups - 1].N_atoms_per_type[i]);
			vs.color_per_type.emplace_back(vs.group[vs.N_groups - 1].color_per_type[i]);
			vs.weight_per_type.emplace_back(vs.group[vs.N_groups - 1].weight_per_type[i]);
		}
	}
	else
	{
		for (int i = 0; i < vs.group[vs.N_groups - 1]._N_types; i++)
		{
			bool writeit = true;
			for (int j = 0; j < vs.N_types; j++)
			{
				if (vs.types[j].compare(vs.group[vs.N_groups - 1]._alltype[i]) == 0)
				{
					writeit = false;
					vs.N_atoms_per_type[i] = vs.N_atoms_per_type[i] + vs.group[vs.N_groups - 1].N_atoms_per_type[i];
				}
			}
			if (writeit)
			{
				vs.N_types++;
				vs.types.push_back(jgn::string(vs.group[vs.N_groups - 1]._alltype[i]));
				vs.N_atoms_per_type.push_back(vs.group[vs.N_groups - 1].N_atoms_per_type[i]);
				vs.color_per_type.push_back(vs.group[vs.N_groups - 1].color_per_type[i]);
				vs.weight_per_type.push_back(vs.group[vs.N_groups - 1].weight_per_type[i]);
			}
		}
	}
	vs._sellectHistory.reserve(vs.N_atoms);
	for (int i = 0; i < vs.group[vs.N_groups - 1].N_atoms; i++)
	{
		vs._sellectHistory.emplace_back(jgn::vec3(vs.N_groups - 1, i, -1));
	}
	/////////////////// for vs.original
	vs.original->N_atoms += vs.original->group[vs.original->N_groups - 1].N_atoms;
	if (vs.original->N_types == 0)
	{
		vs.original->N_types = vs.original->group[vs.N_groups - 1]._N_types;
		vs.original->types.reserve(vs.original->N_types);
		vs.original->N_atoms_per_type.reserve(vs.N_types);
		for (int i = 0; i < vs.N_types; i++)
		{
			vs.original->types.emplace_back(vs.original->group[vs.N_groups - 1]._alltype[i]);
			vs.original->N_atoms_per_type.emplace_back(vs.original->group[vs.N_groups - 1].N_atoms_per_type[i]);
			vs.original->color_per_type.emplace_back(vs.original->group[vs.N_groups - 1].color_per_type[i]);
			vs.original->weight_per_type.emplace_back(vs.original->group[vs.N_groups - 1].weight_per_type[i]);
		}
	}
	else
	{
		for (int i = 0; i < vs.original->group[vs.original->N_groups - 1]._N_types; i++)
		{
			bool writeit = true;
			for (int j = 0; j < vs.original->N_types; j++)
			{
				if (vs.original->types[j].compare(vs.original->group[vs.N_groups - 1]._alltype[i]) == 0)
				{
					writeit = false;
					vs.original->N_atoms_per_type[i] = vs.original->N_atoms_per_type[i] + vs.original->group[vs.N_groups - 1].N_atoms_per_type[i];
				}
			}
			if (writeit)
			{
				vs.original->N_types++;
				vs.original->types.push_back(jgn::string(vs.original->group[vs.N_groups - 1]._alltype[i]));
				vs.original->N_atoms_per_type.push_back(vs.original->group[vs.N_groups - 1].N_atoms_per_type[i]);
				vs.original->color_per_type.push_back(vs.original->group[vs.N_groups - 1].color_per_type[i]);
				vs.original->weight_per_type.push_back(vs.original->group[vs.N_groups - 1].weight_per_type[i]);
			}
		}
	}
	vs.original->_sellectHistory.reserve(vs.N_atoms);
	for (int i = 0; i < vs.original->group[vs.N_groups - 1].N_atoms; i++)
	{
		vs.original->_sellectHistory.emplace_back(jgn::vec3(vs.original->N_groups - 1, i, -1));
	}
	bonds.findBonds();
}