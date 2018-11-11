// the program in the program ...
// "background display 3/13/62, prs."

#include "Planetarium.h"

#include <string>
#include <vector>

/*
   star data: "stars by prs 3/13/62 for s/w 2b"

   stars of 1st to 4th magnitude (1j .. 4j) of segment 22.5 deg N to 22.5 deg S
   data order: x, y (ascending by x), x-range: 0 .. 8192, y-range: -511 .. +512
units: screen coors, x: offset from right margin, y: N (top) < 0 < S (bottom)
(y-domain scaled to internal screen representation, x-domain proportional.)
*/

static constexpr int stars_m1[] = {
	1537,  371, //  87 Taur, Aldebaran
	1762, -189, //  19 Orio, Rigel
	1990,  168, //  58 Orio, Betelgeuze
	2280, -377, //   9 CMaj, Sirius
	2583,  125, //  10 CMin, Procyon
	3431,  283, //  32 Leon, Regulus
	4551, -242, //  67 Virg, Spica
	4842,  448, //  16 Boot, Arcturus
	6747,  196  //  53 Aqil, Altair
};
static constexpr int stars_m2[] = {
	1819,  143, //  24 Orio, Bellatrix
	1884,  -29, //  46 Orio
	1910,  -46, //  50 Orio
	1951, -221, //  53 Orio
	2152, -407, //   2 CMaj
	2230,  375, //  24 Gemi
	3201, -187, //  30 Hyda, Alphard
	4005,  344, //  94 Leon, Denebola
	5975,  288  //  55 Ophi
};
static constexpr int stars_m3[] = {
	46,  333, //  88 Pegs, Algenib
	362, -244, //  31 Ceti
	490,  338, //  99 Pisc
	566, -375, //  52 Ceti
	621,  462, //   6 Arie
	764,  -78, //  68 Ceti, Mira
	900,   64, //  86 Ceti
	1007,   84, //  92 Ceti
	1243, -230, //  23 Erid
	1328, -314, //  34 Erid
	1495,  432, //  74 Taur
	1496,  356, //  78 Taur
	1618,  154, //   1 Orio
	1644,   52, //   8 Orio
	1723, -119, //  67 Erid
	1755, -371, //   5 Leps
	1779, -158, //  20 Orio
	1817,  -57, //  28 Orio
	1843, -474, //   9 Leps
	1860,   -8, //  34 Orio
	1868, -407, //  11 Leps
	1875,  225, //  39 Orio
	1880, -136, //  44 Orio
	1887,  480, // 123 Taur
	1948, -338, //  14 Leps
	2274,  296, //  31 Gemi
	2460,  380, //  54 Gemi
	2470,  504, //  55 Gemi
	2513,  193, //   3 CMin
	2967,  154, //  11 Hyda
	3016,  144, //  16 Hyda
	3424,  393, //  30 Leon
	3496,  463, //  41 Leon, Algieba
	3668, -357, //  nu Hyda
	3805,  479, //  68 Leon
	3806,  364, //  10 Leon
	4124, -502, //   2 Corv
	4157, -387, //   4 Corv
	4236, -363, //   7 Corv
	4304,  -21, //  29 Virg
	4384,  90,  //  43 Virg
	4421,  262, //  47 Virg
	4606,   -2, //  79 Virg
	4721,  430, //   8 Boot
	5037, -356, //   9 Libr
	5186, -205, //  27 Libr
	5344,  153, //  24 Serp
	5357,  358, //  28 Serp
	5373,  -71, //  32 Serp
	5430, -508, //   7 Scor
	5459, -445, //   8 Scor
	5513,  -78, //   1 Ophi
	5536, -101, //   2 Ophi
	5609,  494, //  27 Herc
	5641, -236, //  13 Ophi
	5828, -355, //  35 Ophi
	5860,  330, //  64 Herc
	5984, -349, //  55 Serp
	6047,   63, //  62 Ophi
	6107, -222, //  64 Ophi
	6159,  217, //  72 Ophi
	6236,  -66, //  58 Serp
	6439, -483, //  37 Sgtr
	6490,  312, //  17 Aqil
	6491, -115, //  16 Aqil
	6507, -482, //  41 Sgtr
	6602,   66, //  30 Aqil
	6721,  236, //  50 Aqil
	6794,  437, //  12 Sgte
	6862,  -25, //  65 Aqil
	6914, -344, //   9 Capr
	7014,  324, //   6 Dlph
	7318, -137, //  22 Aqar
	7391,  214, //   8 Pegs
	7404, -377, //  49 Capr
	7513,  -18, //  34 Aqar
	7539,  130, //  26 Pegs
	7644,  -12, //  55 Aqar
	7717,  235, //  42 Pegs
	7790, -372, //  76 Aqar
	7849,  334  //  54 Pegs, Markab
};
static constexpr int stars_m4[] = {
	1, -143, //  33 Pisc
	54,  447, //  89 Pegs
	54, -443, //   7 Ceti
	82, -214, //   8 Ceti
	223, -254, //  17 Ceti
	248,  160, //  63 Pisc
	273,  -38, //  20 Ceti
	329,  167, //  71 Pisc
	376,  467, //  84 Pisc
	450, -198, //  45 Ceti
	548,  113, // 106 Pisc
	570,  197, // 110 Pisc
	595, -255, //  53 Ceti
	606, -247, //  55 Ceti
	615,  428, //   5 Arie
	617,   61, //  14 Pisc
	656, -491, //  59 Ceti
	665,   52, // 113 Pisc
	727,  191, //  65 Ceti
	803, -290, //  72 Ceti
	813,  182, //  73 Ceti
	838, -357, //  76 Ceti
	878,   -2, //  82 Ceti
	907, -340, //  89 Ceti
	908,  221, //  87 Ceti
	913, -432, //   1 Erid
	947, -487, //   2 Erid
	976, -212, //   3 Erid
	992,  194, //  91 Ceti
	1058,  440, //  57 Arie
	1076,  470, //  58 Arie
	1087, -209, //  13 Erid
	1104,   68, //  96 Ceti
	1110, -503, //  16 Erid
	1135,  198, //   1 Taur
	1148,  214, //   2 Taur
	1168,  287, //   5 Taur
	1170, -123, //  17 Erid
	1185, -223, //  18 Erid
	1191, -500, //  19 Erid
	1205,    2, //  10 Taur
	1260, -283, //  26 Erid
	1304,  -74, //  32 Erid
	1338,  278, //  35 Taur
	1353,  130, //  38 Taur
	1358,  497, //  37 Taur
	1405, -162, //  38 Erid
	1414,  205, //  47 Taur
	1423,  197, //  49 Taur
	1426, -178, //  40 Erid
	1430,  463, //  50 Taur
	1446,  350, //  54 Taur
	1463,  394, //  61 Taur
	1470,  392, //  64 Taur
	1476,  502, //  65 Taur
	1477,  403, //  68 Taur
	1483,  350, //  71 Taur
	1485,  330, //  73 Taur
	1495,  358, //  77 Taur
	1507,  364, //
	1518,   -6, //  45 Erid
	1526,  333, //  86 Taur
	1537,  226, //  88 Taur
	1544,  -81, //  48 Erid
	1551,  280, //  90 Taur
	1556,  358, //  92 Taur
	1557, -330, //  53 Erid
	1571, -452, //  54 Erid
	1596,  -78, //  57 Erid
	1622,  199, //   2 Orio
	1626,  124, //   3 Orio
	1638, -128, //  61 Erid
	1646,  228, //   7 Orio
	1654,  304, //   9 Orio
	1669,   36, //  10 Orio
	1680, -289, //  64 Erid
	1687, -167, //  65 Erid
	1690, -460, //
	1690,  488, // 102 Taur
	1700,  347, //  11 Orio
	1729,  352, //  15 Orio
	1732, -202, //  69 Erid
	1750, -273, //   3 Leps
	1753,   63, //  17 Orio
	1756, -297, //   4 Leps
	1792, -302, //   6 Leps
	1799, -486, //
	1801,  -11, //  22 Orio
	1807,   79, //  23 Orio
	1816, -180, //  29 Orio
	1818,   40, //  25 Orio
	1830,  497, // 114 Taur
	1830,   69, //  30 Orio
	1851,  134, //  32 Orio
	1857,  421, // 119 Taur
	1861, -168, //  36 Orio
	1874,  214, //  37 Orio
	1878, -138, //
	1880, -112, //  42 Orio
	1885,  210, //  40 Orio
	1899,  -60, //  48 Orio
	1900,   93, //  47 Orio
	1900, -165, //  49 Orio
	1909,  375, // 126 Taur
	1936, -511, //  13 Leps
	1957, 287,  // 134 Taur
	1974, -475, //  15 Leps
	1982,  461, //  54 Orio
	2002, -323, //  16 Leps
	2020,  -70, //
	2030,  220, //  61 Orio
	2032, -241, //   3 Mono
	2037,  458, //  62 Orio
	2057, -340, //  18 Leps
	2059,  336, //  67 Orio
	2084,  368, //  69 Orio
	2084,  324, //  70 Orio
	2105, -142, //   5 Mono
	2112, -311, //
	2153,  106, //   8 Mono
	2179,  462, //  18 Gemi
	2179, -107, //  10 Mono
	2184, -159, //  11 Mono
	2204,  168, //  13 Mono
	2232, -436, //   7 CMaj
	2239, -413, //   8 CMaj
	2245, -320, //
	2250,  227, //  15 Mono
	2266,  303, //  30 Gemi
	2291,   57, //  18 Mono
	2327,  303, //  38 Gemi
	2328, -457, //  15 CMaj
	2330, -271, //  14 CMaj
	2340, -456, //  19 CMaj
	2342, -385, //  20 CMaj
	2378,  -93, //  19 Mono
	2379,  471, //  43 Gemi
	2385, -352, //  23 CMaj
	2428,   -8, //  22 Mono
	2491, -429, //
	2519,  208, //   4 CMin
	2527,  278, //   6 CMin
	2559, -503, //
	2597, -212, //  26 Mono
	2704, -412, //
	2709,  -25, //  28 Mono
	2714,   60, //
	2751,  -61, //  29 Mono
	2757, -431, //  16 Pupp
	2768, -288, //  19 Pupp
	2794,  216, //  17 Canc
	2848,  -82, //
	2915,  138, //   4 Hyda
	2921,   84, //   5 Hyda
	2942, -355, //   9 Hyda
	2944,  497, //  43 Canc
	2947,   85, //   7 Hyda
	2951, -156, //
	2953,  421, //  47 Canc
	2968, -300, //  12 Hyda
	2976,  141, //  13 Hyda
	3032,  279, //  65 Canc
	3124,   62, //  22 Hyda
	3157, -263, //  26 Hyda
	3161, -208, //  27 Hyda
	3209,  -53, //  31 Hyda
	3225,  -17, //  32 Hyda
	3261,  116, //
	3270,  -16, //  35 Hyda
	3274, -316, //  38 Hyda
	3276,  236, //  14 Leon
	3338, -327, //  39 Hyda
	3385,  194, //  29 Leon
	3415, -286, //  40 Hyda
	3428,  239, //  31 Leon
	3429,    3, //  15 Sext
	3446, -270, //  41 Hyda
	3495,  455, //  40 Leon
	3534, -372, //  42 Hyda
	3557,   -3, //  30 Sext
	3570,  223, //  47 Leon
	3726, -404, //  al Crat
	3736,  -44, //  61 Leon
	3738,  471, //  60 Leon
	3754,  179, //  63 Leon
	3793, -507, //  11 Crat
	3821,  -71, //  74 Leon
	3836, -324, //  12 Crat
	3846,  150, //  77 Leon
	3861,  252, //  78 Leon
	3868, -390, //  15 Crat
	3935, -211, //  21 Crat
	3936,   -6, //  91 Leon
	3981, -405, //  27 Crat
	3986,  161, //   3 Virg
	3998,  473, //  93 Leon
	4013,   53, //   5 Virg
	4072,  163, //   8 Virg
	4097,  211, //   9 Virg
	4180,   -3, //  15 Virg
	4185,  418, //  11 Coma
	4249, -356, //   8 Corv
	4290, -170, //  26 Virg
	4305,  245, //  30 Virg
	4376, -205, //  40 Virg
	4403,  409, //  36 Coma
	4465, -114, //  51 Virg
	4466,  411, //  42 Coma
	4512, -404, //  61 Virg
	4563, -352, //  69 Virg
	4590, -131, //  74 Virg
	4603,   95, //  78 Virg
	4679,  409, //   4 Boot
	4691,  371, //   5 Boot
	4759,   46, //  93 Virg
	4820,   66, //
	4822, -223, //  98 Virg
	4840, -126, //  99 Virg
	4857, -294, // 100 Virg
	4864,  382, //  20 Boot
	4910,  -41, // 105 Virg
	4984,  383, //  29 Boot
	4986,  322, //  30 Boot
	4994, -119, // 107 Virg
	5009,  396, //  35 Boot
	5013,   53, // 109 Virg
	5045,  444, //  37 Boot
	5074,  -90, //  16 Libr
	5108,   57, // 110 Virg
	5157, -442, //  24 Libr
	5283, -221, //  37 Libr
	5290, -329, //  38 Libr
	5291,  247, //  13 Serp
	5326, -440, //  43 Libr
	5331,  455, //  21 Serp
	5357,  175, //  27 Serp
	5372,  420, //  35 Serp
	5381,  109, //  37 Serp
	5387,  484, //  38 Serp
	5394, -374, //  46 Libr
	5415,  364, //  41 Serp
	5419, -318, //  48 Libr
	5455, -253, //  xi Scor
	5467, -464, //   9 Scor
	5470, -469, //  10 Scor
	5497, -437, //  14 Scor
	5499, -223, //  15 Scor
	5558,   29, //  50 Serp
	5561,  441, //  20 Herc
	5565, -451, //   4 Ophi
	5580,  325, //  24 Herc
	5582, -415, //   7 Ophi
	5589, -186, //   3 Ophi
	5606, -373, //   8 Ophi
	5609,   50, //  10 Ophi
	5610, -484, //   9 Ophi
	5620,  266, //  29 Herc
	5713, -241, //  20 Ophi
	5742,  235, //  25 Ophi
	5763,  217, //  27 Ophi
	5807,  293, //  60 Herc
	5868,   -8, //  41 Ophi
	5888, -478, //  40 Ophi
	5889, -290, //  53 Serp
	5924, -114, //
	5925,   96, //  49 Ophi
	5987, -183, //  57 Ophi
	6006, -292, //  56 Serp
	6016, -492, //  58 Ophi
	6117,  -84, //  57 Serp
	6117,   99, //  66 Ophi
	6119,  381, //  93 Herc
	6119,   67, //  67 Ophi
	6125,   30, //  68 Ophi
	6146,   57, //  70 Ophi
	6158,  198, //  71 Ophi
	6170,  473, // 102 Herc
	6188, -480, //  13 Sgtr
	6234,   76, //  74 Ophi
	6235,  499, // 106 Herc
	6247, -204, //  xi Scut
	6254, -469, //  21 Sgtr
	6255,  494, // 109 Herc
	6278, -333, //  ga Scut
	6313, -189, //  al Scut
	6379,  465, // 110 Herc
	6382, -110, //  be Scut
	6386,  411, // 111 Herc
	6436,   93, //  63 Serp
	6457,  340, //  13 Aqil
	6465, -134, //  12 Aqil
	6478, -498, //  39 Sgtr
	6553,  483, //   1 Vulp
	6576, -410, //  44 Sgtr
	6576, -368, //  46 Sgtr
	6607,    3, //  32 Aqil
	6651,  163, //  38 Aqil
	6657,  445, //   9 Vulp
	6665,  -35, //  41 Aqil
	6688,  405, //   5 Sgte
	6693,  393, //   6 Sgte
	6730,  416, //   7 Sgte
	6739,  430, //   8 Sgte
	6755,   17, //  55 Aqil
	6766,  187, //  59 Aqil
	6772,  140, //  60 Aqil
	6882,  339, //  67 Aqil
	6896, -292, //   5 Capr
	6898, -292, //   6 Capr
	6913, -297, //   8 Capr
	6958, -413, //  11 Capr
	6988,  250, //   2 Dlph
	7001,  326, //   4 Dlph
	7015,  -33, //  71 Aqil
	7020,  475, //  29 Vulp
	7026,  354, //   9 Dlph
	7047,  335, //  11 Dlph
	7066,  359, //  12 Dlph
	7067, -225, //   2 Aqar
	7068, -123, //   3 Aqar
	7096, -213, //   6 Aqar
	7161, -461, //  22 Capr
	7170, -401, //  23 Capr
	7192, -268, //  13 Aqar
	7199,  222, //   5 Equl
	7223,  219, //   7 Equl
	7230,  110, //   8 Equl
	7263, -393, //  32 Capr
	7267,  441, //   1 Pegs
	7299, -506, //  36 Capr
	7347, -453, //  39 Capr
	7353, -189, //  23 Aqar
	7365, -390, //  40 Capr
	7379, -440, //  43 Capr
	7394,  384, //   9 Pegs
	7499,  -60, //  31 Aqar
	7513,  104, //  22 Pegs
	7515, -327, //  33 Aqar
	7575, -189, //  43 Aqar
	7603,  -43, //  48 Aqar
	7604,  266, //  31 Pegs
	7624,   20, //  52 Aqar
	7639,   96, //  35 Pegs
	7654, -255, //  57 Aqar
	7681,  -14, //  62 Aqar
	7727, -440, //  66 Aqar
	7747,  266, //  46 Pegs
	7761, -321, //  71 Aqar
	7779, -185, //  73 Aqar
	7795,  189, //  50 Pegs
	7844,   75, //   4 Pisc
	7862,  202, //  55 Pegs
	7874, -494, //  88 Aqar
	7903, -150, //  90 Aqar
	7911, -219, //  91 Aqar
	7919,   62, //   6 Pisc
	7923, -222, //  93 Aqar
	7952, -470, //  98 Aqar
	7969, -482, //  99 Aqar
	7975,   16, //   8 Pisc
	7981,  133, //  10 Pisc
	7988,  278, //  70 Pegs
	8010, -489, // 101 Aqar
	8049,  116, //  17 Pisc
	8059, -418, // 104 Aqar
	8061,   28, //  18 Pisc
	8064, -344, // 105 Aqar
	8159,  144, //  28 Pisc
	8174, -149, //  30 Pisc
	8188, -407  //   2 Ceti
};


// dimensional constants (for readability)
static constexpr int SCREEN_WIDTH = 1024,
			 HALFSCREEN = SCREEN_WIDTH/2,
			 MAP_WIDTH = 8192;  // range of x-domain (0 .. 020000)
static int fpr;    // (010000) right frame margin, map center



class Magnitude {
	public:
		Magnitude(const int data[], int length) {
			cursor = 0;  // data cursor (label flo, initialized to offset J)
			// transform coors (like macro "mark")
			for (int i = 0; i < length; i+=2) {
				// x-coor: max - x (flip horizontally)
				coors.push_back(MAP_WIDTH - data[i]);
				// y-coor here as is (orig. prepares for display instructions)
				coors.push_back(data[i + 1]);
			}
		}

        void dislis(int b) { /* (macro dislis) */
            // scans stars, displays on-screen ones,
            // limits scan per frame by cursor-pos. (stars are ordered by x-coors)
            // the original implementation loops over a subset of the entire set
            // of coordinates, in bounds of offsets J and Q+2 (Q: index of last x)
            // here, coors are private, J is always zero and Q+2 is coors.length.
            // argument b: brightness (display intensity).

            int didPlot = false;         // (program flag 5)
            unsigned int startIdx = cursor;  // data index on entry (label fpo)
            unsigned int cx = cursor,        // data pos x-coor (label fin)
                cy = cursor + 1;    // data pos y-coor (label fyn)
            int sx;                      // screen x-coor (just AC in original)

            for (;;) { // loop over coors (label fin)
                // prepare the screen x-coordinate for display
                sx = coors[cx] - fpr; // x-coor - right margin
                // check, if inbounds to the right
                if (sx >= 0) { // off-screen, try wrap/overlap (label fgr)
                    sx = -MAP_WIDTH + SCREEN_WIDTH;
                }
                else {
                    sx += SCREEN_WIDTH;
                }
                // check, if inbounds to the left (label frr, fou)
                if (sx <= 0) { // off-screen to the left (label fuu)
                    // did we plot any?
                    if (didPlot) break;
                    // since the view moves from right to left, we won't inspect it in
                    // the next run again, advance the data cursor (start with next star)
                    cursor += 2;
                    // the original loops over offsets J .. Q+2
                    if (cursor == coors.size()) cursor = 0;
                }
                else { // on-screen (0 >= sx > SCREEN_WIDTH)
                    // display it (label fie)
                    plot(sx - HALFSCREEN, coors[cy], b); // in main
                    didPlot = true;
                }
                // next star (label fid)
                cy++;
                if (cy == coors.size()) { // data wrap-around (label flp; length: Q+2)
                    // did we start at 0 (have we seen all)?
                    if (startIdx == 0) break; // in original offset J, here always zero
                    // no, start over with first star
                    cx = 0;  // in original offset J, here always zero
                    cy = 1;  // in original J+1
                }
                else {
                    // have we performed a full wrap (seen all)?
                    if (cy == startIdx) break;
                    // continue with next star (next pair of coors)
                    cx = cy;
                    cy++;
                }
            }
        }

	private:
		std::vector<int> coors; // star data
		unsigned int cursor;

};

static Magnitude m1(stars_m1, sizeof(stars_m1) / sizeof(stars_m1[0]));
static Magnitude m2(stars_m2, sizeof(stars_m2) / sizeof(stars_m2[0]));
static Magnitude m3(stars_m3, sizeof(stars_m3) / sizeof(stars_m3[0]));
static Magnitude m4(stars_m4, sizeof(stars_m4) / sizeof(stars_m4[0]));

// static vars
int bcc;    // frame skip counter (spacewar 3.1 mode)
int bkc;    // step counter

// config
bool NOSKIP,   // opt out of skip of every 2nd frame
	 INTERLACED;   // Spacewar 2b - mode

Planetarium::Planetarium()
{
	bcc = 0;
	bkc = 0;
	fpr = 4096;

	NOSKIP = false;
	INTERLACED = false;
}

void Planetarium::reset() {
    fpr = 4096;
    bcc = bkc = 0;
}

void Planetarium::update() { /* main method ( label bck ) */
	// two implementations: once as in sw 3.1 and once as in sw 2b
	if (!INTERLACED) {
		// spacewar 3.1: stars modulated by display intensities
		// displays every second frame only (opt-out option not in original code)
		if (!NOSKIP) {
			if (++bcc < 0) return;
			bcc = -2;
		}
		m1.dislis(3);
		m2.dislis(2);
		m3.dislis(1);
		m4.dislis(0);
		// advance every 32nd frame (every 16th display frame)
		if (++bkc >= 0) {
			bkc = (NOSKIP)? -32 : -16;
			fpr--;
			if (fpr < 0) fpr += MAP_WIDTH; // reset right margin (8192)
		}
	}
	else {
		// spacewar 2b: stars modulated by frequency of update
		// (requires emulation of P7 phosphor, speed options not implemented)
		m1.dislis(0);
		bcc++;
		if (bcc & 1) m3.dislis(0);
		m2.dislis(0);
		if ((bcc & 3) != 0) m4.dislis(0);
		m1.dislis(0); // display first magnitude again (brightest)
		bcc %= 4;     // not in the original code (wraps around by overflow)
		// advance every 32nd frame
		if (++bkc >= 0) {
			bkc = -32;
			fpr--;
			if (fpr < 0) fpr += MAP_WIDTH; // reset right margin
		}
	}
}


// constructor, in original an assembler macro

// API methods (exported)

void Planetarium::setOption(std::string key, int v) {
	//std::string k = key.toUpperCase().replace("/[^A-Z0-9]/g", '');
	if (key == "FRAMESKIP")
		v = !v;
	if (key == "NOSKIP" || key == "FRAMESKIP") {
		if (NOSKIP && bkc < -16)
			bkc += 16;
		NOSKIP = !!v;
	}

	if (key == "INTERLACED" || key == "SPACEWAR2B") {
		INTERLACED = !!v;
		bcc = bkc = 0;
	}
}

