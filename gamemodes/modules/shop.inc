#include <YSI\y_hooks>
new PlayerText:Shop_TXD[MAX_PLAYERS][50];
new ShopSize[3];

#define 		PAGINATOR		21

enum ShopInfo
{
	id,
	page,
	status
};

new Shop_Status[MAX_PLAYERS][ShopInfo];

enum Shop_List
{
	id,
	item,
	price,
	Float:shopX,
	Float:shopY,
	Float:shopZ,
	Float:shopZoom
};

new Shop[][Shop_List] = 
{
	{1,1,150},
	{1,2,150},
	{1,3,150},
	{1,4,150},
	{1,5,150},
	{1,6,150},
	{1,7,150},
	{1,8,150},
	{1,15,150},
	{1,16,150},
	{1,17,150},
	{1,18,150},
	{1,19,150},
	{1,20,150},
	{1,21,150},
	{1,22,150},
	{1,23,150},
	{1,24,150},
	{1,25,150},
	{1,26,150},
	{1,27,150},
	{1,28,150},
	{1,29,150},
	{1,30,150},
	{1,32,150},
	{1,33,150},
	{1,34,150},
	{1,35,150},
	{1,36,150},
	{1,37,150},
	{1,38,150},
	{1,42,150},
	{1,43,150},
	{1,44,150},
	{1,45,150},
	{1,46,150},
	{1,47,150},
	{1,48,150},
	{1,49,150},
	{1,50,150},
	{1,51,150},
	{1,52,150},
	{1,57,150},
	{1,58,150},
	{1,59,150},
	{1,60,150},
	{1,61,150},
	{1,62,150},
	{1,66,150},
	{1,67,150},
	{1,68,150},
	{1,70,150},
	{1,71,150},
	{1,72,150},
	{1,73,150},
	{1,78,150},
	{1,79,150},
	{1,80,150},
	{1,81,150},
	{1,82,150},
	{1,83,150},
	{1,84,150},
	{1,86,150},
	{1,94,150},
	{1,95,150},
	{1,96,150},
	{1,97,150},
	{1,98,150},
	{1,99,150},
	{1,100,150},
	{1,101,150},
	{1,102,150},
	{1,103,150},
	{1,104,150},
	{1,105,150},
	{1,106,150},
	{1,107,150},
	{1,108,150},
	{1,109,150},
	{1,110,150},
	{1,111,150},
	{1,112,150},
	{1,113,150},
	{1,114,150},
	{1,115,150},
	{1,116,150},
	{1,117,150},
	{1,118,150},
	{1,119,150},
	{1,120,150},
	{1,121,150},
	{1,122,150},
	{1,123,150},
	{1,124,150},
	{1,125,150},
	{1,126,150},
	{1,127,150},
	{1,128,150},
	{1,132,150},
	{1,133,150},
	{1,134,150},
	{1,135,150},
	{1,136,150},
	{1,137,150},
	{1,142,150},
	{1,143,150},
	{1,144,150},
	{1,146,150},
	{1,147,150},
	{1,149,150},
	{1,153,150},
	{1,154,150},
	{1,155,150},
	{1,156,150},
	{1,158,150},
	{1,159,150},
	{1,160,150},
	{1,161,150},
	{1,162,150},
	{1,163,150},
	{1,164,150},
	{1,165,150},
	{1,166,150},
	{1,167,150},
	{1,168,150},
	{1,170,150},
	{1,171,150},
	{1,173,150},
	{1,175,150},
	{1,176,150},
	{1,177,150},
	{1,179,150},
	{1,180,150},
	{1,181,150},
	{1,182,150},
	{1,183,150},
	{1,184,150},
	{1,185,150},
	{1,186,150},
	{1,187,150},
	{1,188,150},
	{1,189,150},
	{1,200,150},
	{1,202,150},
	{1,203,150},
	{1,204,150},
	{1,206,150},
	{1,208,150},
	{1,209,150},
	{1,210,150},
	{1,212,150},
	{1,213,150},
	{1,217,150},
	{1,220,150},
	{1,222,150},
	{1,223,150},
	{1,227,150},
	{1,228,150},
	{1,229,150},
	{1,230,150},
	{1,234,150},
	{1,235,150},
	{1,236,150},
	{1,239,150},
	{1,240,150},
	{1,241,150},
	{1,242,150},
	{1,247,150},
	{1,248,150},
	{1,249,150},
	{1,250,150},
	{1,252,150},
	{1,253,150},
	{1,254,150},
	{1,255,150},
	{1,258,150},
	{1,259,150},
	{1,260,150},
	{1,261,150},
	{1,262,150},
	{1,264,150},
	{1,268,150},
	{1,269,150},
	{1,270,150},
	{1,271,150},
	{1,272,150},
	{1,273,150},
	{1,289,150},
	{1,290,150},
	{1,291,150},
	{1,292,150},
	{1,293,150},
	{1,294,150},
	{1,295,150},
	{1,296,150},
	{1,297,150},
	{1,299,150},
	{2,9,150},
	{2,10,150},
	{2,11,150},
	{2,12,150},
	{2,13,150},
	{2,31,150},
	{2,39,150},
	{2,40,150},
	{2,41,150},
	{2,53,150},
	{2,54,150},
	{2,55,150},
	{2,56,150},
	{2,63,150},
	{2,64,150},
	{2,65,150},
	{2,69,150},
	{2,75,150},
	{2,76,150},
	{2,77,150},
	{2,85,150},
	{2,87,150},
	{2,88,150},
	{2,89,150},
	{2,90,150},
	{2,91,150},
	{2,92,150},
	{2,93,150},
	{2,129,150},
	{2,130,150},
	{2,131,150},
	{2,138,150},
	{2,139,150},
	{2,140,150},
	{2,141,150},
	{2,145,150},
	{2,148,150},
	{2,150,150},
	{2,152,150},
	{2,157,150},
	{2,169,150},
	{2,172,150},
	{2,178,150},
	{2,190,150},
	{2,191,150},
	{2,192,150},
	{2,193,150},
	{2,194,150},
	{2,195,150},
	{2,196,150},
	{2,197,150},
	{2,198,150},
	{2,199,150},
	{2,201,150},
	{2,205,150},
	{2,207,150},
	{2,211,150},
	{2,214,150},
	{2,215,150},
	{2,216,150},
	{2,218,150},
	{2,219,150},
	{2,224,150},
	{2,225,150},
	{2,226,150},
	{2,231,150},
	{2,232,150},
	{2,233,150},
	{2,237,150},
	{2,238,150},
	{2,243,150},
	{2,244,150},
	{2,245,150},
	{2,246,150},
	{2,251,150},
	{2,256,150},
	{2,257,150},
	{2,263,150},
	{2,298,150},
	// Аксесуары (очки)
	{3, 19006, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19007, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19008, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19009, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19010, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19011, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19012, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19013, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19014, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19015, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19016, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19017, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19018, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19019, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19020, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19021, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19022, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19023, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19024, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19025, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19026, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19027, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19028, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19029, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19030, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19031, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19032, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19033, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19034, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19035, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19085, 70, 0.0, 0.0, 85.0, 0.5},
	{3, 19138, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19139, 70, 352.0, 350.0, 124.0, 0.6},
	{3, 19140, 70, 352.0, 350.0, 124.0, 0.6},
	//Кепки / Шляпы / Береты
	{3, 18636, 70, -20.0, 0.0, 120.0, 0.75},
	{3, 18639, 70, 90.0, 90.0, 90.0, 0.75},
	{3, 18921, 70, 90.0, 90.0, 90.0, 0.75},
	{3, 18922, 70, 90.0, 90.0, 90.0, 0.75},
	{3, 18923, 70, 90.0, 90.0, 90.0, 0.75},
	{3, 18924, 70, 90.0, 90.0, 90.0, 0.75},
	{3, 18925, 70, 90.0, 90.0, 90.0, 0.75},
	{3, 18926, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18927, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18928, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18929, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18930, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18931, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18932, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18933, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18934, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18935, 70, 80.0, 300.0, 90.0, 0.75},
	{3, 18939, 70, 90.0, 310.0, 90.0, 0.75},
	{3, 18940, 70, 90.0, 310.0, 90.0, 0.75},
	{3, 18941, 70, 90.0, 310.0, 90.0, 0.75},
	{3, 18942, 70, 90.0, 310.0, 90.0, 0.75},
	{3, 18943, 70, 90.0, 310.0, 90.0, 0.75},
	{3, 18944, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18945, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18946, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18947, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18948, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18949, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18950, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18951, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18953, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18954, 70, 0.0, 270.0, 0.0, 0.75},
	{3, 18955, 70, 0.0, 350.0, 245.0, 0.75},
	{3, 18956, 70, 0.0, 350.0, 245.0, 0.75},
	{3, 18957, 70, 0.0, 350.0, 245.0, 0.75},
	{3, 18958, 70, 0.0, 350.0, 245.0, 0.75},
	{3, 18959, 70, 0.0, 350.0, 245.0, 0.75},
	{3, 18960, 70, 0.0, 350.0, 245.0, 0.75},
	{3, 18961, 70, 335.0, 0.0, 45.0, 0.90},
	{3, 18962, 70, 0.0, 270.0, 25.0, 0.90},
	{3, 18964, 70, 300.0, 0.0, 90.0, 0.75},
	{3, 18965, 70, 300.0, 0.0, 90.0, 0.75},
	{3, 18966, 70, 300.0, 0.0, 90.0, 0.75},
	{3, 18967, 70, 0.0, 10.0, 0.0, 0.75},
	{3, 18968, 70, 0.0, 10.0, 0.0, 0.75},
	{3, 18969, 70, 0.0, 10.0, 0.0, 0.75},
	{3, 18970, 70, -20.0, 0.0, 90.0, 0.75},
	{3, 18971, 70, -20.0, 0.0, 90.0, 0.75},
	{3, 18972, 70, -20.0, 0.0, 90.0, 0.75},
	{3, 18973, 70, -20.0, 0.0, 90.0, 0.75},
	{3, 19095, 70, 95.0, 270.0, 110.0, 0.75},
	{3, 19096, 70, 95.0, 270.0, 110.0, 0.75},
	{3, 19097, 70, 95.0, 270.0, 110.0, 0.75},
	{3, 19098, 70, 95.0, 270.0, 110.0, 0.75},
	{3, 19099, 70, 95.0, 270.0, 110.0, 0.75},
	{3, 19100, 70, 95.0, 270.0, 110.0, 0.75},
	{3, 19161, 70, 95.0, 243.0, 100.0, 0.90},
	{3, 19162, 70, 95.0, 243.0, 100.0, 0.90},
	{3, 19488, 70, 325.0, 0.0, 90.0, 0.90},
	{3, 19553, 70, 90.0, 310.0, 90.0, 0.75},
	{3, 19554, 70, 90.0, 270.0, 90.0, 0.75},
	{3, 19558, 70, 80.0, 310.0, 90.0, 0.75},
	// Банданы
	{3, 18891, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18892, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18893, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18894, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18895, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18896, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18897, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18898, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18899, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18900, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18901, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18902, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18903, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18904, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18905, 70, 270.0, 50.0, 180.0, 0.90},
	{3, 18906, 70, 140.0, 0.0, 0.0, 0.90},
	{3, 18907, 70, 140.0, 0.0, 0.0, 0.90},
	{3, 18908, 70, 140.0, 0.0, 0.0, 0.90},
	{3, 18909, 70, 140.0, 0.0, 0.0, 0.90},
	{3, 18910, 70, 140.0, 0.0, 0.0, 0.90},
	{3, 18911, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18912, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18913, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18914, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18915, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18916, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18917, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18918, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18919, 70, 90.0, 150.0, 0.0, 0.90},
	{3, 18920, 70, 90.0, 150.0, 0.0, 0.90},
	//Часы
	{3, 19039, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19040, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19041, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19042, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19043, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19044, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19045, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19046, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19047, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19048, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19049, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19050, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19051, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19052, 70, 90.0, 110.0, 300.0, 0.60},
	{3, 19053, 70, 90.0, 110.0, 300.0, 0.60},
	
	// Шлемы
	{3,18976,70, 352.0, 360.0, 59.0, 0.8},
	{3,18977,70, 352.0, 360.0, 59.0, 0.8},
	{3,18978,70, 352.0, 360.0, 59.0, 0.8},
	{3,18979,70, 352.0, 360.0, 59.0, 0.8},
	{3,18936,70, 268.0, 136.0, 277.0, 0.8},
	{3,18937,70, 268.0, 136.0, 277.0, 0.8},
	{3,18938,70, 268.0, 136.0, 277.0, 0.8},
	// Рюкзаки
	{3,1210,70, 178.0, 179.0, 311.0, 0.8},
	{3,19624,70, 153.0, 179.0, 122.0, 0.8},
	{3,1310,70, 163.0, 181.0, 134.0, 0.8},
	{3,371,70, 199.0, 184.0, 196.0, 1.5},
	{3,2919,70, 321.0, 360.0, 132.0, 1.0},
	{3,11745,70, 321.0, 360.0, 132.0, 1.0},
	{3,19559,70, 0.0, 0.0, 132.0, 1.0},
	{3,3026,70, 0.0, 180.0, 180.0, 0.8},	
	// Разное
	{3,2114,70, 0.0, 180.0, 180.0, 1.0},
	{3,18640,70, 355.0, 39.0, 201.0, 0.8},
	{3,19878,70, 313.0, 39.0, 201.0, 0.8},
	{3,19077,70, 301.0, 217.0, 3.0, 0.8},
	{3,18975,70, 301.0, 217.0, 3.0, 0.8},
	{3,19351,70, 234.0, 88.0, 256.0, 1.0},
	{3,19350,70, 98.0, 93.0, 181.0, 1.0},
	{3,19555,70, 171.0, 171.0, 231.0, 0.8},
	{3,19556,70, 174.0, 194.0, 311.0, 0.8},
	{3,18952,70, 0.0, 270.0, 0.0, 0.8},
	{3,19136,70, 0.0, 270.0, 0.0, 0.8},
	// наушники
	{3,19422,70, 107.0, 330.0, 0.0, 1.41},
	{3,19423,70, 107.0, 330.0, 0.0, 1.41},
	{3,19424,70, 107.0, 330.0, 0.0, 1.41},
	{3,19421,70, 107.0, 330.0, 0.0, 1.41},
	// Распиратор
	{3,19472,70},
	//Гитары
	{3,19317,70},
	{3,19318,70}
	
};


new ShopList[100][1000];


stock TXDHideAll(playerid)
{
	Shop_Status[playerid][status] = 0;
	Shop_Status[playerid][page] = 0;
	Shop_Status[playerid][id] = 0;
	for(new i = 0; i <= 49; i++)
		PlayerTextDrawHide(playerid,Shop_TXD[playerid][i]);
	

}

stock TXDHideSlot(playerid)
{
	for(new i = 1; i <= 21; i++)
	{
		PlayerTextDrawHide(playerid,Shop_TXD[playerid][i]);
		PlayerTextDrawHide(playerid,Shop_TXD[playerid][i+26]);
	}
	
	PlayerTextDrawHide(playerid,Shop_TXD[playerid][26]);
	PlayerTextDrawHide(playerid,Shop_TXD[playerid][24]);
	PlayerTextDrawHide(playerid,Shop_TXD[playerid][25]);
}


stock ShopMenu(playerid, cur_page, shopid)
{	
	
	SelectTextDraw(playerid, 0x87cefaFF);
	
	
	if(!Shop_Status[playerid][status])
	{
		for(new i = 0; i <= 48; i++)
			PlayerTextDrawShow(playerid,Shop_TXD[playerid][i]);
			
		Shop_Status[playerid][status] = 1;
	}
	
			
	new max_page;
	SendClientMessageEx(playerid, COLOR_GREEN, "%d %d", ShopSize[shopid], shopid);
	for(new i; i < ShopSize[shopid]; i+=PAGINATOR)
		max_page++;
	
		
	TXDHideSlot(playerid);
		
		
	if(max_page <= cur_page)
		cur_page = max_page-1;
	
	if(cur_page < 0)
		cur_page = 0;
	
	Shop_Status[playerid][page] = cur_page;
	Shop_Status[playerid][id] = shopid;
	
	// пагинация
	if(cur_page > 0) 
		PlayerTextDrawShow(playerid,Shop_TXD[playerid][25]);
	
	if(cur_page+1 < max_page)
		PlayerTextDrawShow(playerid,Shop_TXD[playerid][24]);
	
	new str[32];
	format(str, 30, "%d/%d", cur_page+1, max_page);
	PlayerTextDrawSetString(playerid,Shop_TXD[playerid][26], str);
	PlayerTextDrawShow(playerid,Shop_TXD[playerid][26]);
	
	
	new max_item;
	if(PAGINATOR*cur_page+PAGINATOR > ShopSize[shopid])
		max_item = ShopSize[shopid];
	else
		max_item = PAGINATOR*cur_page+PAGINATOR;
		
	new txdid = 1, Float:attX = 0.000000, Float:attY = 0.000000, Float:attZ = 21.000000, Float:attZoom = 0.907194;
	
	for(new i = PAGINATOR*cur_page; i < max_item; i++)
	{
		new shopmoney[32];
		format(shopmoney, 30, "$%d", Shop[ShopList[shopid][i]][price]);
		
		
		if(Shop[ShopList[shopid][i]][shopX] ||  Shop[ShopList[shopid][i]][shopY] || Shop[ShopList[shopid][i]][shopZ] || Shop[ShopList[shopid][i]][shopZoom])
		{
			attX = Shop[ShopList[shopid][i]][shopX];
			attY = Shop[ShopList[shopid][i]][shopY];
			attZ = Shop[ShopList[shopid][i]][shopZ];
			attZoom = Shop[ShopList[shopid][i]][shopZoom];
		}

		
		PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][txdid], attX, attY, attZ, attZoom);
		PlayerTextDrawSetString(playerid,Shop_TXD[playerid][txdid+26], shopmoney);
		PlayerTextDrawShow(playerid,Shop_TXD[playerid][txdid+26]);
		
		PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][txdid], Shop[ShopList[shopid][i]][item]);
		PlayerTextDrawShow(playerid,Shop_TXD[playerid][txdid]);
		
		txdid++;
	}
	
	return 1;
}


stock ShopTXD(playerid)
{
	Shop_TXD[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, 137.615051, "box");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][0], 0.000000, 18.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][0], 0.000000, 290.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][0], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, Shop_TXD[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, Shop_TXD[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][0], 255);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][0], 0);

	Shop_TXD[playerid][1] = CreatePlayerTextDraw(playerid, 177.000000, 140.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][1], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][1], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][1], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][1], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][1], 1);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][1], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][2] = CreatePlayerTextDraw(playerid, 218.000000, 140.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][2], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][2], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][2], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][2], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][2], 2);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][2], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][3] = CreatePlayerTextDraw(playerid, 259.000000, 140.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][3], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][3], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][3], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][3], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][3], 3);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][3], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][4] = CreatePlayerTextDraw(playerid, 300.000000, 140.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][4], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][4], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][4], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][4], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][4], 4);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][4], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][5] = CreatePlayerTextDraw(playerid, 341.000000, 140.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][5], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][5], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][5], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][5], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][5], 5);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][5], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][6] = CreatePlayerTextDraw(playerid, 382.000000, 140.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][6], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][6], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][6], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][6], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][6], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][6], 6);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][6], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][7] = CreatePlayerTextDraw(playerid, 423.000000, 140.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][7], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][7], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][7], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][7], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][7], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][7], 7);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][7], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][8] = CreatePlayerTextDraw(playerid, 177.000000, 186.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][8], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][8], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][8], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][8], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][8], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][8], 8);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][8], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][9] = CreatePlayerTextDraw(playerid, 218.000000, 186.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][9], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][9], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][9], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][9], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][9], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][9], 9);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][9], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][10] = CreatePlayerTextDraw(playerid, 259.000000, 186.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][10], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][10], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][10], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][10], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][10], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][10], 10);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][10], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][11] = CreatePlayerTextDraw(playerid, 300.000000, 186.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][11], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][11], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][11], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][11], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][11], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][11], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][11], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][11], 11);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][11], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][12] = CreatePlayerTextDraw(playerid, 341.000000, 186.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][12], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][12], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][12], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][12], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][12], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][12], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][12], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][12], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][12], 12);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][12], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][13] = CreatePlayerTextDraw(playerid, 382.000000, 186.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][13], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][13], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][13], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][13], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][13], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][13], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][13], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][13], 13);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][13], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][14] = CreatePlayerTextDraw(playerid, 423.000000, 186.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][14], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][14], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][14], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][14], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][14], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][14], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][14], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][14], 14);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][14], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][15] = CreatePlayerTextDraw(playerid, 177.000000, 232.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][15], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][15], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][15], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][15], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][15], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][15], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][15], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][15], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][15], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][15], 15);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][15], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][16] = CreatePlayerTextDraw(playerid, 218.000000, 232.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][16], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][16], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][16], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][16], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][16], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][16], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][16], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][16], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][16], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][16], 16);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][16], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][17] = CreatePlayerTextDraw(playerid, 259.000000, 232.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][17], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][17], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][17], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][17], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][17], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][17], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][17], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][17], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][17], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][17], 17);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][17], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][18] = CreatePlayerTextDraw(playerid, 300.000000, 232.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][18], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][18], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][18], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][18], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][18], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][18], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][18], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][18], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][18], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][18], 18);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][18], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][19] = CreatePlayerTextDraw(playerid, 341.000000, 232.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][19], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][19], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][19], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][19], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][19], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][19], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][19], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][19], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][19], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][19], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][19], 19);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][19], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][20] = CreatePlayerTextDraw(playerid, 382.000000, 232.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][20], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][20], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][20], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][20], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][20], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][20], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][20], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][20], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][20], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][20], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][20], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][20], 20);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][20], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][21] = CreatePlayerTextDraw(playerid, 423.000000, 232.000000, "");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][21], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][21], 40.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][21], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][21], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][21], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][21], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][21], -2139062172);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][21], 5);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][21], 0);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][21], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][21], true);
	PlayerTextDrawSetPreviewModel(playerid, Shop_TXD[playerid][21], 21);
	PlayerTextDrawSetPreviewRot(playerid, Shop_TXD[playerid][21], 0.000000, 0.000000, 21.000000, 0.907194);

	Shop_TXD[playerid][22] = CreatePlayerTextDraw(playerid, 320.000000, 114.385322, "box");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][22], 0.000000, 2.000000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][22], 0.000000, 290.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][22], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][22], -1);
	PlayerTextDrawUseBox(playerid, Shop_TXD[playerid][22], 1);
	PlayerTextDrawBoxColor(playerid, Shop_TXD[playerid][22], 1535377151);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][22], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][22], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][22], 255);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][22], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][22], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][22], 0);

	Shop_TXD[playerid][23] = CreatePlayerTextDraw(playerid, 178.000000, 115.414817, "Clothes Shop");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][23], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][23], 1);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][23], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][23], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][23], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][23], 255);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][23], 0);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][23], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][23], 0);

	Shop_TXD[playerid][24] = CreatePlayerTextDraw(playerid, 442.333251, 284.000000, "NEXT");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][24], 0.300000, 1.200000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][24], 12.000000, 38.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][24], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][24], -1);
	PlayerTextDrawUseBox(playerid, Shop_TXD[playerid][24], 1);
	PlayerTextDrawBoxColor(playerid, Shop_TXD[playerid][24], -2139062172);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][24], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][24], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][24], 255);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][24], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][24], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][24], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][24], true);

	Shop_TXD[playerid][25] = CreatePlayerTextDraw(playerid, 400.000000, 284.000000, "PREV");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][25], 0.300000, 1.200000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][25], 12.000000, 38.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][25], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][25], -1);
	PlayerTextDrawUseBox(playerid, Shop_TXD[playerid][25], 1);
	PlayerTextDrawBoxColor(playerid, Shop_TXD[playerid][25], -2139062172);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][25], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][25], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][25], 255);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][25], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][25], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][25], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][25], true);

	Shop_TXD[playerid][26] = CreatePlayerTextDraw(playerid, 320.000000, 284.000000, "1/5");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][26], 0.300000, 1.200000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][26], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][26], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][26], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][26], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][26], 255);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][26], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][26], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][26], 0);

	Shop_TXD[playerid][27] = CreatePlayerTextDraw(playerid, 197.000000, 177.000000, "$1");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][27], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][27], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][27], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][27], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][27], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][27], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][27], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][27], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][27], 0);

	Shop_TXD[playerid][28] = CreatePlayerTextDraw(playerid, 238.000000, 177.000000, "$2");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][28], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][28], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][28], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][28], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][28], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][28], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][28], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][28], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][28], 0);

	Shop_TXD[playerid][29] = CreatePlayerTextDraw(playerid, 279.000000, 177.000000, "$3");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][29], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][29], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][29], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][29], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][29], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][29], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][29], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][29], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][29], 0);

	Shop_TXD[playerid][30] = CreatePlayerTextDraw(playerid, 320.000000, 177.000000, "$4");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][30], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][30], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][30], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][30], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][30], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][30], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][30], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][30], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][30], 0);

	Shop_TXD[playerid][31] = CreatePlayerTextDraw(playerid, 361.000000, 177.000000, "$5");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][31], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][31], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][31], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][31], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][31], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][31], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][31], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][31], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][31], 0);

	Shop_TXD[playerid][32] = CreatePlayerTextDraw(playerid, 402.000000, 177.000000, "$6");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][32], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][32], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][32], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][32], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][32], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][32], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][32], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][32], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][32], 0);

	Shop_TXD[playerid][33] = CreatePlayerTextDraw(playerid, 443.000000, 177.000000, "$7");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][33], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][33], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][33], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][33], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][33], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][33], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][33], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][33], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][33], 0);

	Shop_TXD[playerid][34] = CreatePlayerTextDraw(playerid, 197.000000, 223.000000, "$8");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][34], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][34], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][34], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][34], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][34], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][34], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][34], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][34], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][34], 0);

	Shop_TXD[playerid][35] = CreatePlayerTextDraw(playerid, 238.000000, 223.000000, "$9");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][35], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][35], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][35], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][35], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][35], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][35], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][35], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][35], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][35], 0);

	Shop_TXD[playerid][36] = CreatePlayerTextDraw(playerid, 279.000000, 223.000000, "$10");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][36], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][36], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][36], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][36], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][36], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][36], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][36], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][36], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][36], 0);

	Shop_TXD[playerid][37] = CreatePlayerTextDraw(playerid, 320.000000, 223.000000, "$11");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][37], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][37], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][37], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][37], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][37], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][37], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][37], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][37], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][37], 0);

	Shop_TXD[playerid][38] = CreatePlayerTextDraw(playerid, 361.000000, 223.000000, "$12");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][38], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][38], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][38], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][38], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][38], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][38], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][38], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][38], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][38], 0);

	Shop_TXD[playerid][39] = CreatePlayerTextDraw(playerid, 402.000000, 223.000000, "$13");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][39], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][39], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][39], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][39], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][39], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][39], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][39], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][39], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][39], 0);

	Shop_TXD[playerid][40] = CreatePlayerTextDraw(playerid, 443.000000, 223.000000, "$14");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][40], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][40], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][40], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][40], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][40], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][40], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][40], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][40], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][40], 0);

	Shop_TXD[playerid][41] = CreatePlayerTextDraw(playerid, 197.000000, 269.000000, "$15");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][41], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][41], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][41], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][41], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][41], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][41], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][41], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][41], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][41], 0);

	Shop_TXD[playerid][42] = CreatePlayerTextDraw(playerid, 238.000000, 269.000000, "$16");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][42], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][42], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][42], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][42], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][42], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][42], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][42], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][42], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][42], 0);

	Shop_TXD[playerid][43] = CreatePlayerTextDraw(playerid, 279.000000, 269.000000, "$17");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][43], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][43], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][43], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][43], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][43], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][43], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][43], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][43], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][43], 0);

	Shop_TXD[playerid][44] = CreatePlayerTextDraw(playerid, 320.000000, 269.000000, "$18");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][44], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][44], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][44], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][44], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][44], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][44], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][44], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][44], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][44], 0);

	Shop_TXD[playerid][45] = CreatePlayerTextDraw(playerid, 361.000000, 269.000000, "$19");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][45], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][45], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][45], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][45], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][45], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][45], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][45], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][45], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][45], 0);

	Shop_TXD[playerid][46] = CreatePlayerTextDraw(playerid, 402.000000, 269.000000, "$20");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][46], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][46], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][46], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][46], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][46], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][46], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][46], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][46], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][46], 0);

	Shop_TXD[playerid][47] = CreatePlayerTextDraw(playerid, 443.000000, 269.000000, "$21");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][47], 0.200000, 0.699998);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][47], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][47], -1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][47], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][47], 1);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][47], 180);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][47], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][47], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][47], 0);

	Shop_TXD[playerid][48] = CreatePlayerTextDraw(playerid, 197.000000, 284.000000, "CLOSE");
	PlayerTextDrawLetterSize(playerid, Shop_TXD[playerid][48], 0.300000, 1.200000);
	PlayerTextDrawTextSize(playerid, Shop_TXD[playerid][48], 12.000000, 36.000000);
	PlayerTextDrawAlignment(playerid, Shop_TXD[playerid][48], 2);
	PlayerTextDrawColor(playerid, Shop_TXD[playerid][48], -1);
	PlayerTextDrawUseBox(playerid, Shop_TXD[playerid][48], 1);
	PlayerTextDrawBoxColor(playerid, Shop_TXD[playerid][48], -2139062172);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][48], 0);
	PlayerTextDrawSetOutline(playerid, Shop_TXD[playerid][48], 0);
	PlayerTextDrawBackgroundColor(playerid, Shop_TXD[playerid][48], 255);
	PlayerTextDrawFont(playerid, Shop_TXD[playerid][48], 1);
	PlayerTextDrawSetProportional(playerid, Shop_TXD[playerid][48], 1);
	PlayerTextDrawSetShadow(playerid, Shop_TXD[playerid][48], 0);
	PlayerTextDrawSetSelectable(playerid, Shop_TXD[playerid][48], true);
	
	for(new i = 0; i <= 49; i++)
	{
		PlayerTextDrawHide(playerid,Shop_TXD[playerid][i]);
	}
	return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	new slot;
	for(new i = 1; i <= 21; i++)
	{
		if(playertextid == Shop_TXD[playerid][i])
			slot = i;
	}
	
	if(slot)
	{
		
		slot = slot-1+Shop_Status[playerid][page]*21;
		
		new shopid = Shop_Status[playerid][id];
		new shopslot = ShopList[shopid][slot];
		new itemid = Shop[shopslot][item];
		
		SetPVarInt(playerid, "Itemid", itemid);
		SetPVarInt(playerid, "Shopid", shopid);

		

		//SendClientMessageEx(playerid, -1, "Слот %d | Магазин %d | ID скина %d | Строка %d", slot, shopid, itemid, shopslot);
		//SetPlayerSkin(playerid, itemid);
		
		new str[512];	
		if(shopid == 0 || shopid == 1)
			format(str, sizeof(str), "{FFFFFF}Вы подтверждаете покупку одежды №%d за 150$?\n", itemid);
			
		
		if(shopid == 2)
			for(new i = 0; i<sizeof(Items); i++)
				if(Items[i][Model] == itemid)
					format(str, sizeof(str), "{FFFFFF}Вы подтверждаете покупку %s за 70$?\n", Items[i][Name]);

		
		ShowPlayerDialog(playerid, 1001, DIALOG_STYLE_MSGBOX, "Магазин", str, "Да", "Нет");
		
		return 1;
	}

	if(playertextid == Shop_TXD[playerid][24])
		ShopMenu(playerid, Shop_Status[playerid][page]+1, Shop_Status[playerid][id]);
	
	if(playertextid == Shop_TXD[playerid][25])
		ShopMenu(playerid, Shop_Status[playerid][page]-1, Shop_Status[playerid][id]);

	if(playertextid == Shop_TXD[playerid][48])
	{
		CancelSelectTextDraw(playerid);
		TXDHideAll(playerid);
	}
	
    return 1; 
}  

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(_:clickedid == INVALID_TEXT_DRAW) {
		TXDHideAll(playerid);
	}
	return 1;
}

