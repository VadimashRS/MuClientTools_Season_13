// safer.h - written and placed in the public domain by Wei Dai

//! \file safer.h
//! \brief Classes for the SAFER and SAFER-K block ciphers

#ifndef CRYPTOPP_SAFER_H
#define CRYPTOPP_SAFER_H

#include "seckey.h"
#include "secblock.h"

NAMESPACE_BEGIN(CryptoPP)

//! \class SAFER
//! \brief SAFER block cipher
class SAFER
{
public:
	//! \class Base
	//! \brief SAFER block cipher default operation
	class CRYPTOPP_NO_VTABLE Base : public BlockCipher
	{
	public:
		unsigned int OptimalDataAlignment() const {return 1;}
		void UncheckedSetKey(const byte *userkey, unsigned int length, const NameValuePairs &params);

	protected:
		virtual bool Strengthened() const =0;

		SecByteBlock keySchedule;
		static const byte exp_tab[256];
		static const byte log_tab[256];
	};

	//! \class Enc
	//! \brief SAFER block cipher encryption operation
	class CRYPTOPP_NO_VTABLE Enc : public Base
	{
	public:
		void ProcessAndXorBlock(const byte *inBlock, const byte *xorBlock, byte *outBlock) const;
	};

	//! \class Dec
	//! \brief SAFER block cipher decryption operation
	class CRYPTOPP_NO_VTABLE Dec : public Base
	{
	public:
		void ProcessAndXorBlock(const byte *inBlock, const byte *xorBlock, byte *outBlock) const;
	};
};

//! \class SAFER_Impl
//! \brief SAFER block cipher default implementation
//! \tparam BASE SAFER::Enc or SAFER::Dec derived base class
//! \tparam INFO SAFER_Info derived class
//! \tparam STR flag indicating a strengthened implementation
//! \details SAFER-K is not strengthened; while SAFER-SK is strengthened.
template <class BASE, class INFO, bool STR>
class CRYPTOPP_NO_VTABLE SAFER_Impl : public BlockCipherImpl<INFO, BASE>
{
protected:
	bool Strengthened() const {return STR;}
};

//! \class SAFER_K_Info
//! \brief SAFER-K block cipher information
struct SAFER_K_Info : public FixedBlockSize<8>, public VariableKeyLength<16, 8, 16, 8>, public VariableRounds<10, 1, 13>
{
	CRYPTOPP_CONSTEXPR static const char *StaticAlgorithmName() {return "SAFER-K";}
};

//! \class SAFER_K
//! \brief SAFER-K block cipher
//! \sa <a href="http://www.weidai.com/scan-mirror/cs.html#SAFER-K">SAFER-K</a>
class SAFER_K : public SAFER_K_Info, public SAFER, public BlockCipherDocumentation
{
public:
	typedef BlockCipherFinal<ENCRYPTION, SAFER_Impl<Enc, SAFER_K_Info, false> > Encryption;
	typedef BlockCipherFinal<DECRYPTION, SAFER_Impl<Dec, SAFER_K_Info, false> > Decryption;
};

//! \class SAFER_SK_Info
//! \brief SAFER-SK block cipher information
struct SAFER_SK_Info : public FixedBlockSize<8>, public VariableKeyLength<16, 8, 16, 8>, public VariableRounds<10, 1, 13>
{
	CRYPTOPP_CONSTEXPR static const char *StaticAlgorithmName() {return "SAFER-SK";}
};

//! \class SAFER_SK
//! \brief SAFER-SK block cipher
//! \sa <a href="http://www.weidai.com/scan-mirror/cs.html#SAFER-SK">SAFER-SK</a>
class SAFER_SK : public SAFER_SK_Info, public SAFER, public BlockCipherDocumentation
{
public:
	typedef BlockCipherFinal<ENCRYPTION, SAFER_Impl<Enc, SAFER_SK_Info, true> > Encryption;
	typedef BlockCipherFinal<DECRYPTION, SAFER_Impl<Dec, SAFER_SK_Info, true> > Decryption;
};

typedef SAFER_K::Encryption SAFER_K_Encryption;
typedef SAFER_K::Decryption SAFER_K_Decryption;

typedef SAFER_SK::Encryption SAFER_SK_Encryption;
typedef SAFER_SK::Decryption SAFER_SK_Decryption;

NAMESPACE_END

#endif


//////////////////////////////////////////////////////////////////////
// iDev.Games - MuOnline S9EP2 IGC9.5 - TRONG.WIN - DAO VAN TRONG     
//////////////////////////////////////////////////////////////////////

