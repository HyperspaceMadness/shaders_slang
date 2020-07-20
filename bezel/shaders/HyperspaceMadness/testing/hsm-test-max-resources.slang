#version 450

/*
Shader to test maximum use of resources, e.g. textures, parameters & passes
*/

// layout(push_constant) uniform Push
// {
// 	float scanline_darkness;
// } params;

layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
    vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	vec4 FinalViewportSize;
	uint FrameCount;

    float param_num_0;
    float param_num_1;
    float param_num_2;
    float param_num_3;
    float param_num_4;
    float param_num_5;
    float param_num_6;
    float param_num_7;
    float param_num_8;
    float param_num_9;
    float param_num_10;
    float param_num_11;
    float param_num_12;
    float param_num_13;
    float param_num_14;
    float param_num_15;
    float param_num_16;
    float param_num_17;
    float param_num_18;
    float param_num_19;
    float param_num_20;
    float param_num_21;
    float param_num_22;
    float param_num_23;
    float param_num_24;
    float param_num_25;
    float param_num_26;
    float param_num_27;
    float param_num_28;
    float param_num_29;
    float param_num_30;
    float param_num_31;
    float param_num_32;
    float param_num_33;
    float param_num_34;
    float param_num_35;
    float param_num_36;
    float param_num_37;
    float param_num_38;
    float param_num_39;
    float param_num_40;
    float param_num_41;
    float param_num_42;
    float param_num_43;
    float param_num_44;
    float param_num_45;
    float param_num_46;
    float param_num_47;
    float param_num_48;
    float param_num_49;
    float param_num_50;
    float param_num_51;
    float param_num_52;
    float param_num_53;
    float param_num_54;
    float param_num_55;
    float param_num_56;
    float param_num_57;
    float param_num_58;
    float param_num_59;
    float param_num_60;
    float param_num_61;
    float param_num_62;
    float param_num_63;
    float param_num_64;
    float param_num_65;
    float param_num_66;
    float param_num_67;
    float param_num_68;
    float param_num_69;
    float param_num_70;
    float param_num_71;
    float param_num_72;
    float param_num_73;
    float param_num_74;
    float param_num_75;
    float param_num_76;
    float param_num_77;
    float param_num_78;
    float param_num_79;
    float param_num_80;
    float param_num_81;
    float param_num_82;
    float param_num_83;
    float param_num_84;
    float param_num_85;
    float param_num_86;
    float param_num_87;
    float param_num_88;
    float param_num_89;
    float param_num_90;
    float param_num_91;
    float param_num_92;
    float param_num_93;
    float param_num_94;
    float param_num_95;
    float param_num_96;
    float param_num_97;
    float param_num_98;
    float param_num_99;
    float param_num_100;
    float param_num_101;
    float param_num_102;
    float param_num_103;
    float param_num_104;
    float param_num_105;
    float param_num_106;
    float param_num_107;
    float param_num_108;
    float param_num_109;
    float param_num_110;
    float param_num_111;
    float param_num_112;
    float param_num_113;
    float param_num_114;
    float param_num_115;
    float param_num_116;
    float param_num_117;
    float param_num_118;
    float param_num_119;
    float param_num_120;
    float param_num_121;
    float param_num_122;
    float param_num_123;
    float param_num_124;
    float param_num_125;
    float param_num_126;
    float param_num_127;
    float param_num_128;
    float param_num_129;
    float param_num_130;
    float param_num_131;
    float param_num_132;
    float param_num_133;
    float param_num_134;
    float param_num_135;
    float param_num_136;
    float param_num_137;
    float param_num_138;
    float param_num_139;
    float param_num_140;
    float param_num_141;
    float param_num_142;
    float param_num_143;
    float param_num_144;
    float param_num_145;
    float param_num_146;
    float param_num_147;
    float param_num_148;
    float param_num_149;
    float param_num_150;
    float param_num_151;
    float param_num_152;
    float param_num_153;
    float param_num_154;
    float param_num_155;
    float param_num_156;
    float param_num_157;
    float param_num_158;
    float param_num_159;
    float param_num_160;
    float param_num_161;
    float param_num_162;
    float param_num_163;
    float param_num_164;
    float param_num_165;
    float param_num_166;
    float param_num_167;
    float param_num_168;
    float param_num_169;
    float param_num_170;
    float param_num_171;
    float param_num_172;
    float param_num_173;
    float param_num_174;
    float param_num_175;
    float param_num_176;
    float param_num_177;
    float param_num_178;
    float param_num_179;
    float param_num_180;
    float param_num_181;
    float param_num_182;
    float param_num_183;
    float param_num_184;
    float param_num_185;
    float param_num_186;
    float param_num_187;
    float param_num_188;
    float param_num_189;
    float param_num_190;
    float param_num_191;
    float param_num_192;
    float param_num_193;
    float param_num_194;
    float param_num_195;
    float param_num_196;
    float param_num_197;
    float param_num_198;
    float param_num_199;
    float param_num_200;
    float param_num_201;
    float param_num_202;
    float param_num_203;
    float param_num_204;
    float param_num_205;
    float param_num_206;
    float param_num_207;
    float param_num_208;
    float param_num_209;
    float param_num_210;
    float param_num_211;
    float param_num_212;
    float param_num_213;
    float param_num_214;
    float param_num_215;
    float param_num_216;
    float param_num_217;
    float param_num_218;
    float param_num_219;
    float param_num_220;
    float param_num_221;
    float param_num_222;
    float param_num_223;
    float param_num_224;
    float param_num_225;
    float param_num_226;
    float param_num_227;
    float param_num_228;
    float param_num_229;
    float param_num_230;
    float param_num_231;
    float param_num_232;
    float param_num_233;
    float param_num_234;
    float param_num_235;
    float param_num_236;
    float param_num_237;
    float param_num_238;
    float param_num_239;
    float param_num_240;
    float param_num_241;
    float param_num_242;
    float param_num_243;
    float param_num_244;
    float param_num_245;
    float param_num_246;
    float param_num_247;
    float param_num_248;
    float param_num_249;
    float param_num_250;
    float param_num_251;
    float param_num_252;
    float param_num_253;
    float param_num_254;
    float param_num_255;
} global;

#pragma parameter param_num_0	 	"param_num_0" 1 0 4 0.1
#define param_num_0 global.param_num_0

#pragma parameter param_num_1 	 	"param_num_1" 1 0 4 0.1
#define param_num_1 global.param_num_1

#pragma parameter param_num_2 	 	"param_num_2" 1 0 4 0.1
#define param_num_2 global.param_num_2

#pragma parameter param_num_3 	 	"param_num_3" 1 0 4 0.1
#define param_num_3 global.param_num_3

#pragma parameter param_num_4 	 	"param_num_4" 1 0 4 0.1
#define param_num_4 global.param_num_4

#pragma parameter param_num_5 	 	"param_num_5" 1 0 4 0.1
#define param_num_5 global.param_num_5

#pragma parameter param_num_6 	 	"param_num_6" 1 0 4 0.1
#define param_num_6 global.param_num_6

#pragma parameter param_num_7 	 	"param_num_7" 1 0 4 0.1
#define param_num_7 global.param_num_7

#pragma parameter param_num_8 	 	"param_num_8" 1 0 4 0.1
#define param_num_8 global.param_num_8

#pragma parameter param_num_9 	 	"param_num_9" 1 0 4 0.1
#define param_num_9 global.param_num_9

#pragma parameter param_num_10 	 	"param_num_10" 1 0 4 0.1
#define param_num_10 global.param_num_10

#pragma parameter param_num_11 	 	"param_num_11" 1 0 4 0.1
#define param_num_11 global.param_num_11

#pragma parameter param_num_12 	 	"param_num_12" 1 0 4 0.1
#define param_num_12 global.param_num_12

#pragma parameter param_num_13 	 	"param_num_13" 1 0 4 0.1
#define param_num_13 global.param_num_13

#pragma parameter param_num_14 	 	"param_num_14" 1 0 4 0.1
#define param_num_14 global.param_num_14

#pragma parameter param_num_15 	 	"param_num_15" 1 0 4 0.1
#define param_num_15 global.param_num_15

#pragma parameter param_num_16 	 	"param_num_16" 1 0 4 0.1
#define param_num_16 global.param_num_16

#pragma parameter param_num_17 	 	"param_num_17" 1 0 4 0.1
#define param_num_17 global.param_num_17

#pragma parameter param_num_18 	 	"param_num_18" 1 0 4 0.1
#define param_num_18 global.param_num_18

#pragma parameter param_num_19 	 	"param_num_19" 1 0 4 0.1
#define param_num_19 global.param_num_19

#pragma parameter param_num_20 	 	"param_num_20" 1 0 4 0.1
#define param_num_20 global.param_num_20

#pragma parameter param_num_21 	 	"param_num_21" 1 0 4 0.1
#define param_num_21 global.param_num_21

#pragma parameter param_num_22 	 	"param_num_22" 1 0 4 0.1
#define param_num_22 global.param_num_22

#pragma parameter param_num_23 	 	"param_num_23" 1 0 4 0.1
#define param_num_23 global.param_num_23

#pragma parameter param_num_24 	 	"param_num_24" 1 0 4 0.1
#define param_num_24 global.param_num_24

#pragma parameter param_num_25 	 	"param_num_25" 1 0 4 0.1
#define param_num_25 global.param_num_25

#pragma parameter param_num_26 	 	"param_num_26" 1 0 4 0.1
#define param_num_26 global.param_num_26

#pragma parameter param_num_27 	 	"param_num_27" 1 0 4 0.1
#define param_num_27 global.param_num_27

#pragma parameter param_num_28 	 	"param_num_28" 1 0 4 0.1
#define param_num_28 global.param_num_28

#pragma parameter param_num_29 	 	"param_num_29" 1 0 4 0.1
#define param_num_29 global.param_num_29

#pragma parameter param_num_30	 	"param_num_30" 1 0 4 0.1
#define param_num_30 global.param_num_30

#pragma parameter param_num_31 	 	"param_num_31" 1 0 4 0.1
#define param_num_31 global.param_num_31

#pragma parameter param_num_32 	 	"param_num_32" 1 0 4 0.1
#define param_num_32 global.param_num_32

#pragma parameter param_num_33 	 	"param_num_33" 1 0 4 0.1
#define param_num_33 global.param_num_33

#pragma parameter param_num_34 	 	"param_num_34" 1 0 4 0.1
#define param_num_34 global.param_num_34

#pragma parameter param_num_35 	 	"param_num_35" 1 0 4 0.1
#define param_num_35 global.param_num_35

#pragma parameter param_num_36 	 	"param_num_36" 1 0 4 0.1
#define param_num_36 global.param_num_36

#pragma parameter param_num_37 	 	"param_num_37" 1 0 4 0.1
#define param_num_37 global.param_num_37

#pragma parameter param_num_38 	 	"param_num_38" 1 0 4 0.1
#define param_num_38 global.param_num_38

#pragma parameter param_num_39 	 	"param_num_39" 1 0 4 0.1
#define param_num_39 global.param_num_39

#pragma parameter param_num_40	 	"param_num_40" 1 0 4 0.1
#define param_num_40 global.param_num_40

#pragma parameter param_num_41 	 	"param_num_41" 1 0 4 0.1
#define param_num_41 global.param_num_41

#pragma parameter param_num_42 	 	"param_num_42" 1 0 4 0.1
#define param_num_42 global.param_num_42

#pragma parameter param_num_43 	 	"param_num_43" 1 0 4 0.1
#define param_num_43 global.param_num_43

#pragma parameter param_num_44 	 	"param_num_44" 1 0 4 0.1
#define param_num_44 global.param_num_44

#pragma parameter param_num_45 	 	"param_num_45" 1 0 4 0.1
#define param_num_45 global.param_num_45

#pragma parameter param_num_46 	 	"param_num_46" 1 0 4 0.1
#define param_num_46 global.param_num_46

#pragma parameter param_num_47 	 	"param_num_47" 1 0 4 0.1
#define param_num_47 global.param_num_47

#pragma parameter param_num_48 	 	"param_num_48" 1 0 4 0.1
#define param_num_48 global.param_num_48

#pragma parameter param_num_49 	 	"param_num_49" 1 0 4 0.1
#define param_num_49 global.param_num_49

#pragma parameter param_num_50	 	"param_num_50" 1 0 4 0.1
#define param_num_50 global.param_num_50

#pragma parameter param_num_51 	 	"param_num_51" 1 0 4 0.1
#define param_num_51 global.param_num_51

#pragma parameter param_num_52 	 	"param_num_52" 1 0 4 0.1
#define param_num_52 global.param_num_52

#pragma parameter param_num_53 	 	"param_num_53" 1 0 4 0.1
#define param_num_53 global.param_num_53

#pragma parameter param_num_54 	 	"param_num_54" 1 0 4 0.1
#define param_num_54 global.param_num_54

#pragma parameter param_num_55 	 	"param_num_55" 1 0 4 0.1
#define param_num_55 global.param_num_55

#pragma parameter param_num_56 	 	"param_num_56" 1 0 4 0.1
#define param_num_56 global.param_num_56

#pragma parameter param_num_57 	 	"param_num_57" 1 0 4 0.1
#define param_num_57 global.param_num_57

#pragma parameter param_num_58 	 	"param_num_58" 1 0 4 0.1
#define param_num_58 global.param_num_58

#pragma parameter param_num_59 	 	"param_num_59" 1 0 4 0.1
#define param_num_59 global.param_num_59

#pragma parameter param_num_60	 	"param_num_60" 1 0 4 0.1
#define param_num_60 global.param_num_60

#pragma parameter param_num_61 	 	"param_num_61" 1 0 4 0.1
#define param_num_61 global.param_num_61

#pragma parameter param_num_62 	 	"param_num_62" 1 0 4 0.1
#define param_num_62 global.param_num_62

#pragma parameter param_num_63 	 	"param_num_63" 1 0 4 0.1
#define param_num_63 global.param_num_63

#pragma parameter param_num_64 	 	"param_num_64" 1 0 4 0.1
#define param_num_64 global.param_num_64

#pragma parameter param_num_65 	 	"param_num_65" 1 0 4 0.1
#define param_num_65 global.param_num_65

#pragma parameter param_num_66 	 	"param_num_66" 1 0 4 0.1
#define param_num_66 global.param_num_66

#pragma parameter param_num_67 	 	"param_num_67" 1 0 4 0.1
#define param_num_67 global.param_num_67

#pragma parameter param_num_68 	 	"param_num_68" 1 0 4 0.1
#define param_num_68 global.param_num_68

#pragma parameter param_num_69 	 	"param_num_69" 1 0 4 0.1
#define param_num_69 global.param_num_69

#pragma parameter param_num_70	 	"param_num_70" 1 0 4 0.1
#define param_num_70 global.param_num_70

#pragma parameter param_num_71 	 	"param_num_71" 1 0 4 0.1
#define param_num_71 global.param_num_71

#pragma parameter param_num_72 	 	"param_num_72" 1 0 4 0.1
#define param_num_72 global.param_num_72

#pragma parameter param_num_73 	 	"param_num_73" 1 0 4 0.1
#define param_num_73 global.param_num_73

#pragma parameter param_num_74 	 	"param_num_74" 1 0 4 0.1
#define param_num_74 global.param_num_74

#pragma parameter param_num_75 	 	"param_num_75" 1 0 4 0.1
#define param_num_75 global.param_num_75

#pragma parameter param_num_76 	 	"param_num_76" 1 0 4 0.1
#define param_num_76 global.param_num_76

#pragma parameter param_num_77 	 	"param_num_77" 1 0 4 0.1
#define param_num_77 global.param_num_77

#pragma parameter param_num_78 	 	"param_num_78" 1 0 4 0.1
#define param_num_78 global.param_num_78

#pragma parameter param_num_79 	 	"param_num_79" 1 0 4 0.1
#define param_num_79 global.param_num_79

#pragma parameter param_num_80	 	"param_num_80" 1 0 4 0.1
#define param_num_80 global.param_num_80

#pragma parameter param_num_81 	 	"param_num_81" 1 0 4 0.1
#define param_num_81 global.param_num_81

#pragma parameter param_num_82 	    	"param_num_82" 1 0 4 0.1
#define param_num_82 global.param_num_82

#pragma parameter param_num_83 	 	    "param_num_83" 1 0 4 0.1
#define param_num_83 global.param_num_83

#pragma parameter param_num_84 	 	    "param_num_84" 1 0 4 0.1
#define param_num_84 global.param_num_84

#pragma parameter param_num_85 	 	    "param_num_85" 1 0 4 0.1
#define param_num_85 global.param_num_85

#pragma parameter param_num_86 	    	"param_num_86" 1 0 4 0.1
#define param_num_86 global.param_num_86

#pragma parameter param_num_87 	    	"param_num_87" 1 0 4 0.1
#define param_num_87 global.param_num_87

#pragma parameter param_num_88 	    	"param_num_88" 1 0 4 0.1
#define param_num_88 global.param_num_88

#pragma parameter param_num_89 	    	"param_num_89" 1 0 4 0.1
#define param_num_89 global.param_num_89

#pragma parameter param_num_90	 	    "param_num_90" 1 0 4 0.1
#define param_num_90 global.param_num_90

#pragma parameter param_num_91 	    	"param_num_91" 1 0 4 0.1
#define param_num_91 global.param_num_91

#pragma parameter param_num_92 	    	"param_num_92" 1 0 4 0.1
#define param_num_92 global.param_num_92

#pragma parameter param_num_93 	    	"param_num_93" 1 0 4 0.1
#define param_num_93 global.param_num_93

#pragma parameter param_num_94 	    	"param_num_94" 1 0 4 0.1
#define param_num_94 global.param_num_94

#pragma parameter param_num_95 	    	"param_num_95" 1 0 4 0.1
#define param_num_95 global.param_num_95

#pragma parameter param_num_96 	    	"param_num_96" 1 0 4 0.1
#define param_num_96 global.param_num_96

#pragma parameter param_num_97 	 	    "param_num_97" 1 0 4 0.1
#define param_num_97 global.param_num_97

#pragma parameter param_num_98 	 	    "param_num_98" 1 0 4 0.1
#define param_num_98 global.param_num_98

#pragma parameter param_num_99 	 	    "param_num_99" 1 0 4 0.1
#define param_num_99 global.param_num_99

#pragma parameter param_num_100	 	    "param_num_100" 1 0 4 0.1
#define param_num_100 global.param_num_100

#pragma parameter param_num_101 	 	"param_num_101" 1 0 4 0.1
#define param_num_101 global.param_num_101

#pragma parameter param_num_102 	 	"param_num_102" 1 0 4 0.1
#define param_num_102 global.param_num_102

#pragma parameter param_num_103 	 	"param_num_103" 1 0 4 0.1
#define param_num_103 global.param_num_103

#pragma parameter param_num_104 	 	"param_num_104" 1 0 4 0.1
#define param_num_104 global.param_num_104

#pragma parameter param_num_105 	 	"param_num_105" 1 0 4 0.1
#define param_num_105 global.param_num_105

#pragma parameter param_num_106 	 	"param_num_106" 1 0 4 0.1
#define param_num_106 global.param_num_106

#pragma parameter param_num_107 	 	"param_num_107" 1 0 4 0.1
#define param_num_107 global.param_num_107

#pragma parameter param_num_108 	 	"param_num_108" 1 0 4 0.1
#define param_num_108 global.param_num_108

#pragma parameter param_num_109 	 	"param_num_109" 1 0 4 0.1
#define param_num_109 global.param_num_109

#pragma parameter param_num_110	 	    "param_num_110" 1 0 4 0.1
#define param_num_110 global.param_num_110

#pragma parameter param_num_111 	 	"param_num_111" 1 0 4 0.1
#define param_num_111 global.param_num_111

#pragma parameter param_num_112 	 	"param_num_112" 1 0 4 0.1
#define param_num_112 global.param_num_112

#pragma parameter param_num_113 	 	"param_num_113" 1 0 4 0.1
#define param_num_113 global.param_num_113

#pragma parameter param_num_114 	 	"param_num_114" 1 0 4 0.1
#define param_num_114 global.param_num_114

#pragma parameter param_num_115 	 	"param_num_115" 1 0 4 0.1
#define param_num_115 global.param_num_115

#pragma parameter param_num_116 	 	"param_num_116" 1 0 4 0.1
#define param_num_116 global.param_num_116

#pragma parameter param_num_117 	 	"param_num_117" 1 0 4 0.1
#define param_num_117 global.param_num_117

#pragma parameter param_num_118 	 	"param_num_118" 1 0 4 0.1
#define param_num_118 global.param_num_118

#pragma parameter param_num_119 	 	"param_num_119" 1 0 4 0.1
#define param_num_119 global.param_num_119

#pragma parameter param_num_120	 	    "param_num_120" 1 0 4 0.1
#define param_num_120 global.param_num_120

#pragma parameter param_num_121 	 	"param_num_121" 1 0 4 0.1
#define param_num_121 global.param_num_121

#pragma parameter param_num_122 	 	"param_num_122" 1 0 4 0.1
#define param_num_122 global.param_num_122

#pragma parameter param_num_123 	 	"param_num_123" 1 0 4 0.1
#define param_num_123 global.param_num_123

#pragma parameter param_num_124 	 	"param_num_124" 1 0 4 0.1
#define param_num_124 global.param_num_124

#pragma parameter param_num_125 	 	"param_num_125" 1 0 4 0.1
#define param_num_125 global.param_num_125

#pragma parameter param_num_126 	 	"param_num_126" 1 0 4 0.1
#define param_num_126 global.param_num_126

#pragma parameter param_num_127 	 	"param_num_127" 1 0 4 0.1
#define param_num_127 global.param_num_127

#pragma parameter param_num_128 	 	"param_num_128" 1 0 4 0.1
#define param_num_128 global.param_num_128

#pragma parameter param_num_129 	 	"param_num_129" 1 0 4 0.1
#define param_num_129 global.param_num_129

#pragma parameter param_num_130	 	    "param_num_130" 1 0 4 0.1
#define param_num_130 global.param_num_130

#pragma parameter param_num_131 	 	"param_num_131" 1 0 4 0.1
#define param_num_131 global.param_num_131

#pragma parameter param_num_132 	 	"param_num_132" 1 0 4 0.1
#define param_num_132 global.param_num_132

#pragma parameter param_num_133 	 	"param_num_133" 1 0 4 0.1
#define param_num_133 global.param_num_133

#pragma parameter param_num_134 	 	"param_num_134" 1 0 4 0.1
#define param_num_134 global.param_num_134

#pragma parameter param_num_135 	 	"param_num_135" 1 0 4 0.1
#define param_num_135 global.param_num_135

#pragma parameter param_num_136 	 	"param_num_136" 1 0 4 0.1
#define param_num_136 global.param_num_136

#pragma parameter param_num_137 	 	"param_num_137" 1 0 4 0.1
#define param_num_137 global.param_num_137

#pragma parameter param_num_138 	 	"param_num_138" 1 0 4 0.1
#define param_num_138 global.param_num_138

#pragma parameter param_num_139 	 	"param_num_139" 1 0 4 0.1
#define param_num_139 global.param_num_139

#pragma parameter param_num_140	 	    "param_num_140" 1 0 4 0.1
#define param_num_140 global.param_num_140

#pragma parameter param_num_141 	 	"param_num_141" 1 0 4 0.1
#define param_num_141 global.param_num_141

#pragma parameter param_num_142 	 	"param_num_142" 1 0 4 0.1
#define param_num_142 global.param_num_142

#pragma parameter param_num_143 	 	"param_num_143" 1 0 4 0.1
#define param_num_143 global.param_num_143

#pragma parameter param_num_144 	 	"param_num_144" 1 0 4 0.1
#define param_num_144 global.param_num_144

#pragma parameter param_num_145 	 	"param_num_145" 1 0 4 0.1
#define param_num_145 global.param_num_145

#pragma parameter param_num_146 	 	"param_num_146" 1 0 4 0.1
#define param_num_146 global.param_num_146

#pragma parameter param_num_147 	 	"param_num_147" 1 0 4 0.1
#define param_num_147 global.param_num_147

#pragma parameter param_num_148 	 	"param_num_148" 1 0 4 0.1
#define param_num_148 global.param_num_148

#pragma parameter param_num_149 	 	"param_num_149" 1 0 4 0.1
#define param_num_149 global.param_num_149

#pragma parameter param_num_150	 	    "param_num_150" 1 0 4 0.1
#define param_num_150 global.param_num_150

#pragma parameter param_num_151 	 	"param_num_151" 1 0 4 0.1
#define param_num_151 global.param_num_151

#pragma parameter param_num_152 	 	"param_num_152" 1 0 4 0.1
#define param_num_152 global.param_num_152

#pragma parameter param_num_153 	 	"param_num_153" 1 0 4 0.1
#define param_num_153 global.param_num_153

#pragma parameter param_num_154 	 	"param_num_154" 1 0 4 0.1
#define param_num_154 global.param_num_154

#pragma parameter param_num_155 	 	"param_num_155" 1 0 4 0.1
#define param_num_155 global.param_num_155

#pragma parameter param_num_156 	 	"param_num_156" 1 0 4 0.1
#define param_num_156 global.param_num_156

#pragma parameter param_num_157 	 	"param_num_157" 1 0 4 0.1
#define param_num_157 global.param_num_157

#pragma parameter param_num_158 	 	"param_num_158" 1 0 4 0.1
#define param_num_158 global.param_num_158

#pragma parameter param_num_159 	 	"param_num_159" 1 0 4 0.1
#define param_num_159 global.param_num_159

#pragma parameter param_num_160	 	    "param_num_160" 1 0 4 0.1
#define param_num_160 global.param_num_160

#pragma parameter param_num_161 	 	"param_num_161" 1 0 4 0.1
#define param_num_161 global.param_num_161

#pragma parameter param_num_162 	 	"param_num_162" 1 0 4 0.1
#define param_num_162 global.param_num_162

#pragma parameter param_num_163 	 	"param_num_163" 1 0 4 0.1
#define param_num_163 global.param_num_163

#pragma parameter param_num_164 	 	"param_num_164" 1 0 4 0.1
#define param_num_164 global.param_num_164

#pragma parameter param_num_165 	 	"param_num_165" 1 0 4 0.1
#define param_num_165 global.param_num_165

#pragma parameter param_num_166 	 	"param_num_166" 1 0 4 0.1
#define param_num_166 global.param_num_166

#pragma parameter param_num_167 	 	"param_num_167" 1 0 4 0.1
#define param_num_167 global.param_num_167

#pragma parameter param_num_168 	 	"param_num_168" 1 0 4 0.1
#define param_num_168 global.param_num_168

#pragma parameter param_num_169 	 	"param_num_169" 1 0 4 0.1
#define param_num_169 global.param_num_169

#pragma parameter param_num_170	 	    "param_num_170" 1 0 4 0.1
#define param_num_170 global.param_num_170

#pragma parameter param_num_171 	 	"param_num_171" 1 0 4 0.1
#define param_num_171 global.param_num_171

#pragma parameter param_num_172 	 	"param_num_172" 1 0 4 0.1
#define param_num_172 global.param_num_172

#pragma parameter param_num_173 	 	"param_num_173" 1 0 4 0.1
#define param_num_173 global.param_num_173

#pragma parameter param_num_174 	 	"param_num_174" 1 0 4 0.1
#define param_num_174 global.param_num_174

#pragma parameter param_num_175 	 	"param_num_175" 1 0 4 0.1
#define param_num_175 global.param_num_175

#pragma parameter param_num_176 	 	"param_num_176" 1 0 4 0.1
#define param_num_176 global.param_num_176

#pragma parameter param_num_177 	 	"param_num_177" 1 0 4 0.1
#define param_num_177 global.param_num_177

#pragma parameter param_num_178 	 	"param_num_178" 1 0 4 0.1
#define param_num_178 global.param_num_178

#pragma parameter param_num_179 	 	"param_num_179" 1 0 4 0.1
#define param_num_179 global.param_num_179

#pragma parameter param_num_180	 	    "param_num_180" 1 0 4 0.1
#define param_num_180 global.param_num_180

#pragma parameter param_num_181 	 	"param_num_181" 1 0 4 0.1
#define param_num_181 global.param_num_181

#pragma parameter param_num_182 	 	"param_num_182" 1 0 4 0.1
#define param_num_182 global.param_num_182

#pragma parameter param_num_183 	 	"param_num_183" 1 0 4 0.1
#define param_num_183 global.param_num_183

#pragma parameter param_num_184 	 	"param_num_184" 1 0 4 0.1
#define param_num_184 global.param_num_184

#pragma parameter param_num_185 	 	"param_num_185" 1 0 4 0.1
#define param_num_185 global.param_num_185

#pragma parameter param_num_186 	 	"param_num_186" 1 0 4 0.1
#define param_num_186 global.param_num_186

#pragma parameter param_num_187 	 	"param_num_187" 1 0 4 0.1
#define param_num_187 global.param_num_187

#pragma parameter param_num_188 	 	"param_num_188" 1 0 4 0.1
#define param_num_188 global.param_num_188

#pragma parameter param_num_189 	 	"param_num_189" 1 0 4 0.1
#define param_num_189 global.param_num_189

#pragma parameter param_num_190	 	    "param_num_190" 1 0 4 0.1
#define param_num_190 global.param_num_190

#pragma parameter param_num_191 	 	"param_num_191" 1 0 4 0.1
#define param_num_191 global.param_num_191

#pragma parameter param_num_192 	 	"param_num_192" 1 0 4 0.1
#define param_num_192 global.param_num_192

#pragma parameter param_num_193 	 	"param_num_193" 1 0 4 0.1
#define param_num_193 global.param_num_193

#pragma parameter param_num_194 	 	"param_num_194" 1 0 4 0.1
#define param_num_194 global.param_num_194

#pragma parameter param_num_195 	 	"param_num_195" 1 0 4 0.1
#define param_num_195 global.param_num_195

#pragma parameter param_num_196 	 	"param_num_196" 1 0 4 0.1
#define param_num_196 global.param_num_196

#pragma parameter param_num_197 	 	"param_num_197" 1 0 4 0.1
#define param_num_197 global.param_num_197

#pragma parameter param_num_198 	 	"param_num_198" 1 0 4 0.1
#define param_num_198 global.param_num_198

#pragma parameter param_num_199 	 	"param_num_199" 1 0 4 0.1
#define param_num_199 global.param_num_199

#pragma parameter param_num_200	 	"param_num_200" 1 0 4 0.1
#define param_num_200 global.param_num_200

#pragma parameter param_num_201 	 	"param_num_201" 1 0 4 0.1
#define param_num_201 global.param_num_201

#pragma parameter param_num_202 	 	"param_num_202" 1 0 4 0.1
#define param_num_202 global.param_num_202

#pragma parameter param_num_203 	 	"param_num_203" 1 0 4 0.1
#define param_num_203 global.param_num_203

#pragma parameter param_num_204 	 	"param_num_204" 1 0 4 0.1
#define param_num_204 global.param_num_204

#pragma parameter param_num_205 	 	"param_num_205" 1 0 4 0.1
#define param_num_205 global.param_num_205

#pragma parameter param_num_206 	 	"param_num_206" 1 0 4 0.1
#define param_num_206 global.param_num_206

#pragma parameter param_num_207 	 	"param_num_207" 1 0 4 0.1
#define param_num_207 global.param_num_207

#pragma parameter param_num_208 	 	"param_num_208" 1 0 4 0.1
#define param_num_208 global.param_num_208

#pragma parameter param_num_209 	 	"param_num_209" 1 0 4 0.1
#define param_num_209 global.param_num_209

#pragma parameter param_num_210	 	    "param_num_210" 1 0 4 0.1
#define param_num_210 global.param_num_210

#pragma parameter param_num_211 	 	"param_num_211" 1 0 4 0.1
#define param_num_211 global.param_num_211

#pragma parameter param_num_212 	 	"param_num_212" 1 0 4 0.1
#define param_num_212 global.param_num_212

#pragma parameter param_num_213 	 	"param_num_213" 1 0 4 0.1
#define param_num_213 global.param_num_213

#pragma parameter param_num_214 	 	"param_num_214" 1 0 4 0.1
#define param_num_214 global.param_num_214

#pragma parameter param_num_215 	 	"param_num_215" 1 0 4 0.1
#define param_num_215 global.param_num_215

#pragma parameter param_num_216 	 	"param_num_216" 1 0 4 0.1
#define param_num_216 global.param_num_216

#pragma parameter param_num_217 	 	"param_num_217" 1 0 4 0.1
#define param_num_217 global.param_num_217

#pragma parameter param_num_218 	 	"param_num_218" 1 0 4 0.1
#define param_num_218 global.param_num_218

#pragma parameter param_num_219 	 	"param_num_219" 1 0 4 0.1
#define param_num_219 global.param_num_219

#pragma parameter param_num_220	 	"param_num_220" 1 0 4 0.1
#define param_num_220 global.param_num_220

#pragma parameter param_num_221 	 	"param_num_221" 1 0 4 0.1
#define param_num_221 global.param_num_221

#pragma parameter param_num_222 	 	"param_num_222" 1 0 4 0.1
#define param_num_222 global.param_num_222

#pragma parameter param_num_223 	 	"param_num_223" 1 0 4 0.1
#define param_num_223 global.param_num_223

#pragma parameter param_num_224 	 	"param_num_224" 1 0 4 0.1
#define param_num_224 global.param_num_224

#pragma parameter param_num_225 	 	"param_num_225" 1 0 4 0.1
#define param_num_225 global.param_num_225

#pragma parameter param_num_226 	 	"param_num_226" 1 0 4 0.1
#define param_num_226 global.param_num_226

#pragma parameter param_num_227 	 	"param_num_227" 1 0 4 0.1
#define param_num_227 global.param_num_227

#pragma parameter param_num_228 	 	"param_num_228" 1 0 4 0.1
#define param_num_228 global.param_num_228

#pragma parameter param_num_229 	 	"param_num_229" 1 0 4 0.1
#define param_num_229 global.param_num_229

#pragma parameter param_num_230	 	    "param_num_230" 1 0 4 0.1
#define param_num_230 global.param_num_230

#pragma parameter param_num_231 	 	"param_num_231" 1 0 4 0.1
#define param_num_231 global.param_num_231

#pragma parameter param_num_232 	 	"param_num_232" 1 0 4 0.1
#define param_num_232 global.param_num_232

#pragma parameter param_num_233 	 	"param_num_233" 1 0 4 0.1
#define param_num_233 global.param_num_233

#pragma parameter param_num_234 	 	"param_num_234" 1 0 4 0.1
#define param_num_234 global.param_num_234

#pragma parameter param_num_235 	 	"param_num_235" 1 0 4 0.1
#define param_num_235 global.param_num_235

#pragma parameter param_num_236 	 	"param_num_236" 1 0 4 0.1
#define param_num_236 global.param_num_236

#pragma parameter param_num_237 	 	"param_num_237" 1 0 4 0.1
#define param_num_237 global.param_num_237

#pragma parameter param_num_238 	 	"param_num_238" 1 0 4 0.1
#define param_num_238 global.param_num_238

#pragma parameter param_num_239 	 	"param_num_239" 1 0 4 0.1
#define param_num_239 global.param_num_239

#pragma parameter param_num_240	 	    "param_num_240" 1 0 4 0.1
#define param_num_240 global.param_num_240

#pragma parameter param_num_241 	 	"param_num_241" 1 0 4 0.1
#define param_num_241 global.param_num_241

#pragma parameter param_num_242 	 	"param_num_242" 1 0 4 0.1
#define param_num_242 global.param_num_242

#pragma parameter param_num_243 	 	"param_num_243" 1 0 4 0.1
#define param_num_243 global.param_num_243

#pragma parameter param_num_244 	 	"param_num_244" 1 0 4 0.1
#define param_num_244 global.param_num_244

#pragma parameter param_num_245 	 	"param_num_245" 1 0 4 0.1
#define param_num_245 global.param_num_245

#pragma parameter param_num_246 	 	"param_num_246" 1 0 4 0.1
#define param_num_246 global.param_num_246

#pragma parameter param_num_247 	 	"param_num_247" 1 0 4 0.1
#define param_num_247 global.param_num_247

#pragma parameter param_num_248 	 	"param_num_248" 1 0 4 0.1
#define param_num_248 global.param_num_248

#pragma parameter param_num_249 	 	"param_num_249" 1 0 4 0.1
#define param_num_249 global.param_num_249

#pragma parameter param_num_250	 	    "param_num_250" 1 0 4 0.1
#define param_num_250 global.param_num_250

#pragma parameter param_num_251  	 	"param_num_251" 1 0 4 0.1
#define param_num_251 global.param_num_251

#pragma parameter param_num_252  	 	"param_num_252" 1 0 4 0.1
#define param_num_252 global.param_num_252

#pragma parameter param_num_253  	 	"param_num_253" 1 0 4 0.1
#define param_num_253 global.param_num_253

#pragma parameter param_num_254  	 	"param_num_254" 1 0 4 0.1
#define param_num_254 global.param_num_254

// #pragma parameter param_num_255  	 	"param_num_255" 1 0 4 0.1
// #define param_num_255 global.param_num_255



#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;

layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 1)  uniform sampler2D Source;
layout(set = 0, binding = 2)  uniform sampler2D PresetTex_1;
layout(set = 0, binding = 3)  uniform sampler2D PresetTex_2;
layout(set = 0, binding = 4)  uniform sampler2D PresetTex_3;
layout(set = 0, binding = 5)  uniform sampler2D PresetTex_4;
layout(set = 0, binding = 6)  uniform sampler2D PresetTex_5;
layout(set = 0, binding = 7)  uniform sampler2D PresetTex_6;
layout(set = 0, binding = 8)  uniform sampler2D PresetTex_7;
layout(set = 0, binding = 9)  uniform sampler2D PresetTex_8;
layout(set = 0, binding = 10) uniform sampler2D PresetTex_9;
layout(set = 0, binding = 11) uniform sampler2D PresetTex_10;
layout(set = 0, binding = 12) uniform sampler2D PresetTex_11;
layout(set = 0, binding = 13) uniform sampler2D PresetTex_12;
layout(set = 0, binding = 14) uniform sampler2D PresetTex_13;
layout(set = 0, binding = 15) uniform sampler2D PresetTex_14;
layout(set = 0, binding = 16) uniform sampler2D PresetTex_15;
layout(set = 0, binding = 17) uniform sampler2D PresetTex_16;

void main()
{
    float prev_pass_used_area = 0.9;

    // Squeeze the texture from the last pass into the top left quadrant
    if ((vTexCoord.x < prev_pass_used_area) && (vTexCoord.y < prev_pass_used_area))
    {
        FragColor = texture(Source, vTexCoord * (1 / prev_pass_used_area));
    }
    // Put the color from the preset textures in all other quadrants
    else 
    {
        vec2 check_coord = vec2(1);

        float num_textures = 16 + 5;

        FragColor = vec4(3);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        check_coord -= (1 - prev_pass_used_area) / num_textures;
        check_coord -= (1 - prev_pass_used_area) / num_textures;
        check_coord -= (1 - prev_pass_used_area) / num_textures;
        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_16, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_15, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_14, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_13, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_12, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_11, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_10, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_9, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_8, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_7, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_6, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_5, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_4, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_3, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_2, vTexCoord);

        check_coord -= (1 - prev_pass_used_area) / num_textures;
        if ((vTexCoord.x < check_coord.x) && (vTexCoord.y < check_coord.y)) FragColor = texture(PresetTex_1, vTexCoord);
    }
    FragColor = mix(FragColor, vec4(0), 0.07);
}
