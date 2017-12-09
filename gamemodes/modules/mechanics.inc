

new TimeJob1[MAX_PLAYERS];
new JobPayDay[MAX_PLAYERS];
new PlayerText:PT_PAYDAY[MAX_PLAYERS];
new Text:T_PAYDAY[2];

new PlayerText:PT_MYTIMER[MAX_PLAYERS][2];
new Text:T_MYTIMER[2];

new Float:PosProgressBar[MAX_PLAYERS];


new CurrentMech = 0;

#define Random(%0,%1) random(%1 - %0)+%0

#define CAR 0
#define BIKE 1
#define MOTORBIKE 2
#define BOAT 3
#define PLANE 4
#define RC 5
#define TRAIN 6
#define TRAILER 7
#define HELICOPTER 8

#define MAX_PROCESS 9000
#define Radius 4
#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

new TimerP;
new Process[MAX_PLAYERS][MAX_VEHICLES];
new ColorBallon[MAX_PLAYERS] = 1;


new PrevSkin[MAX_PLAYERS];


new Text:ChangeColor[66];
new ColorsAvailable[66] = {
    1, 0, 2, 3, 4, 6, 8, 12, 13, 16, 17, 20, 24, 28, 44, 43, 46, 51, 52, 55, 57, 79, 93, 86, 87, 65, 97, 112, 117, 118, 126, 111, 103, 102, 128, 145, 136, 139, 143, 158, 175, 170, 171, 154, 176, 179, 182, 191, 194, 195, 196, 198, 215, 224, 225, 237, 241, 244, 245, 248, 251, 252, 253, 254
};
new AllCarColors[256] = {
    0x000000FF,0xFFFFFFFF,0x55aaa7FF,0xce575bFF,0x58685dFF,0xb06c77FF,0xf8ad38FF,0x7a96acFF,0xdfdec9FF,0x81897aFF,
    0x677776FF,0x93948eFF,0x7e9689FF,0x807c70FF,0xe8eac3FF,0xbab9a5FF,0x73996aFF,0xa54549FF,0xc55063FF,0xd8d5b2FF,
    0x86979eFF,0xa66b67FF,0x8e4556FF,0xcfc3a9FF,0x6c6d65FF,0x5b5a55FF,0xafb295FF,0x77705eFF,0x5a6466FF,0xa89f82FF,
    0x64433aFF,0x73423dFF,0xb5bcb4FF,0xa1a58aFF,0x96947fFF,0x918a6cFF,0x5a5b53FF,0x5b6656FF,0xa8b186FF,0x8d9389FF,
    0x3f3c35FF,0x80765dFF,0x873b3bFF,0x7d3334FF,0x3b5741FF,0x71413dFF,0xaaa176FF,0x89815dFF,0xc2b894FF,0xd6d0b0FF,
    0xa9a98fFF,0x647d67FF,0x849283FF,0x495261FF,0x565b61FF,0x9d846eFF,0xb0af90FF,0xa19273FF,0x7a3138FF,0x5c6c69FF,
    0x9e9c83FF,0x887554FF,0x803c3dFF,0x928f7cFF,0xcfcda7FF,0xd4d27fFF,0x6f534fFF,0xa7ada1FF,0xe1dd9eFF,0xd9b79bFF,
    0xa84645FF,0x96a097FF,0x6f725dFF,0xb6bd93FF,0x764040FF,0x434842FF,0xb0ac89FF,0xb5a778FF,0x8a473fFF,0x375369FF,
    0x9a555aFF,0xaa9c75FF,0xac5359FF,0x56665bFF,0x786151FF,0x995061FF,0x60843cFF,0x72858bFF,0x7c454aFF,0xa7a373FF,
    0xb8b29aFF,0x585e5cFF,0x827f6eFF,0x388a85FF,0x4b6566FF,0x4c5858FF,0xc3c0a1FF,0x97a79aFF,0x80a999FF,0xe1c99dFF,
    0x6e8c8aFF,0x57585cFF,0xd6b98dFF,0x426d80FF,0xa29368FF,0x818274FF,0x3d717fFF,0xb6ab7eFF,0x587482FF,0x696a62FF,
    0x8f7d59FF,0xa3a091FF,0x80948bFF,0x786954FF,0x72866aFF,0xaa4553FF,0x53616aFF,0x8f4f4fFF,0xbfc1b6FF,0x938369FF,
    0xb5a180FF,0x763b41FF,0x747567FF,0x846c50FF,0x914b4dFF,0x38526bFF,0xef87a2FF,0x3c3d38FF,0x6cb85dFF,0x725a4eFF,
    0x78acaaFF,0x987e59FF,0x9b675aFF,0x545d4cFF,0x706c83FF,0x7dc6bdFF,0xcb90c6FF,0x7fca6fFF,0xf7ebc3FF,0x9697abFF,
    0xc3bda3FF,0xbdaf88FF,0xcdbf67FF,0xab8e90FF,0xa28796FF,0xd2ee99FF,0xbd8a93FF,0xaa6a85FF,0x72715cFF,0x665b45FF,
    0x656952FF,0x7e926fFF,0x7398b5FF,0x7da477FF,0x6bcf79FF,0x65c8a9FF,0xe0d59dFF,0xc8c5b4FF,0xde7c5fFF,0x77694cFF,
    0x5d6d49FF,0xd17f74FF,0x6f93b3FF,0x62b79aFF,0x667264FF,0x6aa998FF,0x6daaa5FF,0xaa7faaFF,0x875e4aFF,0xbfb1b0FF,
    0xb4a8acFF,0x987f9dFF,0x686947FF,0x80604bFF,0x8e6c50FF,0xd8685aFF,0xd294a9FF,0xbf9899FF,0xbb839cFF,0x826168FF,
    0xbd825aFF,0xba6254FF,0xd28865FF,0xcf7958FF,0xc88c84FF,0xbba899FF,0x4f5847FF,0x516b48FF,0x6c825bFF,0x677c5bFF,
    0xaa757dFF,0x8dca85FF,0xd4c7a4FF,0xc0bfaaFF,0xdfd249FF,0xbac775FF,0xbdc2a2FF,0xbabb5eFF,0x717caaFF,0x7d7b4aFF,
    0xc1aa74FF,0x536370FF,0x79936cFF,0x606f6cFF,0x798f8dFF,0x515459FF,0x4d585aFF,0x677a76FF,0x7d99a7FF,0x5d7b7dFF,
    0x6f8b8cFF,0x72668aFF,0xac6c53FF,0xd3caadFF,0x98a053FF,0x545945FF,0xcc996eFF,0xa3caafFF,0xd29779FF,0xcc9054FF,
    0xdd888fFF,0xd6c377FF,0xd07151FF,0x596271FF,0x936556FF,0x89864fFF,0x9cd665FF,0x5a765dFF,0xd0b858FF,0x66b758FF,
    0x83605aFF,0xb79153FF,0xc37d9fFF,0xbf6791FF,0x5b7f51FF,0x71894fFF,0x5d7166FF,0xc3919dFF,0xcca470FF,0xaf6c52FF,
    0x77c4a4FF,0x99c556FF,0x9b616fFF,0x63bd63FF,0x7c5d49FF,0x57694fFF,0x809ea8FF,0x748080FF,0x935d5bFF,0x90575eFF,
    0xaaa184FF,0x7d7e70FF,0x716d62FF,0xc9c3a3FF,0x9b907aFF,0x838786FF
};





stock IsVehicleUpgradeCompatible(modelz,componentid)
{
	switch(modelz)
	{
		case 400:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 401:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1017: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
			}
		}
		case 404:
		{
			switch(componentid)
			{
				case 1000: { return 1; }
				case 1002: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1016: { return 1; }
				case 1017: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 405:
		{
			switch(componentid)
			{
				case 1000: { return 1; }
				case 1001: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1014: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 410:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1017: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1023: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 415:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 418:
		{
			switch(componentid)
			{
				case 1002: { return 1; }
				case 1006: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1016: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 420:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1019: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 421:
		{
			switch(componentid)
			{
				case 1000: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1014: { return 1; }
				case 1016: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 422:
		{
			switch(componentid)
			{
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1017: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 426:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1019: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 436:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1017: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1022: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 439:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1017: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 477:
		{
			switch(componentid)
			{
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 478:
		{
			switch(componentid)
			{
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1012: { return 1; }
				case 1013: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1022: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 489:
		{
			switch(componentid)
			{
				case 1000: { return 1; }
				case 1002: { return 1; }
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1016: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 491:
		{
			switch(componentid)
			{
				case 1003: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1014: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 492:
		{
			switch(componentid)
			{
				case 1000: { return 1; }
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1016: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 496:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1002: { return 1; }
				case 1003: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1011: { return 1; }
				case 1017: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
			}
		}
		case 500:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 516:
		{
			switch(componentid)
			{
				case 1000: { return 1; }
				case 1002: { return 1; }
				case 1004: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1015: { return 1; }
				case 1016: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 517:
		{
			switch(componentid)
			{
				case 1002: { return 1; }
				case 1003: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1016: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 518:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 527:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1014: { return 1; }
				case 1015: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 529:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1011: { return 1; }
				case 1012: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 534:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1100: { return 1; }
				case 1101: { return 1; }
				case 1106: { return 1; }
				case 1122: { return 1; }
				case 1123: { return 1; }
				case 1124: { return 1; }
				case 1125: { return 1; }
				case 1126: { return 1; }
				case 1127: { return 1; }
				case 1178: { return 1; }
				case 1179: { return 1; }
				case 1180: { return 1; }
				case 1185: { return 1; }
			}
		}
		case 535:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1109: { return 1; }
				case 1110: { return 1; }
				case 1113: { return 1; }
				case 1114: { return 1; }
				case 1115: { return 1; }
				case 1116: { return 1; }
				case 1117: { return 1; }
				case 1118: { return 1; }
				case 1119: { return 1; }
				case 1120: { return 1; }
				case 1121: { return 1; }
			}
		}
		case 536:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1103: { return 1; }
				case 1104: { return 1; }
				case 1105: { return 1; }
				case 1107: { return 1; }
				case 1108: { return 1; }
				case 1128: { return 1; }
				case 1181: { return 1; }
				case 1182: { return 1; }
				case 1183: { return 1; }
				case 1184: { return 1; }
			}
		}
		case 540:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1004: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 542:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1014: { return 1; }
				case 1015: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 546:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1002: { return 1; }
				case 1004: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1023: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 547:
		{
			switch(componentid)
			{
				case 1000: { return 1; }
				case 1003: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1016: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
			}
		}
		case 549:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1011: { return 1; }
				case 1012: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 550:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 551:
		{
			switch(componentid)
			{
				case 1002: { return 1; }
				case 1003: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1016: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1021: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 558:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1088: { return 1; }
				case 1089: { return 1; }
				case 1090: { return 1; }
				case 1091: { return 1; }
				case 1092: { return 1; }
				case 1093: { return 1; }
				case 1094: { return 1; }
				case 1095: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1163: { return 1; }
				case 1164: { return 1; }
				case 1165: { return 1; }
				case 1166: { return 1; }
				case 1167: { return 1; }
				case 1168: { return 1; }
			}
		}
		case 559:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1065: { return 1; }
				case 1066: { return 1; }
				case 1067: { return 1; }
				case 1068: { return 1; }
				case 1069: { return 1; }
				case 1070: { return 1; }
				case 1071: { return 1; }
				case 1072: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1158: { return 1; }
				case 1159: { return 1; }
				case 1160: { return 1; }
				case 1161: { return 1; }
				case 1162: { return 1; }
				case 1173: { return 1; }
			}
		}
		case 560:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1026: { return 1; }
				case 1027: { return 1; }
				case 1028: { return 1; }
				case 1029: { return 1; }
				case 1030: { return 1; }
				case 1031: { return 1; }
				case 1032: { return 1; }
				case 1033: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1138: { return 1; }
				case 1139: { return 1; }
				case 1140: { return 1; }
				case 1141: { return 1; }
				case 1169: { return 1; }
				case 1170: { return 1; }
			}
		}
		case 561:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1055: { return 1; }
				case 1056: { return 1; }
				case 1057: { return 1; }
				case 1058: { return 1; }
				case 1059: { return 1; }
				case 1060: { return 1; }
				case 1061: { return 1; }
				case 1062: { return 1; }
				case 1063: { return 1; }
				case 1064: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1154: { return 1; }
				case 1155: { return 1; }
				case 1156: { return 1; }
				case 1157: { return 1; }
			}
		}
		case 562:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1034: { return 1; }
				case 1035: { return 1; }
				case 1036: { return 1; }
				case 1037: { return 1; }
				case 1038: { return 1; }
				case 1039: { return 1; }
				case 1040: { return 1; }
				case 1041: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1146: { return 1; }
				case 1147: { return 1; }
				case 1148: { return 1; }
				case 1149: { return 1; }
				case 1171: { return 1; }
				case 1172: { return 1; }
			}
		}
		case 565:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1045: { return 1; }
				case 1046: { return 1; }
				case 1047: { return 1; }
				case 1048: { return 1; }
				case 1049: { return 1; }
				case 1050: { return 1; }
				case 1051: { return 1; }
				case 1052: { return 1; }
				case 1053: { return 1; }
				case 1054: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1150: { return 1; }
				case 1151: { return 1; }
				case 1152: { return 1; }
				case 1153: { return 1; }
			}
		}
		case 567:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1102: { return 1; }
				case 1129: { return 1; }
				case 1130: { return 1; }
				case 1131: { return 1; }
				case 1132: { return 1; }
				case 1133: { return 1; }
				case 1186: { return 1; }
				case 1187: { return 1; }
				case 1188: { return 1; }
				case 1189: { return 1; }
			}
		}
		case 575:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1042: { return 1; }
				case 1043: { return 1; }
				case 1044: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1099: { return 1; }
				case 1174: { return 1; }
				case 1175: { return 1; }
				case 1176: { return 1; }
				case 1177: { return 1; }
			}
		}
		case 576:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1134: { return 1; }
				case 1135: { return 1; }
				case 1136: { return 1; }
				case 1137: { return 1; }
				case 1190: { return 1; }
				case 1191: { return 1; }
				case 1192: { return 1; }
				case 1193: { return 1; }
			}
		}
		case 580:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 585:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1003: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 589:
		{
			switch(componentid)
			{
				case 1000: { return 1; }
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1016: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1020: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 600:
		{
			switch(componentid)
			{
				case 1004: { return 1; }
				case 1005: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1013: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1020: { return 1; }
				case 1022: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
		case 603:
		{
			switch(componentid)
			{
				case 1001: { return 1; }
				case 1006: { return 1; }
				case 1007: { return 1; }
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1017: { return 1; }
				case 1018: { return 1; }
				case 1019: { return 1; }
				case 1020: { return 1; }
				case 1023: { return 1; }
				case 1024: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
				case 1142: { return 1; }
				case 1143: { return 1; }
				case 1144: { return 1; }
				case 1145: { return 1; }
			}
		}
		case 402,403,406..409,411..414,416,419,423,424,427..429,431..435,437,438,440..445,448,450,451,455..459,461..463,466..468,470,471,474,475,479..486,490,494,495,498,499,502..510,514,515,521..526,528,530..533,541,552,543..545,554..557,566,568,578,571..574,579,581..584,586..588,591,594,596..599,601,602,604..611:
		{
			switch(componentid)
			{
				case 1008: { return 1; }
				case 1009: { return 1; }
				case 1010: { return 1; }
				case 1025: { return 1; }
				case 1073: { return 1; }
				case 1074: { return 1; }
				case 1075: { return 1; }
				case 1076: { return 1; }
				case 1077: { return 1; }
				case 1078: { return 1; }
				case 1079: { return 1; }
				case 1080: { return 1; }
				case 1081: { return 1; }
				case 1082: { return 1; }
				case 1083: { return 1; }
				case 1084: { return 1; }
				case 1085: { return 1; }
				case 1087: { return 1; }
				case 1096: { return 1; }
				case 1097: { return 1; }
				case 1098: { return 1; }
			}
		}
	}
	return 0;
}




#define COLOR_GREY 0xD3D3D3FF
#define MAX_VEHICLE_COMPONENT 172
enum AllComponents
{
    idcomp,
    Type[20],
    Name[20],
	Price
};
new AllTuningComponentsInfo[MAX_VEHICLE_COMPONENT][AllComponents]= {
{1008,    "Nitro",        "Nos 5x",4500},
{1009,    "Nitro",        "Nos 2x",3500},
{1010,    "Nitro",        "Nos 10x",6500},
{1073,    "Wheels",        "Shadow",400},
{1074,    "Wheels",        "Mega",500                },
{1075,    "Wheels",        "Rimshine",350            },
{1076,    "Wheels",        "Wires",700                },
{1077,    "Wheels",        "Classic",550          },
{1078,    "Wheels",        "Twist"  ,800              },
{1079,    "Wheels",        "Cutter"  ,400          },
{1080,    "Wheels",        "Switch"  ,600          },
{1081,    "Wheels",        "Grove"   ,500             },
{1082,    "Wheels",        "Import"   ,400         },
{1083,    "Wheels",        "Dollar"  ,900          },
{1084,    "Wheels",        "Trance" ,850           },
{1085,    "Wheels",        "Atomic"  ,500          },
{1025,    "Wheels",        "Offroad"  ,400          },
{1096,    "Wheels",        "Ahab"   ,550             },
{1097,    "Wheels",        "Virtual" ,700           },
{1098,    "Wheels",        "Access"    ,500        },
{1086,    "Stero",        "Sony"        ,500        },
{1087,    "Hydraulics",    "LowRider" , 3000           },
{1000,    "Spoiler",    "Pro"    ,200                 },
{1001,    "Spoiler",    "Win"    ,300                },
{1002,    "Spoiler",    "Drag"   ,400                 },
{1003,    "Spoiler",    "Alpha"  ,300                  },
{1014,    "Spoiler",    "Champ"   ,200                  },
{1015,    "Spoiler",    "Race"    ,300                },
{1016,    "Spoiler",    "Worx"    ,400                },
{1049,    "Spoiler",    "Alien"   ,300                 },
{1050,    "Spoiler",    "X-Flow"   ,200             },
{1058,    "Spoiler",    "Alien"    ,300                },
{1023,    "Spoiler",    "Fury"     ,400               },
{1158,    "Spoiler",    "X-Flow"   ,300             },
{1146,    "Spoiler",    "X-Flow    " ,200               },
{1147,    "Spoiler",    "Alien"      ,300              },
{1138,    "Spoiler",    "Alien"      ,400              },
{1139,    "Spoiler",    "X-Flow"     ,300           },
{1060,    "Spoiler",    "X-Flow"       ,200         },
{1162,    "Spoiler",    "Alien"        ,300            },
{1163,    "Spoiler",    "X-Flow"       ,400         },
{1164,    "Spoiler",    "Alien"        ,300            },
{1004,    "Hood",        "Champ Scoop"   ,200             },
{1005,    "Hood",        "Fury Scoop"    ,300            },
{1011,    "Hood",        "Race Scoop"    ,400            },
{1012,    "Hood",        "Worx Scoop"    ,300            },
{1100,    "Bullbars",    "Chrome Grill"   ,200         },
{1123,    "Bullbars",    "Chrome Bars"    ,300			 },
{1125,    "Bullbars",    "Chrome lights1" ,400  		 },
{1117,    "Front Bumper","Chrome"         ,300       },
{1152,    "Front Bumper","X-Flow"         ,200       },
{1153,    "Front Bumper","Alien"          ,300      },
{1155,    "Front Bumper","Alien"          ,400      },
{1157,    "Front Bumper","X-Flow"         ,300       },
{1160,    "Front Bumper","Alien"          ,200      },
{1160,    "Front Bumper","Alien"          ,300      },
{1165,    "Front Bumper","X-Flow"         ,400       },
{1166,    "Front Bumper","Alien"          ,300      },
{1169,    "Front Bumper","Alien"           ,200     },
{1170,    "Front Bumper","X-Flow"          ,300      },
{1171,    "Front Bumper","Alien"           ,400     },
{1172,    "Front Bumper","X-Flow"          ,300      },
{1173,    "Front Bumper","X-Flow"          ,200      },
{1174,    "Front Bumper","Chrome"          ,300      },
{1176,    "Front Bumper","Chrome"          ,400      },
{1179,    "Front Bumper","Chrome"          ,300      },
{1181,    "Front Bumper","Slamin"          ,200      },
{1182,    "Front Bumper","Chrome"          ,300      },
{1185,    "Front Bumper","Slamin"          ,400      },
{1188,    "Front Bumper","Slamin"          ,300      },
{1189,    "Front Bumper","Chrome"          ,200      },
{1190,    "Front Bumper","Slamin"          ,300      },
{1191,    "Front Bumper","Chrome"          ,400      },
{1140,    "Rear Bumper","X-Flow"           ,300     },
{1141,    "Rear Bumper","Alien"            ,200    },
{1148,    "Rear Bumper","X-Flow"           ,300     },
{1149,    "Rear Bumper","Alien"            ,400    },
{1150,    "Rear Bumper","Alien"            ,300    },
{1151,    "Rear Bumper","X-Flow"           ,200     },
{1154,    "Rear Bumper","Alien"            ,300    },
{1156,    "Rear Bumper","X-Flow"           ,400     },
{1159,    "Rear Bumper","Alien"            ,300    },
{1161,    "Rear Bumper","X-Flow"           ,200     },
{1167,    "Rear Bumper","X-Flow"           ,300     },
{1168,    "Rear Bumper","Alien"            ,400    },
{1175,    "Rear Bumper","Slamin"           ,300     },
{1177,    "Rear Bumper","Slamin"            ,200    },
{1178,    "Rear Bumper","Slamin"            ,300    },
{1180,    "Rear Bumper","Chrome"            ,400    },
{1183,    "Rear Bumper","Slamin"            ,300    },
{1184,    "Rear Bumper","Chrome"           ,200     },
{1186,    "Rear Bumper","Slamin"           ,300     },
{1187,    "Rear Bumper","Chrome"           ,400     },
{1192,    "Rear Bumper","Chrome"           ,300     },
{1193,    "Rear Bumper","Slamin"           ,200    			 },
{1143,    "Vents",    "Oval"            	,300		},
{1145,    "Vents",    "Square"        		,400			},
{1032,    "Roof",        "Alien"         	,300		   },
{1006,    "Roof",        "Scoop"           ,200 		    },
{1038,    "Roof",        "Alien"           ,300					 },
{1035,    "Roof",        "X-Flow"          ,400			  },
{1033,    "Roof",        "X-Flow"          ,300  			},
{1053,    "Roof",        "X-Flow"           ,200         },
{1054,    "Roof",        "Alien"            ,300            },
{1055,    "Roof",        "Alien"            ,400            },
{1061,    "Roof",        "X-Flow"           ,300         },
{1067,    "Roof",        "Alien"            ,200            },
{1068,    "Roof",        "X-Flow"           ,300         },
{1088,    "Roof",        "Alien"            ,400            },
{1091,    "Roof",        "X-Flow"           ,300         },
{1103,    "Roof",        "Covertible"        ,200        },
{1128,    "Roof",        "Vinyl Hardtop"     ,300           },
{1130,    "Roof",        "Hardtop"           ,400         },
{1131,    "Roof",        "Softtop"           ,300         },
{1013,    "Lamps",        "Round Fog"        ,200            },
{1024,    "Lamps",        "Square Fog"       ,300         },
{1109,    "Rear Bullbars","Chrome"           ,400     },
{1110,    "Rear Bullbars","Slamin"           ,300     },
{1115,    "Front Bullbars","Chrome"           ,200     },
{1116,    "Front Bullbars","Slamin"           ,300     },
{1018,    "Exhaust",    "Upswept"             ,400       },
{1019,    "Exhaust",    "Twin"                ,300        },
{1020,    "Exhaust",    "Large"              ,200          },
{1021,    "Exhaust",    "Medium"             ,300       },
{1022,    "Exhaust",    "Small"              ,400          },
{1028,    "Exhaust",    "Alien"              ,300          },
{1029,    "Exhaust",    "X-Flow"            ,200        },
{1034,    "Exhaust",  "Alien"               ,300         },
{1037,    "Exhaust",    "X-Flow"            ,400        },
{1043,    "Exhaust",    "Slamin"            ,300        },
{1044,    "Exhaust",    "Chrome"             ,200       },
{1045,    "Exhaust",    "X-Flow"             ,300       },
{1046,    "Exhaust",    "Alien"              ,400          },
{1059,    "Exhaust",    "X-Flow"             ,300       },
{1064,    "Exhaust",    "Alien"              ,400          },
{1065,    "Exhaust",    "Alien"              ,200          },
{1066,    "Exhaust",    "X-Flow"             ,300       },
{1092,    "Exhaust",    "Alien"              ,400          },
{1089,    "Exhaust",    "X-Flow"             ,300       },
{1126,    "Exhaust",    "Chrome"           	,200		 },
{1127,    "Exhaust",    "Slamin"           	,300		 },
{1129,    "Exhaust",    "Chrome"            ,400        },
{1113,    "Exhaust",    "Chrome"            ,300        },
{1114,    "Exhaust",    "Slamin"           ,200         },
{1104,    "Exhaust",    "Chrome"           ,300         },
{1105,    "Exhaust",    "Slamin"           ,400         },
{1132,    "Exhaust",    "Slamin"           ,300         },
{1135,    "Exhaust",    "Slamin"            ,200        },
{1136,    "Exhaust",    "Chrome"            ,300        },
{1007,    "Sideskirt",    "Sideskirt"       ,400         },
{1026,    "Sideskirt",    "Alien"           ,300         },
{1031,    "Sideskirt",    "X-Flow"          ,200      },
{1036,    "Sideskirt",    "Alien"           ,300         },
{1039,    "Sideskirt",    "X-Flow"          ,400      },
{1041,    "Sideskirt",    "X-Flow"          ,300      },
{1042,    "Sideskirt",    "Chrome"          ,200      },
{1047,    "Sideskirt",    "Alien"           ,300         },
{1048,    "Sideskirt",    "X-Flow"          ,400      },
{1056,    "Sideskirt",    "Alien"           ,300         },
{1057,    "Sideskirt",    "X-Flow"          ,200      },
{1069,    "Sideskirt",    "Alien"           ,300         },
{1070,    "Sideskirt",    "X-Flow"          ,400      },
{1090,    "Sideskirt",    "Alien"           ,300         },
{1093,    "Sideskirt",    "X-Flow"          ,200      },
{1095,    "Sideskirt",    "X-Flow"          ,300      },
{1106,    "Sideskirt",    "Chrome Arches"   ,400         },
{1108,    "Sideskirt",    "Chrome Strip"    ,300        },
{1118,    "Sideskirt",    "Chrome Trim"     ,200       },
{1119,    "Sideskirt",    "Wheelcovers"     ,300       },
{1122,    "Sideskirt",    "Chrome Flames"   ,400         },
{1133,    "Sideskirt",    "Chrome Strip"    ,300        },
{1134,    "Sideskirt",    "Chrome Strip"    ,200        }
};  


forward MyTimer(playerid,time,text[]);
public MyTimer(playerid,time,text[])
{
	new Float:count12;


	count12 = (178.380661-124.500732)/time;
	
	PosProgressBar[playerid] += count12;
	
	new str[32];
	format(str,sizeof(str),"%s",text);
	TextDrawSetString(T_MYTIMER[0],str);
	
	PlayerTextDrawTextSize(playerid, PT_MYTIMER[playerid][1], 124.500732+PosProgressBar[playerid], -4.666666);
	
	PlayerTextDrawShow(playerid,PT_MYTIMER[playerid][0]);
	PlayerTextDrawShow(playerid,PT_MYTIMER[playerid][1]);
	
	TextDrawShowForPlayer(playerid,T_MYTIMER[0]);
	TextDrawShowForPlayer(playerid,T_MYTIMER[1]);

}

forward MyTimerEnd(playerid);
public MyTimerEnd(playerid)
{
	PlayerTextDrawTextSize(playerid, PT_MYTIMER[playerid][1], 124.500732, -4.666666);
	PosProgressBar[playerid] = 0.0;
	PlayerTextDrawHide(playerid,PT_MYTIMER[playerid][0]);
	PlayerTextDrawHide(playerid,PT_MYTIMER[playerid][1]);
		
	TextDrawHideForPlayer(playerid,T_MYTIMER[0]);
	TextDrawHideForPlayer(playerid,T_MYTIMER[1]);
	
}




Dialog:dTunungPL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new tu_comp = GetPVarInt(playerid,"tuning_comp");
		new veh = GetPlayerVehicleID(playerid);
		
		if((character_info[playerid][money] >= AllTuningComponentsInfo[tu_comp][Price]) && veh != 0)
		{
			AddVehicleComponent(veh, AllTuningComponentsInfo[tu_comp][idcomp]); 
			
			character_info[playerid][money]-=AllTuningComponentsInfo[tu_comp][Price];
			GivePlayerMoney(playerid,-AllTuningComponentsInfo[tu_comp][Price]);
			
			
			
			PlayerPlaySound(playerid,1133,0.0,0.0,0.0);
			PlayerPlaySound(GetPVarInt(playerid,"tuning_mechID"),1133,0.0,0.0,0.0);
			
			new str[128];
			
		
			new result = (AllTuningComponentsInfo[tu_comp][Price] * 25)/100;
			factions[50][bank] += result;
		
			
			
			
			format(str,sizeof(str),"На ваш транспорт был установлен %s(%s)",AllTuningComponentsInfo[tu_comp][Name],AllTuningComponentsInfo[tu_comp][Type]);
			SendClientMessage(playerid,0xFFA500FF,str);
			
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Spoiler"))
				{
					veh_info[veh][spoiler] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Hood"))
				{
					veh_info[veh][hood] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Roof"))
				{
					veh_info[veh][roof] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Sideskirt"))
				{
					veh_info[veh][sideskirt] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Lamps"))
				{
					veh_info[veh][lamps] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Nitro"))
				{
					veh_info[veh][nitro] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
				
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Exhaust"))
				{
					veh_info[veh][exhaust] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Wheels"))
				{
					veh_info[veh][wheel] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Hydraulics"))
				{
					veh_info[veh][hydraulics] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
				
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Front Bumper"))
				{
					veh_info[veh][front_bumper] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			if(!strcmp(AllTuningComponentsInfo[tu_comp][Type], "Rear Bumper"))
				{
					veh_info[veh][rear_bumper] = AllTuningComponentsInfo[tu_comp][idcomp];
				}
			
		}
		else
		{
			SendClientMessage(playerid,COLOR_GREY,"У вас недостаточно денежных средств.");
		}
	}
	else
	{
		
		SCM(GetPVarInt(playerid,"tuning_mechID"),0xB22222FF,"Игрок отказался от вашей услуги.");
	}
	return 1;
}

Dialog:dTuningPart(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[156];
		
		
		new itext = strval(inputtext); 
		for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
		{
			if(AllTuningComponentsInfo[i][idcomp] == itext)
			{
				
				
				format(str,sizeof(str),"Вы отправили заявку игроку для установки {FFA500}%s(%s){FFFFFF} на его транспорт, ожидайте ответа...",AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Type]);
				SendClientMessage(playerid,COLOR_GREY,str);
				
				
				new pl = GetPVarInt(playerid,"tuning_pl");
				SetPVarInt(pl,"tuning_comp",i);
				SetPVarInt(pl,"tuning_mechID",playerid);
				format(str,sizeof(str),"{FFA500}%s {FFFFFF}предлагает вам установить {FFA500}%s(%s){FFFFFF} на ваш транспорт за {006400}$%d{FFFFFF}. Вы согласны с этим?",character_info[playerid][name],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Type],AllTuningComponentsInfo[i][Price]);
				Dialog_Show(pl,dTunungPL,DIALOG_STYLE_MSGBOX,"Тюнинг",str,"Принять","Отмена");

				
			}
		}
		
	}
	return 1;
}


CMD:paint(playerid)
{
	
	if(!IsMech(playerid)) return SendClientMessage(playerid,COLOR_GREY,"Вы должны быть механиком чтобы использовать данную команду.");
	if(!GetPVarInt(playerid,"start_job2")) return SCM(playerid,COLOR_GREY,"Сначало нужно приступить к работе.");

	SendClientMessage(playerid,0xFFA500FF,"Возьмите в руки балончик и распрыскивайте им на транспорт чтобы покрасить.");
	
	for(new i; i < sizeof(ChangeColor); i++)
    {
        TextDrawSetPreviewModel(ChangeColor[i], 19349);
        TextDrawShowForPlayer(playerid,ChangeColor[i]);
    }
    SelectTextDraw(playerid, 0xFFFFFF66) ;
	
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	
    if (clickedid == ChangeColor[1] )
    {
        CancelSelectTextDraw(playerid);
        for(new i; i < sizeof(ChangeColor); i++)
        {
            TextDrawHideForPlayer(playerid,ChangeColor[i]);
        }
    }
    for(new i=2; i < sizeof(ChangeColor); i++)
    {
        if(clickedid == ChangeColor[i])
        {
            CancelSelectTextDraw(playerid);
			
			
			ColorBallon[playerid] = ColorsAvailable[i-2];
			for(new v; v < MAX_VEHICLES; v++) Process[playerid][v] = 0;

			
            for(new j; j < sizeof(ChangeColor); j++)
            {
                TextDrawHideForPlayer(playerid,ChangeColor[j]);
            }
        }
    }
	
	if(_:clickedid == INVALID_TEXT_DRAW)
	{
		for(new i; i < sizeof(ChangeColor); i++)
        {
            TextDrawHideForPlayer(playerid,ChangeColor[i]);
        }
	}
    return 1;
}


CMD:tuning(playerid,params[])
{
	if(sscanf(params,"d", params[0])) return SendClientMessage(playerid,COLOR_GREY,"Используйте /tuning [ID_PLAYER]");
	if(!IsMech(playerid)) return SendClientMessage(playerid,COLOR_GREY,"Вы должны быть механиком чтобы использовать данную команду.");
	if(!GetPVarInt(playerid,"start_job2")) return SCM(playerid,COLOR_GREY,"Сначало нужно приступить к работе.");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, COLOR_GREY, "Данный игрок находится не в сети.");
	if(!IsPlayerInAnyVehicle(params[0])) return SendClientMessage(playerid, COLOR_GREY, "Игрок должен находиться в машине за рулем.");
	if(params[0] == playerid) return SCM(playerid,COLOR_GREY,"Невозможно использовать на себя.");
	new Float:x,Float:y,Float:z;
	GetPlayerPos(params[0], x,y,z);
	if(!PlayerToPoint(5.0, playerid, x,y,z)) return SendClientMessage(playerid, COLOR_GREY, "Вы должны быть рядом с игроком!");
	
	SetPVarInt(playerid,"tuning_veh",GetPlayerVehicleID(params[0]));
	SetPVarInt(playerid,"tuning_pl",params[0]);
	Dialog_Show(playerid,dTuningList,DIALOG_STYLE_LIST,"Тюнинг детали","1. Нитро(временно недоступно)\n2. Колеса\n3. Гидравлика\n4. Спойлер\n5. Передний бампер\n6. Задний бампер\n7. Крыша\n8. Выхлопная труба\n9. Боковая юбка\n10. Установить замок\n11. Установить сигнализацию","Выбрать","Отмена");
	
	return 1;
}

Dialog:dTuningList(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[512];
		format(str,sizeof(str),"ID\tНазвание\tЦена\n");
		new idveh = GetPVarInt(playerid,"tuning_veh");
		
		switch(listitem)
		{
			case 0:
			{
				
				/*for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					
					if(!strcmp("Nitro", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
						
					}
				}*/
			}
			case 1:
			{
				for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					if(!strcmp("Wheels", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
					}
				}
			}
			case 2:
			{
				for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					if(!strcmp("Hydraulics", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
					}
				}
			}
			case 3:
			{
				for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					if(!strcmp("Spoiler", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
						
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
					}
				}
			}
			case 4:
			{
				for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					if(!strcmp("Front Bumper", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
					}
				}
			}
			case 5:
			{
				for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					if(!strcmp("Rear Bumper", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
					}
				}
			}
			case 6:
			{
				for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					if(!strcmp("Roof", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
					}
				}
			}
			case 7:
			{
				for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					if(!strcmp("Exhaust", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
					}
				}
			}
			case 8:
			{
				for(new i=0;i<MAX_VEHICLE_COMPONENT;i++)
				{
					if(!strcmp("Sideskirt", AllTuningComponentsInfo[i][Type]))
					{
						if(IsVehicleUpgradeCompatible(GetVehicleModel(idveh),AllTuningComponentsInfo[i][idcomp]))
						{
							format(str,sizeof(str),"%s%d\t%s\t{008000}$%d\n",str,AllTuningComponentsInfo[i][idcomp],AllTuningComponentsInfo[i][Name],AllTuningComponentsInfo[i][Price]);
						}
					}
				}
			}
			case 9:
			{
				return Dialog_Show(playerid, dInstallLock1, DIALOG_STYLE_TABLIST, "Установка", "Замок низкого класса\t700$\nЗамок среднего класса\t2000$\nЗамок высокого класса\t5000$", "Выбрать", "Отмена");
			}
			case 10:
			{
				
				return Dialog_Show(playerid, dInstallAlarm1, DIALOG_STYLE_TABLIST, "Установка", "Сигнализация низкого класса\t1000$\nСигнализация высокого класса\t3000$", "Выбрать", "Отмена");
			}
		}
		Dialog_Show(playerid,dTuningPart,DIALOG_STYLE_TABLIST_HEADERS,"Установка",str,"Выбрать","Отмена");
	}
	return 1;
}

Dialog:dInstallAlarm1(playerid, response, listitem, inputtext[])
{
	if(response)
	{
	
	
		new v = GetPVarInt(playerid,"tuning_veh");
		new alarm_name[28], alarm_price;
		switch(listitem)
		{
			case 0: format(alarm_name, sizeof(alarm_name), "Сигнализация низкого класса"), alarm_price = 700;
			case 1: format(alarm_name, sizeof(alarm_name), "Сигнализация высокого класса"), alarm_price = 2000;
			default: return 1;
		}
		
		new str[300];
		new alarm_name_now[24];
		switch(veh_info[v][alarm_type])
		{
			case 1: format(alarm_name_now, sizeof(alarm_name_now), "Низкого класса");
			case 2: format(alarm_name_now, sizeof(alarm_name_now), "Высокого класса");
			default: format(alarm_name_now, sizeof(alarm_name_now), "Не определена");
		}
		
		new target_pl = GetPVarInt(playerid,"tuning_pl");
		format(str, sizeof(str), "{ffffff}Вы действительно хотите приобрести {33AA33}%s{ffffff} для вашего автомобиля?\nЭто обойдется вам в {33AA33}%d${ffffff}!\n\n{b1b1b1}В данный момент на транспорте установлена сигналиация: {ffffff}%s", alarm_name, alarm_price, alarm_name_now);
		
		SetPVarInt(target_pl, "buy_alarm_type", listitem+1);
		SetPVarInt(target_pl, "buy_alarm_money", alarm_price);
		SetPVarInt(target_pl, "buy_alarm_veh", v);
		SetPVarInt(target_pl, "buy_alarm_pl", playerid);
		
		
		
		Dialog_Show(target_pl, dInstallAlarm2, DIALOG_STYLE_MSGBOX, "Замок", str, "Да", "Нет"); 
	}
	return 1;
}

Dialog:dInstallAlarm2(playerid, response, listitem, inputtext[])
{
	
	if(response)
	{
		new v = GetPVarInt(playerid,"buy_alarm_veh");
		
		new buy_alarm_type = GetPVarInt(playerid, "buy_alarm_type");
		new buy_alarm_money = GetPVarInt(playerid, "buy_alarm_money");
		
		DeletePVar(playerid, "buy_alarm_type");
		DeletePVar(playerid, "buy_alarm_money");
		
		if(takemoney(playerid, buy_alarm_money, "buy alarm type") == 1)
		{
			veh_info[v][alarm_type] = buy_alarm_type;
			SCM(playerid, COLOR_GREEN, "Сигнализация была установлена!");
			
			
			new result = (buy_alarm_money * 25)/100;
			factions[50][bank] += result;
			
			
			new pl = GetPVarInt(playerid, "buy_alarm_pl");
			SCM(pl,0x008000FF,"Игрок подтвердил вашу услугу.");
		}
		else 
		{
			SCM(playerid, COLOR_GRAY, "У вас недостаточно денежных средств!");
		}
	}
	else
	{
		new pl = GetPVarInt(playerid, "buy_alarm_pl");
		SCM(pl,0xB22222FF,"Игрок отказался от вашей услуги.");
	}
	return 1;
}

Dialog:dInstallLock1(playerid, response, listitem, inputtext[])
{
	if(response)
	{
	
		new v = GetPVarInt(playerid,"tuning_veh");
		new lock_name[24], lock_price;
		switch(listitem)
		{
			case 0: format(lock_name, sizeof(lock_name), "Замок низкого класса"), lock_price = 700;
			case 1: format(lock_name, sizeof(lock_name), "Замок среднего класса"), lock_price = 2000;
			case 2: format(lock_name, sizeof(lock_name), "Замок высокого класса"), lock_price = 5000;
			default: return 1;
		}
		
		new str[256];
		new lock_name_now[24];
		switch(veh_info[v][lock_type])
		{
			case 1: format(lock_name_now, sizeof(lock_name_now), "Низкого класса");
			case 2: format(lock_name_now, sizeof(lock_name_now), "Среднего класса");
			case 3: format(lock_name_now, sizeof(lock_name_now), "Высокого класса");
			default: format(lock_name_now, sizeof(lock_name_now), "Не определен");
		}
		
		
		new target_pl = GetPVarInt(playerid,"tuning_pl");
		
		format(str, sizeof(str), "{ffffff}Вы действительно хотите приобрести {33AA33}%s{ffffff} для вашего автомобиля?\nЭто обойдется вам в {33AA33}%d${ffffff}!\n\n{b1b1b1}В данный момент на транспорте установлен замок: {ffffff}%s", lock_name, lock_price, lock_name_now);
		
		
		SetPVarInt(target_pl, "buy_lock_veh", v);
		SetPVarInt(target_pl, "buy_lock_type", listitem+1);
		SetPVarInt(target_pl, "buy_lock_money", lock_price);
		SetPVarInt(target_pl, "buy_lock_pl", playerid);
		
		Dialog_Show(target_pl, dInstallLock2, DIALOG_STYLE_MSGBOX, "Замок", str, "Да", "Нет"); 
	}
	return 1;
}

Dialog:dInstallLock2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new v = GetPVarInt(playerid,"buy_lock_veh");
			
		new buy_lock_type = GetPVarInt(playerid, "buy_lock_type");
		new buy_lock_money = GetPVarInt(playerid, "buy_lock_money");
		DeletePVar(playerid, "buy_lock_type");
		DeletePVar(playerid, "buy_lock_money");
			
		if(takemoney(playerid, buy_lock_money, "buy lock type") == 1)
		{
			veh_info[v][lock_type] = buy_lock_type;
			SCM(playerid, COLOR_GREEN, "Замок был установлен!");
			
			
			new result = (buy_lock_money * 25)/100;
			factions[50][bank] += result;
			
			new pl = GetPVarInt(playerid, "buy_lock_pl");
			SCM(pl,0x008000FF,"Игрок подтвердил вашу услугу.");
			
		}
		else SCM(playerid, COLOR_GRAY, "У вас недостаточно денежных средств!");
	}
	else
	{
		new pl = GetPVarInt(playerid, "buy_lock_pl");
		SCM(pl,0xB22222FF,"Игрок отказался от вашей услуги.");
	}
	return 1;
}


stock LoadJob()
{

	//CreateActor(8, 2695.6311,-2472.9978,2340.4041,233.6272);
	//CreateDynamic3DTextLabel("{008080}Работа грузчика\n{BFC0C2}N чтобы начать работу",-1,2695.6311,-2472.9978,2340.4041,5.0);
	
	CreateDynamic3DTextLabel("Раздевалка\n{ffffff}Нажмите 'N' чтобы начать работу автомеханика.",COLOR_INFO,2542.1763,-1287.2441,34.9524,5.5);
	
	
	

	
	
	
	CreateDynamic3DTextLabel("Подъёмник\n{ffffff}Нажмите 'N' чтобы поднять/опустить подёмник.",COLOR_INFO,2537.6047,-1276.9384,34.9453,5.5);
//	CreateDynamic3DTextLabel("{008080}Подъемник\n{BFC0C2}N чтобы активировать",-1,2220.168,-2166.318,14.181,1.0);//
	
	
	CreateDynamic3DTextLabel("Ворота\n{ffffff}Нажмите 'N' чтобы открыть/закрыть ворота.",COLOR_INFO,1354.7822,-1760.6909,13.5493,2.0);
	CreateDynamic3DTextLabel("Ворота\n{ffffff}Нажмите 'N' чтобы открыть/закрыть ворота.",COLOR_INFO,1354.8346,-1759.8159,13.4393,2.0);
	
	CreateDynamic3DTextLabel("Ворота\n{ffffff}Нажмите 'N' чтобы открыть/закрыть ворота",COLOR_INFO,2523.4775,-1269.3802,34.9453,2.0);
//	CreateDynamic3DTextLabel("{008080}Ворота\n{BFC0C2}N чтобы активировать",-1,2214.567,-2166.939,13.988,1.0);
	
//	CreateDynamic3DTextLabel("{008080}Ремонт\n{BFC0C2}/fix чтобы отремонтировать",-1,1943.6290,-1813.3380,15.4749,5.0);
	
	
	
	
//	CreateDynamicPickup(1650,23,1560.3517,-1694.3448,5.8970);
//	CreateDynamic3DTextLabel("{008080}Ремонт и заправка\n{BFC0C2}N чтобы использовать",-1,1560.3517,-1694.3448,5.8970,5.0);
	
	
//	CreateDynamicPickup(1650,23,2301.0442,-1937.7793,13.5838);
//	CreateDynamic3DTextLabel("{008080}Ремонт и заправка\n{BFC0C2}N чтобы использовать",-1,2301.0442,-1937.7793,13.5838,5.0);
	
//	CreateDynamicPickup(1650,23,1097.7919,-1314.7067,13.6940);
//	CreateDynamic3DTextLabel("{008080}Ремонт и заправка\n{BFC0C2}N чтобы использовать",-1,1097.7919,-1314.7067,13.6940,5.0);
//	
	
	
	
	CreateDynamicPickup(1241,23,1141.9927,-1322.5067,13.5871);
	
	
}




hook OnPlayerEnterCheckpoint(playerid)
{
	if(GetPVarInt(playerid,"Hand_Box") == 1)
	{
		UseAnim(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
		SetPlayerAttachedObject(playerid, playerid, 2060, 5, 0.01, 0.1, 0.2, 100, 10, 85);
		SetPlayerCheckpoint(playerid,2707.3708,-2472.8254,2340.4041,1.0);
		
		SetPVarInt(playerid,"Hand_Box",2);
		return 1;
	}
	if(GetPVarInt(playerid,"Hand_Box") == 2)
	{
		static str[9];
	
		RemovePlayerAttachedObject(playerid, playerid);
		ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1,0,1,1,0,1);
		
		
		JobPayDay[playerid] += Random(3,10);
		format(str,sizeof(str),"$%d",JobPayDay[playerid]);
		PlayerTextDrawSetString(playerid,PT_PAYDAY[playerid],str);
		
		PlayerPlaySound(playerid,1056,0.0,0.0,0.0);
		SetPlayerCheckpoint(playerid,2503.0017,-2270.1233,3.0129,1.0);
		SetPVarInt(playerid,"Hand_Box",1);
		return 1;
	}
	return 1;
}


hook OnPlayerConnect(playerid)
{
	TimeJob1[playerid] = 0;
	PrevSkin[playerid] = 0;
	
	PT_PAYDAY[playerid] = CreatePlayerTextDraw(playerid, 486.325164, 177.916671, "$0");
	PlayerTextDrawLetterSize(playerid, PT_PAYDAY[playerid], 0.301009, 1.279165);
	PlayerTextDrawAlignment(playerid, PT_PAYDAY[playerid], 2);
	PlayerTextDrawColor(playerid, PT_PAYDAY[playerid], 8388863);
	PlayerTextDrawSetShadow(playerid, PT_PAYDAY[playerid], 0);
	PlayerTextDrawSetOutline(playerid, PT_PAYDAY[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, PT_PAYDAY[playerid], 51);
	PlayerTextDrawFont(playerid, PT_PAYDAY[playerid], 3);
	PlayerTextDrawSetProportional(playerid, PT_PAYDAY[playerid], 1);
	
	
	
	PT_MYTIMER[playerid][0] = CreatePlayerTextDraw(playerid, 128.032226, 280.333374, "back");
	PlayerTextDrawLetterSize(playerid, PT_MYTIMER[playerid][0], 0.000000, 0.392405);
	PlayerTextDrawTextSize(playerid, PT_MYTIMER[playerid][0], 124.500732, 1.166667);
	PlayerTextDrawAlignment(playerid, PT_MYTIMER[playerid][0], 1);
	PlayerTextDrawColor(playerid, PT_MYTIMER[playerid][0], 0);
	PlayerTextDrawUseBox(playerid, PT_MYTIMER[playerid][0], true);
	PlayerTextDrawBoxColor(playerid, PT_MYTIMER[playerid][0], -2139062017);
	PlayerTextDrawSetShadow(playerid, PT_MYTIMER[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, PT_MYTIMER[playerid][0], 0);
	PlayerTextDrawFont(playerid, PT_MYTIMER[playerid][0], 0);


	PT_MYTIMER[playerid][1] = CreatePlayerTextDraw(playerid, 128.032226, 280.333374, "font");
	PlayerTextDrawLetterSize(playerid, PT_MYTIMER[playerid][1], 0.000000, 0.392405);
	PlayerTextDrawTextSize(playerid, PT_MYTIMER[playerid][1], 124.500732, -4.666666);//178.380661
	PlayerTextDrawAlignment(playerid, PT_MYTIMER[playerid][1], 1);
	PlayerTextDrawColor(playerid, PT_MYTIMER[playerid][1], 0);
	PlayerTextDrawUseBox(playerid, PT_MYTIMER[playerid][1], true);
	PlayerTextDrawBoxColor(playerid, PT_MYTIMER[playerid][1], -1061109505);
	PlayerTextDrawSetShadow(playerid, PT_MYTIMER[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, PT_MYTIMER[playerid][1], 0);
	PlayerTextDrawFont(playerid, PT_MYTIMER[playerid][1], 0);
	
	return 1;
}

new ElevatorMech;
new bool:ElevatorStatus = false;

new ElevatorMech2;
new bool:ElevatorStatus2 = false;



new DoorMech[3];
new bool:DoorStatus[3];

hook OnGameModeInit()
{
	
	
	

	LoadJob();
	
	T_PAYDAY[0] = TextDrawCreate(520.184509, 160.166656, "usebox");
	TextDrawLetterSize(T_PAYDAY[0], 0.000000, 3.539442);
	TextDrawTextSize(T_PAYDAY[0], 453.402648, 0.000000);
	TextDrawAlignment(T_PAYDAY[0], 1);
	TextDrawColor(T_PAYDAY[0], 0);
	TextDrawUseBox(T_PAYDAY[0], true);
	TextDrawBoxColor(T_PAYDAY[0], 336860330);
	TextDrawSetShadow(T_PAYDAY[0], 0);
	TextDrawSetOutline(T_PAYDAY[0], 0);
	TextDrawFont(T_PAYDAY[0], 0);

	T_PAYDAY[1] = TextDrawCreate(464.773040, 163.333358, FixText("Зарплата"));
	TextDrawLetterSize(T_PAYDAY[1], 0.258843, 0.987499);
	TextDrawAlignment(T_PAYDAY[1], 1);
	TextDrawColor(T_PAYDAY[1], -1);
	TextDrawSetShadow(T_PAYDAY[1], 0);
	TextDrawSetOutline(T_PAYDAY[1], 1);
	TextDrawBackgroundColor(T_PAYDAY[1], 51);
	TextDrawFont(T_PAYDAY[1], 1);
	TextDrawSetProportional(T_PAYDAY[1], 1);
	
	
	T_MYTIMER[1] = TextDrawCreate(189.877014, 255.833297, "usebox");
	TextDrawLetterSize(T_MYTIMER[1], 0.000000, 3.838515);
	TextDrawTextSize(T_MYTIMER[1], 116.535873, 0.000000);
	TextDrawAlignment(T_MYTIMER[1], 1);
	TextDrawColor(T_MYTIMER[1], 0);
	TextDrawUseBox(T_MYTIMER[1], true);
	TextDrawBoxColor(T_MYTIMER[1], 102);
	TextDrawSetShadow(T_MYTIMER[1], 0);
	TextDrawSetOutline(T_MYTIMER[1], 0);
	TextDrawFont(T_MYTIMER[1], 0);

	T_MYTIMER[0] = TextDrawCreate(154.143478, 261.333343, FixText("Название"));
	TextDrawLetterSize(T_MYTIMER[0], 0.200746, 1.040000);
	TextDrawAlignment(T_MYTIMER[0], 2);
	TextDrawColor(T_MYTIMER[0], -1);
	TextDrawSetShadow(T_MYTIMER[0], 0);
	TextDrawSetOutline(T_MYTIMER[0], 1);
	TextDrawBackgroundColor(T_MYTIMER[0], 51);
	TextDrawFont(T_MYTIMER[0], 1);
	TextDrawSetProportional(T_MYTIMER[0], 1);
	
	
	
	ElevatorMech = CreateDynamicObject(19872,2539.363281,-1274.864013,32.241210,0.000,0.000,90.000,-1,-1,-1,100.000,100.000);
    SetDynamicObjectMaterial(ElevatorMech, 0, 2917, "a51_crane", "girder2_grey_64HV", 0x00000000);
	
	
	ElevatorMech2 = CreateDynamicObject(19872,2220.993,-2163.428,11.293,0.000,0.000,135.000,-1,-1,-1,300.000,300.000);
	SetDynamicObjectMaterial(ElevatorMech2, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0xFF87CEFA);
	
	DoorMech[0] = CreateDynamicObject(5779,1351.37720,-1760.19434,13.96962,0.00000,0.00000,270.09396);
	DoorMech[1] = CreateDynamicObject(5779,1358.24438, -1760.23035, 10.90933,0.00000, 0.00000, 269.97025);
	DoorMech[2] = CreateDynamicObject(9093, 2522.14233, -1272.91077, 35.18735,   0.00000, 0.00000, 0.00000);	
	
	new tmpooob;
	tmpooob= CreateDynamicObject(19273,976.192,-1253.227,17.422,0.000,0.000,360.000,-1,-1,-1,100.000,100.000); 
	SetDynamicObjectMaterial(tmpooob, 0, -1, "none", "none", 0xFFFFFFFF);
	

	
	
	
	
	return 1;
}


stock FixText(string[]) 
{ 
	new result[256]; 
	for (new i=0; i < 256; i++) 
	{ 
		switch (string[i]) 
		{ 
			case 'а', 'А': result[i] = 'A'; 
			case 'б', 'Б': result[i] = 'Ђ'; 
			case 'в', 'В': result[i] = 'B'; 
			case 'г', 'Г': result[i] = '‚'; //
			case 'д', 'Д': result[i] = 'ѓ'; 
			case 'е', 'Е': result[i] = 'E'; 
			case 'ё', 'Ё': result[i] = 'E'; 
			case 'ж', 'Ж': result[i] = '„'; 
			case 'з', 'З': result[i] = '3';
			case 'и', 'И': result[i] = '…'; 
			case 'й', 'Й': result[i] = '†'; 
			case 'к', 'К': result[i] = 'K'; 
			case 'л', 'Л': result[i] = '‡'; 
			case 'м', 'М': result[i] = 'M'; 
			case 'н', 'Н': result[i] = 'H'; 
			case 'о', 'О': result[i] = 'O'; 
			case 'п', 'П': result[i] = 'Њ'; 
			case 'р', 'Р': result[i] = 'P'; 
			case 'с', 'С': result[i] = 'C'; 
			case 'т', 'Т': result[i] = 'T'; 
			case 'у', 'У': result[i] = 'Y'; 
			case 'ф', 'Ф': result[i] = 'Ѓ'; 
			case 'х', 'Х': result[i] = 'X'; 
			case 'ц', 'Ц': result[i] = '‰'; 
			case 'ч', 'Ч': result[i] = 'Ќ'; 
			case 'ш', 'Ш': result[i] = 'Ћ'; 
			case 'щ', 'Щ': result[i] = 'Љ'; 
			case 'ъ', 'Ъ': result[i] = 'ђ'; 
			case 'ы', 'Ы': result[i] = '‘'; 
			case 'ь', 'Ь': result[i] = '’'; 
			case 'э', 'Э': result[i] = '“'; 
			case 'ю', 'Ю': result[i] = '”'; 
			case 'я', 'Я': result[i] = '•'; 
			default: result[i] = string[i]; 
		} 
	} 
	return result; 
}  


forward UpTimeJob1(playerid);
public UpTimeJob1(playerid)
{
	TimeJob1[playerid] += 1;
	
	if(TimeJob1[playerid] >= 60)
	{
		DisablePlayerCheckpoint(playerid);
		SendClientMessage(playerid,COLOR_GREY,"Время вашей подработки кончилось. Подойдите к маркеру чтобы забрать зарплату.");
		KillTimer(GetPVarInt(playerid,"TimerJob1"));
	}
}


stock InviteJob1(playerid)
{
	
	if(GetPVarInt(playerid,"start_job1") == 0)
	{
		Dialog_Show(playerid,dInviteJob1,DIALOG_STYLE_MSGBOX,"РАБОТА: Грузчик","Вы действительно хотите подписать контракт работы Грузчика на 1 час?","Начать","Отмена");
	}
	
	else
	{
		
		Dialog_Show(playerid,dUnInviteJob1,DIALOG_STYLE_MSGBOX,"РАБОТА: Грузчик","Вы действительно хотите закончить работу грузчика и забрать зарплату?","Закончить","Отмена");
	}
	
}
stock InviteJob2(playerid)
{
	
	if(GetPVarInt(playerid,"start_job2") == 0)
	{
		Dialog_Show(playerid,dInviteJob2,DIALOG_STYLE_MSGBOX,"РАБОТА: Автомеханик","Вы действительно хотите начать работу автомеханика?","Начать","Отмена");
	}
	
	else
	{
		
		Dialog_Show(playerid,dUnInviteJob2,DIALOG_STYLE_MSGBOX,"РАБОТА: Автомеханик","Вы действительно хотите закончить работу автомеханика и забрать зарплату?","Закончить","Отмена");
	}
	
}


Dialog:dInviteJob2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
	
		
		
	
		SetPVarInt(playerid,"start_job2",1);
	

		SendClientMessage(playerid,COLOR_GREY,"Вы начали работу автомеханика, используйте /help для списка доступных команд.");
		
		PrevSkin[playerid] = GetPlayerSkin(playerid);
		SetPlayerSkin(playerid,50);
		
		CurrentMech ++;


	}

	return 1;
}


Dialog:dUnInviteJob2(playerid, response, listitem, inputtext[])
{
	if(response)
	{


		DeletePVar(playerid,"start_job2");
		
		CurrentMech--;
		
		SetPlayerSkin(playerid,PrevSkin[playerid]);
		

	}

	return 1;
}

Dialog:dInviteJob1(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(TimeJob1[playerid] >= 60) return SendClientMessage(playerid,COLOR_GREY,"Вы уже отработали 1 час на данной работе. Приходите завтра.");
		
		
		
		JobPayDay[playerid] = 0;
		SetPVarInt(playerid,"start_job1",1);
		SetPVarInt(playerid,"Hand_Box",1);

		SendClientMessage(playerid,COLOR_GREY,"Вы начали работу грузчика. Вам необходимо взять груз возле корабля и отнести его на склад.");
		SendClientMessage(playerid,COLOR_GREY,"Когда вы доставите груз на склад, вам автоматически будет начисятся зарплата.");
		SendClientMessage(playerid,COLOR_GREY,"Когда, вы закончите работу, подойдите к этому же маркеру - чтобы забрать свою зарплату.");
		
		
		PrevSkin[playerid] = GetPlayerSkin(playerid);
		SetPlayerSkin(playerid,8);

		PlayerTextDrawShow(playerid,PT_PAYDAY[playerid]);
		TextDrawShowForPlayer(playerid,T_PAYDAY[0]);
		TextDrawShowForPlayer(playerid,T_PAYDAY[1]);

		SetPlayerCheckpoint(playerid,2503.0017,-2270.1233,3.0129,1.0);

		SetPVarInt(playerid,"TimerJob1",SetTimerEx("UpTimeJob1",60000,1,"i",playerid));
	}

	return 1;
}


Dialog:dUnInviteJob1(playerid, response, listitem, inputtext[])
{
	if(response)
	{


		DeletePVar(playerid,"start_job1");
		DeletePVar(playerid,"Hand_Box");
		DisablePlayerCheckpoint(playerid);

		GivePlayerMoney(playerid,JobPayDay[playerid]);
		character_info[playerid][money] += JobPayDay[playerid];
		PlayerTextDrawSetString(playerid,PT_PAYDAY[playerid],"$0");
		PlayerTextDrawHide(playerid,PT_PAYDAY[playerid]);
		TextDrawHideForPlayer(playerid,T_PAYDAY[0]);
		TextDrawHideForPlayer(playerid,T_PAYDAY[1]);
		
		
		SetPlayerSkin(playerid,PrevSkin[playerid]);

		JobPayDay[playerid] = 0;

		PlayerPlaySound(playerid,1055,0.0,0.0,0.0);

		KillTimer(GetPVarInt(playerid,"TimerJob1"));

	}

	return 1;
}
hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
    {
        if(GetPVarInt(playerid, "Hand_Box") ==2)
        {
            SendClientMessage(playerid, COLOR_RED, "Вы уронили мешок!");
            RemovePlayerAttachedObject(playerid, playerid);
            SetPlayerCheckpoint(playerid,2503.0017,-2270.1233,3.0129,1.0);
            ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1,0,1,1,0,1);
			SetPVarInt(playerid,"Hand_Box",1);
            return 1;
        }
    }  
	return 1;
}


forward Raskraska(playerid);
public Raskraska(playerid)
{
    new Float: P[3];
    GetPlayerPos(playerid,P[0],P[1],P[2]);
    for(new v; v < MAX_VEHICLES; v++)
    {
          if((GetVehicleDistanceFromPoint(v,P[0],P[1],P[2])<= Radius) && Process[playerid][v] < MAX_PROCESS)
          {
                  if(IsPlayerAimingVehicle(playerid, v))
                  {
						Process[playerid][v] += 100;
						if(Process[playerid][v] >= MAX_PROCESS)
						{
							ChangeVehicleColor(v,ColorBallon[playerid],ColorBallon[playerid]);
							veh_info[v][vcolor1] = ColorBallon[playerid];
							veh_info[v][vcolor2] = ColorBallon[playerid];
						}
				  }
          }
    }
    return 1;
}
#define YAHOOO 0.42
stock IsPlayerAimingVehicle(playerid, vehicleid)
{
    new Float:X1, Float:Y1, Float:Z1, Float:X2, Float:Y2, Float:Z2;
    GetPlayerPos(playerid, X1, Y1, Z1);
    GetVehiclePos(vehicleid, X2, Y2, Z2);
    new Float:Distance = floatsqroot(floatpower(floatabs(X1-X2), 2) + floatpower(floatabs(Y1-Y2), 2));
    if(Distance < 350)
    {
        new Float:A;
        GetPlayerFacingAngle(playerid, A);
        X1 += (Distance * floatsin(-A, degrees));
        Y1 += (Distance * floatcos(-A, degrees));
        Distance = floatsqroot(floatpower(floatabs(X1-X2), 2) + floatpower(floatabs(Y1-Y2), 2));
        if(Distance < YAHOOO )return true;
    }
    return false;
}


Dialog:dSelectDoorM(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(DoorStatus[0] == false)
				{
					MoveDynamicObject(DoorMech[0],1351.37720,-1760.19434,13.96962,0.5, 0.00000, 0.00000, -89.49998);
					DoorStatus[0] = true;
				}
				else if(DoorStatus[0] == true)
				{
					MoveDynamicObject(DoorMech[0],1351.39001, -1760.25293, 10.80433,0.5,0.00000,0.00000,270.09396);
					DoorStatus[0] = false;
				}
			}
			case 1:
			{
				if(DoorStatus[1] == false)
				{
					MoveDynamicObject(DoorMech[1],1358.24438, -1760.23035, 14.08096,0.5,0.00000, 0.00000, 269.97025);
					
					DoorStatus[1] = true;
				}
				else if(DoorStatus[1] == true)
				{
					MoveDynamicObject(DoorMech[1],1358.24438, -1760.23035, 10.90933,0.5,0.00000, 0.00000, 269.97025);
					DoorStatus[1] = false;
				}
			}
		}
	}
	return 1;
}


Dialog:dSelectDoorM2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(DoorStatus[2] == false)
				{
					MoveDynamicObject(DoorMech[2], 2522.14233, -1272.91077, 35.18735,0.5, 0.0,0.0,180.0);
					DoorStatus[2] = true;
				}
				else if(DoorStatus[2] == true)
				{
					MoveDynamicObject(DoorMech[2], 2522.14233, -1272.91077, 38.47305,0.5, 0.0,0.0,180.0);
					DoorStatus[2] = false;
				}
				
			}	
		}
	}
	return 1;
}
 
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	
	
	
	if(IsMech(playerid))
	{
	
       if(PRESSED(KEY_FIRE) && GetPlayerWeapon(playerid) == 41) { TimerP = SetTimerEx("Raskraska",30,1,"d",playerid); }
       if(RELEASED(KEY_FIRE)) { KillTimer(TimerP); }
	}
    
	
	
	
	if (PRESSED(KEY_NO))
	{
	
		if(IsPlayerInRangeOfPoint(playerid,5.0,1560.3517,-1694.3448,5.8970) || IsPlayerInRangeOfPoint(playerid,5.0,2301.0442,-1937.7793,13.5838) || IsPlayerInRangeOfPoint(playerid,5.0,1097.7919,-1314.7067,13.6940))
		{
			if(!IsPlayerInAnyVehicle(playerid)) return 1;
			if(character_info[playerid][faction] == 1 || character_info[playerid][faction] == 2 || character_info[playerid][faction] == 68)
			Dialog_Show(playerid,dFixxx,DIALOG_STYLE_MSGBOX,"Ремеонт и заправка","Вы действительно хотите отремонтировать и заправить ваш служебный автомобиль?","Да","Нет");
		}
		
		if(IsPlayerInRangeOfPoint(playerid,2.0,2523.4487,-1269.4114,34.9453))
		{
			if(IsMech(playerid))
			{
				Dialog_Show(playerid,dSelectDoorM2,DIALOG_STYLE_LIST,"Дверь гаража","Первые ворота","Открыть","Отмена");
				
			}
		}
		
	
		
		if(IsPlayerInRangeOfPoint(playerid,2.0,1354.7822,-1760.6909,13.5493) || IsPlayerInRangeOfPoint(playerid,2.0,1354.8346,-1759.8159,13.4393))
		{
			if(IsMech(playerid))
			{
				Dialog_Show(playerid,dSelectDoorM,DIALOG_STYLE_LIST,"Дверь гаража","Первые ворота\nВторые ворота","Открыть","Отмена");
				
			}
		}
		if(IsPlayerInRangeOfPoint(playerid,2.0,2537.6047,-1276.9384,34.9453))
		{
			if(IsMech(playerid))
			{
				if(ElevatorStatus == false)
				{
					MoveDynamicObject(ElevatorMech, 2539.363281,-1274.864013,32.241210, 0.5, 0.0,0.0,90.0);
					
					ElevatorStatus = true;
				}
				else if(ElevatorStatus == true)
				{
					MoveDynamicObject(ElevatorMech, 2539.363281,-1274.864013,34.00000, 0.5, 0.0,0.0,90.0);
					ElevatorStatus = false;
				}
			}
		}
		
		if(IsPlayerInRangeOfPoint(playerid,2.0,2219.617,-2165.477,14.181))//Я
		{
			if(IsMech(playerid))
			{
				if(ElevatorStatus2 == false)
				{
					MoveDynamicObject(ElevatorMech2, 2220.993,-2163.428,12.09300, 0.5, 0.000,0.000,135.000);
					
					ElevatorStatus2 = true;
				}
				else if(ElevatorStatus2 == true)
				{
					MoveDynamicObject(ElevatorMech2, 2220.993,-2163.428,11.293, 0.5, 0.000,0.000,135.000);
					ElevatorStatus2 = false;
				}
			}
		}
		
		
		if(IsPlayerInRangeOfPoint(playerid,2.0,2542.1763,-1287.2441,34.9524))
		{
			if(IsMech(playerid))
			{
				InviteJob2(playerid);
			}
		}
		
		
		if(IsPlayerInRangeOfPoint(playerid,2.0,2232.3530,-2171.6445,13.5538))
		{
			if(IsMech(playerid))
			{
				InviteJob2(playerid);
			}
		}
		
		
		/*if(IsPlayerInRangeOfPoint(playerid,2.0,2695.6311,-2472.9978,2340.4041))
		{
			if(hour > 8 && hour < 19)
			{
				InviteJob1(playerid);
			}
			else
			{
				SendClientMessage(playerid,COLOR_GREY,"Работа грузчика доступно только с 8.00 до 19.00.");
			}
		}*/
		
		
		
	}
	
	if((newkeys & KEY_JUMP) && !(oldkeys & KEY_JUMP) || (newkeys & KEY_FIRE))
    {
        if(GetPVarInt(playerid, "Hand_Box") ==2)
        {
            SendClientMessage(playerid, COLOR_RED, "Вы уронили мешок!");
            RemovePlayerAttachedObject(playerid, playerid);
            SetPlayerCheckpoint(playerid,2503.0017,-2270.1233,3.0129,1.0);
            ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1,0,1,1,0,1);
			SetPVarInt(playerid,"Hand_Box",1);
            return 1;
        }
    } 
	
	return 1;
}

CMD:diagnostic(playerid,params[])
{	
	if(sscanf(params,"d", params[0])) return SendClientMessage(playerid,COLOR_GREY,"Используйте /diagnostic [ID_PLAYER]");
	if(!IsMech(playerid)) return SendClientMessage(playerid,COLOR_GREY,"Вы должны быть механиком чтобы использовать данную команду.");
	if(!GetPVarInt(playerid,"start_job2")) return SCM(playerid,COLOR_GREY,"Сначало нужно приступить к работе.");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, COLOR_GREY, "Данный игрок находится не в сети.");
	if(!IsPlayerInAnyVehicle(params[0])) return SendClientMessage(playerid, COLOR_GREY, "Игрок должен находиться в машине за рулем.");
	if(params[0] == playerid) return SCM(playerid,COLOR_GREY,"Невозможно использовать на себя.");
	new Float:x,Float:y,Float:z;
	GetPlayerPos(params[0], x,y,z);
	if(!PlayerToPoint(5.0, playerid, x,y,z)) return SendClientMessage(playerid, COLOR_GREY, "Вы должны быть рядом с игроком!");
	
	SetPVarInt(playerid,"fix_player",params[0]);
	SetPVarInt(playerid,"fix_veh",GetPlayerVehicleID(params[0]));
	
	new veh = GetPlayerVehicleID(params[0]);
	new str[1024];
	
	
	format(str,sizeof(str),"{FFFFFF}ID: {FFA500}%d\n{FFFFFF}Модель: {FFA500}%s\n{FFFFFF}Номер: {FFA500}%s\n\n\n{FFFFFF}Необходимый ремонт частей:\n\n",veh_info[veh][id],VehicleNames[GetVehicleModel(veh)-400],veh_info[veh][number]);
	
	
	GetVehiclePanelsDamageStatus(veh, veh_info[veh][vPanels][0],veh_info[veh][vPanels][1],veh_info[veh][vPanels][2],veh_info[veh][vPanels][3],veh_info[veh][vPanels][4],veh_info[veh][vPanels][5],veh_info[veh][vPanels][6]);
	GetVehicleDoorsDamageStatus(veh, veh_info[veh][vDoors][0],veh_info[veh][vDoors][1],veh_info[veh][vDoors][2],veh_info[veh][vDoors][3],veh_info[veh][vDoors][4],veh_info[veh][vDoors][5]);
	GetVehicleLightsDamageStatus(veh, veh_info[veh][vLights][0],veh_info[veh][vLights][1],veh_info[veh][vLights][2],veh_info[veh][vLights][3]);
	GetVehicleTiresDamageStatus(veh, veh_info[veh][vTires][0],veh_info[veh][vTires][1],veh_info[veh][vTires][2],veh_info[veh][vTires][3]);
		
	
	new Float:vhel;
	new zPrice;
	GetVehicleHealth(veh,vhel);
	
	new dvig_price = 0;
	
	if(vhel < 999)
	{
		dvig_price = 1000 - floatround(vhel);
		dvig_price = dvig_price * 3;
	}
	zPrice+=dvig_price;
	
	format(str,sizeof(str),"%s{FFFFFF}Двигатель: {006400}$%d\n",str,dvig_price);
	
	
	
	
	if(veh_info[veh][vPanels][4] != 0) 
	{
		format(str,sizeof(str),"%s{FFFFFF}Лобовое стекло: {006400}$%d\n",str,FixParts[IdxParts("Лобовое стекло")][fPrice]);
		zPrice+=FixParts[IdxParts("Лобовое стекло")][fPrice];
	}
	if(veh_info[veh][vPanels][5] != 0)
	{
		format(str,sizeof(str),"%s{FFFFFF}Передний бампер: {006400}$%d\n",str,FixParts[IdxParts("Передний бампер")][fPrice]);
		zPrice+=FixParts[IdxParts("Передний бампер")][fPrice];
	}
	
	if(veh_info[veh][vPanels][6] != 0) 
	{
		format(str,sizeof(str),"%s{FFFFFF}Задний бампер: {006400}$%d\n",str,FixParts[IdxParts("Задний бампер")][fPrice]);
		zPrice+=FixParts[IdxParts("Задний бампер")][fPrice];
	}
	
	
	if(veh_info[veh][vDoors][0] != 0) 
	{
		format(str,sizeof(str),"%s{FFFFFF}Капот: {006400}$%d\n",str,FixParts[IdxParts("Капот")][fPrice]);
		zPrice+=FixParts[IdxParts("Капот")][fPrice];
	}
	
	
	if(veh_info[veh][vDoors][1] != 0) 
	{
		format(str,sizeof(str),"%s{FFFFFF}Багажник: {006400}$%d\n",str,FixParts[IdxParts("Багажник")][fPrice]);
		zPrice+=FixParts[IdxParts("Багажник")][fPrice];
	}
	
	if(veh_info[veh][vDoors][2] != 0 || veh_info[veh][vDoors][3] != 0) 
	{
		format(str,sizeof(str),"%s{FFFFFF}Двери: {006400}$%d\n",str,FixParts[IdxParts("Двери")][fPrice]);
		zPrice+=FixParts[IdxParts("Двери")][fPrice];
	}
	
	
	if(veh_info[veh][vLights][0] != 0 || veh_info[veh][vLights][1] != 0 || veh_info[veh][vLights][2] != 0 || veh_info[veh][vLights][3] != 0) 
	{
		format(str,sizeof(str),"%s{FFFFFF}Фары: {006400}$%d\n",str,FixParts[IdxParts("Фары")][fPrice]);
		zPrice+=FixParts[IdxParts("Фары")][fPrice];
	}
	
	for(new i=0;i<4;i++) 
	{
		if(veh_info[veh][vTires][i] != 0) 
		{
			format(str,sizeof(str),"%s{FFFFFF}Колесо: {006400}$%d\n",str,FixParts[IdxParts("Колесо")][fPrice]);
			zPrice+=FixParts[IdxParts("Колесо")][fPrice];
		}
	}
	
	
	if(IsCop(params[0]) || IsMedic(params[0]))
	{
		format(str,sizeof(str),"%s\nИТОГОВАЯ ЦЕНА РЕМОНТА:\t{006400}$%d (50% скидка для гос.служащих)",str,zPrice/2);
		SetPVarInt(playerid,"VEH_PRICE",zPrice/2);
	}
	else
	{
		format(str,sizeof(str),"%s\nИТОГОВАЯ ЦЕНА РЕМОНТА:\t{006400}$%d",str,zPrice);
		SetPVarInt(playerid,"VEH_PRICE",zPrice);
	}
	
	
	SetPVarInt(playerid,"VEH_FIX",veh);
	
	
	SYS_AME(playerid, "делает диагностику транспорта");
	
	Dialog_Show(playerid,dListFix,DIALOG_STYLE_MSGBOX,"Диагностика",str,"Ок","");
	Dialog_Show(params[0],dListFix,DIALOG_STYLE_MSGBOX,"Диагностика",str,"Ок","");
	return 1;
}


CMD:fix(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_GREY, "Вы должны находиться в машине за рулем.");
	
	if(IsPlayerInRangeOfPoint(playerid,3.0,1943.6290,-1813.3380,15.4749))
	{
		if(CurrentMech > 0) return SCM(playerid, COLOR_GREY, "В игре находятся автомеханики.");
		
		
		
		new veh = GetPlayerVehicleID(playerid);
		new str[1024];
		
		
		format(str,sizeof(str),"{FFFFFF}ID: {FFA500}%d\n{FFFFFF}Модель: {FFA500}%s\n{FFFFFF}Номер: {FFA500}%s\n\n\n{FFFFFF}Необходимый ремонт частей:\n\n",veh_info[veh][id],VehicleNames[GetVehicleModel(veh)-400],veh_info[veh][number]);
		
		
		GetVehiclePanelsDamageStatus(veh, veh_info[veh][vPanels][0],veh_info[veh][vPanels][1],veh_info[veh][vPanels][2],veh_info[veh][vPanels][3],veh_info[veh][vPanels][4],veh_info[veh][vPanels][5],veh_info[veh][vPanels][6]);
		GetVehicleDoorsDamageStatus(veh, veh_info[veh][vDoors][0],veh_info[veh][vDoors][1],veh_info[veh][vDoors][2],veh_info[veh][vDoors][3],veh_info[veh][vDoors][4],veh_info[veh][vDoors][5]);
		GetVehicleLightsDamageStatus(veh, veh_info[veh][vLights][0],veh_info[veh][vLights][1],veh_info[veh][vLights][2],veh_info[veh][vLights][3]);
		GetVehicleTiresDamageStatus(veh, veh_info[veh][vTires][0],veh_info[veh][vTires][1],veh_info[veh][vTires][2],veh_info[veh][vTires][3]);
			
		
		new Float:vhel;
		new zPrice;
		GetVehicleHealth(veh,vhel);
		
		new dvig_price = 0;
		
		if(vhel < 999)
		{
			dvig_price = 1000 - floatround(vhel);
			dvig_price = dvig_price * 3;
		}
		zPrice+=dvig_price;
		
		format(str,sizeof(str),"%s{FFFFFF}Двигатель: {006400}$%d\n",str,dvig_price);
		
		
		
		
		if(veh_info[veh][vPanels][4] != 0) 
		{
			format(str,sizeof(str),"%s{FFFFFF}Лобовое стекло: {006400}$%d\n",str,FixParts[IdxParts("Лобовое стекло")][fPrice]);
			zPrice+=FixParts[IdxParts("Лобовое стекло")][fPrice];
		}
		if(veh_info[veh][vPanels][5] != 0)
		{
			format(str,sizeof(str),"%s{FFFFFF}Передний бампер: {006400}$%d\n",str,FixParts[IdxParts("Передний бампер")][fPrice]);
			zPrice+=FixParts[IdxParts("Передний бампер")][fPrice];
		}
		
		if(veh_info[veh][vPanels][6] != 0) 
		{
			format(str,sizeof(str),"%s{FFFFFF}Задний бампер: {006400}$%d\n",str,FixParts[IdxParts("Задний бампер")][fPrice]);
			zPrice+=FixParts[IdxParts("Задний бампер")][fPrice];
		}
		
		
		if(veh_info[veh][vDoors][0] != 0) 
		{
			format(str,sizeof(str),"%s{FFFFFF}Капот: {006400}$%d\n",str,FixParts[IdxParts("Капот")][fPrice]);
			zPrice+=FixParts[IdxParts("Капот")][fPrice];
		}
		
		
		if(veh_info[veh][vDoors][1] != 0) 
		{
			format(str,sizeof(str),"%s{FFFFFF}Багажник: {006400}$%d\n",str,FixParts[IdxParts("Багажник")][fPrice]);
			zPrice+=FixParts[IdxParts("Багажник")][fPrice];
		}
		
		if(veh_info[veh][vDoors][2] != 0 || veh_info[veh][vDoors][3] != 0) 
		{
			format(str,sizeof(str),"%s{FFFFFF}Двери: {006400}$%d\n",str,FixParts[IdxParts("Двери")][fPrice]);
			zPrice+=FixParts[IdxParts("Двери")][fPrice];
		}
		
		
		if(veh_info[veh][vLights][0] != 0 || veh_info[veh][vLights][1] != 0 || veh_info[veh][vLights][2] != 0 || veh_info[veh][vLights][3] != 0) 
		{
			format(str,sizeof(str),"%s{FFFFFF}Фары: {006400}$%d\n",str,FixParts[IdxParts("Фары")][fPrice]);
			zPrice+=FixParts[IdxParts("Фары")][fPrice];
		}
		
		for(new i=0;i<4;i++) 
		{
			if(veh_info[veh][vTires][i] != 0) 
			{
				format(str,sizeof(str),"%s{FFFFFF}Колесо: {006400}$%d\n",str,FixParts[IdxParts("Колесо")][fPrice]);
				zPrice+=FixParts[IdxParts("Колесо")][fPrice];
			}
		}
		
		
		if(IsCop(playerid) || IsMedic(playerid))
		{
			format(str,sizeof(str),"%s\nИТОГОВАЯ ЦЕНА РЕМОНТА:\t{006400}$%d (50% скидка для гос.служащих)",str,zPrice/2);
			SetPVarInt(playerid,"VEH_PRICE",zPrice/2);
		}
		else
		{
			format(str,sizeof(str),"%s\nИТОГОВАЯ ЦЕНА РЕМОНТА:\t{006400}$%d",str,zPrice);
			SetPVarInt(playerid,"VEH_PRICE",zPrice);
		}
		
		
		SetPVarInt(playerid,"fix_v",veh);
		SetPVarInt(playerid,"fix_p",zPrice);
		
		SYS_AME(playerid, "делает диагностику транспорта");
		
		Dialog_Show(playerid,dListFixZ,DIALOG_STYLE_MSGBOX,"Диагностика",str,"Ремонт","Отмена");

		
		
		
	}
	else
	{
		return SCM(playerid, COLOR_GREY, "Ваша машина должна находиться на подъемнике.");
	}
	
	
	
	
	
	return 1;
}


CMD:fixcar(playerid,params[])
{
	if(sscanf(params,"d", params[0])) return SendClientMessage(playerid,COLOR_GREY,"Используйте /fixcar [ID_PLAYER]");
	if(!IsMech(playerid)) return SendClientMessage(playerid,COLOR_GREY,"Вы должны быть механиком чтобы использовать данную команду.");
	if(!GetPVarInt(playerid,"start_job2")) return SCM(playerid,COLOR_GREY,"Сначало нужно приступить к работе.");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, COLOR_GREY, "Данный игрок находится не в сети.");
	if(!IsPlayerInAnyVehicle(params[0])) return SendClientMessage(playerid, COLOR_GREY, "Игрок должен находиться в машине за рулем.");
	if(params[0] == playerid) return SCM(playerid,COLOR_GREY,"Невозможно использовать на себя.");
	new Float:x,Float:y,Float:z;
	GetPlayerPos(params[0], x,y,z);
	if(!PlayerToPoint(5.0, playerid, x,y,z)) return SendClientMessage(playerid, COLOR_GREY, "Вы должны быть рядом с игроком!");
		
	
	new veh = GetPlayerVehicleID(params[0]);
	new pr_V = GetPVarInt(playerid,"VEH_PRICE");
	
	if(GetPVarInt(playerid,"VEH_FIX") != 0 && GetPVarInt(playerid,"VEH_FIX") == veh)
	{
		SendClientMessage(playerid,0xFFA500FF,"Вы отправили запрос на подтверждение ремонта транспорта, ждите...");
		
		new str[256];
		format(str,sizeof(str),"{FFA500}%s {FFFFFF}предлагает ремонт вашего транспорта(ID: %d) за {006400}$%d. {FFFFFF}Вы действительно хотите этого?",character_info[playerid][name],veh,pr_V);
		Dialog_Show(params[0],dAcceptFix,DIALOG_STYLE_MSGBOX,"Подтверждение ремонта",str,"Принять","Отмена");
		
		
		SetPVarInt(params[0],"price_fixcar",pr_V);
		SetPVarInt(params[0],"veh_fixcar",veh);
		SetPVarInt(params[0],"pl_fixcar",playerid);
		
		
	}
	else
	{
		
		SendClientMessage(playerid, COLOR_GREY, "Для начала вы должны сделать диагностику данного транспорта.");
	}
	DeletePVar(playerid,"VEH_FIX");
	return 1;
}




Dialog:dListFixZ(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new pri = GetPVarInt(playerid,"fix_p");
		new ve = GetPVarInt(playerid,"fix_v");
		
		if(character_info[playerid][money] >= pri)
		{
			SendClientMessage(playerid, 0xFFA500FF, "Вы починили ваше транспортное средство.");
			RepairVehicle(ve);
			
			character_info[playerid][money]-=pri;
			GivePlayerMoney(playerid,-pri);
			
			new result = (pri * 25)/100;
			factions[50][bank] += result;
			
			
		}
		else
		{
			SendClientMessage(playerid, 0xFFA500FF, "У вас недостаточно денежных средств для этой операции.");
		}
	}
	return 1;
}
Dialog:dAcceptFix(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new pri = GetPVarInt(playerid,"price_fixcar");
		new ve = GetPVarInt(playerid,"veh_fixcar");
		
		if(character_info[playerid][money] >= pri)
		{
			SendClientMessage(playerid, 0xFFA500FF, "Вы подтвердили запрос. Ваш транспорт был отремонтирован.");
			RepairVehicle(ve);
			
			character_info[playerid][money]-=pri;
			GivePlayerMoney(playerid,-pri);
			
			new result = (pri * 25)/100;
			factions[50][bank] += result;
			
			
		}
		else
		{
			SendClientMessage(playerid, 0xFFA500FF, "У вас недостаточно денежных средств для этой операции.");
		}
		
		
		
		
	}
	else
	{
		SetPVarInt(playerid,"VEH_FIX",0);
		SetPVarInt(playerid,"VEH_PRICE",0);
	}
	return 1;
}



stock IdxParts(zname[])
{
	for(new i=0;i<sizeof(FixParts);i++)
	{
		if(!strcmp(FixParts[i][fName], zname))
        {
			return i;
		}
	}
	return 0;
}







stock GetDamage(i)
{
	new str[24];
	format(str,sizeof(str),"Unknown");
	
	switch(i)
	{
		case 1: { format(str,sizeof(str),"Легкое повреждение"); }
		case 2: { format(str,sizeof(str),"Среднее повреждение"); }
		case 3: { format(str,sizeof(str),"Тяжелое повреждение"); }
		case 4: { format(str,sizeof(str),"Деталь отсутствует"); }
	}
	return str;
}





#define CAR 0
#define BIKE 1
#define MOTORBIKE 2
#define BOAT 3
#define PLANE 4
#define RC 5
#define TRAIN 6
#define TRAILER 7
#define HELICOPTER 8

stock GetVehiclePanelsDamageStatus(vehicleid, &FrontLeft, &FrontRight, &RearLeft, &RearRight, &WindShield, &FrontBumper, &RearBumper)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	FrontLeft = Panels & 15;
	FrontRight = Panels >> 4 & 15;
	RearLeft = Panels >> 8 & 15;
	RearRight = Panels >> 12 & 15;
	WindShield = Panels >> 16 & 15;
	FrontBumper = Panels >> 20 & 15;
	RearBumper = Panels >> 24 & 15;
	return true;
}

stock GetVehicleDoorsDamageStatus(vehicleid, &Bonnet, &Boot, &FrontLeft, &FrontRight, &RearLeft, &RearRight)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	Bonnet = Doors & 7;
	Boot = Doors >> 8 & 7;
	FrontLeft = Doors >> 16 & 7;
	FrontRight = Doors >> 24 & 7;
	RearLeft = Doors >> 32 & 7;
	RearRight = Doors >> 40 & 7;
	return true;
}

stock GetVehicleLightsDamageStatus(vehicleid, &First, &Second, &Third, &Fourth)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	First = Lights & 1;
	Second = Lights >> 1 & 1;
	Third = Lights >> 2 & 1;
	Fourth = Lights >> 3 & 1;
	return true;
}

stock GetVehicleTiresDamageStatus(vehicleid, &FrontLeft, &FrontRight, &RearLeft, &RearRight)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	if(GetVehicleType(vehicleid) == MOTORBIKE || GetVehicleType(vehicleid) == BIKE) FrontLeft = Tires >> 1 & 1, FrontRight = Tires & 1;
	else
	{
		RearRight = Tires & 1;
		FrontRight = Tires >> 1 & 1;
		RearLeft = Tires >> 2 & 1;
		FrontLeft = Tires >> 3 & 1;
	}
	return true;
}

stock UpdateVehiclePanelsDamageStatus(vehicleid, FrontLeft, FrontRight, RearLeft, RearRight, WindShield, FrontBumper, RearBumper)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	return UpdateVehicleDamageStatus(vehicleid, FrontLeft | (FrontRight << 4) | (RearLeft << 8) | (RearRight << 12) | (WindShield << 16) | (FrontBumper << 20) | (RearBumper << 24), Doors, Lights, Tires);
}

stock UpdateVehicleDoorsDamageStatus(vehicleid, Bonnet, Boot, FrontLeft, FrontRight, RearLeft, RearRight)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	return UpdateVehicleDamageStatus(vehicleid, Panels, Bonnet | (Boot << 8) | (FrontLeft << 16) | (FrontRight << 24) | (RearLeft << 32) | (RearRight << 40), Lights, Tires);
}

stock UpdateVehicleLightsDamageStatus(vehicleid, First, Second, Third, Fourth)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	return UpdateVehicleDamageStatus(vehicleid, Panels, Doors, First | (Second << 1) | (Third << 2) | (Fourth << 3), Tires);
}



stock GetVehicleType(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 400 .. 416, 418 .. 424, 426 .. 429, 431 .. 434, 436 .. 440, 442 .. 445, 451, 455 .. 459, 466, 467, 470, 471, 474, 475, 477 .. 480, 482, 483, 485, 486, 489 .. 492, 494 .. 496, 498 .. 500, 502 .. 508, 514 .. 518, 524 .. 536, 539 .. 547, 549 .. 552, 554 .. 562, 565 .. 568, 571 .. 576, 578 .. 580, 582, 583, 585, 587 .. 589, 596 .. 605, 609: return CAR;
		case 481, 509, 510: return BIKE;
		case 448, 461 .. 463, 468, 521 .. 523, 581, 586: return MOTORBIKE;
		case 430, 446, 452 .. 454, 472, 473, 484, 493, 595: return BOAT;
		case 460, 476, 511 .. 513, 519, 520, 553, 577, 592, 593: return PLANE;
		case 441, 464, 465, 501, 564, 594: return RC;
		case 449, 537, 538, 569, 570, 590: return TRAIN;
		case 435, 450, 584, 591, 606 .. 608, 610, 611: return TRAILER;
		case 417, 425, 447, 469, 487, 488, 497, 548, 563: return HELICOPTER;
	}
	return -1;
}

stock UpdateVehicleTiresDamageStatus(vehicleid, FrontLeft, FrontRight, RearLeft, RearRight)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	if(GetVehicleType(vehicleid) == MOTORBIKE || GetVehicleType(vehicleid) == BIKE) return UpdateVehicleDamageStatus(vehicleid, Panels, Doors, Lights, FrontRight | (FrontLeft << 1));
	else return UpdateVehicleDamageStatus(vehicleid, Panels, Doors, Lights, RearRight | (FrontRight << 1) | (RearLeft << 2) | (FrontLeft << 3));
}











