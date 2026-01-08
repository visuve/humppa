#include <iostream>
#include <string_view>

namespace poelkky::alphabet
{
	constexpr wchar_t A[64] =	L"    A    "
								L"   A A   "
								L"  A   A  "
								L" AAAAAAA "
								L"A       A"
								L"A       A"
								L"A       A";

	constexpr wchar_t B[64] =	L"BBBBBBBB "
								L"B       B"
								L"B       B"
								L"BBBBBBBB "
								L"B       B"
								L"B       B"
								L"BBBBBBBB ";

	constexpr wchar_t C[64] =	L"  CCCCCCC"
								L" C       "
								L"C        "
								L"C        "
								L"C        "
								L" C       "
								L"  CCCCCCC";

	constexpr wchar_t D[64] =	L"DDDDDDD  "
								L"D      D "
								L"D       D"
								L"D       D"
								L"D       D"
								L"D      D "
								L"DDDDDDD  ";

	constexpr wchar_t E[64] =	L"EEEEEEEEE"
								L"E        "
								L"E        "
								L"EEEEEEEE "
								L"E        "
								L"E        "
								L"EEEEEEEEE";

	constexpr wchar_t F[64] =	L"FFFFFFFFF"
								L"F        "
								L"F        "
								L"FFFFFFFF "
								L"F        "
								L"F        "
								L"F        ";

	constexpr wchar_t G[64] =	L" GGGGGGG "
								L"G       G"
								L"G        "
								L"G   GGGGG"
								L"G       G"
								L"G       G"
								L" GGGGGGG ";

	constexpr wchar_t H[64] =	L"H       H"
								L"H       H"
								L"H       H"
								L"HHHHHHHHH"
								L"H       H"
								L"H       H"
								L"H       H";

	constexpr wchar_t I[64] =	L" IIIIIII "
								L"    I    "
								L"    I    "
								L"    I    "
								L"    I    "
								L"    I    "
								L" IIIIIII ";

	constexpr wchar_t J[64] =	L"  JJJJJJJ"
								L"      J  "
								L"      J  "
								L"      J  "
								L"      J  "
								L"J     J  "
								L" JJJJJ   ";

	constexpr wchar_t K[64] =	L"K      K "
								L"K     K  "
								L"K    K   "
								L"KKKKKK   "
								L"K    K   "
								L"K     K  "
								L"K      K ";

	constexpr wchar_t L[64] =	L"L        "
								L"L        "
								L"L        "
								L"L        "
								L"L        "
								L"L        "
								L"LLLLLLLLL";

	constexpr wchar_t M[64] =	L"M       M"
								L"MM     MM"
								L"M M   M M"
								L"M  M M  M"
								L"M   M   M"
								L"M       M"
								L"M       M";

	constexpr wchar_t N[64] =	L"N       N"
								L"NN      N"
								L"N N     N"
								L"N  NN   N"
								L"N    N  N"
								L"N     N N"
								L"N      NN";

	constexpr wchar_t O[64] =	L"  OOOOO  "
								L" O     O "
								L"O       O"
								L"O       O"
								L"O       O"
								L" O     O "
								L"  OOOOO  ";

	constexpr wchar_t P[64] =	 L"PPPPPPPP "
								L"P       P"
								L"P       P"
								L"PPPPPPPP "
								L"P        "
								L"P        "
								L"P        ";

	constexpr wchar_t Q[64] =	L"  QQQQQ  "
								L" Q     Q "
								L"Q       Q"
								L"Q       Q"
								L"Q   Q   Q"
								L" Q    QQ "
								L"  QQQQ  Q";

	constexpr wchar_t R[64] =	L"RRRRRRRR "
								L"R       R"
								L"R       R"
								L"RRRRRRRR "
								L"R     R  "
								L"R      R "
								L"R       R";

	constexpr wchar_t S[64] =	L" SSSSSSSS"
								L"S        "
								L"S        "
								L" SSSSSSS "
								L"        S"
								L"        S"
								L"SSSSSSSS ";

	constexpr wchar_t T[64] =	L"TTTTTTTTT"
								L"    T    "
								L"    T    "
								L"    T    "
								L"    T    "
								L"    T    "
								L"    T    ";

	constexpr wchar_t U[64] =	L"U       U"
								L"U       U"
								L"U       U"
								L"U       U"
								L"U       U"
								L" U     U "
								L"  UUUUU  ";

	constexpr wchar_t V[64] =	L"V       V"
								L"V       V"
								L"V       V"
								L" V     V "
								L"  V   V  "
								L"   V V   "
								L"    V    ";

	constexpr wchar_t W[64] =	L"W       W"
								L"W       W"
								L"W       W"
								L"W   W   W"
								L"W  W W  W"
								L" W W W W "
								L"  W   W  ";

	constexpr wchar_t X[64] =	L"X       X"
								L" X     X "
								L"  X   X  "
								L"   XXX   "
								L"  X   X  "
								L" X     X "
								L"X       X";

	constexpr wchar_t Y[64] =	L"Y       Y"
								L" Y     Y "
								L"  Y   Y  "
								L"   YYY   "
								L"    Y    "
								L"    Y    "
								L"    Y    ";

	constexpr wchar_t Z[64] =	L"ZZZZZZZZZ"
								L"       Z "
								L"     Z   "
								L"    Z    "
								L"   Z     "
								L" Z       "
								L"ZZZZZZZZZ";

	constexpr wchar_t Å[64] =	L"    Å    "
								L"         "
								L"   ÅÅÅ   "
								L"  Å   Å  "
								L" ÅÅÅÅÅÅÅ "
								L"Å       Å"
								L"Å       Å";

	constexpr wchar_t Ä[64] =	L"  Ä   Ä  "
								L"         "
								L"   ÄÄÄ   "
								L"  Ä   Ä  "
								L" ÄÄÄÄÄÄÄ "
								L"Ä       Ä"
								L"Ä       Ä";

	constexpr wchar_t Ö[64] =	L"  Ö   Ö  "
								L"         "
								L"  ÖÖÖÖÖ  "
								L" Ö     Ö "
								L"Ö       Ö"
								L" Ö     Ö "
								L"  ÖÖÖÖÖ  ";

	void print_row(size_t row, wchar_t c)
	{
		switch (c)
		{
		case L'a': case L'A': std::wcout.write(A + (row * 9), 9); return;
		case L'b': case L'B': std::wcout.write(B + (row * 9), 9); return;
		case L'c': case L'C': std::wcout.write(C + (row * 9), 9); return;
		case L'd': case L'D': std::wcout.write(D + (row * 9), 9); return;
		case L'e': case L'E': std::wcout.write(E + (row * 9), 9); return;
		case L'f': case L'F': std::wcout.write(F + (row * 9), 9); return;
		case L'g': case L'G': std::wcout.write(G + (row * 9), 9); return;
		case L'h': case L'H': std::wcout.write(H + (row * 9), 9); return;
		case L'i': case L'I': std::wcout.write(I + (row * 9), 9); return;
		case L'j': case L'J': std::wcout.write(J + (row * 9), 9); return;
		case L'k': case L'K': std::wcout.write(K + (row * 9), 9); return;
		case L'l': case L'L': std::wcout.write(L + (row * 9), 9); return;
		case L'm': case L'M': std::wcout.write(M + (row * 9), 9); return;
		case L'n': case L'N': std::wcout.write(N + (row * 9), 9); return;
		case L'o': case L'O': std::wcout.write(O + (row * 9), 9); return;
		case L'p': case L'P': std::wcout.write(P + (row * 9), 9); return;
		case L'q': case L'Q': std::wcout.write(Q + (row * 9), 9); return;
		case L'r': case L'R': std::wcout.write(R + (row * 9), 9); return;
		case L's': case L'S': std::wcout.write(S + (row * 9), 9); return;
		case L't': case L'T': std::wcout.write(T + (row * 9), 9); return;
		case L'u': case L'U': std::wcout.write(U + (row * 9), 9); return;
		case L'v': case L'V': std::wcout.write(V + (row * 9), 9); return;
		case L'w': case L'W': std::wcout.write(W + (row * 9), 9); return;
		case L'x': case L'X': std::wcout.write(X + (row * 9), 9); return;
		case L'y': case L'Y': std::wcout.write(Y + (row * 9), 9); return;
		case L'z': case L'Z': std::wcout.write(Z + (row * 9), 9); return;
		case L'å': case L'Å': std::wcout.write(Å + (row * 9), 9); return;
		case L'ä': case L'Ä': std::wcout.write(Ä + (row * 9), 9); return;
		case L'ö': case L'Ö': std::wcout.write(Ö + (row * 9), 9); return;
		case L' ': std::wcout << L"         "; return;
		}
	}

	void print(const std::wstring& text)
	{
		for (size_t row = 0; row < 7; ++row)
		{
			for (char c : text)
			{
				print_row(row, c);

				std::wcout << L"   ";
			}

			std::wcout << std::endl;
		}
	}
}

// NOTE: windows only for now...
int wmain(int argc, wchar_t** argv)
{
	using namespace poelkky::alphabet;

	for (size_t i = 1; i < argc; ++i)
	{
		print(argv[i]);

		std::wcout << std::endl;
	}
	
	return 0;
}
