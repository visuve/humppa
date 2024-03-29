#include <iostream>
#include <chrono>
#include <clocale>
#include <vector>

const std::vector<std::u8string> encrypted_messages
{
	{ //1
		0x1b, 0x3c, 0x43, 0x9c, 0x88, 0xf1, 0x4c, 0x4c,
		0x41, 0x42, 0x3d, 0xfb, 0x4a, 0x30, 0x44, 0x88,
		0x6a, 0x5a, 0xe4, 0x57, 0x5f, 0x56, 0x2d, 0x22,
		0xee, 0x22, 0x5f, 0x56, 0x58, 0x55, 0x0b
	},
	{ //2
		0x20, 0x47, 0x4e, 0x48, 0x44, 0x4a, 0x38, 0x4b,
		0xf1, 0x4d, 0x9c, 0x70, 0x9a, 0x72, 0xf7, 0x52,
		0x52, 0x53, 0xeb, 0x2d, 0x51, 0x2d, 0x54, 0x5e,
		0x58, 0x56, 0x5e, 0x5d, 0x51, 0xe6, 0x5d, 0x1d,
		0x6d, 0x63, 0x64, 0x68, 0xb2, 0x5a, 0x34
	},
	{ //3
		0x2a, 0x40, 0x43, 0x49, 0x3d, 0x46, 0x41, 0x36,
		0x4b, 0xf3, 0x4a, 0x34, 0x4a, 0x31, 0x4d, 0x50,
		0x5c, 0x5e, 0x55, 0x59, 0x2d, 0xef, 0x51, 0x58,
		0x59, 0x5d, 0x56, 0x8a, 0x60, 0x88, 0x62, 0xd9,
		0x6a, 0x62, 0x63, 0x1a, 0x67, 0x63, 0x62, 0x10,
		0x2c, 0xd3, 0x15, 0x60, 0x6e, 0xd7, 0x10, 0x0c,
		0x0a, 0x7e, 0x0b, 0xcd, 0x78, 0x7a, 0x72, 0x04,
		0x05, 0xc3, 0x04, 0x70, 0x7b, 0x73, 0xc6, 0x0d,
		0x03, 0x07, 0x06, 0x06, 0x06, 0xbf, 0x0a, 0x74,
		0x0c, 0x74, 0x75, 0x74, 0x0a, 0x0e, 0x09, 0x1d,
		0x69, 0x40
	},
	{ //4
		0x1e, 0x45, 0x38, 0xfe, 0x44, 0x46, 0xfd, 0x33,
		0x36, 0x35, 0x4c, 0x4a, 0x4b, 0x49, 0xf5, 0x5c,
		0x52, 0x5f, 0x55, 0x23, 0x56, 0x28, 0x44, 0x59,
		0x5b, 0x5e, 0x5c, 0x59, 0x50, 0x29, 0x21, 0x1e,
		0x1a, 0x22
	},
	{ //5
		0x17, 0x45, 0x44, 0x32, 0xfe, 0x41, 0x41, 0x37,
		0x3f, 0xf1, 0x47, 0x36, 0x37, 0x30, 0x35, 0x2a,
		0x50, 0xe8
	},
	{ //6
		0x1c, 0x49, 0x46, 0x39, 0x4e, 0x4e, 0x3a, 0xf4,
		0x36, 0x34, 0xf7, 0x4f, 0x34, 0x45, 0x4c, 0x59,
		0x5a, 0x5a, 0x2a, 0x54, 0x5d, 0x5f, 0xeb, 0x25,
		0x52, 0x5f, 0x26, 0x22, 0x22, 0x5f, 0x22, 0x65,
		0x6a, 0x1b, 0x1d, 0xd8, 0x66, 0x1b, 0x19, 0x63,
		0x62, 0x17, 0xd7, 0x6e, 0x10, 0xd2, 0x6b, 0xab,
		0x49, 0x0c, 0xcf, 0x0b, 0x0b, 0xca, 0x73, 0x05,
		0x79, 0x73, 0x78, 0x01, 0x76, 0xc2, 0x7b, 0x7d,
		0x0b, 0x00, 0x7c, 0x01, 0x0d, 0x0f, 0x04, 0x03,
		0x70, 0x73, 0x75, 0xb2
	},
	{ //7
		0x2b, 0x3a, 0xfe, 0x44, 0x41, 0x44, 0x9d, 0x71,
		0xf4, 0x43, 0x35, 0x48, 0x4d, 0x4a, 0x4b, 0xed,
		0x58, 0x2a, 0x57, 0x2d, 0x8f, 0x6f, 0x28, 0xe5,
		0x4d, 0x5a, 0x56, 0x86, 0x64, 0x55, 0x5b, 0x6a,
		0x68, 0xb8, 0xa4, 0x6e, 0x6f, 0xbc, 0x5e, 0x29,
		0xd4, 0x63, 0x15, 0x68, 0x6d, 0x6a, 0x6b, 0xcd,
		0x71, 0x66, 0xa9, 0xb3, 0x7f, 0xcb, 0x77, 0x70,
		0x71, 0x06, 0x7a, 0x7d, 0x01, 0x7c, 0x7b, 0x7f,
		0xbd
	},
	{ //8
		0x2f, 0x35, 0x41, 0xa5, 0x87, 0x3a, 0xf9, 0x33,
		0x36, 0x58, 0x48, 0x37, 0x32, 0x5c, 0x38, 0x27,
		0x28, 0x2d, 0x42, 0x46, 0x2a, 0xe8, 0x2f, 0x27,
		0xe7, 0x2c, 0x24, 0x4c, 0x4d, 0x21, 0x4e, 0x72,
		0x1e, 0x1e, 0xdd, 0x1d, 0x75, 0x61, 0x69, 0x7a,
		0x14, 0x10, 0x16, 0x69, 0x1a, 0x11, 0x10, 0xcc
	},
	{ //9
		0x2e, 0x50, 0x51, 0x56, 0x32, 0x31, 0x30, 0xf5,
		0xf4, 0xf7
	},
	{ //10
		0x1b, 0x9d, 0x87, 0x3d, 0x4a, 0x49, 0x98, 0x8c,
		0x09, 0x3c, 0x94, 0x88, 0x43, 0x38, 0x4a, 0x5f,
		0x45, 0x57, 0x2f, 0x29, 0x2c, 0x59, 0x58, 0x87,
		0x9d, 0x1a, 0x3a, 0x23, 0x49, 0x27, 0x4d, 0x65,
		0x21, 0x06, 0x1a, 0x6a, 0x60, 0x19, 0x73, 0x13,
		0x67, 0x63, 0x11, 0x2c, 0x1a, 0xb1, 0xab, 0x79,
		0x65, 0x66, 0xac, 0xb0, 0x08, 0x0f, 0x0d, 0x7d,
		0x03, 0x3a, 0x00, 0x06, 0x3d, 0x09, 0x06, 0x05,
		0x7d, 0x7e, 0x06, 0x10, 0x11, 0x0f, 0xd8, 0xcc,
		0x49, 0x73, 0x73, 0x0d, 0x77, 0x4e, 0x6a, 0x65,
		0xac, 0x06, 0x12, 0x1b, 0x14, 0x6a, 0x6b, 0x19,
		0xa3
	},
	{ //11
		0x25, 0x3a, 0x35, 0x44, 0x3d, 0x07, 0x49, 0x4c,
		0x08, 0x44, 0x33, 0x59, 0x93, 0x8b, 0x0e, 0x41,
		0x59, 0x47, 0x2a, 0x2e, 0x2e, 0x17, 0x21, 0x58,
		0x2f, 0x2c, 0x21, 0x52, 0x48, 0x5e, 0x1e, 0x75,
		0x61, 0x6d, 0x70, 0x1c, 0x2f
	},
	{ //12
		0x19, 0x3d, 0x01, 0x56, 0x3e, 0x3d, 0x53, 0x46,
		0xac, 0x74, 0xae, 0x72, 0x0f, 0x33, 0x30, 0x28,
		0x2e, 0x24, 0x25, 0xb1, 0x6b, 0x14, 0x2e, 0x20,
		0x1b, 0x2c, 0x20, 0x27, 0x53, 0x51, 0x5c, 0xd8
	},
	{ //13
		0x17, 0x40, 0x3b, 0x07, 0x3d, 0x31, 0x3d, 0x0b,
		0x30, 0x32, 0x37, 0x30, 0x33, 0x39, 0x4d, 0x13,
		0x42, 0x2a, 0x29, 0x28, 0x57, 0xef
	},
	{ //14
		0x1e, 0x3f, 0x3c, 0x41, 0x47, 0x3b, 0x57, 0x35,
		0x3f, 0x0e, 0x33, 0xaf, 0x8d, 0x32, 0x32, 0x5e,
		0x50, 0x40, 0x28, 0x23, 0x2d, 0x2e, 0x52, 0x1c,
		0x49, 0x4b, 0x23, 0x5d, 0x5c, 0x1a, 0x24, 0x1d,
		0x1c, 0x14, 0x73, 0x13, 0x1d, 0x67, 0x69, 0x65,
		0x2d, 0x7e, 0x7a, 0x14, 0x15, 0x19, 0x19, 0x0b,
		0x74, 0x63, 0x0b, 0x71, 0x0e, 0x65, 0x0a, 0xce
	},
	{ //15
		0x34, 0x46, 0x40, 0x3d, 0x33, 0x03, 0x27, 0x5a,
		0x4b, 0x3c, 0x48, 0x48, 0x5e, 0x0b, 0x39, 0x29,
		0x2d, 0x17, 0x41, 0x54, 0x2c, 0x2f, 0x53, 0x24,
		0x2e, 0x5a, 0x2c, 0x19, 0x27, 0x5e, 0x25, 0x72,
		0x61, 0x1b, 0x1f, 0x86, 0xa4, 0x74, 0x22, 0x7d,
		0x15, 0x6a, 0x1c, 0x60, 0x7e, 0x12, 0x7e, 0x61,
		0x93, 0xb3, 0x08, 0x96, 0xb4, 0xc1
	},
	{ //16
		0x34, 0x50, 0x4c, 0x3d, 0x4a, 0x3c, 0x56, 0x5d,
		0x0f, 0x30, 0x30, 0x59, 0x5e, 0x49, 0x36, 0x29,
		0x56, 0x14, 0x2a, 0x5b, 0x41, 0x42, 0x5c, 0x1e,
		0x25, 0x5d, 0x23, 0x5b, 0x24, 0x24, 0x4a, 0x75,
		0x75, 0x24, 0x1a, 0x1f, 0x71, 0x20, 0x69, 0x63,
		0x7d, 0x7b, 0x64, 0x7e, 0x84, 0x52, 0x7e, 0x65,
		0x7f, 0x08, 0x74, 0x7b, 0x0c, 0x79, 0x70, 0x3e,
		0x7e, 0x03, 0x70, 0x73, 0x07, 0x79, 0x3a
	},
	{ //17
		0x1a, 0xaa, 0x88, 0x3f, 0xad, 0x8d, 0x00, 0x5c,
		0x5c, 0x0d, 0x5b, 0x58, 0x5e, 0x5c, 0x45, 0x17,
		0x41, 0x58, 0x2a, 0x2f, 0x53, 0x50, 0x10, 0x52,
		0x4c, 0x4f, 0x51, 0x49, 0x4d, 0x50, 0x4a, 0x27,
		0x1f, 0x1b, 0x6d, 0x1f, 0x6f, 0x1d, 0x1c, 0x16,
		0x3a, 0x2d, 0x61, 0x62, 0x7d, 0x86, 0xa4, 0x37,
		0x65, 0x61, 0x79, 0x33, 0x61, 0x63, 0x62, 0x76,
		0x01, 0x01, 0x01, 0x69, 0x07, 0x05, 0x39
	},
	{ //18
		0x19, 0x51, 0x52, 0x33, 0x39, 0x57, 0x55, 0x00,
		0x31, 0x4b, 0x37, 0x5c, 0x5e, 0x5c, 0x5e, 0x42,
		0x05, 0x1a, 0x5c, 0x29, 0x47, 0x1e, 0x42, 0x49,
		0x56, 0xbd, 0x97, 0xbb, 0x91, 0x4c, 0x17, 0x6d,
		0x70, 0x2a, 0x1f, 0x77, 0x74, 0x73, 0x76, 0x7a,
		0x14, 0x38
	},
	{ //19
		0x1c, 0xa4, 0x8e, 0xa2, 0x88, 0x0f, 0x55, 0x5b,
		0x00, 0x45, 0x37, 0x59, 0x43, 0x5e, 0x5c, 0x5c,
		0x42, 0x07, 0x1a, 0x40, 0x29, 0x2b, 0x2a, 0x50,
		0x10, 0x54, 0xbd, 0x91, 0x2b, 0x4e, 0x22, 0x6c,
		0x74, 0x6c, 0x85, 0xa9, 0x83, 0xab, 0x2e, 0x7b,
		0x79, 0x7a, 0x78, 0x39, 0x24, 0x60, 0x13, 0x60,
		0x62, 0x3b, 0x61, 0x61, 0x65, 0x00, 0x67, 0x31,
		0x04, 0x06, 0x0c, 0x07, 0x75, 0x6b, 0x03, 0x12,
		0x0f, 0x12, 0x7e, 0x08, 0x10, 0x7b, 0x7b, 0x00,
		0x5a
	},
	{ //20
		0x1d, 0x49, 0x4d, 0x4a, 0x56, 0x4d, 0x0d, 0x4f,
		0x5a, 0x00, 0x33, 0x5d, 0x5e, 0x38, 0x44, 0x1e,
		0x1b, 0x46, 0x42, 0x29, 0x1f, 0x2c, 0x50, 0x56,
		0x4c, 0xb7, 0x9d, 0xb1, 0x9b, 0x0e
	},
	{ //21
		0x16, 0xae, 0x84, 0x38, 0x39, 0xaa, 0x80, 0x03,
		0x5d, 0x40, 0x3c, 0x5c, 0x06, 0x5c, 0x33, 0x40,
		0x5f, 0x5c, 0x59, 0x23, 0x1e, 0x2d, 0x55, 0xb4,
		0x60, 0x27, 0xb7, 0x9b, 0x2a, 0x15, 0x24, 0x62,
		0x8d, 0x5b, 0x1e, 0x76, 0x77, 0x37
	},
	{ //22
		0x30, 0x4b, 0x56, 0x54, 0x55, 0xad, 0x8f, 0x04,
		0x46, 0x44, 0x07, 0x5f, 0x40, 0x5b, 0x5c, 0x43,
		0x44, 0x1e, 0x25, 0x41, 0x2f, 0x2e, 0x2e, 0x55,
		0x49, 0x4f, 0x20, 0x53, 0x48, 0x26, 0x26, 0x6d,
		0x2f
	},
	{ //23
		0x29, 0x52, 0x53, 0xae, 0x8c, 0x0b, 0x30, 0x5c,
		0x5d, 0x33, 0x32, 0x58, 0x37, 0x03, 0x36, 0x28,
		0x40, 0x43, 0x5f, 0x19, 0x2f, 0x42, 0x58, 0x57,
		0x51, 0x17, 0x0c, 0x48, 0x26, 0x50, 0x51, 0x6f,
		0x30, 0x2f, 0x71, 0x1c, 0x28, 0x6a, 0x6b, 0x11,
		0x10, 0x62, 0x7a, 0x78, 0x62, 0x23, 0x16, 0x9a,
		0xb8, 0x08, 0x09, 0x9e, 0xbc, 0x3b, 0x00, 0x92,
		0xb0, 0x6f, 0x91, 0xb5, 0x72, 0x33, 0x6e, 0x08,
		0x7c, 0xe8, 0xca, 0x10, 0x14, 0x17, 0xed, 0xc1,
		0x44, 0x02, 0x04, 0x03, 0x05, 0x01, 0x42, 0x6b,
		0x19, 0x06, 0x69, 0x6e, 0x6d, 0x1a, 0x58
	},
	{ //24
		0x26, 0x1c, 0x42, 0x57, 0x54, 0x08, 0x4a, 0x44,
		0x07, 0x34, 0x46, 0x4b, 0x44, 0x47, 0x48, 0x1f
	},
	{ //25
		0x2b, 0xb2, 0x90, 0x0b, 0x42, 0x48, 0x4c, 0x4a,
		0x47, 0x47, 0x00, 0x03, 0x5f, 0x4d, 0x4c, 0xa0,
		0x82, 0x1d, 0x50, 0x46, 0x47, 0x55, 0x54, 0x4a,
		0x16, 0x5a, 0x49, 0x56, 0x57, 0x52, 0x5f, 0x72,
		0x6c, 0x2d, 0x11, 0x13, 0x75, 0x74, 0x6c, 0x6e,
		0x64, 0x21, 0x24, 0x65, 0x61, 0x6e, 0x6f, 0x7e,
		0x3e, 0x7f, 0x83, 0xa7, 0x7d, 0x00, 0x01, 0x37,
		0x7c, 0x74, 0x70, 0x79, 0x71, 0x73, 0x72, 0x0e,
		0x0c, 0x4d, 0x00, 0x02, 0x0e, 0x08, 0x4a
	},
	{ //26
		0x2a, 0x42, 0x43, 0x4d, 0x49, 0x57, 0x56, 0x4c,
		0x19, 0x5f, 0x42, 0x1c, 0x4d, 0x37, 0x30, 0x29,
		0x01, 0x59, 0x53, 0x41, 0x51, 0x53, 0x50, 0x27,
		0x4c, 0x25, 0x24, 0x4d, 0x0d, 0x5e, 0x4a, 0x1e,
		0x8e, 0xb6, 0x1c, 0x1b, 0x8a, 0xb2, 0x2b, 0x38,
		0x6f, 0x61, 0x14, 0x3c, 0x66, 0x6e, 0x7a, 0x74,
		0x75, 0x63, 0x75, 0x65, 0x79, 0x7a, 0x66, 0x28,
		0x72, 0x70, 0x2b, 0x23, 0x22, 0x0a, 0x32, 0x0c,
		0x14, 0x00, 0x7a, 0x4e
	},
	{ //27
		0x1f, 0x56, 0x12, 0x4e, 0x4e, 0x17, 0x4f, 0x41,
		0x59, 0x41, 0x1a, 0x32, 0x5d, 0x42, 0x5f, 0x01,
		0x5d, 0x5a, 0x56, 0xba, 0x80, 0x07, 0x29, 0x48,
		0x52, 0x50, 0x5e, 0x59, 0x49, 0x13, 0x0e, 0x6b,
		0x69, 0x6a, 0x68, 0x35, 0x04, 0x62, 0x6d, 0x65,
		0x79, 0x7a, 0x60, 0x3d, 0x13, 0x7a, 0x3e, 0x7d,
		0x9f, 0xa7, 0x7a, 0x71, 0x61, 0x62, 0x26, 0x7e,
		0x7d, 0x72, 0x7e, 0x68, 0x76, 0x78, 0x77, 0x0b,
		0x4a
	},
	{ //28
		0x29, 0x4b, 0x11, 0x4b, 0x4d, 0x43, 0x15, 0x48,
		0x36, 0x43, 0x43, 0x44, 0x5e, 0x1c, 0x4a, 0x5f,
		0x03, 0x5b, 0x5b, 0x12, 0x07, 0x59, 0x29, 0x26,
		0xac, 0x94, 0x09, 0x59, 0x56, 0x58, 0x59, 0x69,
		0x6a, 0x6a, 0x31, 0x1a, 0x76, 0x62, 0x67, 0x63,
		0x61, 0x38, 0x63, 0x67, 0x66, 0x10, 0x9a, 0xbe,
		0x39
	},
	{ //29
		0x2c, 0x4a, 0x4b, 0x17, 0x49, 0x3c, 0x40, 0x4f,
		0xbd, 0x85, 0x18, 0x48, 0x43, 0x1d, 0x3d, 0x59,
		0x55, 0x58, 0x46, 0x53, 0x5b, 0x05, 0x56, 0x4a,
		0x53, 0x56, 0x25, 0x23, 0x22, 0x4c, 0x4d, 0x33,
		0x6b, 0x69, 0x71, 0x6d, 0x36, 0x6d, 0x1d, 0x69,
		0x9d, 0xa5, 0x6c, 0x13, 0x99, 0xa1, 0x26, 0x23,
		0x1d, 0x60, 0x0c, 0x7c, 0x7f, 0x7f, 0x24, 0x7b,
		0x6b, 0x7f, 0x71, 0x2f, 0x7c, 0x74, 0x70, 0x0e,
		0x09, 0x0a, 0x50, 0x5e, 0x0d, 0x78, 0x78, 0x76,
		0x1c, 0x04, 0x0f, 0x73, 0x1f, 0x47
	},
	{ //30
		0x26, 0x4a, 0x4e, 0x42, 0x11, 0x45, 0x4a, 0x45,
		0x4f, 0xb9, 0x9b, 0x18, 0x46, 0xbd, 0x9f, 0x53,
		0x5c, 0x52, 0x2e, 0x5f, 0x56, 0x47, 0x54, 0x5b,
		0xaa, 0x8a, 0x0f, 0x4d, 0x5d, 0x5e, 0x4e, 0x6d,
		0x35, 0x65, 0x64, 0x30, 0x65, 0x77, 0x6b, 0x68,
		0x14, 0x3e, 0x62, 0x61, 0x6d, 0x9d, 0xbf, 0x83,
		0xa1, 0x74, 0x35, 0x20, 0x12, 0x7e, 0x7a, 0x7e,
		0x2d, 0x7e, 0x76, 0x7c, 0x76, 0x8d, 0xaf, 0xf3,
		0xd1, 0x04, 0x57, 0x07, 0x10, 0x0b, 0x05, 0x1d,
		0x0a, 0x02, 0x0c, 0x05, 0x18, 0x06, 0x07, 0x05,
		0x57
	},
	{ //31
		0x27, 0x4b, 0x4f, 0x46, 0x49, 0x13, 0x4a, 0x34,
		0x36, 0xb8, 0x9a, 0x19, 0x4b, 0x47, 0x46, 0x44,
		0x04, 0x57, 0x50, 0x52, 0x54, 0x50, 0x5d, 0x5e,
		0x50, 0x53, 0x4f, 0x14, 0x5b, 0x5c, 0x4b, 0x74,
		0x69, 0x6e, 0x61, 0x65, 0x71, 0x21
	},
};

std::u8string message_of_the_day(const std::chrono::year_month_day& ymd)
{
	if (!ymd.ok())
	{
		throw std::invalid_argument("Ei hevostella!");
	}

	size_t i = static_cast<uint32_t>(ymd.day()) - 1;

	if (i >= encrypted_messages.size())
	{
		throw std::runtime_error("Laiska koodari.");
	}

	std::u8string message = encrypted_messages[i];

	for (size_t j = 0; j < message.size(); ++j)
	{
		char8_t& xored = message[j];
		xored ^= (j + 1);
		xored += 0x2Au;
		xored ^= (i + 1);
	}

	return message;
}

int main()
{
	std::setlocale(LC_ALL, "fi_FI.UTF-8");

	try
	{
		const auto now = std::chrono::system_clock::now();
		const auto ymd = std::chrono::floor<std::chrono::days>(now);
		
		std::cout << "Nyt on " << std::format("{:%d.%m.%Y}.", ymd) << std::endl;

		const std::u8string motd = message_of_the_day(ymd);

		std::cout << "\nPultsarin suusta kuuluu: " << std::endl;
		printf("\t\"%s\"\n", motd.c_str());
	}
	catch (const std::exception& e)
	{
		std::cerr << "Kaikki on mennyttä: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}
