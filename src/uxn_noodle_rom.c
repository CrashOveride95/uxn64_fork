const u16 uxn_rom[] = {
    0xa001, 0xcf80, 0x1037, 0xa003, 0x4880, 0x4f31, 0xa003, 0x7380,
    0x6331, 0xa003, 0x9680, 0x6d31, 0xa003, 0xc180, 0x8131, 0xa070,
    0xfe80, 0x0837, 0xa0c0, 0xf380, 0x0a37, 0xa090, 0xf380, 0x0c37,
    0xa016, 0x322e, 0xa004, 0x0311, 0xa000, 0x0411, 0xa000, 0x0211,
    0xa000, 0x08a0, 0x0008, 0xa007, 0x672e, 0xa000, 0x28a0, 0x0012,
    0xa007, 0x822e, 0x8022, 0x3680, 0x033f, 0x0380, 0x0719, 0x8024,
    0x3680, 0x033f, 0x0380, 0x0419, 0xa007, 0x062e, 0x8059, 0x1080,
    0x0219, 0x805a, 0x1080, 0x0219, 0xa007, 0xa52e, 0xa001, 0x852e,
    0xa00c, 0x412e, 0x00a0, 0x029a, 0x8020, 0x37a0, 0x052a, 0x8080,
    0x37a0, 0x02a8, 0x8090, 0x3780, 0x06a0, 0x111a, 0x2ea0, 0x0096,
    0x176c, 0xa002, 0x7a80, 0x2037, 0xa002, 0x0680, 0x8037, 0xa002,
    0x9b80, 0x9037, 0x8006, 0xa011, 0x1a2e, 0xa000, 0x9617, 0x800c,
    0x3080, 0x2837, 0x800e, 0x3080, 0x2a37, 0xa040, 0x2f17, 0x6c80,
    0x00a0, 0x111a, 0x2e80, 0x0080, 0x0e0d, 0xa001, 0xf813, 0xa000,
    0x83a0, 0x0040, 0xa016, 0xa92e, 0x8012, 0x1606, 0x0680, 0x1f0a,
    0x0480, 0x7f0b, 0x1c80, 0x040d, 0xa000, 0xda13, 0x8022, 0x0e80,
    0x06a0, 0x111a, 0x2e00, 0x8000, 0xa011, 0x1a2e, 0x8083, 0x1606,
    0x800d, 0x0880, 0x031a, 0x1980, 0x070e, 0x8006, 0xa011, 0x1a2e,
    0x0006, 0x8002, 0x0d02, 0x6c80, 0x0889, 0x0380, 0x090d, 0xa000,
    0x83a0, 0x16f3, 0x2e02, 0x6c80, 0x0a89, 0x0380, 0x040d, 0xa00c,
    0x762e, 0x807f, 0x8903, 0x800c, 0x0da0, 0x0083, 0xa000, 0x40a0,
    0x16a9, 0x2e02, 0x6c80, 0x208a, 0x0380, 0x060d, 0xa001, 0x852e,
    0x026c, 0xa000, 0x83a0, 0x16cb, 0x2e03, 0x803f, 0x0880, 0x080d,
    0x06a0, 0x0083, 0xa016, 0xee2e, 0x026c, 0x8000, 0x1006, 0x8007,
    0x1c80, 0x110d, 0x0680, 0x031f, 0x8001, 0x1c80, 0x101f, 0x8006,
    0x18a0, 0x111a, 0x2e01, 0x8000, 0x1100, 0x0080, 0x9616, 0x8000,
    0x090c, 0x00a0, 0x0185, 0x2e00, 0xa00f, 0x112e, 0x8011, 0x1080,
    0x0008, 0x800e, 0x0d80, 0x9616, 0x8000, 0x0980, 0x050d, 0xa003,
    0x2a2e, 0x0080, 0x9236, 0x8094, 0x3680, 0x1110, 0x8000, 0x0a80,
    0x9616, 0x8000, 0x0a1c, 0x8056, 0x0d27, 0x2780, 0x47a0, 0x11d4,
    0x2ea0, 0x03ee, 0x2d80, 0x1210, 0x8030, 0x0d27, 0x2780, 0x5ba0,
    0x11d4, 0x2ea0, 0x04f7, 0x2d27, 0x2780, 0x65a0, 0x11d4, 0x2ea0,
    0x0508, 0x2d27, 0x2780, 0x79a0, 0x11d4, 0x2ea0, 0x0519, 0x2d27,
    0x2780, 0x6fa0, 0x11d4, 0x2ea0, 0x04bf, 0x2d27, 0x2780, 0x51a0,
    0x11d4, 0x2ea0, 0x04ce, 0x2d22, 0x2200, 0xa000, 0x1111, 0x6c80,
    0x1110, 0x8008, 0x1830, 0x2c00, 0x8011, 0x1180, 0x9236, 0x8008,
    0x3180, 0x9436, 0x800a, 0x316c, 0xa00f, 0xc32e, 0xa00d, 0x212e,
    0x2680, 0x0a30, 0x392f, 0x800a, 0x3180, 0x4930, 0x6f38, 0x2f26,
    0x8008, 0x3039, 0x2f80, 0x0831, 0x8047, 0x306f, 0x386f, 0xa007,
    0x672e, 0x0080, 0x5330, 0x39a0, 0x0008, 0x3880, 0x033f, 0x030f,
    0x8051, 0x3039, 0xa000, 0x0838, 0x8003, 0x3f03, 0x4fa0, 0x0706,
    0x2ea0, 0x0ffe, 0x2e00, 0xa00f, 0xd92e, 0x2680, 0x0a30, 0x392f,
    0x800a, 0x3180, 0x5330, 0x6f38, 0x2f26, 0x8008, 0x3039, 0x2f80,
    0x0831, 0x8051, 0x306f, 0x386f, 0xa007, 0x822e, 0xa00f, 0xfe2e,
    0x00a0, 0x005a, 0x1080, 0x011f, 0x8030, 0x3f80, 0x5330, 0x3839,
    0x8002, 0x3f03, 0x0fa0, 0x0059, 0x1080, 0x011f, 0x8030, 0x3f80,
    0x5130, 0x3839, 0x8002, 0x3f03, 0x4fa0, 0x07a5, 0x2e00, 0x8096,
    0x1680, 0x030d, 0x2222, 0x0080, 0x4930, 0xa000, 0x0338, 0x39a0,
    0x000a, 0x3b03, 0x0f80, 0x4730, 0x39a0, 0x000a, 0x3b03, 0x4f07,
    0x8002, 0x0b80, 0x020d, 0x2200, 0x0680, 0x0308, 0x804c, 0x0d06,
    0x8008, 0x0880, 0x450d, 0xa000, 0x9617, 0x0680, 0x030b, 0x8019,
    0x0d06, 0x8003, 0x0a07, 0x8008, 0x0b1c, 0x8016, 0x0d06, 0x8007,
    0x0a07, 0x800d, 0x0b1c, 0x8016, 0x0d00, 0x8010, 0x1f18, 0xa006,
    0x962e, 0x0080, 0x0419, 0x8010, 0x1f18, 0xa006, 0x9e2e, 0x0080,
    0x0919, 0x8010, 0x1f18, 0xa006, 0xb32e, 0x0022, 0x8047, 0xa003,
    0x382e, 0x00a0, 0x0077, 0x10a0, 0x0078, 0x103a, 0x8030, 0x3f6c,
    0xa00b, 0xdba0, 0x0bba, 0x8096, 0x1680, 0x010a, 0x8007, 0x1018,
    0x8001, 0x0d24, 0x2280, 0x0531, 0xa000, 0x9616, 0x8000, 0x0a80,
    0x101f, 0x8010, 0x1080, 0x000a, 0x1880, 0x101f, 0x8002, 0x1080,
    0x301f, 0x18a0, 0x134d, 0x3834, 0x8096, 0x1680, 0x1011, 0x6c80,
    0x7130, 0x3924, 0x806f, 0x3039, 0x2480, 0xb40e, 0x2c00, 0x8012,
    0x1080, 0x0008, 0x801d, 0x0d80, 0x5330, 0x3980, 0x033f, 0x8015,
    0x3038, 0x2480, 0x5130, 0x3980, 0x033f, 0x8013, 0x3038, 0x2480,
    0x8e0e, 0x2c00, 0x2222, 0x0022, 0x2280, 0x9616, 0x8000, 0x090c,
    0x0080, 0x5ba0, 0x0338, 0x2e00, 0x2222, 0x8096, 0x1680, 0x0009,
    0x0c00, 0x8065, 0xa003, 0x382e, 0x0022, 0x2280, 0x9616, 0x8000,
    0x090c, 0x0080, 0x79a0, 0x0338, 0x2e00, 0x8082, 0x1606, 0x8001,
    0x1ca0, 0x0608, 0x2d06, 0x80f0, 0x1ca0, 0x0642, 0x2d06, 0x8004,
    0x0980, 0x040d, 0xa006, 0xd82e, 0x0680, 0x0809, 0x800c, 0x0d80,
    0x0790, 0x8000, 0x0804, 0x11a0, 0x108b, 0x2e02, 0x8083, 0x1680,
    0x0089, 0x0380, 0x020d, 0x0200, 0x8009, 0x8903, 0x8006, 0x0d02,
    0xa006, 0xe92e, 0x0080, 0x2089, 0x0380, 0x040d, 0xa006, 0xd82e,
    0x8071, 0x8903, 0x8006, 0x0d80, 0x00a0, 0x0696, 0x2e80, 0x7789,
    0x0380, 0x060d, 0x8001, 0xa006, 0x962e, 0x8065, 0x8903, 0x8006,
    0x0d80, 0x02a0, 0x0696, 0x2e80, 0x7289, 0x0380, 0x060d, 0x8003,
    0xa006, 0x962e, 0x8074, 0x8903, 0x8006, 0x0d80, 0x04a0, 0x0696,
    0x2e80, 0x7989, 0x0380, 0x060d, 0x8005, 0xa006, 0x962e, 0x805b,
    0x8903, 0x800a, 0x0d80, 0x0310, 0x8001, 0x19a0, 0x06b3, 0x2e80,
    0x5d89, 0x0380, 0x080d, 0x8003, 0x1001, 0xa006, 0xb32e, 0x0606,
    0x8030, 0x0a04, 0x8039, 0x0ba0, 0x0101, 0x2980, 0x080d, 0x0680,
    0x3119, 0xa006, 0x9e2e, 0x0200, 0x0280, 0x8316, 0x806e, 0x8903,
    0x8006, 0x0da0, 0x0c41, 0x2e02, 0x0080, 0x7289, 0x0380, 0x060d,
    0xa001, 0xa22e, 0x0200, 0x806f, 0x8903, 0x8006, 0x0da0, 0x0c76,
    0x2e02, 0x0080, 0x7389, 0x0380, 0x060d, 0xa00c, 0xcd2e, 0x0200,
    0x0200, 0x8012, 0x1080, 0x020d, 0x0200, 0x0680, 0x101c, 0x8000,
    0x0880, 0x090d, 0x8015, 0xb0a0, 0x0001, 0x3905, 0x3106, 0x8020,
    0x1c80, 0x0008, 0x8006, 0x0d80, 0x15b0, 0x2105, 0x3106, 0x8040,
    0x1c80, 0x0008, 0x8009, 0x0d80, 0x13b0, 0xa000, 0x0139, 0x0531,
    0x0680, 0x801c, 0x8000, 0x0880, 0x060d, 0x8013, 0xb021, 0x0531,
    0x02a0, 0x0d4f, 0x2e00, 0x8002, 0x11a0, 0x1053, 0x2e6c, 0x8007,
    0x1c80, 0x0411, 0x8002, 0x1080, 0x040d, 0xa001, 0xe80e, 0xa010,
    0x6f2e, 0x6c80, 0x071c, 0x0680, 0x0310, 0x0980, 0x080d, 0x8007,
    0x9080, 0x0008, 0x0411, 0x8003, 0x1180, 0x0210, 0x8004, 0x0da0,
    0x01c3, 0x0ea0, 0x108b, 0x2e6c, 0x8012, 0x9080, 0x0008, 0x0411,
    0xa00d, 0x212e, 0xa00f, 0xfe2e, 0x6ca0, 0x1ebd, 0xafa0, 0x0473,
    0x2e38, 0x6faf, 0x9480, 0xff1e, 0x6f15, 0x21aa, 0x80f4, 0x0d22,
    0x22a0, 0x0d4f, 0x2e6c, 0x2680, 0x5930, 0x2880, 0x570d, 0x0680,
    0x010b, 0x8050, 0x0d07, 0x8001, 0x0b80, 0x490d, 0x0680, 0x2436,
    0x8003, 0x3f03, 0x8004, 0x190a, 0x803a, 0x0d07, 0x8022, 0x3680,
    0x033f, 0x0380, 0x0719, 0x0a80, 0x2b0d, 0xa00f, 0xd92e, 0x0680,
    0x5a11, 0x8000, 0x0480, 0x303f, 0x8053, 0x3038, 0x8057, 0x3106,
    0x8059, 0x1180, 0x0004, 0x8030, 0x3f80, 0x5130, 0x3880, 0x5531,
    0xa007, 0xd52e, 0x6c22, 0x6c26, 0x8049, 0x31a0, 0x0088, 0x3880,
    0x4d31, 0x2680, 0x4731, 0xa000, 0x1838, 0x804b, 0x31a0, 0x0ffe,
    0x2e6c, 0x2680, 0x5331, 0xa000, 0x5a10, 0x8030, 0x3f38, 0x8057,
    0x3126, 0x8051, 0x31a0, 0x0059, 0x1080, 0x303f, 0x3880, 0x5531,
    0xa007, 0xd52e, 0x6c26, 0x8077, 0x3028, 0x8026, 0x0d06, 0x8001,
    0x0b80, 0x1f0d, 0x0780, 0x010b, 0x8018, 0x0d06, 0x807f, 0x0a80,
    0x110d, 0x0780, 0x7f0a, 0x800a, 0x0d80, 0x7811, 0x8077, 0x1180,
    0x030e, 0x6c22, 0x6c80, 0x5910, 0x8077, 0x1001, 0x0a80, 0x0f0d,
    0x8051, 0x3080, 0x6f31, 0x8055, 0x3080, 0x7331, 0x8023, 0x0c80,
    0x5130, 0xaf80, 0x5530, 0x6f39, 0xa000, 0x7710, 0x8030, 0x3faf,
    0x3980, 0x013f, 0x3826, 0x806f, 0x316f, 0xa000, 0x0139, 0x3880,
    0x7331, 0x805a, 0x1080, 0x7810, 0x010a, 0x800f, 0x0d80, 0x5330,
    0x8071, 0x3180, 0x5730, 0x8075, 0x3180, 0x230c, 0x8053, 0x30af,
    0x8057, 0x306f, 0x39a0, 0x0078, 0x1080, 0x303f, 0xaf39, 0x8001,
    0x3f38, 0x2680, 0x7131, 0x6fa0, 0x0001, 0x3938, 0x8075, 0x3180,
    0x5530, 0xa000, 0x0839, 0x2680, 0x5b31, 0xa000, 0x0838, 0x805f,
    0x3180, 0x5730, 0xa000, 0x0839, 0x2680, 0x5d31, 0xa000, 0x0838,
    0x8061, 0x3180, 0x7330, 0x2680, 0x7931, 0xa000, 0x0838, 0x807d,
    0x3180, 0x7530, 0x2680, 0x7b31, 0xa000, 0x0838, 0x807f, 0x3180,
    0x5130, 0x8065, 0x3180, 0x5530, 0x8069, 0x3180, 0x5330, 0x26a0,
    0x0008, 0x3980, 0x6731, 0x806b, 0x31a0, 0x0d21, 0x2e6c, 0x8021,
    0x3180, 0x1f31, 0x8025, 0x3180, 0x2331, 0x801f, 0x3080, 0x2330,
    0x39a0, 0x1724, 0x2e80, 0x2b31, 0xa000, 0x0080, 0x2130, 0x8025,
    0x3039, 0xa017, 0x242e, 0x3980, 0x2d31, 0xa0ff, 0xffa0, 0x0023,
    0x3080, 0x1f30, 0xa017, 0x322e, 0x8010, 0x3f38, 0x8027, 0x31a0,
    0xffff, 0xa000, 0x2530, 0x8021, 0x30a0, 0x1732, 0x2e80, 0x103f,
    0x3880, 0x2931, 0x802b, 0x3080, 0x2d30, 0x3880, 0x2f31, 0x8023,
    0x3080, 0x2530, 0x8005, 0x302e, 0x8023, 0x3080, 0x2530, 0xa00e,
    0x6d2e, 0x8023, 0x3080, 0x1f30, 0x2880, 0x2530, 0x8021, 0x3028,
    0x1c80, 0x4f0d, 0x802f, 0x3080, 0x103f, 0x8031, 0x3180, 0x3130,
    0x802d, 0x30a0, 0x1732, 0x2e80, 0x140d, 0x802f, 0x3080, 0x2d30,
    0x3880, 0x2f31, 0x8023, 0x3080, 0x2730, 0x3880, 0x2331, 0x8031,
    0x3080, 0x2b30, 0xa017, 0x3c2e, 0x8014, 0x0d80, 0x2f30, 0x802b,
    0x3038, 0x802f, 0x3180, 0x2530, 0x8029, 0x3038, 0x8025, 0x31a0,
    0x090e, 0x2c6c, 0x800e, 0x3080, 0x0a30, 0xaa0c, 0x24af, 0x800c,
    0x3080, 0x0830, 0xaa0c, 0x2426, 0xefa0, 0x0a32, 0x2e80, 0x0008,
    0x8006, 0x0d26, 0xef80, 0x0530, 0x2e21, 0x2727, 0xa017, 0x3c2e,
    0x80e4, 0x0d22, 0x2262, 0x2127, 0x27a0, 0x173c, 0x2e80, 0xcd0d,
    0x2222, 0xa00d, 0x4f2e, 0x6c2f, 0x2fa0, 0x0800, 0xa008, 0x0027,
    0x0307, 0x0426, 0x0f0f, 0xa019, 0x4da0, 0x0003, 0x1080, 0x303f,
    0x3880, 0x004f, 0x3814, 0x8007, 0x4f19, 0x1f80, 0x011c, 0x8000,
    0x0880, 0x2e0d, 0x2680, 0x0004, 0x0580, 0x0004, 0x24ef, 0x64ef,
    0x6425, 0x3825, 0x2538, 0x2427, 0x27a0, 0x0a32, 0x2e80, 0x0008,
    0x800d, 0x0d27, 0x2780, 0x0530, 0x2ea0, 0x0e6d, 0x2e80, 0x020c,
    0x2222, 0x2201, 0x8a80, 0xa70d, 0x2201, 0x8a80, 0x9e0d, 0x2262,
    0x626c, 0x2f2f, 0x8004, 0x1006, 0x8006, 0x0d02, 0x6262, 0x8001,
    0x6c06, 0x8001, 0x0980, 0x1b0d, 0x0267, 0x676f, 0x6f38, 0xa000,
    0x013c, 0xa000, 0x0028, 0x6f6f, 0x39a0, 0x0001, 0x3ca0, 0x0000,
    0x281c, 0x6c06, 0x8002, 0x0980, 0x1b0d, 0x0267, 0x676f, 0x6f38,
    0xa000, 0x033c, 0xa000, 0x0028, 0x6f6f, 0x39a0, 0x0003, 0x3ca0,
    0x0000, 0x281c, 0x6c06, 0x8003, 0x0980, 0x1b0d, 0x0267, 0x676f,
    0x6f38, 0xa000, 0x053c, 0xa000, 0x0028, 0x6f6f, 0x39a0, 0x0005,
    0x3ca0, 0x0000, 0x281c, 0x6c06, 0x8004, 0x0980, 0x0d0d, 0x026f,
    0x6f38, 0xa000, 0x033c, 0xa000, 0x0028, 0x6c06, 0x8005, 0x0980,
    0x0d0d, 0x026f, 0x6f39, 0xa000, 0x033c, 0xa000, 0x0028, 0x6c06,
    0x8006, 0x0980, 0x0a0d, 0x0264, 0x626f, 0xa000, 0x013c, 0x036c,
    0x0680, 0x0709, 0x8009, 0x0d02, 0x626f, 0xa000, 0x013c, 0x036c,
    0x0262, 0x6280, 0x006c, 0x2f2f, 0x8003, 0x1080, 0x0080, 0x0310,
    0x8000, 0x2703, 0x0704, 0x8000, 0x0405, 0x8000, 0x04ef, 0x64ef,
    0x6425, 0x3825, 0x2538, 0x2427, 0x27a0, 0x0b95, 0x2e80, 0x0008,
    0x800b, 0x0d27, 0x2780, 0x170e, 0x2727, 0xa00e, 0x6d2e, 0x2222,
    0x018a, 0x80cd, 0x0d22, 0x018a, 0x80c2, 0x0d22, 0x6262, 0x6c27,
    0x27a0, 0x0001, 0x3980, 0x4d0e, 0x0f27, 0x2127, 0x8046, 0x0e80,
    0x101f, 0x0f58, 0x2727, 0x2180, 0x3b0e, 0x8020, 0x1f0f, 0x5827,
    0xa000, 0x0139, 0x2780, 0x2d0e, 0x8030, 0x1f0f, 0x584f, 0x0680,
    0x0308, 0x8019, 0x0d06, 0x8006, 0x0880, 0x120d, 0x0680, 0x0908,
    0x800b, 0x0d06, 0x800c, 0x0880, 0x040d, 0x0222, 0x226c, 0x02a0,
    0x0bdb, 0x2e6c, 0x6c80, 0x670e, 0x8005, 0x0d22, 0x2280, 0x016c,
    0x2703, 0x8007, 0x1c0f, 0x807b, 0x0e14, 0x8007, 0x4f19, 0x1f80,
    0x011c, 0x6c80, 0x040d, 0x8022, 0x0c6c, 0x8042, 0x0e80, 0x030d,
    0x2222, 0x6c27, 0x0380, 0x071c, 0x0f80, 0x580e, 0x94a0, 0x0107,
    0x4f19, 0x8040, 0x1f1f, 0x1d05, 0x0515, 0x6c80, 0x210e, 0x8003,
    0x0d22, 0x226c, 0x2703, 0x8007, 0x1c0f, 0x8037, 0x0e94, 0xa001,
    0x074f, 0x1980, 0x401f, 0x1f80, 0xff1e, 0x1c05, 0x0515, 0x6c26,
    0x8003, 0x3f03, 0x8078, 0x1080, 0x0119, 0x0a80, 0x120d, 0x2780,
    0x033f, 0x0380, 0x7710, 0x8001, 0x190a, 0x8003, 0x0d80, 0x016c,
    0x8000, 0x6c6c, 0xaf80, 0x033f, 0x2480, 0x033f, 0x24a0, 0x0077,
    0x103a, 0x3880, 0x303f, 0x6fa0, 0x0007, 0x3c38, 0xa01e, 0xbd38,
    0x6c80, 0x00a0, 0x111a, 0x2ea0, 0x0083, 0xa000, 0x20a0, 0x16a9,
    0x2ea0, 0x1541, 0xa000, 0x83a0, 0x000c, 0xa016, 0xb92e, 0xa01e,
    0xbda0, 0x0473, 0x2ea0, 0x16a9, 0x2ea0, 0x0001, 0x11a0, 0x10f0,
    0x2ea0, 0x0d21, 0x2e6c, 0xa01e, 0xbda0, 0x0473, 0x2ea0, 0x16a9,
    0x2ea0, 0x0001, 0x11a0, 0x10f0, 0x2ea0, 0x0083, 0xa016, 0xd22e,
    0xa000, 0x0339, 0xa00c, 0xc9a0, 0x1706, 0x2ea0, 0x1772, 0x2da0,
    0x0083, 0x80a8, 0x37a0, 0xfff0, 0xa01e, 0xbd39, 0x80aa, 0x37a0,
    0x1ebd, 0x80ac, 0x37a0, 0x0083, 0xa016, 0xd22e, 0xa000, 0x0939,
    0xa00c, 0xe52e, 0xa00d, 0x212e, 0x6c74, 0x6761, 0x00a0, 0x0083,
    0x80a8, 0x37a0, 0x0473, 0x2e80, 0xaa37, 0xa01e, 0xbd80, 0xae37,
    0xa00d, 0x212e, 0x6c26, 0xa016, 0x642e, 0x8000, 0x0880, 0x2f0d,
    0x26a0, 0x0002, 0x3814, 0x8078, 0x0980, 0x230d, 0x26a0, 0x0003,
    0x38a0, 0x1664, 0x2e80, 0x0008, 0x8014, 0x0d26, 0xa000, 0x0338,
    0xa016, 0x642e, 0x0fa0, 0x1664, 0x2e4f, 0xa007, 0xa52e, 0x6c22,
    0x6c80, 0x5930, 0xa000, 0x002a, 0x0c6c, 0x8051, 0x30a0, 0x0008,
    0x3980, 0x5330, 0xa000, 0x0839, 0x8059, 0x1080, 0x5a10, 0xa01b,
    0x2da0, 0x154e, 0x2ea0, 0x10f0, 0x2e80, 0x06a0, 0x111a, 0x2e80,
    0x7730, 0xa000, 0x002a, 0x0c6c, 0x8012, 0x10a0, 0x0e15, 0x2da0,
    0x0526, 0x17a0, 0x1ebd, 0x802c, 0x3780, 0x7130, 0x802a, 0x3780,
    0x7810, 0x805a, 0x108b, 0x0c04, 0x0280, 0x0080, 0x0007, 0xa000,
    0x7710, 0x3a80, 0x303f, 0xa01e, 0xbd38, 0x802c, 0x3780, 0x6f30,
    0x8028, 0x3780, 0x7710, 0x8059, 0x108b, 0x0c04, 0x0280, 0x00a0,
    0x092f, 0x1701, 0x8a80, 0xf70d, 0x2280, 0x2ab6, 0xa000, 0x0838,
    0x0537, 0x018a, 0x80c4, 0x0d22, 0xa011, 0x452e, 0x8077, 0x1080,
    0x5910, 0x8002, 0x190a, 0x802d, 0x0d80, 0x7810, 0x805a, 0x1080,
    0x0219, 0x0a80, 0x200d, 0x8077, 0x30a0, 0x0000, 0x2880, 0x160d,
    0xa019, 0x0580, 0x2c37, 0x8079, 0x3080, 0x2837, 0x807b, 0x3080,
    0x2a37, 0xa00f, 0x2f17, 0xa019, 0x0d80, 0x2c37, 0x8055, 0x30a0,
    0x0008, 0x3980, 0x2837, 0x8057, 0x30a0, 0x0008, 0x3980, 0x2a37,
    0xa005, 0x2f17, 0x6ca0, 0x0126, 0x1780, 0x5330, 0x802a, 0x3780,
    0x5a10, 0x8000, 0x8f80, 0x5130, 0x8028, 0x3780, 0x5910, 0x8000,
    0x8000, 0xcf80, 0x1530, 0x382f, 0x8000, 0x0780, 0x1330, 0x386f,
    0xa00b, 0x952e, 0x8000, 0x0480, 0x303f, 0xa019, 0x3d38, 0x802c,
    0x37a0, 0x092f, 0x1701, 0x8a80, 0xd60d, 0x2242, 0x802a, 0x36a0,
    0x0008, 0x3880, 0x2a37, 0x018a, 0x80b9, 0x0d22, 0x6c80, 0x1210,
    0x8047, 0x0d26, 0xa000, 0x7810, 0x8030, 0x3fa0, 0x0001, 0x392a,
    0x8034, 0x0d27, 0xa000, 0x7710, 0x8030, 0x3fa0, 0x0001, 0x392a,
    0x8024, 0x0d80, 0x333f, 0x2480, 0x333f, 0x2427, 0x27a0, 0x0c24,
    0x2e80, 0x2c37, 0x8071, 0x3038, 0x802a, 0x3780, 0x6f30, 0x3880,
    0x2837, 0xa009, 0x2f17, 0x6c22, 0x226c, 0x2680, 0x1530, 0x39a0,
    0x005a, 0x1080, 0x0119, 0x2a80, 0x440d, 0x2780, 0x1330, 0x39a0,
    0x0059, 0x1080, 0x0119, 0x2a80, 0x340d, 0x2727, 0xa00b, 0x952e,
    0x8000, 0x0480, 0x303f, 0xa019, 0x3d38, 0x802c, 0x3780, 0x1530,
    0x3980, 0x303f, 0x8053, 0x3038, 0x802a, 0x3780, 0x1330, 0x3980,
    0x303f, 0x8051, 0x3038, 0x8028, 0x37a0, 0x092f, 0x176c, 0x2222,
    0x6c80, 0x0c30, 0x800e, 0x3027, 0x27a0, 0x0003, 0x3980, 0x2a37,
    0xa000, 0x0339, 0x8028, 0x37a0, 0x402f, 0x1780, 0x40a0, 0x0fb1,
    0x2e80, 0x9236, 0x800c, 0x3180, 0x9436, 0x800e, 0x3180, 0x0210,
    0x0680, 0x0108, 0x0480, 0x0308, 0xa000, 0x0028, 0xa00f, 0x9c2d,
    0x8092, 0x3680, 0x9436, 0x806f, 0xa011, 0xd42e, 0x8000, 0x08a0,
    0x0f9c, 0x2d80, 0x0c30, 0xa000, 0x0339, 0x8028, 0x3780, 0x0e30,
    0xa000, 0x0339, 0x802a, 0x37a0, 0x1a45, 0xa000, 0x0310, 0x8030,
    0x3f38, 0x802c, 0x3780, 0x9616, 0x8000, 0x0906, 0x8010, 0x1f80,
    0x4118, 0x802f, 0x1780, 0x0008, 0x8001, 0x0d6c, 0x800c, 0x3080,
    0x0e30, 0xa041, 0x4380, 0x9616, 0x8001, 0x0d04, 0x0280, 0x010e,
    0x6c0f, 0x802a, 0x3780, 0x2837, 0xa01a, 0x8d80, 0x2c37, 0x4f80,
    0x2f17, 0x6c80, 0x4730, 0x8028, 0x3780, 0x4930, 0x802a, 0x37a0,
    0x0311, 0x8000, 0xa015, 0xf52e, 0x6c80, 0x6530, 0xa000, 0x0239,
    0x8028, 0x3780, 0x6730, 0xa000, 0x0239, 0x802a, 0x3780, 0x5910,
    0x0180, 0x5a10, 0x8002, 0x1880, 0x00a0, 0x15f5, 0x2e6c, 0x8047,
    0x3080, 0x4930, 0xa001, 0x0fa0, 0x1a9d, 0xa015, 0x4e2e, 0x8042,
    0x0e80, 0x4730, 0x2180, 0x4b30, 0x8049, 0x30a0, 0x0026, 0x38a0,
    0x0119, 0x0e80, 0x490e, 0x8047, 0x3021, 0x804b, 0x3080, 0x4930,
    0xa000, 0x5838, 0xa001, 0x040e, 0x8050, 0x0e6c, 0x0f80, 0x2a37,
    0x2426, 0x8028, 0x37cf, 0x802e, 0x1721, 0x21aa, 0x80f2, 0x0d22,
    0x2242, 0x6ca0, 0x1a0d, 0x802c, 0x37a0, 0x0602, 0x1080, 0x4730,
    0xa000, 0x0438, 0x8049, 0x30a0, 0x0005, 0x3880, 0x410e, 0x6ca0,
    0x19cd, 0x802c, 0x37a0, 0x0804, 0x1080, 0x4730, 0xa000, 0x0438,
    0x8049, 0x30a0, 0x002d, 0x3880, 0x250e, 0x6ca0, 0x0007, 0x1080,
    0x601f, 0xa019, 0x4d38, 0x802c, 0x37a0, 0x0803, 0x1080, 0x4730,
    0xa000, 0x0438, 0x8049, 0x30a0, 0x005f, 0x3880, 0x010e, 0x6ca0,
    0x0426, 0x1780, 0x2033, 0x800d, 0x330f, 0x8000, 0x8000, 0x0780,
    0x011c, 0x8009, 0x1aa0, 0x0000, 0x3880, 0x2837, 0x8000, 0x0780,
    0x011f, 0x800a, 0x1aa0, 0x0000, 0x3880, 0x2a37, 0x06cf, 0x0880,
    0x101f, 0x8009, 0x1880, 0x2f17, 0x018a, 0x80cf, 0x0d22, 0x426c,
    0xa004, 0x2617, 0x8065, 0x3080, 0x2837, 0x8067, 0x30a0, 0x0002,
    0x3980, 0x2a37, 0xa019, 0x1580, 0x2c37, 0xa001, 0x2f17, 0xa00a,
    0x0110, 0x8005, 0x1a18, 0x802f, 0x176c, 0x0f80, 0x6530, 0xa000,
    0x0838, 0x8028, 0x3780, 0x6730, 0xa000, 0x0239, 0x802a, 0x37a0,
    0x0083, 0xcfa0, 0x1193, 0x2ea0, 0x1925, 0x802c, 0x374f, 0x8000,
    0x0980, 0x2f17, 0x6c80, 0x1210, 0x8000, 0x0880, 0x010d, 0x6c80,
    0x5910, 0x8005, 0x0a80, 0x010d, 0x6c80, 0x7130, 0x8053, 0x302a,
    0x8001, 0x0d6c, 0xa001, 0x2617, 0x806f, 0x3080, 0x2837, 0x8071,
    0x30a0, 0x0008, 0x3980, 0x2a37, 0x8077, 0x1080, 0x08a0, 0x11a5,
    0x2e80, 0x7880, 0x08a0, 0x11bf, 0x2e80, 0x7810, 0x8008, 0xa011,
    0xa52e, 0x6c0f, 0xa001, 0x2617, 0x94cf, 0x8022, 0x0e21, 0x9480,
    0xf60d, 0x2242, 0x6c0f, 0x0680, 0x041f, 0xcf80, 0x010e, 0x4f04,
    0x800f, 0x1c06, 0x8009, 0x0a80, 0x271a, 0x1880, 0x3018, 0x0404,
    0x8020, 0x1980, 0x0004, 0x8030, 0x3fa0, 0x1bbd, 0x3880, 0x2c37,
    0x802f, 0x176c, 0x0f26, 0xcf80, 0x0218, 0x30a0, 0x1732, 0x2e80,
    0x2b0d, 0x26cf, 0x8006, 0x1830, 0xa017, 0x3c2e, 0x801e, 0x0d24,
    0x26cf, 0x30a0, 0x1732, 0x2e80, 0x130d, 0x26cf, 0x8004, 0x1830,
    0xa017, 0x3c2e, 0x8006, 0x0d22, 0x2242, 0x8001, 0x6c22, 0x2242,
    0x8000, 0x6c0f, 0xb0a0, 0x0001, 0x3980, 0x3731, 0x0101, 0xb0a0,
    0x0001, 0x3980, 0x3931, 0x0101, 0xb080, 0x3331, 0x0101, 0x3080,
    0x3531, 0x8033, 0x3080, 0x3730, 0x39a0, 0x1724, 0x2e80, 0x3f31,
    0x8035, 0x3080, 0x3930, 0x39a0, 0x1724, 0x2ea0, 0x0000, 0x2439,
    0x8041, 0x31a0, 0xffff, 0xa000, 0x3730, 0x8033, 0x30a0, 0x1732,
    0x2e80, 0x103f, 0x3880, 0x3b31, 0xa0ff, 0xffa0, 0x0039, 0x3080,
    0x3530, 0xa017, 0x322e, 0x8010, 0x3f38, 0x803d, 0x3180, 0x3f30,
    0x8041, 0x3038, 0x8043, 0x3180, 0x3730, 0x8028, 0x3780, 0x3930,
    0x802a, 0x37cf, 0x802e, 0x1780, 0x3730, 0x8033, 0x3028, 0x8039,
    0x3080, 0x3530, 0x281c, 0x804f, 0x0d80, 0x4330, 0x8010, 0x3f80,
    0x4531, 0x8045, 0x3080, 0x4130, 0xa017, 0x322e, 0x8014, 0x0d80,
    0x4330, 0x8041, 0x3038, 0x8043, 0x3180, 0x3730, 0x803b, 0x3038,
    0x8037, 0x3180, 0x4530, 0x803f, 0x30a0, 0x173c, 0x2e80, 0x140d,
    0x8043, 0x3080, 0x3f30, 0x3880, 0x4331, 0x8039, 0x3080, 0x3d30,
    0x3880, 0x3931, 0xa012, 0x872c, 0x426c, 0x0f80, 0x1b30, 0x8017,
    0x30aa, 0x0c24, 0x2680, 0x2837, 0x8019, 0x3080, 0x2a37, 0xcf80,
    0x2e17, 0x801d, 0x3080, 0x2a37, 0xcf80, 0x2e17, 0x21aa, 0x80e3,
    0x0d22, 0x2280, 0x1d30, 0x8019, 0x30aa, 0x0c24, 0x2680, 0x2a37,
    0x8017, 0x3080, 0x2837, 0xcf80, 0x2e17, 0x801b, 0x3080, 0x2837,
    0xcf80, 0x2e17, 0x21aa, 0x80e3, 0x0d22, 0x2242, 0x6c13, 0xaf13,
    0x8b13, 0x7d13, 0x9813, 0xcc13, 0xb213, 0xbd13, 0xbd14, 0x5e13,
    0xe913, 0xcf14, 0x1b14, 0x7814, 0x6114, 0x6914, 0x6914, 0xf614,
    0x9414, 0x7b14, 0xb915, 0x3e15, 0x3e15, 0x2315, 0x3e27, 0x2780,
    0x0a31, 0x8008, 0x3127, 0x2780, 0x0530, 0x2ea0, 0x0e6d, 0x2ea0,
    0x0101, 0x11a0, 0x10f0, 0x2e00, 0x2727, 0x2f2f, 0x8008, 0x3080,
    0x0a30, 0x6f6f, 0xa008, 0xae2e, 0x800a, 0x3180, 0x0831, 0x0022,
    0x2200, 0x2222, 0xa001, 0x0111, 0xa010, 0xf02e, 0x00a0, 0x0003,
    0x3924, 0xa000, 0x0339, 0x24a0, 0x09c7, 0x2e00, 0x2222, 0x0080,
    0x0c30, 0x800e, 0x3080, 0x40a0, 0x0fb1, 0x2ea0, 0x1740, 0xa012,
    0x132e, 0x800a, 0x3180, 0x0831, 0x0080, 0x0c30, 0x800e, 0x3080,
    0x40a0, 0x0fb1, 0x2ea0, 0x1740, 0xa012, 0x132e, 0x800e, 0x3180,
    0x0c31, 0x8008, 0x3080, 0x0a30, 0x800c, 0x3080, 0x0e30, 0xa008,
    0xae2e, 0xa001, 0x0111, 0xa010, 0xf02e, 0x0080, 0x0c30, 0x800e,
    0x3080, 0x40a0, 0x0fb1, 0x2ea0, 0x1740, 0xa012, 0x132e, 0x800e,
    0x3180, 0x0c31, 0x8008, 0x3080, 0x0a30, 0xa014, 0xf92e, 0x2180,
    0x1931, 0x2180, 0x1731, 0x800c, 0x3080, 0x0e30, 0xa014, 0xf92e,
    0x801d, 0x3180, 0x1b31, 0xa017, 0x43a0, 0x1213, 0x2e00, 0x2222,
    0x00a0, 0x0101, 0x11a0, 0x10f0, 0x2ea0, 0x0003, 0x3924, 0xa000,
    0x0339, 0x24a0, 0x0af6, 0x2e00, 0x2222, 0x0080, 0x0c30, 0x800e,
    0x3080, 0x40a0, 0x0fb1, 0x2e80, 0x40a0, 0x12fa, 0x2e80, 0x0a31,
    0x8008, 0x3100, 0x800c, 0x3080, 0x0e30, 0x8040, 0xa00f, 0xb12e,
    0x8040, 0xa012, 0xfa2e, 0x800e, 0x3180, 0x0c31, 0xa009, 0x842e,
    0xa001, 0x0111, 0xa010, 0xf02e, 0x0080, 0x0c30, 0x800e, 0x3080,
    0x40a0, 0x0fb1, 0x2e80, 0x40a0, 0x12fa, 0x2e80, 0x0e31, 0x800c,
    0x3180, 0x0830, 0x800a, 0x3080, 0x1f0e, 0x8019, 0x3180, 0x1731,
    0x800c, 0x3080, 0x0e30, 0x8010, 0x0e80, 0x1d31, 0x801b, 0x3180,
    0x43a0, 0x12fa, 0x2e00, 0x2222, 0x0080, 0x1210, 0x800b, 0x0d80,
    0x7130, 0x3824, 0x806f, 0x3038, 0x246c, 0x8015, 0x3039, 0x8030,
    0x3f80, 0x5330, 0x3824, 0x8013, 0x3039, 0x8030, 0x3f80, 0x5130,
    0x3824, 0x6ca0, 0x0078, 0x1080, 0x013f, 0x3980, 0x1531, 0xa000,
    0x7710, 0x8001, 0x3f39, 0x8013, 0x31a0, 0x06d8, 0x2e00, 0x2222,
    0x0075, 0x6e74, 0x6974, 0x6c65, 0x642e, 0x6963, 0x6e00, 0x802c,
    0x3780, 0x3013, 0x801a, 0x1326, 0x802a, 0x3780, 0x2b33, 0x2680,
    0x2837, 0x802e, 0x33a0, 0x0126, 0x17a0, 0x852f, 0x1780, 0x6e0e,
    0x8000, 0x8073, 0x0ea0, 0x0226, 0x1780, 0x620e, 0xa085, 0x2f17,
    0x805b, 0x0e80, 0x0080, 0x600e, 0xa000, 0x00a0, 0x0008, 0x3880,
    0x2a37, 0xa000, 0x0080, 0x2837, 0x8043, 0x0e80, 0xe612, 0x8047,
    0x0ea0, 0x0126, 0x1780, 0x360e, 0xa085, 0x2f17, 0x802f, 0x0e80,
    0xbf12, 0x8033, 0x0e80, 0x260e, 0xa085, 0x2f17, 0x801f, 0x0e80,
    0xd132, 0xa000, 0x0838, 0x8028, 0x3780, 0xbd32, 0xa000, 0x0838,
    0x802a, 0x3780, 0x9b12, 0x80ab, 0x12a0, 0x8118, 0x0e6c, 0x802c,
    0xb6a0, 0x0010, 0x3805, 0x376c, 0x8000, 0xa081, 0x2f17, 0x018a,
    0x80f7, 0x0d22, 0x6c0f, 0xa001, 0x2617, 0x8028, 0x3680, 0x1e33,
    0x0480, 0x0313, 0x8000, 0x8000, 0x8000, 0xcf80, 0x2f17, 0x018a,
    0x80f7, 0x0d22, 0x802a, 0xb6a0, 0x0008, 0x3805, 0x37a0, 0x0000,
    0x8028, 0x3701, 0x8a80, 0xde0d, 0x2242, 0x6c2e, 0x7468, 0x656d,
    0x6500, 0xa016, 0x2b80, 0xa837, 0xa000, 0x0680, 0xaa37, 0xa0ff,
    0xfa80, 0xac37, 0x80a2, 0x36a0, 0x0006, 0x2980, 0x150d, 0xa0ff,
    0xfa34, 0x8008, 0x37a0, 0xfffc, 0x3480, 0x0a37, 0xa0ff, 0xfe34,
    0x800c, 0x376c, 0x9480, 0x0c0e, 0x0f21, 0x1480, 0x060e, 0x4f80,
    0x401f, 0x186c, 0x0680, 0x2f0a, 0x0780, 0x3a0b, 0x1c80, 0x1c0d,
    0x0680, 0x600a, 0x0780, 0x670b, 0x1c80, 0x180d, 0x0680, 0x400a,
    0x0780, 0x470b, 0x1c80, 0x080d, 0x0280, 0x006c, 0x8030, 0x196c,
    0x8037, 0x196c, 0x8057, 0x196c, 0x6c27, 0x3824, 0xaf80, 0x006f,
    0x1521, 0xaa80, 0xf60d, 0x2222, 0x6c24, 0x2f27, 0x3824, 0x94ef,
    0x1561, 0x21aa, 0x80f7, 0x0d22, 0x2262, 0x6c26, 0x8003, 0x0e24,
    0x396c, 0x9480, 0x0009, 0x0c6c, 0x2194, 0x80fb, 0x0d6c, 0x2f94,
    0xef15, 0x6121, 0x9480, 0xf70d, 0x2280, 0x006f, 0x156c, 0x80e1,
    0x0e15, 0x6c94, 0x8002, 0x0d22, 0x6c80, 0x0005, 0x0580, 0xd20e,
    0xa000, 0x0139, 0x156c, 0x2f94, 0xd44f, 0x0980, 0x110d, 0x94d4,
    0x4f1d, 0x8005, 0x0d22, 0x6280, 0x016c, 0x2161, 0x80e8, 0x0c22,
    0x6280, 0x006c, 0x2680, 0x0f3f, 0x0880, 0x050d, 0xa000, 0x0024,
    0x396c, 0xa080, 0x00af, 0x3824, 0x6f38, 0x2a6c, 0xa080, 0x00af,
    0x3824, 0x6f38, 0x2b6c, 0x0480, 0x000e, 0x0680, 0x041f, 0x8000,
    0x0e80, 0x0f1c, 0x0680, 0x090a, 0x8027, 0x1a18, 0x8030, 0x1880,
    0x1817, 0x6ca0, 0x0001, 0x3921, 0x9406, 0x8018, 0x1780, 0xf70d,
    0x226c, 0xa000, 0x8380, 0xa837, 0xa000, 0x1280, 0xaa37, 0xa018,
    0xf380, 0xac37, 0xa018, 0xffaf, 0x3404, 0x6f35, 0xa019, 0x01af,
    0x3404, 0x6f35, 0xa018, 0xff34, 0x8003, 0x3f03, 0xa019, 0x0134,
    0x8003, 0x3f03, 0xa007, 0xa52e, 0xa018, 0xf514, 0x8002, 0x8903,
    0x800b, 0x0da0, 0x187e, 0xa000, 0x0480, 0x490e, 0x026c, 0x8003,
    0x8903, 0x800b, 0x0da0, 0x1895, 0xa000, 0x0180, 0x370e, 0x026c,
    0xa017, 0xeea0, 0x1763, 0x2e80, 0x00a0, 0x18f5, 0x1480, 0x101f,
    0xa018, 0xdb38, 0x34a0, 0x1763, 0x2ea0, 0x0a18, 0x176c, 0x556e,
    0x7375, 0x7070, 0x6f72, 0x7465, 0x6420, 0x7467, 0x612d, 0x7479,
    0x7065, 0x3a20, 0x0080, 0xaa37, 0x801f, 0x33a0, 0x0126, 0x17a0,
    0x0000, 0x800e, 0x33a0, 0x0000, 0x800b, 0x33a0, 0x1876, 0xaf80,
    0xac37, 0xa000, 0x00a0, 0x0000, 0x6fa0, 0x0000, 0x2e80, 0x071f,
    0xa00b, 0xb32e, 0x80ec, 0x3221, 0x2680, 0xe733, 0xa018, 0xff34,
    0x2980, 0x0d0d, 0xa000, 0x0080, 0xd933, 0x80d9, 0x3221, 0x80d5,
    0x3380, 0xa236, 0xa000, 0x0029, 0x80c0, 0x0da0, 0x0026, 0x17a0,
    0x187a, 0xa000, 0x83a0, 0x16d2, 0x2ea0, 0x0003, 0x39a0, 0x16de,
    0x2ea0, 0x0d4f, 0x2e6c, 0x0000, 0x0000, 0x6963, 0x6e00, 0x2f80,
    0x00ef, 0x1461, 0x8000, 0xef14, 0x6180, 0x006f, 0x1438, 0x38a0,
    0x0003, 0x3b03, 0x6c14, 0x6c6e, 0x6f2d, 0x6461, 0x7461, 0x0052,
    0x4157, 0x2d63, 0x6f6c, 0x6f72, 0x0052, 0x4157, 0x2d74, 0x7275,
    0x6500, 0x5241, 0x572d, 0x6277, 0x0052, 0x4c45, 0x2d63, 0x6f6c,
    0x6f72, 0x0052, 0x4c45, 0x2d74, 0x7275, 0x6500, 0x524c, 0x452d,
    0x6277, 0x0075, 0x6e6b, 0x6e6f, 0x776e, 0x0018, 0x9718, 0x9f18,
    0xa918, 0xb218, 0xd318, 0xd318, 0xd318, 0xd318, 0xd318, 0xb918,
    0xc318, 0xcc00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x00f8, 0xfcfc, 0xfcfc, 0x7800, 0x0000, 0x0000,
    0x0103, 0x070f, 0x1f3f, 0x7fff, 0xffff, 0xffff, 0xff00, 0x0004,
    0x0e1f, 0x0e04, 0x00fc, 0xfeff, 0xffff, 0xffff, 0xff00, 0x0000,
    0x8244, 0x3800, 0x0000, 0x3844, 0x9228, 0x1000, 0x0055, 0x8000,
    0x8000, 0x8000, 0x8055, 0xff7f, 0xff7f, 0xff7f, 0xff00, 0x0000,
    0x1000, 0x0000, 0x0000, 0x0010, 0x3810, 0x0000, 0x0000, 0x0038,
    0x3838, 0x0000, 0x0000, 0x1038, 0x7c38, 0x1000, 0x0000, 0x387c,
    0x7c7c, 0x3800, 0x0010, 0x387c, 0xfe7c, 0x3810, 0x0038, 0x7cfe,
    0xfefe, 0x7c38, 0x007c, 0xfefe, 0xfefe, 0xfe7c, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0010,
    0x2810, 0x0000, 0x0000, 0x1028, 0x4428, 0x1000, 0x0000, 0x3844,
    0x4444, 0x3800, 0x0010, 0x2844, 0x8244, 0x2810, 0x0038, 0x4482,
    0x8282, 0x4438, 0x007c, 0x8282, 0x8282, 0x827c, 0x00fe, 0xfefe,
    0xfefe, 0xfefe, 0x00fe, 0xd6aa, 0xd6aa, 0xd6fe, 0x00fe, 0x9282,
    0xd682, 0x92fe, 0x00fe, 0x8292, 0xaa92, 0x82fe, 0x00fe, 0xa6ca,
    0x92a6, 0xcafe, 0x00fe, 0xcaa6, 0x92ca, 0xa6fe, 0x00fe, 0xaaaa,
    0xaaaa, 0xaafe, 0x00fe, 0x82fe, 0x82fe, 0x82fe, 0x00c0, 0xe050,
    0x2814, 0x0a04, 0x00e0, 0xd0a8, 0x4422, 0x120c, 0x00c0, 0xb848,
    0x4878, 0x0402, 0x00a8, 0x5088, 0x50a8, 0x0402, 0x00fc, 0x8484,
    0x8084, 0xea04, 0x0030, 0x4884, 0x8448, 0x3402, 0x0032, 0x4582,
    0x8448, 0x3402, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0010,
    0x2810, 0x0000, 0x0000, 0x0038, 0x2838, 0x0000, 0x0000, 0x1028,
    0x4428, 0x1000, 0x0000, 0x3844, 0x4444, 0x3800, 0x0010, 0x2844,
    0x8244, 0x2810, 0x0038, 0x4482, 0x8282, 0x4438, 0x007c, 0x8282,
    0x8282, 0x827c, 0x007c, 0xfefe, 0xfefe, 0xfe7c, 0x0080, 0xc0e0,
    0xf0f8, 0xe010, 0x0020, 0x2020, 0xb87c, 0x7c38, 0x383f, 0x4080,
    0x8080, 0x8080, 0x8000, 0x3f7f, 0x7f7f, 0x7f7f, 0x7fff, 0x0000,
    0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xfffc, 0x0201,
    0x0101, 0x0101, 0x0100, 0xfcfe, 0xfefe, 0xfefe, 0xfe01, 0x0101,
    0x0101, 0x0101, 0x01fe, 0xfefe, 0xfefe, 0xfefe, 0xfe80, 0x8080,
    0x8080, 0x8080, 0x807f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f80, 0x8080,
    0x8080, 0x8040, 0x3f7f, 0x7f7f, 0x7f7f, 0x7f3f, 0x0000, 0x0000,
    0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0x0001, 0x0101,
    0x0101, 0x0102, 0xfcfe, 0xfefe, 0xfefe, 0xfefc, 0x0000, 0x0000,
    0x0000, 0x0000, 0x00ff, 0xffff, 0xffff, 0xffff, 0xff00, 0x0000,
    0x0000, 0x0001, 0x0200, 0x0000, 0x0000, 0x0000, 0x0100, 0x0000,
    0x0000, 0x00ff, 0x0000, 0x0000, 0x0000, 0x0000, 0xff00, 0x0000,
    0x0000, 0x0080, 0x4000, 0x0000, 0x0000, 0x0000, 0x8040, 0x4040,
    0x4040, 0x4040, 0x4080, 0x8080, 0x8080, 0x8080, 0x8002, 0x0202,
    0x0202, 0x0202, 0x0201, 0x0101, 0x0101, 0x0101, 0x0102, 0x0100,
    0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0xff00,
    0x0000, 0x0000, 0x00ff, 0x0000, 0x0000, 0x0000, 0x0040, 0x8000,
    0x0000, 0x0000, 0x0080, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x00cc, 0xcc33, 0x33cc, 0xcc33, 0x3300, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0808, 0x0808, 0x0008, 0x0000, 0x1414,
    0x0000, 0x0000, 0x0000, 0x247e, 0x2424, 0x7e24, 0x0000, 0x081e,
    0x281c, 0x0a3c, 0x0800, 0x0022, 0x0408, 0x1022, 0x0000, 0x3048,
    0x324c, 0x443a, 0x0000, 0x0810, 0x0000, 0x0000, 0x0000, 0x0408,
    0x0808, 0x0804, 0x0000, 0x2010, 0x1010, 0x1020, 0x0000, 0x0022,
    0x1408, 0x1422, 0x0000, 0x0008, 0x083e, 0x0808, 0x0000, 0x0000,
    0x0000, 0x0008, 0x1000, 0x0000, 0x003e, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0008, 0x0000, 0x0002, 0x0408, 0x1020, 0x0000, 0x3c46,
    0x4a52, 0x623c, 0x0000, 0x1808, 0x0808, 0x081c, 0x0000, 0x3c42,
    0x023c, 0x407e, 0x0000, 0x3c42, 0x1c02, 0x423c, 0x0000, 0x0c14,
    0x2444, 0x7e04, 0x0000, 0x7e40, 0x7c02, 0x423c, 0x0000, 0x3c40,
    0x7c42, 0x423c, 0x0000, 0x7e02, 0x0408, 0x1010, 0x0000, 0x3c42,
    0x3c42, 0x423c, 0x0000, 0x3c42, 0x423e, 0x023c, 0x0000, 0x0000,
    0x1000, 0x0010, 0x0000, 0x0010, 0x0000, 0x1010, 0x2000, 0x0008,
    0x1020, 0x1008, 0x0000, 0x0000, 0x3e00, 0x3e00, 0x0000, 0x0010,
    0x0804, 0x0810, 0x0000, 0x3c42, 0x0c10, 0x0010, 0x0000, 0x3c42,
    0x324a, 0x423c, 0x0000, 0x3c42, 0x427e, 0x4242, 0x0000, 0x7c42,
    0x7c42, 0x427c, 0x0000, 0x3c42, 0x4040, 0x423c, 0x0000, 0x7c42,
    0x4242, 0x427c, 0x0000, 0x7e40, 0x7840, 0x407e, 0x0000, 0x7e40,
    0x7840, 0x4040, 0x0000, 0x3c42, 0x4046, 0x423c, 0x0000, 0x4242,
    0x7e42, 0x4242, 0x0000, 0x1c08, 0x0808, 0x081c, 0x0000, 0x7e02,
    0x0202, 0x423c, 0x0000, 0x4244, 0x7844, 0x4242, 0x0000, 0x4040,
    0x4040, 0x407e, 0x0000, 0x4266, 0x5a42, 0x4242, 0x0000, 0x4262,
    0x524a, 0x4642, 0x0000, 0x3c42, 0x4242, 0x423c, 0x0000, 0x7c42,
    0x427c, 0x4040, 0x0000, 0x3c42, 0x4242, 0x443a, 0x0000, 0x7c42,
    0x427c, 0x4442, 0x0000, 0x3e40, 0x3c02, 0x423c, 0x0000, 0x7e08,
    0x0808, 0x0810, 0x0000, 0x4242, 0x4242, 0x443a, 0x0000, 0x4242,
    0x4242, 0x2418, 0x0000, 0x4242, 0x425a, 0x6642, 0x0000, 0x4242,
    0x3c42, 0x4242, 0x0000, 0x4242, 0x3e02, 0x423c, 0x0000, 0x7e02,
    0x0c30, 0x407e, 0x0000, 0x0c08, 0x0808, 0x080c, 0x0000, 0x4020,
    0x1008, 0x0402, 0x0000, 0x3010, 0x1010, 0x1030, 0x0000, 0x0814,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x007e, 0x0000, 0x0804,
    0x0000, 0x0000, 0x0000, 0x003c, 0x023e, 0x423a, 0x0000, 0x4040,
    0x7c42, 0x427c, 0x0000, 0x003c, 0x4240, 0x423c, 0x0000, 0x0202,
    0x3e42, 0x423e, 0x0000, 0x003c, 0x427e, 0x403e, 0x0000, 0x003e,
    0x4078, 0x4040, 0x0000, 0x003c, 0x423e, 0x023c, 0x0000, 0x4040,
    0x5c62, 0x4242, 0x0000, 0x0800, 0x1808, 0x0804, 0x0000, 0x0800,
    0x1808, 0x0848, 0x3000, 0x4042, 0x4478, 0x4442, 0x0000, 0x1010,
    0x1010, 0x100c, 0x0000, 0x006c, 0x5252, 0x5252, 0x0000, 0x005c,
    0x6242, 0x4242, 0x0000, 0x003c, 0x4242, 0x423c, 0x0000, 0x007c,
    0x4242, 0x7c40, 0x4000, 0x003e, 0x4242, 0x3e02, 0x0200, 0x005c,
    0x6240, 0x4040, 0x0000, 0x003e, 0x403c, 0x027c, 0x0000, 0x087e,
    0x0808, 0x0810, 0x0000, 0x0042, 0x4242, 0x443a, 0x0000, 0x0042,
    0x4242, 0x2418, 0x0000, 0x0052, 0x5252, 0x522e, 0x0000, 0x0042,
    0x2418, 0x2442, 0x0000, 0x0042, 0x423e, 0x027c, 0x0000, 0x007e,
    0x023c, 0x407e, 0x0000, 0x0c08, 0x1010, 0x080c, 0x0000, 0x0808,
    0x0808, 0x0808, 0x0000, 0x3010, 0x0808, 0x1030, 0x0000, 0x0000,
    0x324c, 0x0000, 0x003c, 0x4299, 0xa1a1, 0x9942, 0x3c42,
};