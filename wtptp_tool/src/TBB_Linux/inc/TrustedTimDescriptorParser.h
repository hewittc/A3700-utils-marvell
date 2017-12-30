/******************************************************************************
 *
 *  (C)Copyright 2005 - 2008 Marvell. All Rights Reserved.
 *  
 *  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF MARVELL.
 *  The copyright notice above does not evidence any actual or intended 
 *  publication of such source code.
 *  This Module contains Proprietary Information of Marvell and should be
 *  treated as Confidential.
 *  The information in this file is provided for the exclusive use of the 
 *  licensees of Marvell.
 *  Such users have the right to use, modify, and incorporate this code into 
 *  products for purposes authorized by the license agreement provided they 
 *  include this notice and the associated copyright notice with any such
 *  product. 
 *  The information in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/
  /********************************************************************************
Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	* Neither the name of Marvell nor the names of its contributors may be
	  used to endorse or promote products derived from this software without
	  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/


#ifndef __TRUSTED_TIM_DESCRIPTOR_PARSER_H__
#define __TRUSTED_TIM_DESCRIPTOR_PARSER_H__

#include "TimDescriptorParser.h"
#include "RSAKey.h"
#include "ECCKey.h"
#include "DigitalSignature.h"

#include <list>
#include <iterator>
using namespace std;

typedef list<pKEY_MOD_3_4_0> t_KeyInfoList;
typedef list<pKEY_MOD_3_4_0>::iterator t_KeyInfoListIter;

#if TOOLS_GUI == 0
class CCommandLineParser;
class CKey;
#endif

class CTrustedTimDescriptorParser: public CTimDescriptorParser {
public:
	CTrustedTimDescriptorParser(CCommandLineParser& CommandLineParser);
	virtual ~CTrustedTimDescriptorParser(void);

	virtual void Reset(); // use to reset parser if tim descriptor read fails
	virtual bool VerifyNumberOfKeys();

	virtual bool ParseTrustedDescriptor(CCommandLineParser& CommandLineParser,
			CTimDescriptorLine*& pLine);
	bool ParseKeyFile(CCommandLineParser& CommandLineParser,
			string& sKeyFilePath, CKey*& pKey, bool bIgnorePrivateKey = false);
	bool ParseBinaryKeyFile(string& sKeyBinaryFilePath,
			CCommandLineParser& CommandLineParser, CKey*& pKey);

protected:
	bool ParseKeyInfoTIM(CTimDescriptorLine*& pLine);
	bool ParseKeyInfoBlf(CTimDescriptorLine*& pLine, string& sNum);
	bool ParseRSAKeyTIM(CRSAKey* pKey, CTimDescriptorLine*& pLine);
	bool ParseRSAKeyBlf(CRSAKey* pKey, CTimDescriptorLine*& pLine);
	bool ParseECCKeyTIM(CECCKey* pKey, CTimDescriptorLine*& pLine);
	bool ParseECCKeyBlf(CECCKey* pKey, CTimDescriptorLine*& pLine);
	bool CheckPINCount();

	bool ParseDsaInfoTIM(CCommandLineParser& CommandLineParser);
	bool ParseDsaInfoBlf(CCommandLineParser& CommandLineParser);
	bool ParseDTIMKeysDataBlf(CCommandLineParser& CommandLineParser);
	bool ParseRSATIM(CCommandLineParser& CommandLineParser,
			CTimDescriptorLine*& pLine);
	bool ParseRSABlf(CDigitalSignature& DSig,
			CCommandLineParser& CommandLineParser, CTimDescriptorLine*& pLine);
	bool ParseECDSATIM(CCommandLineParser& CommandLineParser,
			CTimDescriptorLine*& pLine);
	bool ParseECDSABlf(CDigitalSignature& DSig,
			CCommandLineParser& CommandLineParser, CTimDescriptorLine*& pLine);
};
#endif //__TRUSTED_TIM_DESCRIPTOR_PARSER_H__