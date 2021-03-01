/****************************************************************************
 *
 *   Copyright (c) 2020 Estimation and Control Library (ECL). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name ECL nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.1616,
static constexpr const int16_t declination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ {  26022, 24276, 22531, 20786, 19040, 17295, 15550, 13804, 12059, 10314,  8568,  6823,  5078,  3332,  1587,  -158, -1903, -3649, -5394, -7139, -8884,-10630,-12375,-14120,-15866,-17611,-19356,-21102,-22847,-24593,-26338,-28083,-29829, 31258, 29512, 27767, 26022, },
/* LAT: -80 */ {  22592, 20455, 18511, 16734, 15092, 13552, 12087, 10674,  9298,  7948,  6615,  5296,  3987,  2682,  1375,    56, -1283, -2653, -4060, -5509, -7000, -8534,-10109,-11725,-13387,-15103,-16886,-18755,-20735,-22851,-25123,-27556,-30125, 30064, 27441, 24928, 22592, },
/* LAT: -70 */ {  14965, 13570, 12448, 11490, 10626,  9798,  8960,  8075,  7124,  6106,  5036,  3941,  2854,  1797,   773,  -238, -1273, -2374, -3569, -4862, -6236, -7660, -9104,-10543,-11967,-13381,-14807,-16288,-17904,-19805,-22302,-26068, 30847, 24203, 19629, 16839, 14965, },
/* LAT: -60 */ {   8373,  8137,  7866,  7600,  7355,  7108,  6806,  6378,  5768,  4953,  3955,  2843,  1720,   685,  -205,  -970, -1700, -2516, -3508, -4691, -6010, -7372, -8689, -9899,-10965,-11867,-12586,-13083,-13254,-12804,-10719, -3619,  4753,  7556,  8355,  8497,  8373, },
/* LAT: -50 */ {   5448,  5489,  5440,  5357,  5290,  5259,  5230,  5108,  4771,  4115,  3111,  1842,   498,  -694, -1582, -2162, -2568, -3003, -3670, -4659, -5882, -7149, -8289, -9196, -9804,-10056, -9876, -9132, -7635, -5283, -2384,   361,  2469,  3892,  4766,  5242,  5448, },
/* LAT: -40 */ {   3928,  4022,  4036,  3998,  3944,  3915,  3924,  3917,  3750,  3224,  2213,   779,  -788, -2117, -3002, -3474, -3674, -3741, -3897, -4430, -5372, -6436, -7326, -7878, -8004, -7647, -6776, -5400, -3684, -1973,  -507,   716,  1757,  2617,  3269,  3697,  3928, },
/* LAT: -30 */ {   2961,  3048,  3085,  3078,  3026,  2953,  2897,  2866,  2743,  2275,  1256,  -251, -1862, -3133, -3895, -4260, -4358, -4169, -3740, -3483, -3799, -4528, -5234, -5604, -5500, -4933, -3985, -2776, -1555,  -598,    86,   687,  1307,  1903,  2407,  2764,  2961, },
/* LAT: -20 */ {   2318,  2366,  2391,  2402,  2367,  2278,  2176,  2103,  1959,  1473,   435, -1041, -2525, -3606, -4164, -4303, -4120, -3584, -2731, -1911, -1595, -1922, -2569, -3053, -3107, -2763, -2134, -1313,  -525,   -25,   245,   549,   985,  1454,  1868,  2169,  2318, },
/* LAT: -10 */ {   1924,  1920,  1907,  1913,  1893,  1815,  1712,  1626,  1444,   901,  -146, -1515, -2797, -3649, -3945, -3743, -3184, -2411, -1564,  -798,  -312,  -321,  -778, -1289, -1514, -1434, -1125,  -622,  -116,   135,   192,   355,   720,  1147,  1531,  1810,  1924, },
/* LAT:   0 */ {   1712,  1681,  1633,  1632,  1629,  1567,  1472,  1365,  1114,   498,  -533, -1758, -2824, -3435, -3463, -2985, -2225, -1441,  -782,  -239,   182,   309,    44,  -372,  -635,  -695,  -597,  -332,   -35,    62,    10,   102,   437,   867,  1277,  1588,  1712, },
/* LAT:  10 */ {   1580,  1590,  1554,  1577,  1610,  1569,  1457,  1278,   905,   190,  -828, -1907, -2749, -3111, -2932, -2341, -1567,  -850,  -326,    59,   388,   546,   396,    75,  -165,  -273,  -293,  -207,   -98,  -133,  -264,  -235,    61,   504,   975,  1375,  1580, },
/* LAT:  20 */ {   1404,  1554,  1620,  1717,  1808,  1794,  1648,  1354,   812,   -44, -1089, -2049, -2663, -2793, -2482, -1889, -1179,  -525,   -57,   258,   520,   672,   589,   347,   145,    28,   -58,  -115,  -190,  -374,  -606,  -663,  -435,     3,   537,  1050,  1404, },
/* LAT:  30 */ {   1115,  1483,  1745,  1971,  2133,  2148,  1967,  1551,   826,  -205, -1330, -2221, -2654, -2608, -2219, -1645,  -990,  -369,   101,   412,   647,   799,   785,   639,   487,   364,   214,    13,  -263,  -633,  -999, -1161, -1007,  -587,   -14,   594,  1115, },
/* LAT:  40 */ {    771,  1359,  1853,  2245,  2494,  2540,  2327,  1797,   886,  -347, -1599, -2484, -2821, -2679, -2238, -1649,  -995,  -363,   153,   523,   798,  1002,  1103,  1096,  1019,   873,   614,   215,  -314,  -917, -1440, -1689, -1579, -1166,  -567,   109,   771, },
/* LAT:  50 */ {    496,  1246,  1926,  2480,  2844,  2949,  2719,  2064,   917,  -594, -2036, -2970, -3276, -3090, -2602, -1957, -1246,  -545,    76,   588,  1011,  1372,  1659,  1835,  1858,  1678,  1245,   552,  -330, -1232, -1918, -2214, -2095, -1654, -1014,  -274,   496, },
/* LAT:  60 */ {    323,  1181,  1986,  2677,  3175,  3381,  3160,  2337,   802, -1189, -2932, -3926, -4182, -3921, -3345, -2597, -1767,  -922,  -109,   648,  1345,  1981,  2530,  2933,  3103,  2930,  2311,  1216,  -187, -1511, -2394, -2714, -2552, -2053, -1349,  -536,   323, },
/* LAT:  70 */ {    131,  1074,  1974,  2771,  3380,  3663,  3392,  2215,  -102, -2890, -4864, -5678, -5670, -5171, -4389, -3445, -2412, -1339,  -258,   808,  1838,  2809,  3683,  4397,  4856,  4905,  4323,  2888,   724, -1384, -2697, -3151, -2992, -2452, -1690,  -807,   131, },
/* LAT:  80 */ {   -434,   494,  1353,  2049,  2430,  2215,   906, -1956, -5386, -7516, -8198, -8005, -7330, -6380, -5265, -4048, -2768, -1452,  -119,  1215,  2534,  3819,  5049,  6188,  7185,  7947,  8296,  7880,  6050,  2469, -1037, -2780, -3181, -2874, -2207, -1359,  -434, },
/* LAT:  90 */ { -30356,-28611,-26865,-25120,-23375,-21629,-19884,-18138,-16393,-14648,-12903,-11157, -9412, -7667, -5922, -4177, -2432,  -686,  1059,  2804,  4549,  6294,  8040,  9785, 11530, 13276, 15021, 16766, 18512, 20257, 22003, 23748, 25494, 27239, 28985, 30730,-30356, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.1616,
static constexpr const int16_t inclination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ { -12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580, },
/* LAT: -80 */ { -13667,-13534,-13373,-13193,-12999,-12797,-12592,-12391,-12200,-12023,-11866,-11731,-11620,-11534,-11471,-11429,-11410,-11413,-11440,-11494,-11577,-11691,-11836,-12009,-12206,-12423,-12652,-12885,-13113,-13325,-13513,-13664,-13769,-13821,-13819,-13765,-13667, },
/* LAT: -70 */ { -14118,-13799,-13480,-13157,-12824,-12479,-12123,-11765,-11420,-11110,-10855,-10670,-10556,-10503,-10490,-10495,-10504,-10516,-10541,-10597,-10705,-10877,-11121,-11433,-11804,-12220,-12667,-13131,-13597,-14050,-14469,-14817,-15010,-14960,-14731,-14433,-14118, },
/* LAT: -60 */ { -13525,-13173,-12836,-12503,-12160,-11787,-11372,-10916,-10447,-10013, -9679, -9499, -9491, -9626, -9831,-10028,-10160,-10211,-10204,-10192,-10238,-10392,-10675,-11078,-11572,-12125,-12710,-13306,-13895,-14456,-14952,-15244,-15075,-14693,-14289,-13897,-13525, },
/* LAT: -50 */ { -12499,-12158,-11829,-11508,-11184,-10838,-10438, -9966, -9434, -8909, -8512, -8377, -8569, -9024, -9589,-10108,-10479,-10655,-10638,-10494,-10352,-10350,-10559,-10966,-11502,-12092,-12679,-13219,-13668,-13968,-14078,-14006,-13803,-13520,-13193,-12847,-12499, },
/* LAT: -40 */ { -11240,-10895,-10550,-10206, -9867, -9528, -9165, -8738, -8215, -7646, -7211, -7154, -7598, -8413, -9336,-10173,-10842,-11292,-11451,-11302,-10967,-10688,-10666,-10934,-11388,-11892,-12342,-12670,-12833,-12840,-12749,-12610,-12429,-12197,-11911,-11584,-11240, },
/* LAT: -30 */ {  -9601, -9228, -8853, -8465, -8072, -7695, -7335, -6941, -6426, -5812, -5349, -5408, -6153, -7343, -8596, -9700,-10625,-11349,-11770,-11785,-11429,-10922,-10576,-10562,-10805,-11126,-11388,-11509,-11450,-11275,-11097,-10958,-10808,-10599,-10318, -9974, -9601, },
/* LAT: -20 */ {  -7369, -6938, -6529, -6103, -5659, -5227, -4831, -4412, -3842, -3153, -2690, -2920, -3997, -5594, -7227, -8611, -9694,-10487,-10947,-11003,-10658,-10053, -9489, -9234, -9274, -9435, -9581, -9605, -9436, -9163, -8964, -8869, -8757, -8545, -8229, -7820, -7369, },
/* LAT: -10 */ {  -4411, -3889, -3446, -3014, -2557, -2105, -1686, -1222,  -587,   124,   505,   111, -1183, -3082, -5063, -6695, -7817, -8473, -8756, -8710, -8318, -7646, -6982, -6626, -6581, -6673, -6794, -6822, -6637, -6339, -6177, -6174, -6121, -5899, -5515, -4993, -4411, },
/* LAT:   0 */ {   -901,  -294,   159,   556,   972,  1390,  1786,  2241,  2838,  3427,  3647,  3180,  1916,    26, -2022, -3699, -4738, -5190, -5264, -5106, -4681, -3979, -3274, -2894, -2831, -2903, -3031, -3107, -2979, -2741, -2677, -2803, -2849, -2655, -2231, -1609,  -901, },
/* LAT:  10 */ {   2566,  3177,  3601,  3936,  4290,  4658,  5015,  5414,  5878,  6259,  6310,  5842,  4784,  3235,  1543,   147,  -685,  -955,  -877,  -650,  -250,   378,  1010,  1353,  1414,  1365,  1261,  1169,  1213,  1321,  1254,  1004,   829,   909,  1261,  1855,  2566, },
/* LAT:  20 */ {   5419,  5937,  6309,  6601,  6913,  7257,  7605,  7961,  8305,  8514,  8438,  7990,  7169,  6082,  4954,  4033,  3486,  3350,  3489,  3726,  4050,  4508,  4967,  5224,  5278,  5255,  5204,  5147,  5139,  5125,  4960,  4640,  4354,  4270,  4441,  4858,  5419, },
/* LAT:  30 */ {   7569,  7937,  8251,  8532,  8841,  9189,  9550,  9898, 10182, 10303, 10167,  9754,  9132,  8423,  7759,  7240,  6938,  6886,  7020,  7226,  7469,  7764,  8051,  8225,  8279,  8288,  8287,  8278,  8259,  8181,  7966,  7621,  7272,  7056,  7039,  7230,  7569, },
/* LAT:  40 */ {   9265,  9485,  9740, 10025, 10352, 10715, 11086, 11429, 11687, 11775, 11631, 11275, 10803, 10328,  9929,  9641,  9486,  9475,  9580,  9737,  9909, 10090, 10261, 10386, 10462, 10520, 10571, 10605, 10591, 10485, 10249,  9903,  9539,  9256,  9113,  9124,  9265, },
/* LAT:  50 */ {  10801, 10923, 11125, 11396, 11720, 12077, 12434, 12753, 12979, 13042, 12905, 12608, 12242, 11895, 11617, 11427, 11329, 11322, 11384, 11484, 11595, 11709, 11824, 11939, 12056, 12176, 12287, 12360, 12354, 12234, 11992, 11667, 11328, 11044, 10854, 10774, 10801, },
/* LAT:  60 */ {  12318, 12393, 12546, 12766, 13039, 13341, 13646, 13914, 14092, 14120, 13984, 13733, 13442, 13169, 12947, 12788, 12694, 12660, 12673, 12719, 12785, 12868, 12972, 13103, 13260, 13435, 13599, 13710, 13720, 13604, 13382, 13103, 12824, 12586, 12416, 12325, 12318, },
/* LAT:  70 */ {  13759, 13804, 13902, 14047, 14229, 14435, 14646, 14828, 14932, 14910, 14769, 14564, 14344, 14139, 13964, 13828, 13733, 13677, 13656, 13668, 13708, 13779, 13881, 14015, 14181, 14367, 14551, 14693, 14743, 14674, 14515, 14316, 14122, 13956, 13837, 13770, 13759, },
/* LAT:  80 */ {  15003, 15018, 15057, 15119, 15198, 15286, 15366, 15411, 15388, 15303, 15187, 15060, 14936, 14821, 14721, 14638, 14575, 14534, 14515, 14518, 14544, 14592, 14663, 14755, 14866, 14992, 15126, 15258, 15365, 15411, 15376, 15293, 15200, 15117, 15054, 15015, 15003, },
/* LAT:  90 */ {  15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.1616,
static constexpr const int16_t strength_table[19][37] {
//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
/* LAT: -90 */ {  5460, 5460, 5460, 5460, 5460, 5460, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, },
/* LAT: -80 */ {  6066, 6003, 5925, 5834, 5731, 5620, 5502, 5381, 5258, 5139, 5024, 4919, 4825, 4745, 4681, 4636, 4611, 4608, 4629, 4674, 4744, 4837, 4951, 5082, 5225, 5375, 5524, 5668, 5799, 5913, 6005, 6075, 6120, 6140, 6136, 6111, 6066, },
/* LAT: -70 */ {  6310, 6179, 6030, 5866, 5689, 5497, 5292, 5077, 4858, 4643, 4439, 4256, 4098, 3966, 3862, 3784, 3737, 3724, 3751, 3826, 3952, 4131, 4358, 4624, 4918, 5225, 5528, 5812, 6062, 6267, 6419, 6515, 6558, 6551, 6503, 6420, 6310, },
/* LAT: -60 */ {  6195, 6005, 5805, 5597, 5380, 5146, 4890, 4611, 4319, 4029, 3761, 3532, 3351, 3216, 3116, 3043, 2992, 2972, 2997, 3085, 3251, 3500, 3824, 4208, 4629, 5063, 5484, 5868, 6194, 6444, 6608, 6689, 6692, 6630, 6518, 6369, 6195, },
/* LAT: -50 */ {  5850, 5622, 5392, 5163, 4931, 4687, 4417, 4114, 3786, 3453, 3150, 2908, 2745, 2652, 2604, 2570, 2538, 2513, 2517, 2587, 2757, 3042, 3434, 3902, 4408, 4914, 5390, 5810, 6150, 6393, 6533, 6575, 6534, 6425, 6265, 6069, 5850, },
/* LAT: -40 */ {  5398, 5154, 4910, 4672, 4439, 4202, 3948, 3665, 3351, 3024, 2725, 2500, 2380, 2353, 2373, 2396, 2402, 2392, 2381, 2408, 2533, 2801, 3212, 3722, 4268, 4793, 5263, 5653, 5947, 6136, 6225, 6230, 6161, 6032, 5852, 5635, 5398, },
/* LAT: -30 */ {  4881, 4642, 4405, 4172, 3946, 3728, 3510, 3279, 3024, 2748, 2490, 2305, 2232, 2255, 2322, 2394, 2461, 2514, 2539, 2552, 2615, 2806, 3159, 3641, 4171, 4671, 5093, 5413, 5619, 5719, 5747, 5720, 5642, 5511, 5332, 5117, 4881, },
/* LAT: -20 */ {  4323, 4112, 3905, 3701, 3506, 3323, 3155, 2992, 2816, 2619, 2428, 2292, 2247, 2287, 2375, 2485, 2614, 2745, 2838, 2877, 2901, 2990, 3221, 3598, 4046, 4474, 4826, 5066, 5174, 5183, 5153, 5106, 5023, 4896, 4730, 4534, 4323, },
/* LAT: -10 */ {  3791, 3632, 3481, 3335, 3200, 3080, 2977, 2886, 2791, 2678, 2556, 2455, 2406, 2425, 2508, 2636, 2792, 2953, 3081, 3147, 3162, 3186, 3302, 3548, 3871, 4192, 4460, 4627, 4665, 4614, 4546, 4482, 4393, 4268, 4120, 3957, 3791, },
/* LAT:   0 */ {  3412, 3321, 3238, 3166, 3111, 3074, 3049, 3032, 3010, 2964, 2885, 2790, 2706, 2670, 2707, 2808, 2940, 3076, 3194, 3271, 3304, 3325, 3396, 3548, 3754, 3967, 4148, 4257, 4266, 4200, 4112, 4019, 3906, 3775, 3642, 3519, 3412, },
/* LAT:  10 */ {  3283, 3253, 3234, 3231, 3257, 3305, 3362, 3418, 3456, 3447, 3379, 3264, 3135, 3036, 3005, 3042, 3122, 3220, 3321, 3407, 3471, 3532, 3618, 3734, 3867, 4004, 4123, 4196, 4200, 4140, 4031, 3888, 3727, 3568, 3433, 3338, 3283, },
/* LAT:  20 */ {  3400, 3404, 3432, 3488, 3581, 3704, 3834, 3954, 4037, 4050, 3977, 3835, 3666, 3522, 3442, 3426, 3459, 3530, 3625, 3722, 3812, 3909, 4019, 4130, 4237, 4346, 4447, 4514, 4527, 4470, 4335, 4134, 3908, 3699, 3537, 3437, 3400, },
/* LAT:  30 */ {  3723, 3733, 3790, 3891, 4036, 4209, 4386, 4544, 4653, 4681, 4608, 4452, 4260, 4092, 3982, 3933, 3934, 3982, 4067, 4164, 4260, 4364, 4480, 4598, 4716, 4841, 4960, 5047, 5075, 5020, 4866, 4628, 4355, 4101, 3903, 3776, 3723, },
/* LAT:  40 */ {  4223, 4224, 4293, 4419, 4588, 4777, 4961, 5119, 5224, 5250, 5181, 5031, 4841, 4663, 4532, 4453, 4425, 4444, 4502, 4580, 4665, 4761, 4875, 5009, 5159, 5319, 5470, 5581, 5622, 5571, 5417, 5181, 4907, 4647, 4437, 4293, 4223, },
/* LAT:  50 */ {  4831, 4828, 4888, 5001, 5150, 5310, 5461, 5581, 5654, 5662, 5598, 5469, 5304, 5138, 4998, 4898, 4841, 4827, 4850, 4898, 4966, 5056, 5174, 5324, 5499, 5682, 5849, 5969, 6016, 5974, 5845, 5649, 5423, 5206, 5027, 4899, 4831, },
/* LAT:  60 */ {  5392, 5384, 5416, 5482, 5570, 5664, 5751, 5816, 5847, 5837, 5781, 5685, 5563, 5433, 5312, 5214, 5146, 5111, 5107, 5134, 5189, 5275, 5392, 5538, 5704, 5873, 6022, 6128, 6174, 6154, 6071, 5944, 5797, 5653, 5531, 5442, 5392, },
/* LAT:  70 */ {  5726, 5709, 5709, 5723, 5747, 5773, 5796, 5810, 5808, 5787, 5746, 5687, 5615, 5538, 5463, 5398, 5349, 5320, 5315, 5334, 5378, 5447, 5538, 5646, 5764, 5879, 5979, 6053, 6093, 6097, 6068, 6014, 5947, 5876, 5812, 5761, 5726, },
/* LAT:  80 */ {  5789, 5772, 5759, 5748, 5738, 5729, 5719, 5707, 5691, 5672, 5649, 5623, 5595, 5567, 5541, 5520, 5506, 5500, 5505, 5520, 5545, 5580, 5623, 5671, 5720, 5769, 5812, 5846, 5871, 5884, 5887, 5880, 5866, 5848, 5828, 5807, 5789, },
/* LAT:  90 */ {  5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, },
};
