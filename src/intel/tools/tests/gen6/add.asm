add(16)         g6<1>UW         g1.4<1,4,0>UW   0x11001010V     { align1 WE_all 1H };
add(16)         g4<1>UW         g1.4<2,4,0>UW   0x10101010V     { align1 1H };
add(8)          g30<1>F         g26<8,8,1>F     -g4.4<0,1,0>F   { align1 1Q };
add(16)         g18<1>F         g8<8,8,1>F      -g6.4<0,1,0>F   { align1 1H };
add(1)          m22.4<1>D       g39.4<0,1,0>D   1D              { align1 WE_all 1N };
add(8)          m1<1>D          g3.3<0,1,0>D    g2<0,1,0>D      { align1 1Q };
add(16)         m1<1>D          g3.3<0,1,0>D    g2<0,1,0>D      { align1 1H };
add(8)          g11<1>.xyF      g1<0>.xyyyF     g2<0>.xF        { align16 1Q };
add(8)          m6<1>F          g4<8,8,1>F      0xbd4ccccdF  /* -0.05F */ { align1 1Q };
add(8)          g2<1>F          g4<8,8,1>F      0x3d4ccccdF  /* 0.05F */ { align1 1Q };
add(16)         g2<1>F          g11<8,8,1>F     0xbd4ccccdF  /* -0.05F */ { align1 1H };
add(8)          g6<1>.xUD       g6<4>.xUD       0x00000001UD    { align16 1Q };
add(8)          g19<1>.xUD      g6<4>.xUD       3D              { align16 1Q };
add(8)          m3<1>F          g2<4>F          g1<0>F          { align16 1Q };
add(8)          g67<1>.xD       g38<4>.xD       g40<4>.xD       { align16 1Q };
add(8)          g21<1>.xD       g19<4>.xD       -1D             { align16 1Q };
add(8)          a0<1>UW         g3<16,8,2>UW    0x0040UW        { align1 1Q };
add(8)          a0<1>UW         g4<16,8,2>UW    0x0040UW        { align1 2Q };
add(8)          m2<1>.xD        g3.4<0>.xD      7D              { align16 NoDDClr 1Q };
add(8)          g6<1>.xyF       g1<4>.xyyyF     0x3f800000F  /* 1F */ { align16 1Q };
add(16)         m3<1>F          -g39<8,8,1>F    0x3f800000F  /* 1F */ { align1 1H };
add(8)          m4<1>F          g10<8,8,1>F     g2.7<0,1,0>F    { align1 1Q };
add(16)         m7<1>F          g35<8,8,1>F     g2.7<0,1,0>F    { align1 1H };
add(8)          m3<1>.xyF       g10<4>.xyyyF    0x3f000000F  /* 0.5F */ { align16 NoDDClr 1Q };
add(8)          g26<1>UD        g26<4>UD        g28<4>UD        { align16 1Q };
add(8)          m6<1>.xD        g5<4>.zD        g5<4>.xD        { align16 1Q };
add(8)          g4<1>D          g2<0,1,0>D      g2.4<0,1,0>D    { align1 1Q };
add(16)         g4<1>D          g2<0,1,0>D      g2.4<0,1,0>D    { align1 1H };
add(8)          m2<1>.xyzD      g3.4<0>.xyzzD   g11<4>.xyzzD    { align16 NoDDClr 1Q };
add(8)          g70<1>D         g4<0,1,0>D      1D              { align1 1Q };
add(8)          m2<1>F          g4<8,8,1>D      1D              { align1 1Q };
add(16)         g75<1>D         g6<0,1,0>D      1D              { align1 1H };
add(16)         m3<1>F          g89<8,8,1>D     1D              { align1 1H };
add(8)          g37<1>F         g34<8,8,1>D     1D              { align1 1Q };
add(16)         g68<1>F         g62<8,8,1>D     1D              { align1 1H };
add(8)          g11<1>F         g10<4>.xF       0x48403000VF /* [0F, 1F, 2F, 3F]VF */ { align16 1Q };
add(8)          m4<1>.zD        g1<0>.xD        2D              { align16 NoDDClr,NoDDChk 1Q };
add(8)          g15<1>.yD       g1<0>.xD        49D             { align16 NoDDClr 1Q };
add(8)          g15<1>.zD       g1<0>.xD        50D             { align16 NoDDClr,NoDDChk 1Q };
add(8)          m5<1>.wD        g1<0>.xD        7D              { align16 NoDDChk 1Q };
add(8)          g15<1>.wD       g1<0>.xD        51D             { align16 NoDDChk 1Q };
add(8)          g3<1>.yF        g5<4>.xF        -g1<0>.xF       { align16 NoDDClr 1Q };
add(8)          g3<1>.yF        g13<4>.xF       -g1<0>.xF       { align16 NoDDClr,NoDDChk 1Q };
add(8)          g42<1>.wF       g2<0>.xF        0x40400000F  /* 3F */ { align16 NoDDClr 1Q };
add(8)          g43<1>.wF       g2<0>.xF        0x40e00000F  /* 7F */ { align16 NoDDChk 1Q };
add(8)          m5<1>.zF        g1<0>.xF        0x40000000F  /* 2F */ { align16 NoDDClr,NoDDChk 1Q };
add(8)          m14<1>.zF       g1<0>.xF        0x42180000F  /* 38F */ { align16 NoDDChk 1Q };
add(8)          m3<1>F          g1<4>.xF        0x48403000VF /* [0F, 1F, 2F, 3F]VF */ { align16 1Q };
add(8)          g99<1>.xD       g8<4>.xUD       32D             { align16 1Q };
add(8)          m4<1>.xF        g1<4>.xF        0x42c80000F  /* 100F */ { align16 1Q };
add(8)          g3.1<2>UW       g3.1<16,8,2>UW  g13<16,8,2>UW   { align1 1Q };
add(16)         g3.1<2>UW       g3.1<16,8,2>UW  g5<16,8,2>UW    { align1 1H };
add.sat(8)      m4<1>F          g2<4>.yzxwF     -g2<4>F         { align16 1Q };
add(8)          g15<1>.wF       g2<0>.xF        0x40400000F  /* 3F */ { align16 NoDDClr,NoDDChk 1Q };
add(8)          g2<1>UD         g22<0,1,0>UD    g12<1,4,0>UW    { align1 1Q };
add(8)          g3<1>UD         g22<0,1,0>UD    g12.2<1,4,0>UW  { align1 2Q };
add(8)          m3<1>.xyF       g2<4>.xyyyF     g1<0>.xyyyF     { align16 NoDDChk 1Q };
add.sat(8)      m4<1>F          g2<0,1,0>F      g2.4<0,1,0>F    { align1 1Q };
add.sat(8)      g3<1>F          g2.3<0,1,0>F    g2.4<0,1,0>F    { align1 1Q };
add.sat(16)     m7<1>F          g2<0,1,0>F      g2.4<0,1,0>F    { align1 1H };
add.sat(16)     g3<1>F          g2.3<0,1,0>F    g2.4<0,1,0>F    { align1 1H };
add(8)          m17<1>D         g3<8,8,1>D      12D             { align1 1Q };
add(16)         m17<1>D         g3<8,8,1>D      12D             { align1 1H };
add(8)          m3<1>.yF        g1<4>.yF        -g9<4>.xF       { align16 NoDDClr,NoDDChk 1Q };
add(8)          m5<1>.xyD       g6<4>.xyyyD     g12<4>.xD       { align16 NoDDClr,NoDDChk 1Q };
add(8)          m5<1>.xD        g11<4>.xD       1D              { align16 1Q };
add.sat(8)      m4<1>.xF        -g15<4>.xF      0x3f800000F  /* 1F */ { align16 NoDDClr 1Q };
add(8)          m10<1>UD        g13<0,1,0>UD    g10<1,4,0>UW    { align1 1Q };
add(8)          m11<1>UD        g13<0,1,0>UD    g10.2<1,4,0>UW  { align1 2Q };
add(8)          m17<1>UD        g6<8,8,1>UD     0x00000110UD    { align1 1Q };
add(16)         m17<1>UD        g9<8,8,1>UD     0x00000110UD    { align1 1H };
add.sat(8)      g22<1>.xUD      g20<4>.xUD      g10<4>.xUD      { align16 1Q };
add.l.f0.0(8)   g14<1>.xD       g12<4>.xD       -g12<4>.yD      { align16 1Q };
add(8)          g18<1>F         -g16<4>.xyxyF   g16<4>.zwzwF    { align16 2Q };
add.sat(8)      m4<1>F          g7<4>.xF        0xbf800000F  /* -1F */ { align16 1Q };
add.sat(8)      m4<1>.yF        -g1<0>.xF       0x3f000000F  /* 0.5F */ { align16 NoDDClr,NoDDChk 1Q };
add.sat(8)      m4<1>.wF        g3<4>.yF        0xc0000000F  /* -2F */ { align16 NoDDChk 1Q };
add(8)          m5<1>.xF        g25<4>.xF       -g3<4>.yF       { align16 NoDDClr 1Q };
add(8)          g18<1>.yF       g21<4>.xF       g27<4>.xF       { align16 NoDDChk 1Q };
