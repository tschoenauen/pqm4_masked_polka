#include "keygen.h"
#include <stdlib.h>
#include <stdio.h>


const poly default_polka_key_a = {32768,39848,45083,34767,2812,29188,2090,9113,40601,32734,57107,1462,17887,23061,3123,43426,44893,54154,38624,12289,12129,26551,29211,30587,3434,41631,34279,14321,1784,18890,5599,14913,46283,55772,53896,33981,32706,17845,54126,50972,6367,38793,12705,9846,52944,14529,33766,23716,2861,11953,19838,18422,20359,10352,57295,3948,15662,8348,4144,20174,10574,43459,18482,48397,17174,38099,45030,8047,42416,41668,26713,5982,50929,31826,25712,41411,29330,41565,34146,29116,35837,34455,55370,8232,39721,37431,22893,18026,55402,13643,29189,42163,23592,18058,38089,6447,51267,17907,43170,21879,45279,47208,31537,54357,12073,21235,4167,41393,30955,11340,49303,29672,54592,35134,34445,46185,46184,44738,17210,2798,59370,58562,46650,13048,12924,17693,31105,50346,24356,47191,46333,10005,56504,38725,49369,20082,11487,6675,49366,36563,18778,24469,579,5166,32338,13242,2505,11196,56334,5046,58744,23862,25888,58489,28163,42054,34668,48741,33963,52417,29897,38799,6326,18993,30742,17685,20669,6654,20810,37732,15118,39760,24981,36408,24859,9478,13200,22921,40059,2245,30611,49238,15530,21721,37061,35238,15750,21336,15288,11812,37131,13662,1644,10517,28083,15945,34297,47231,57902,15257,51782,5925,32020,18086,1082,32900,18374,28456,42565,5113,4003,48974,11475,13846,42570,37237,12611,29630,28034,1021,51532,10815,15633,53977,40465,21112,28773,50802,32119,52718,25322,6618,36211,46952,2156,11109,17955,56944,36075,24299,28264,7724,1154,6556,28610,38839,30430,6857,47568,54421,47191,49609,37972,53575,25457,53156,46228,27535,40148,50634,52105,40899,24575,27563,26187,17514,56320,32607,2706,24872,18473,47343,22213,4477,18939,36530,35202,20585,45248,48499,46065,27937,36409,19293,1728,29789,35166,20091,26899,15285,15231,34451,49093,30280,14031,17968,21907,12678,31796,2831,2099,24719,26110,57631,57060,24381,8468,54445,30851,4697,45441,52407,11742,38681,1678,58221,8644,551,4917,2717,28325,14249,18076,22630,18738,25400,59338,30687,56705,18699,1119,30345,5644,7479,3948,18705,16523,15923,35475,30917,37288,25143,21674,45987,53542,51974,33278,26468,21744,45367,24404,30679,35540,49064,10454,35280,57622,32811,53204,33245,1513,26963,4281,5285,14931,19630,18322,39629,45894,28860,271,34433,22702,31765,52097,22251,48402,1953,3448,19513,4056,54376,21308,29562,48955,50261,16770,26649,32984,9659,5457,49909,28640,12978,35765,42204,40313,3331,20220,55592,6450,48858,28735,12545,52514,19457,8381,4574,11486,55825,24885,14257,16912,18769,4936,886,30483,35993,19292,24466,14466,13947,17397,16250,26177,6792,41018,59097,8217,21361,17429,34746,28309,8636,32689,31736,58492,11178,13538,26255,26865,16922,48105,22684,27055,32657,53721,10133,23553,32091,13474,3361,10169,58633,56776,15197,9453,31275,24794,11862,15085,58318,11271,51355,27024,38462,24160,24630,4723,12547,28340,53117,9512,6129,15235,20136,637,48515,56207,34642,22096,13035,47623,14995,51682,50824,57079,58795,41219,41670,58822,38335,10375,53592,55592,5623,10996,19301,27862,32650,50740,27990,52056,40782,48657,24280,56069,29508,8400,24380,29830,15926,39565,26670,56866,39360,26035,34396,33666,21840,29966,33102,51428,35710,58532,49981,26338,47408,22436,53756,30107,13624,17634,31457,19814,15688,7834,27596,23944,18197,46542,44628,45150,55339,48208,52106,46898,32550,54678,36427,34312,39424,39870,43308,42442,17962,33344,15071,51474,58987,34798,26350,28487,11839,1337,13232,11392,14543,36268,20445,24814,5042,35309,46653,21825,55551,32662,1625,20417,49436,31821,12111,629,26201,59276,9537,51176,5083,57998,23229,43207,45160,22438,57072,41544,4181,41618,37721,40184,46872,17100,3546,42363,47466,36998,55037,50622,6455,21300,37987,31055,51639,40999,1005,54353,45474,51471,47663,34737,41628,14446,33342,39050,9533,8134,55866,5575,5476,20219,53151,53247,24598,48516,24863,39374,5515,25777,42523,14362,44387,29533,1806,53456,4988,34192,55918,4936,25519,16418,20880,6699,44343,41467,4431,55545,27652,28255,48558,4021,13590,41978,33887,26540,50635,31863,9895,26950,39540,3971,59239,55198,56251,49417,50460,9690,10586,55094,54845,33982,35463,53700,41623,25293,38737,274,18744,11482,15087,42124,26574,51007,36058,58350,47561,20763,38901,24519,4792,32910,14440,12520,4674,19769,32112,32104,1061,33149,39416,32529,20399,57100,12076,3645,49230,10285,29981,13473,47871,56663,50552,11234,55626,54702,47703,40219,20685,12639,53793,46122,40281,20140,53535,54016,13550,24019,39888,6262,8858,10495,31925,44840,44382,17959,45454,19242,18169,4787,41042,37073,54951,12744,31530,30333,27240,45466,46205,48944,46697,41051,41474,612,37169,36020,18500,48591,45685,26008,42395,3053,34946,37368,41303,17774,50828,4915,23143,56198,44995,38296,124,34434,37779,14362,46966,48884,14071,37258,58420,45333,26649,38199,28751,57424,59033,8708,26562,52758,53119,49667,13749,52711,7753,55854,20747,42872,45144,40199,30875,54484,10293,34473,21565,16820,9261,39076,41266,55592,44460,32932,32100,13491,22185,43688,171,37105,52702,42704,44935,3186,44192,7695,45994,40991,12304,7965,7225,29071,6111,23288,18312,52869,34758,47505,49193,44060,21018,43472,23587,634,47327,58429,16304,3342,38407,31206,5458,18424,49923,24170,50074,6854,32025,22097,747,57147,55859,30110,25075,10551,55313,42972,28342,3306,8750,40464,33459,39974,31126,53486,53009,3197,25130,49379,11003,45183,52818,5171,14999,47869,166,54751,3654,43106,51424,16411,47466,37002,28958,32753,4561,55878,22896,25731,1199,23258,43215,10257,5449,28393,50472,56600,47077,44678,51422,54716,47642,37024,26286,16931,8106,52268,27249,36705,2036,51524,25780,43595,16337,37224,47707,25558,45911,43927,12373,32553,38993,45144,5029,53477,727,45216,10069,24103,18697,6594,19278,75,6328,25275,35492,1434,34836,1428,6406,40764,39413,17740,40906,14874,14666,11914,56490,47654,49773,22799,58230,29142,42130,30525,19605,18842,19870,16516,50719,34123,7054,7995,31060,39809,15381,13536,57428,34276,2335,28261,11864,10875,26172,29427,39575,43600,36400,44090,18353,23696,55857,70,43199,40119,53694,14750,37546,54849,48930,43345,26942,2017,4505,53950,53378,49552,30203,24039,16090,23848,46037,55385,21516,13344,29418,39065,29740,54496,28608};
const poly default_polka_key_b = {17852,8833,13094,25919,2309,22314,412,54639,14762,16066,17620,49964,42675,10191,6414,23541,45446,6681,38466,20501,19469,54758,52311,29369,41546,53526,48119,10839,35485,43000,5867,58931,5280,30886,49460,21548,36291,9207,11422,47265,11260,52523,22989,46806,35837,5099,25021,14221,10943,9301,56349,52859,21250,24277,6561,7659,44107,4239,49341,52840,53968,1107,30695,29528,12973,44612,14430,44370,43399,20826,18193,54785,49839,47055,35062,35475,49956,28652,7950,45566,28630,11529,3578,30029,19582,58689,18940,24983,22168,6471,31748,40361,20831,28118,38894,52447,16229,34311,57387,16294,19036,54046,36973,36195,44186,52157,29639,46544,44145,340,43071,48693,25185,29112,52251,35708,7402,28284,7676,42190,5036,43808,22949,9809,19981,13895,8822,29300,23056,46581,47600,19911,16695,26434,7299,54734,55576,39059,21786,21210,53877,28207,27670,57260,19339,43203,16175,46602,41599,37461,15928,9273,51603,49087,26070,17465,1812,12267,52924,29915,32683,25119,51866,24462,3560,16682,20371,34390,2911,1715,8296,41176,44716,19543,4666,25399,27712,47784,50748,46731,6117,6023,7367,18902,3599,25104,27928,4896,1370,31246,34079,34113,14360,4759,29397,42923,56644,34863,33897,42770,35415,28113,25066,18656,19658,8485,25727,39851,39416,51018,29332,18148,7287,2770,40811,23548,11375,39285,15586,14077,53876,30668,12373,33078,29805,27330,25056,14608,11187,58973,19370,49660,11261,20324,12660,18006,3263,25459,55274,54927,25041,10522,7114,34537,18790,24536,8914,52340,32021,28415,13705,4805,12786,27799,51284,40273,33759,18850,14131,40737,8148,5259,19884,16520,6847,35598,6644,2523,30324,41519,17037,57902,26854,44590,25724,50236,28376,48720,20472,29927,45147,26508,28511,55893,13265,9081,7543,9027,4447,7348,47750,7948,33578,49818,40509,23756,15177,29449,49884,36753,35083,43585,51530,30489,50715,7341,8954,3312,46654,37137,818,57015,18000,11655,39055,13887,18966,8124,34097,27357,5103,11404,22492,45443,36179,9219,13142,4275,21328,56060,44601,26902,18131,27221,25488,39707,32586,33325,23304,16397,5252,9318,19599,29750,215,36603,14551,44708,55479,29287,48010,28466,38850,9395,49927,1818,55389,41886,11226,21829,18703,11258,510,35857,21586,6605,13359,39258,6579,9141,43682,19136,20103,11520,24188,10672,55102,21176,50547,57093,37730,37016,37564,58789,32318,50536,23940,58957,57728,33840,53386,27769,37096,34090,33987,39426,41228,27894,48809,10605,31549,708,24177,56904,34786,53736,57675,54709,4575,41459,50843,40752,23830,5887,21944,33442,11665,1957,52854,32766,50871,28560,37879,44596,20216,50169,339,48381,46464,21627,41882,43974,47059,7006,12289,57129,49501,58681,20811,44121,54307,10186,30802,29139,56191,22212,56361,54369,8635,41616,22561,44505,1321,43674,57760,8086,16757,56643,36835,7841,45270,5450,19324,54793,41039,23196,10935,26178,26103,26729,41285,114,15805,40576,19355,41267,50863,44230,45840,42614,4168,29970,5999,8477,53060,29041,32720,32693,55510,5538,1107,49857,50212,20499,33255,32391,51126,41922,1854,10822,1765,54008,20846,28992,3998,13522,9407,25483,46307,32573,58868,50715,30810,32212,18876,27313,7183,20707,42773,24765,6285,2399,115,25378,9633,49953,38379,9155,42976,55867,39308,16536,59245,32646,40501,52555,22701,51760,16326,8527,25934,49411,7168,9350,26396,138,42394,13384,14686,17085,46075,38541,17013,53607,10177,4734,5508,23525,32340,15894,7466,7469,45036,13479,34888,35266,57089,54659,40971,8655,53097,35791,632,57056,8334,42562,11106,8701,45040,35694,33932,301,36615,23620,56554,10427,57086,28172,52434,8977,58205,33920,43983,26505,13105,13945,16557,40902,44393,58602,57292,28459,17168,1036,44870,8785,39561,33244,43594,51055,32023,14801,36192,19473,11060,12407,41128,30835,29278,53989,57040,40356,168,55975,27204,4306,27523,8812,51726,40967,12421,23380,39351,51833,28019,53225,29569,50873,24504,54481,10517,51283,43840,39265,4668,53575,16779,2698,34244,58537,47766,32007,1311,19038,2961,58578,6916,43343,33872,25823,54642,58907,11739,6378,10366,17757,398,14818,8813,32263,57185,12955,34234,25869,26735,42658,19158,34140,29002,48023,7461,8333,47726,18337,56174,58028,5277,5834,50353,268,22887,25477,21815,35925,27904,25464,22381,3529,38680,9293,40693,48782,44820,15054,31077,36848,14273,23038,50290,17224,29859,47129,1986,50218,19481,17347,57666,14629,10394,31059,18371,57318,17500,15521,41594,23483,45639,11864,2944,58905,25976,3255,10226,14971,45762,31950,50201,14297,19996,9037,6945,45052,46178,2991,773,56066,40501,6069,53877,9125,10551,19085,10130,38093,40742,45398,10663,12203,58316,4934,7084,20402,43087,29386,11681,47731,27079,219,58257,28350,56836,54074,29339,8200,35926,17603,12671,25071,34406,53183,46837,20302,21324,56534,39695,17945,3572,57682,7741,14175,50399,18288,49066,6195,9640,8164,7454,35469,8437,10999,46109,11286,39074,24930,4985,43996,5281,17981,8674,43788,51870,25855,30257,20461,39,23790,17205,36797,2393,25379,21860,39902,2373,29784,10301,40363,48981,26630,25290,42196,45079,21665,5653,43228,45833,19642,24920,6380,56362,21883,51171,28283,49379,4166,20147,40504,45275,44727,42758,707,28607,50397,25259,29106,30908,56448,5471,9481,56856,50102,49338,24901,13532,47162,47243,2362,30857,31494,53060,21503,16147,9378,25219,4885,30872,6561,278,51818,29421,33518,9262,3583,31371,51053,23613,11337,46406,25565,3861,48344,45264,4450,52662,484,29300,20869,54909,28575,25365,48923,51377,8623,50603,21775,9424,32710,56032,40145,12942,21844,22914,13867,30891,26020,57514,32069,35704,50615,7532,2996,20365,53162,37121,3335,33497,25352,47214,36156,22349,20151,10539,6355,57454,34858,46319,42864,53866,32137,56957,24803,23388,17840,51941,45125,30986,54363,37857,27856,58379,23199,12698,11878,22864,31669,13452,38023,8886,20027,23073,33897,2703,53276,51894,10920,44613,19712,25370,57067,44399,26110,19492,58545,13516,2026,57866,27979,51995,11474,51644,4867,31358,36561,58275,42675,34259,36821,32360,12555,22410,37866,23261,56432,30983,14362,40138,312,59257,53543,43550,28456,52613,27909,28779,11709,11293,11161,11029,7667,31307,51402,1163,13786,44710,14367,24590,18501,53128,48422,913,45755,56969,4250,4090,7268};
const poly default_polka_key_b_inv = {39433,26668,38370,23667,48461,17279,50625,44344,51065,42847,7712,24160,47195,12588,15390,48603,48975,1706,11970,46308,57609,27407,24287,59043,58762,57790,36164,25651,25765,41698,29380,55890,43698,42959,27627,3517,20214,58937,25128,50739,42678,29233,29911,28380,31301,5168,20073,38654,4045,15401,15390,41384,48276,13487,30062,51407,31258,51898,13062,466,20767,10822,48855,34980,27816,50557,47410,9722,6779,20876,57546,26942,44962,11310,20821,52806,17328,607,40122,34631,31419,45692,24966,606,40766,37803,10586,28334,15181,37810,3317,9936,4742,52770,28895,39885,372,42744,49138,52032,10211,18848,34003,43443,678,27582,11375,31828,40386,30322,12030,445,31636,50912,50658,13641,52583,24473,34609,52379,27618,25791,55331,40774,3977,57188,30151,56093,21487,36264,57824,54654,16252,6801,32445,24063,14467,15289,11429,11363,7763,38854,16274,30259,1725,24548,36106,842,58959,28806,1081,10600,36791,45974,25650,4486,25381,2404,39315,42579,11751,39873,59184,22651,14827,38055,20903,31527,19716,11038,10132,51694,31693,31783,51016,28241,16022,43723,51934,41946,52589,3018,58162,18880,43018,46223,35091,12438,20347,18833,18775,21160,19706,45876,3200,29172,31694,13463,2981,12266,47596,28755,54249,15007,33498,19562,6959,51077,25282,47903,34504,4002,58785,21272,43811,40890,58288,742,2711,19191,2324,29962,24971,28780,38711,10622,4537,34361,12262,50586,11616,19558,30268,14031,1000,12183,40076,44249,46211,46235,49573,8365,5354,39952,8960,10828,39523,35731,51932,44409,25505,38988,40729,58762,6873,28552,11756,11060,36196,51946,55038,6014,9360,28398,24324,20425,59196,16272,11497,8763,34450,34139,33343,26624,23459,16521,16197,53427,7363,48405,30483,4759,5992,54161,3630,55156,27899,36239,2733,45877,36450,20740,8940,7513,32182,54080,14473,18277,43736,32658,22356,2115,12058,31706,6869,23889,13243,34151,45537,35931,14193,7498,42645,23132,50242,17981,35670,32268,22663,30282,43118,36312,37710,30634,26561,45074,34486,42522,11831,15219,22738,44223,40298,33295,4541,21406,39335,51707,29941,37960,30147,55744,23176,10504,13205,20035,44667,20974,23164,52555,56573,29005,31513,14544,50122,42081,16547,59192,9422,29765,56047,25072,55632,48799,31593,40848,11196,27443,15451,16632,33083,6020,25869,49956,57642,17822,5786,13124,12563,27712,42410,33068,55190,49016,21716,54636,319,19553,43666,7480,40932,13559,44914,40610,9771,20820,39009,35154,12250,33320,48690,38413,40694,2667,33171,30188,33346,5114,56927,35982,15033,48301,49443,26788,1688,58339,45302,15862,21917,25547,47535,39208,47123,30124,51907,14269,8075,9396,25508,16315,55035,18638,24243,30875,50327,9542,12288,31373,49199,9852,21350,11151,3674,13008,17908,48895,8078,45297,41940,49735,16276,29482,12495,57510,45818,24659,33101,55615,32918,42502,44184,35838,34021,17515,12547,6840,21502,27778,9641,20607,7948,17181,53573,2050,53395,48393,17349,34426,10881,37172,22281,28546,9645,31108,43284,34111,25601,46641,47760,23552,27000,43765,3195,58534,57010,18619,34746,4813,46848,30903,19956,57299,2062,48984,5052,11349,13769,46595,39309,2477,51695,14846,29289,27706,25569,28319,2006,30174,12183,18974,6076,15198,25308,10154,57383,27898,33732,41573,24636,14222,14111,3083,17755,23504,22625,34382,22122,54111,35271,9510,1978,4470,39632,16025,46759,32826,12341,48331,25755,6177,30488,976,21649,34334,46904,41349,25139,44162,24099,972,41306,37370,8307,55757,34595,2479,46359,43315,37819,1858,45783,23378,4309,12537,9844,24149,3292,41206,53218,5875,10971,40195,33034,12707,37836,32112,41403,32452,3001,57464,19115,54913,52033,58100,32888,48681,1560,51714,1563,10233,38233,3629,52209,1738,23259,31707,36992,52069,30041,49095,7010,45460,41026,5429,11540,18470,38406,12978,24838,7794,56508,8972,14966,10777,4193,21054,15574,3525,6887,15927,38596,1052,37679,50456,44493,16954,11354,51889,59356,514,36899,45223,25298,45716,40127,52342,26492,12765,38414,43803,52366,278,53787,33300,19819,48507,15108,3760,23733,45480,46894,13520,49839,1959,46587,50051,32322,42877,2466,41275,53928,21392,52714,10148,3273,2188,32063,35419,31130,26419,44544,5602,56297,28813,9455,13546,15142,53358,43602,42831,41529,52740,34883,46266,39928,25607,31522,47637,840,13064,54508,21617,19135,1253,3838,53089,32923,52244,44912,23814,3344,24275,38522,54951,42593,28470,4860,19421,10115,58240,16919,24341,8679,39827,7353,48459,28004,21473,53994,21358,26967,39704,28586,31975,44692,29597,30359,33615,48575,49406,19581,4588,44819,44534,13364,25513,1392,48073,7709,23714,22950,26803,26138,40290,24649,22604,43746,8887,50081,51592,19001,37388,34922,56235,10883,50758,32703,42698,45765,47601,8807,31253,36315,8055,58601,33512,10160,31778,54884,41431,51742,11782,43565,55414,33357,8661,39553,37461,56114,49025,57182,57089,2421,37398,26746,8434,36643,10717,49474,36621,13770,56709,33041,34764,39509,16138,51032,13715,21707,23469,7504,48696,14889,12195,9000,56554,25445,49446,57760,143,46047,27253,2422,18479,57614,11061,40604,28922,59318,25886,291,35330,25506,17178,37758,39091,51388,54214,14260,11100,50646,18502,30719,1749,28924,48944,36685,32760,53879,33892,27156,42700,55088,1195,39924,1128,54291,1460,24603,42601,31239,19536,50380,53597,57453,7214,8713,11017,40838,29620,41575,27482,48891,24957,58385,46411,33865,23912,51788,16492,22822,12270,9471,3664,6779,6269,30429,9589,16062,14879,44189,39031,43709,25789,46700,56820,20004,21618,7445,10217,29495,55641,58386,26011,24069,7035,48819,22110,54838,12192,21193,23347,53677,4720,17510,44552,17952,46875,57638,42991,55651,41780,3384,18529,14969,4494,57639,32213,3836,39026,53906,15637,5613,23712,46727,2137,53482,4227,56696,29836,36372,52742,39926,47477,55591,55303,39850,32091,2888,20262,52279,42861,10693,27830,29044,28241,764,41768,51071,11429,8117,45878,27569,7666,19487,36701,45252,45427,43689,8324,40009,53842,30500,948,3251,21238,37519,24509,3470,44457,20245,11863,22994,55298,31973,30782,46666,12970,41517,46703,40585,15090,33922,37807,4876,20389,52085,31388,52631,18105,51419,33448,11660,36646,4809,49552,29295,20654,26611,47271,38090,32131,41215,8445,3702,38358,56244,49145,43168,45806,47500,25463,27136,27454};
const poly default_polka_key_s = {0,0,0,59392,1,1,1,0,1,59392,0,0,1,0,1,59392,59392,59392,1,59392,59392,1,0,0,59392,59392,1,1,1,59392,0,1,1,59392,1,59392,1,1,0,0,59392,0,0,59392,1,0,59392,59392,59392,0,0,0,1,1,0,0,0,1,59392,1,59392,1,59392,1,59392,0,0,59392,59392,59392,1,0,59392,59392,1,0,59392,59392,59392,0,1,0,59392,0,1,0,59392,0,59392,0,1,1,1,59392,1,1,59392,0,59392,0,0,0,1,59392,1,1,59392,0,59392,0,0,1,1,1,0,59392,1,59392,59392,0,1,0,0,59392,0,59392,1,0,59392,59392,59392,59392,1,1,59392,0,59392,59392,59392,0,0,0,1,59392,1,59392,1,1,0,1,59392,1,0,0,0,1,0,1,59392,1,0,59392,1,59392,59392,0,1,0,0,59392,1,59392,0,1,0,0,0,59392,59392,1,59392,1,1,0,59392,0,59392,0,0,1,1,1,1,0,1,0,1,59392,1,1,1,59392,0,0,0,1,0,0,0,1,0,0,1,0,59392,0,0,59392,59392,1,0,59392,1,59392,0,0,0,0,1,0,59392,59392,0,59392,0,59392,1,59392,0,0,0,59392,0,0,0,59392,0,1,0,0,0,59392,1,59392,1,0,1,0,1,0,0,59392,1,0,1,0,0,59392,0,0,0,0,0,1,59392,0,59392,59392,59392,1,1,0,0,1,1,1,1,1,59392,59392,59392,1,59392,1,59392,59392,59392,1,0,1,0,1,0,0,0,0,0,59392,0,0,0,0,1,59392,1,1,1,59392,0,59392,59392,59392,1,1,0,1,59392,0,1,1,1,59392,1,59392,59392,0,59392,59392,0,0,1,1,59392,0,1,0,0,59392,0,0,59392,0,0,59392,59392,59392,59392,59392,0,59392,0,59392,59392,0,1,0,59392,0,59392,1,0,0,1,1,59392,59392,1,0,1,0,0,0,59392,0,0,0,1,0,0,59392,1,0,1,0,59392,1,1,1,59392,0,59392,0,0,0,59392,0,59392,1,1,59392,0,59392,1,1,59392,59392,0,0,1,59392,1,0,59392,59392,59392,1,1,1,0,0,0,59392,59392,1,0,0,1,0,0,59392,0,59392,0,0,1,1,0,1,59392,0,0,0,1,59392,1,1,1,0,0,59392,0,59392,59392,0,0,0,59392,1,1,0,0,59392,0,1,59392,0,1,0,59392,1,59392,0,59392,0,59392,59392,0,59392,0,0,1,59392,1,1,1,0,0,59392,59392,0,0,0,1,0,59392,0,1,59392,0,0,1,59392,1,1,1,1,1,59392,59392,1,1,0,59392,1,0,1,59392,1,0,0,1,0,1,1,0,59392,0,0,0,1,0,59392,0,59392,0,1,0,1,0,1,1,0,0,0,0,0,0,59392,0,0,0,0,1,59392,0,59392,59392,59392,0,0,1,0,0,59392,59392,59392,1,1,0,1,59392,0,0,0,59392,1,59392,0,0,0,0,59392,1,59392,0,59392,1,59392,1,0,1,1,1,1,0,59392,59392,1,59392,0,0,59392,1,59392,1,0,0,59392,1,0,0,0,0,1,1,0,59392,1,59392,59392,1,1,59392,1,1,0,1,59392,0,0,59392,59392,0,59392,59392,0,0,59392,59392,0,59392,59392,59392,1,1,1,1,59392,0,0,0,0,0,0,59392,59392,1,0,59392,1,1,1,1,59392,1,1,1,1,1,1,1,1,59392,0,1,0,59392,59392,59392,59392,1,1,1,1,0,0,0,59392,1,59392,1,1,0,59392,59392,59392,1,0,1,59392,1,0,0,59392,0,59392,1,59392,0,1,59392,1,1,1,1,59392,1,59392,59392,1,59392,59392,0,1,59392,59392,59392,1,0,59392,59392,59392,0,59392,59392,1,0,0,1,59392,0,1,0,1,0,59392,0,0,0,0,59392,59392,59392,1,0,0,0,0,1,0,59392,59392,59392,0,59392,1,59392,1,1,0,0,0,1,0,0,59392,0,59392,1,1,59392,59392,0,1,1,0,1,0,1,59392,59392,59392,0,1,0,0,59392,1,0,59392,59392,59392,59392,1,59392,1,1,59392,59392,59392,1,0,1,0,59392,0,1,59392,1,1,1,59392,1,1,0,59392,1,0,1,59392,0,0,1,59392,1,1,0,0,59392,0,59392,1,59392,59392,1,59392,0,1,1,59392,0,1,59392,1,59392,0,0,0,1,59392,59392,0,59392,59392,0,59392,1,59392,59392,59392,0,1,0,1,0,1,59392,0,0,0,59392,0,1,59392,0,59392,0,59392,59392,0,59392,0,0,59392,1,1,1,59392,0,1,1,0,1,59392,59392,59392,59392,0,59392,59392,0,1,1,59392,0,0,0,59392,0,59392,59392,0,1,0,59392,59392,1,59392,0,0,59392,1,1,1,1,59392,59392,0,1,0,59392,0,0,0,1,59392,0,1,59392,1,1,0,59392,1,59392,0,59392,1,0,59392,0,0,1,1,59392,59392,59392,59392,0,1,59392,0,1,1,59392,59392,59392,59392,59392,1,1,1,0,59392,1,1,0,59392,0,59392,59392,1,0,0,1,59392,59392,59392,0,0,0,59392,0,0,59392,0,1,59392,1,0,1,59392,0,0};


int keygen(plk_sk* sk, plk_pk* pk){
    /*
    //Code used to read a key from a file storing coefficients on 16bits.
    //As file reading is not possible on the Cortex-M4, we read hardcoded
    //values from above.
    FILE* key_file = fopen("key_0","r");
    if(key_file == NULL){
        printf("ERROR : Unable to open ressource file");
        return 1;
    
    //The key file stores data on 16bits, the buffers reads them as such and then we cast the values on c_int.
	
    uint32_t buf[N];
    fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->a[i] = buf[i];

    fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->b[i] = buf[i];
    
    fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) pk->b_inv[i] = buf[i];
    
    fread(buf, sizeof(uint32_t), N, key_file);
    for(int i = 0; i < N; i++) sk->s[i] = buf[i];

    sk->pk = pk;
    fclose(key_file);
    }*/

    for(int i = 0; i < N; i++) pk->a[i] = default_polka_key_a[i];

    for(int i = 0; i < N; i++) pk->b[i] = default_polka_key_b[i];

    for(int i = 0; i < N; i++) pk->b_inv[i] = default_polka_key_b_inv[i];

    for(int i = 0; i < N; i++) sk->s[i] = default_polka_key_s[i];

    sk->pk = pk;


    return 0;
}
