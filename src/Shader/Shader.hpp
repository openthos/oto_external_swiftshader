// SwiftShader Software Renderer
//
// Copyright(c) 2005-2012 TransGaming Inc.
//
// All rights reserved. No part of this software may be copied, distributed, transmitted,
// transcribed, stored in a retrieval system, translated into any human or computer
// language by any means, or disclosed to third parties without the explicit written
// agreement of TransGaming Inc. Without such an agreement, no rights or licenses, express
// or implied, including but not limited to any patent rights, are granted to you.
//

#ifndef sw_Shader_hpp
#define sw_Shader_hpp

#include "Common/Types.hpp"

#include <string>
#include <vector>

namespace sw
{
	class Shader
	{
	public:
		enum ShaderType
		{
			SHADER_PIXEL = 0xFFFF,
			SHADER_VERTEX = 0xFFFE,
			SHADER_GEOMETRY = 0xFFFD
		};

		enum Opcode
		{
			// Matches order in d3d9types.h
			OPCODE_NOP = 0,
			OPCODE_MOV,
			OPCODE_ADD,
			OPCODE_SUB,
			OPCODE_MAD,
			OPCODE_MUL,
			OPCODE_RCPX,
			OPCODE_RSQX,
			OPCODE_DP3,
			OPCODE_DP4,
			OPCODE_MIN,
			OPCODE_MAX,
			OPCODE_SLT,
			OPCODE_SGE,
			OPCODE_EXP2X,   // D3DSIO_EXP
			OPCODE_LOG2X,   // D3DSIO_LOG
			OPCODE_LIT,
			OPCODE_ATT,   // D3DSIO_DST
			OPCODE_LRP,
			OPCODE_FRC,
			OPCODE_M4X4,
			OPCODE_M4X3,
			OPCODE_M3X4,
			OPCODE_M3X3,
			OPCODE_M3X2,
			OPCODE_CALL,
			OPCODE_CALLNZ,
			OPCODE_LOOP,
			OPCODE_RET,
			OPCODE_ENDLOOP,
			OPCODE_LABEL,
			OPCODE_DCL,
			OPCODE_POWX,
			OPCODE_CRS,
			OPCODE_SGN,
			OPCODE_ABS,
			OPCODE_NRM3,   // D3DSIO_NRM
			OPCODE_SINCOS,
			OPCODE_REP,
			OPCODE_ENDREP,
			OPCODE_IF,
			OPCODE_IFC,
			OPCODE_ELSE,
			OPCODE_ENDIF,
			OPCODE_BREAK,
			OPCODE_BREAKC,
			OPCODE_MOVA,
			OPCODE_DEFB,
			OPCODE_DEFI,

			OPCODE_TEXCOORD = 64,
			OPCODE_TEXKILL,
			OPCODE_TEX,
			OPCODE_TEXBEM,
			OPCODE_TEXBEML,
			OPCODE_TEXREG2AR,
			OPCODE_TEXREG2GB,
			OPCODE_TEXM3X2PAD,
			OPCODE_TEXM3X2TEX,
			OPCODE_TEXM3X3PAD,
			OPCODE_TEXM3X3TEX,
			OPCODE_RESERVED0,
			OPCODE_TEXM3X3SPEC,
			OPCODE_TEXM3X3VSPEC,
			OPCODE_EXPP,
			OPCODE_LOGP,
			OPCODE_CND,
			OPCODE_DEF,
			OPCODE_TEXREG2RGB,
			OPCODE_TEXDP3TEX,
			OPCODE_TEXM3X2DEPTH,
			OPCODE_TEXDP3,
			OPCODE_TEXM3X3,
			OPCODE_TEXDEPTH,
			OPCODE_CMP0,   // D3DSIO_CMP
			OPCODE_BEM,
			OPCODE_DP2ADD,
			OPCODE_DFDX,   // D3DSIO_DSX
			OPCODE_DFDY,   // D3DSIO_DSY
			OPCODE_TEXLDD,
			OPCODE_CMP,   // D3DSIO_SETP
			OPCODE_TEXLDL,
			OPCODE_BREAKP,

			OPCODE_PHASE = 0xFFFD,
			OPCODE_COMMENT = 0xFFFE,
			OPCODE_END = 0xFFFF,

			OPCODE_PS_1_0 = 0xFFFF0100,
			OPCODE_PS_1_1 = 0xFFFF0101,
			OPCODE_PS_1_2 = 0xFFFF0102,
			OPCODE_PS_1_3 = 0xFFFF0103,
			OPCODE_PS_1_4 = 0xFFFF0104,
			OPCODE_PS_2_0 = 0xFFFF0200,
			OPCODE_PS_2_x = 0xFFFF0201,
			OPCODE_PS_3_0 = 0xFFFF0300,
					
			OPCODE_VS_1_0 = 0xFFFE0100,
			OPCODE_VS_1_1 = 0xFFFE0101,
			OPCODE_VS_2_0 = 0xFFFE0200,
			OPCODE_VS_2_x = 0xFFFE0201,
			OPCODE_VS_2_sw = 0xFFFE02FF,
			OPCODE_VS_3_0 = 0xFFFE0300,
			OPCODE_VS_3_sw = 0xFFFE03FF,

			OPCODE_WHILE = 0x80000001,
			OPCODE_ENDWHILE,
			OPCODE_COS,
			OPCODE_SIN,
			OPCODE_TAN,
			OPCODE_ACOS,
			OPCODE_ASIN,
			OPCODE_ATAN,
			OPCODE_ATAN2,
			OPCODE_DP1,
			OPCODE_DP2,
			OPCODE_TRUNC,
			OPCODE_FLOOR,
			OPCODE_CEIL,
			OPCODE_SQRT,
			OPCODE_RSQ,
			OPCODE_LEN2,
			OPCODE_LEN3,
			OPCODE_LEN4,
			OPCODE_DIST1,
			OPCODE_DIST2,
			OPCODE_DIST3,
			OPCODE_DIST4,
			OPCODE_NRM2,
			OPCODE_NRM4,
			OPCODE_DIV,
			OPCODE_MOD,
			OPCODE_EXP2,
			OPCODE_LOG2,
			OPCODE_EXP,
			OPCODE_LOG,
			OPCODE_POW,
			OPCODE_F2B,   // Float to bool
			OPCODE_B2F,   // Bool to float
			OPCODE_ALL,
			OPCODE_ANY,
			OPCODE_NOT,
			OPCODE_OR,
			OPCODE_XOR,
			OPCODE_AND,
			OPCODE_STEP,
			OPCODE_SMOOTH,
			OPCODE_FORWARD1,
			OPCODE_FORWARD2,
			OPCODE_FORWARD3,
			OPCODE_FORWARD4,
			OPCODE_REFLECT1,
			OPCODE_REFLECT2,
			OPCODE_REFLECT3,
			OPCODE_REFLECT4,
			OPCODE_REFRACT1,
			OPCODE_REFRACT2,
			OPCODE_REFRACT3,
			OPCODE_REFRACT4,
			OPCODE_ICMP,
			OPCODE_SELECT,
			OPCODE_EXTRACT,
			OPCODE_INSERT,
			OPCODE_DISCARD,
			OPCODE_FWIDTH,
			OPCODE_LEAVE,   // Return before the end of the function
			OPCODE_CONTINUE,
			OPCODE_TEST,   // Marks the end of the code that can be skipped by 'continue'
		};

		static Opcode OPCODE_DP(int);
		static Opcode OPCODE_LEN(int);
		static Opcode OPCODE_DIST(int);
		static Opcode OPCODE_NRM(int);
		static Opcode OPCODE_FORWARD(int);
		static Opcode OPCODE_REFLECT(int);
		static Opcode OPCODE_REFRACT(int);

		enum Control
		{
			CONTROL_RESERVED0,
			CONTROL_GT,
			CONTROL_EQ,
			CONTROL_GE,
			CONTROL_LT,
			CONTROL_NE,
			CONTROL_LE,
			CONTROL_RESERVED1
		};

		enum SamplerType
		{
			SAMPLER_UNKNOWN,
			SAMPLER_1D,
			SAMPLER_2D,
			SAMPLER_CUBE,
			SAMPLER_VOLUME
		};

		enum Usage   // For vertex input/output declarations
		{
			USAGE_POSITION = 0,
			USAGE_BLENDWEIGHT = 1,
			USAGE_BLENDINDICES = 2,
			USAGE_NORMAL = 3,
			USAGE_PSIZE = 4,
			USAGE_TEXCOORD = 5,
			USAGE_TANGENT = 6,
			USAGE_BINORMAL = 7,
			USAGE_TESSFACTOR = 8,
			USAGE_POSITIONT = 9,
			USAGE_COLOR = 10,
			USAGE_FOG = 11,
			USAGE_DEPTH = 12,
			USAGE_SAMPLE = 13
		};

		enum ParameterType
		{
			PARAMETER_TEMP = 0,
			PARAMETER_INPUT = 1,
			PARAMETER_CONST = 2,
			PARAMETER_TEXTURE = 3,
			PARAMETER_ADDR = 3,
			PARAMETER_RASTOUT = 4,
			PARAMETER_ATTROUT = 5,
			PARAMETER_TEXCRDOUT = 6,
			PARAMETER_OUTPUT = 6,
			PARAMETER_CONSTINT = 7,
			PARAMETER_COLOROUT = 8,
			PARAMETER_DEPTHOUT = 9,
			PARAMETER_SAMPLER = 10,
			PARAMETER_CONST2 = 11,
			PARAMETER_CONST3 = 12,
			PARAMETER_CONST4 = 13,
			PARAMETER_CONSTBOOL = 14,
			PARAMETER_LOOP = 15,
			PARAMETER_TEMPFLOAT16 = 16,
			PARAMETER_MISCTYPE = 17,
			PARAMETER_LABEL = 18,
			PARAMETER_PREDICATE = 19,

		//	PARAMETER_FLOAT1LITERAL,
		//	PARAMETER_FLOAT2LITERAL,
		//	PARAMETER_FLOAT3LITERAL,
			PARAMETER_FLOAT4LITERAL,
			PARAMETER_BOOL1LITERAL,
		//	PARAMETER_BOOL2LITERAL,
		//	PARAMETER_BOOL3LITERAL,
		//	PARAMETER_BOOL4LITERAL,
		//	PARAMETER_INT1LITERAL,
		//	PARAMETER_INT2LITERAL,
		//	PARAMETER_INT3LITERAL,
			PARAMETER_INT4LITERAL,

			PARAMETER_VOID
		};

		enum Modifier
		{
			MODIFIER_NONE,
			MODIFIER_NEGATE,
			MODIFIER_BIAS,
			MODIFIER_BIAS_NEGATE,
			MODIFIER_SIGN,
			MODIFIER_SIGN_NEGATE,
			MODIFIER_COMPLEMENT,
			MODIFIER_X2,
			MODIFIER_X2_NEGATE,
			MODIFIER_DZ,
			MODIFIER_DW,
			MODIFIER_ABS,
			MODIFIER_ABS_NEGATE,
			MODIFIER_NOT
		};

		enum Analysis
		{
			// Flags indicating whether an instruction is affected by an execution enable mask
			ANALYSIS_BRANCH   = 0x00000001,
			ANALYSIS_BREAK    = 0x00000002,
			ANALYSIS_CONTINUE = 0x00000004,
			ANALYSIS_LEAVE    = 0x00000008,
		};

		struct Parameter
		{
			union
			{
				struct
				{
					unsigned int index;   // For registers types

					struct
					{
						ParameterType type : 8;
						unsigned int index;
						unsigned int swizzle : 8;
						unsigned int scale;
						bool deterministic;   // Equal accross shader instances run in lockstep (e.g. unrollable loop couters)
					} rel;
				};

				float value[4];       // For float constants
				int integer[4];       // For integer constants
				int boolean[4];       // For boolean constants

				struct
				{
					unsigned int label;      // Label index
					unsigned int callSite;   // Call index (per label)
				};
			};

			Parameter() : type(PARAMETER_VOID), index(0)
			{
				rel.type = PARAMETER_VOID;
				rel.index = 0;
				rel.swizzle = 0;
				rel.scale = 1;
				rel.deterministic = false;
			}

			std::string string(ShaderType shaderType, unsigned short version) const;
			std::string typeString(ShaderType shaderType, unsigned short version) const;
			std::string relativeString() const;

			ParameterType type : 8;
		};

		struct DestinationParameter : Parameter
		{
			union
			{
				unsigned char mask;

				struct
				{
					bool x : 1;
					bool y : 1;
					bool z : 1;
					bool w : 1;
				};
			};

			DestinationParameter() : mask(0xF), integer(false), saturate(false), partialPrecision(false), centroid(false), shift(0)
			{
			}

			std::string modifierString() const;
			std::string shiftString() const;
			std::string maskString() const;

			bool integer          : 1;
			bool saturate         : 1;
			bool partialPrecision : 1;
			bool centroid         : 1;
			signed char shift     : 4;
		};

		struct SourceParameter : Parameter
		{
			SourceParameter() : swizzle(0xE4), modifier(MODIFIER_NONE)
			{
			}

			std::string swizzleString() const;
			std::string preModifierString() const;
			std::string postModifierString() const;

			unsigned int swizzle : 8;
			Modifier modifier : 8;
		};

		struct Instruction
		{
			explicit Instruction(Opcode opcode);
			Instruction(const unsigned long *token, int size, unsigned char majorVersion);

			virtual ~Instruction();

			void parseOperationToken(unsigned long token, unsigned char majorVersion);
			void parseDeclarationToken(unsigned long token);
			void parseDestinationToken(const unsigned long *token, unsigned char majorVersion);
			void parseSourceToken(int i, const unsigned long *token, unsigned char majorVersion);

			std::string string(ShaderType shaderType, unsigned short version) const;
			static std::string swizzleString(ParameterType type, unsigned char swizzle);
			std::string operationString(unsigned short version) const;
			std::string controlString() const;

			bool isBranch() const;
			bool isCall() const;
			bool isBreak() const;
			bool isLoop() const;
			bool isEndLoop() const;

			Opcode opcode;
			
			union
			{
				Control control;
				
				struct
				{
					unsigned char project : 1;
					unsigned char bias : 1;
				};
			};

			bool predicate;
			bool predicateNot;   // Negative predicate
			unsigned char predicateSwizzle;

			bool coissue;
			SamplerType samplerType;
			Usage usage;
			unsigned char usageIndex;

			DestinationParameter dst;
			SourceParameter src[4];

			union
			{
				unsigned int analysis;

				struct
				{
					// Keep in sync with Shader::Analysis flags
					unsigned int analysisBranch : 1;
					unsigned int analysisBreak : 1;
					unsigned int analysisContinue : 1;
					unsigned int analysisLeave : 1;
				};
			};
		};

		Shader();

		~Shader();

		int getSerialID() const;
		int getLength() const;
		ShaderType getShaderType() const;
		unsigned short getVersion() const;

		void append(Instruction *instruction);
		void declareSampler(int i);

		const Instruction *getInstruction(unsigned int i) const;
		int size(unsigned long opcode) const;
		static int size(unsigned long opcode, unsigned short version);

		void print(const char *fileName, ...) const;
		void printInstruction(int index, const char *fileName) const;

		static bool maskContainsComponent(int mask, int component);
		static bool swizzleContainsComponent(int swizzle, int component);
		static bool swizzleContainsComponentMasked(int swizzle, int component, int mask);

		bool containsDynamicBranching() const;
		bool containsBreakInstruction() const;
		bool containsContinueInstruction() const;
		bool containsLeaveInstruction() const;
		bool usesSampler(int i) const;

		struct Semantic
		{
			Semantic(unsigned char usage = 0xFF, unsigned char index = 0xFF) : usage(usage), index(index), centroid(false)
			{
			}

			bool operator==(const Semantic &semantic) const
			{
				return usage == semantic.usage && index == semantic.index;
			}

			bool active() const
			{
				return usage != 0xFF;
			}

			unsigned char usage;
			unsigned char index;
			bool centroid;
		};

		virtual void analyze() = 0;

		// FIXME: Private
		unsigned int dirtyConstantsF;
		unsigned int dirtyConstantsI;
		unsigned int dirtyConstantsB;

		bool dynamicallyIndexedTemporaries;
		bool dynamicallyIndexedInput;
		bool dynamicallyIndexedOutput;

	protected:
		void parse(const unsigned long *token);

		void analyzeDirtyConstants();
		void analyzeDynamicBranching();
		void analyzeSamplers();
		void analyzeCallSites();
		void analyzeDynamicIndexing();
		void markFunctionAnalysis(int functionLabel, Analysis flag);

		ShaderType shaderType;

		union
		{
			unsigned short version;

			struct
			{
				unsigned char minorVersion;
				unsigned char majorVersion;
			};
		};

		std::vector<Instruction*> instruction;

		unsigned short usedSamplers;   // Bit flags

	private:
		const int serialID;
		static volatile int serialCounter;

		bool dynamicBranching;
		bool containsBreak;
		bool containsContinue;
		bool containsLeave;
	};
}

#endif   // sw_Shader_hpp