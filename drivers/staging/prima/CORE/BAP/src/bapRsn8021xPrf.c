/*
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/*
<<<<<<< HEAD
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release
=======
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Woodside Networks, Inc proprietary. All rights reserved.
 * $File: //depot/software/projects/feature_branches/gen5_phase1/os/linux/classic/ap/apps/ssm/auth8021x/ani8021xPrf.c $
 *
 * Contains definitions for routines to calculate the 802.11i PRF
 * functions.
 *
 * Author:  Mayank D. Upadhyay
 * Date:    19-March-2003
 * History:-
 * Date     Modified by Modification Information
 * ------------------------------------------------------
 */

/*#include <assert.h>
#include <stdlib.h>
#include <aniSsmSha1.h>
*/
#include "vos_utils.h"
#include "vos_memory.h"
#include "bapRsn8021xPrf.h"
#include "bapRsnErrors.h"
//#include "ani8021xUtils.h"

#define AAG_PTK_PRF_ADD_PARAM 159
#define AAG_PTK_PRF_DIV_PARAM 160

#define AAG_PTK_PRF_CONST "Pairwise key expansion"
#define AAG_PTK_PRF_CONST_LEN 22

#define AAG_PTK_PRF_LM_POS 0
#define AAG_PTK_PRF_HM_POS 6
#define AAG_PTK_PRF_LN_POS 12
<<<<<<< HEAD
<<<<<<< HEAD
#define AAG_PTK_PRF_HN_POS AAG_PTK_PRF_LN_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE

#define AAG_PTK_PRF_TEXT_LEN AAG_PTK_PRF_HN_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE
=======
#define AAG_PTK_PRF_HN_POS (AAG_PTK_PRF_LN_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE)

#define AAG_PTK_PRF_TEXT_LEN (AAG_PTK_PRF_HN_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE)
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release
=======
#define AAG_PTK_PRF_HN_POS (AAG_PTK_PRF_LN_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE)

#define AAG_PTK_PRF_TEXT_LEN (AAG_PTK_PRF_HN_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE)
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release

#define AAG_GTK_PRF_CONST "Group key expansion"
#define AAG_GTK_PRF_CONST_LEN 19

#define AAG_GTK_PRF_MAC_POS 0
#define AAG_GTK_PRF_NONCE_POS 6

<<<<<<< HEAD
<<<<<<< HEAD
#define AAG_GTK_PRF_TEXT_LEN AAG_GTK_PRF_NONCE_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE
=======
#define AAG_GTK_PRF_TEXT_LEN (AAG_GTK_PRF_NONCE_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE)
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release
=======
#define AAG_GTK_PRF_TEXT_LEN (AAG_GTK_PRF_NONCE_POS + ANI_EAPOL_KEY_RSN_NONCE_SIZE)
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release

/**
 * aagGetKeyMaterialLen
 *
 * Returns the number of bytes of the PTK that have to be provided to
 * the MAC layer for a given cipher type.
 *
 * @param cipherType the cipher-type
 *
 * @return the number of bytes of key material for this cipher type,
 * or 0 for invalid cipher types.
 */
int
aagGetKeyMaterialLen(eCsrEncryptionType cipherType)
{
    switch (cipherType) {
    case eCSR_ENCRYPT_TYPE_AES:
        return AAG_RSN_KEY_MATERIAL_LEN_CCMP;
        break;
    default:
        return 0;
        break;
    };
}

/**
 * aagPtkPrf
 *
 * The PRF used for calculating the pairwise temporal key under IEEE
 * 802.11i.
 *
 * @param result a fixed size array where the outputis stored. Should
 * have enough place for the SHA-1 overflow.
 * @param prfLen the number of BITS desired from the PRF result
 * @param pmk the pairwise master-key
 * @param authAddr the MAC address of the authenticator
 * @param suppAddr the MAC address of the supplicant
 * @param aNonce the nonce generated by the authenticator
 * @param sNonce the nonce generated by the supplicant
 *
 * @return ANI_OK if the operation succeeds
 */
int
aagPtkPrf(v_U32_t cryptHandle,
          v_U8_t result[AAG_PRF_MAX_OUTPUT_SIZE],
          v_U32_t prfLen,
          tAniPacket *pmk, 
          tAniMacAddr authAddr,
          tAniMacAddr suppAddr,
          v_U8_t aNonce[ANI_EAPOL_KEY_RSN_NONCE_SIZE],
          v_U8_t sNonce[ANI_EAPOL_KEY_RSN_NONCE_SIZE])
{
    v_U8_t *lowMac;
    v_U8_t *highMac;
    v_U8_t *lowNonce;
    v_U8_t *highNonce;

    v_U8_t *keyBytes;
    int keyLen;

    v_U8_t text[AAG_PTK_PRF_TEXT_LEN];

    //Cannot use voss function here because vos_mem_compare doesn't tell whihc is larger
    if (vos_mem_compare2(authAddr, suppAddr, sizeof(tAniMacAddr)) < 0) {
        lowMac = authAddr;
        highMac = suppAddr;
    } else {
        lowMac = suppAddr;
        highMac = authAddr;
    }

    if (vos_mem_compare2(aNonce, sNonce, ANI_EAPOL_KEY_RSN_NONCE_SIZE) < 0) {
        lowNonce = aNonce;
        highNonce = sNonce;
    } else {
        lowNonce = sNonce;
        highNonce = aNonce;
    }

    vos_mem_copy(text + AAG_PTK_PRF_LM_POS, lowMac, sizeof(tAniMacAddr));
    vos_mem_copy(text + AAG_PTK_PRF_HM_POS, highMac, sizeof(tAniMacAddr));
    vos_mem_copy(text + AAG_PTK_PRF_LN_POS, lowNonce, ANI_EAPOL_KEY_RSN_NONCE_SIZE);
    vos_mem_copy(text + AAG_PTK_PRF_HN_POS, highNonce, ANI_EAPOL_KEY_RSN_NONCE_SIZE);

    keyLen = aniAsfPacketGetBytes(pmk, &keyBytes);
    if( !ANI_IS_STATUS_SUCCESS( keyLen ) )
    {
        return keyLen;
    }

    return aagPrf(cryptHandle,
                  result, 
                  keyBytes, keyLen, 
                  (v_U8_t *)AAG_PTK_PRF_CONST, AAG_PTK_PRF_CONST_LEN,
                  text, sizeof(text),
                  prfLen);
}

/**
 * aagGtkPrf
 *
 * The PRF used for calculating the group temporal key under IEEE
 * 802.11i.
 *
 * @param result a fixed size array where the outputis stored. Should
 * have enough place for the SHA-1 overflow.
 * @param prfLen the number of BITS desired from the PRF result
 * @param gmk the group master-key
 * @param authAddr the MAC address of the authenticator
 * @param gNonce the nonce generated by the authenticator for this purpose
 *
 * @return ANI_OK if the operation succeeds
 */
int
aagGtkPrf(v_U32_t cryptHandle,
          v_U8_t result[AAG_PRF_MAX_OUTPUT_SIZE],
          v_U32_t prfLen,
          v_U8_t gmk[AAG_RSN_GMK_SIZE],
          tAniMacAddr authAddr,
          v_U8_t gNonce[ANI_EAPOL_KEY_RSN_NONCE_SIZE])
{
    v_U8_t text[AAG_GTK_PRF_TEXT_LEN];

    vos_mem_copy(text + AAG_GTK_PRF_MAC_POS, authAddr, sizeof(tAniMacAddr));
    vos_mem_copy(text + AAG_GTK_PRF_NONCE_POS, gNonce, ANI_EAPOL_KEY_RSN_NONCE_SIZE);

    return aagPrf(cryptHandle,
                  result,
                  gmk, AAG_RSN_GMK_SIZE,
                  (v_U8_t *)AAG_GTK_PRF_CONST, AAG_GTK_PRF_CONST_LEN,
                  text, sizeof(text),
                  prfLen);

}

/**
 * aagPrf
 *
 * The raw PRF function that is used in IEEE 802.11i.
 *
 * @param result a fixed size array where the outputis stored. Should
 * have enough place for the SHA-1 overflow.
 * @param key the key to use in the PRF
 * @param keyLen the length of the key
 * @param a the parameter A which is usually a unique label
 * @param aLen the length of the parameter A
 * @ param b the parameter B
 * @param bLen the length of parameter B
 * @param prfLen the number to BITS desired from the PRF result
 *
 * @return ANI_OK if the operation succeeds
 */
int
aagPrf(v_U32_t cryptHandle,
       v_U8_t result[AAG_PRF_MAX_OUTPUT_SIZE],
       v_U8_t *key, v_U8_t keyLen,
       v_U8_t *a, v_U8_t aLen,
       v_U8_t *b, v_U8_t bLen,
       v_U32_t prfLen)
{
<<<<<<< HEAD
<<<<<<< HEAD
    static v_U8_t y = 0;
=======
    static v_U8_t y;
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release
=======
    static v_U8_t y;
>>>>>>> 1eaa4f9... prima: import from Ghost KK mr2 source release

    v_U8_t *hmacText = NULL;
    v_U8_t *resultOffset = result;
    int numLoops;
    int loopCtrPos;
    int i, retVal=0;

    hmacText = vos_mem_malloc( aLen + bLen + 2 );
    if( NULL == hmacText )
    {
        return ANI_E_NULL_VALUE;
    }

    vos_mem_copy(hmacText + 0, a, aLen);
    hmacText[aLen] = y;
    vos_mem_copy(hmacText + aLen + 1, b, bLen);
    loopCtrPos = aLen + 1 + bLen;

    numLoops = prfLen + AAG_PTK_PRF_ADD_PARAM;
    numLoops /= AAG_PTK_PRF_DIV_PARAM;

    for (i = 0; i < numLoops; i++) 
    {
        VOS_ASSERT((resultOffset - result + VOS_DIGEST_SHA1_SIZE)
               <= AAG_PRF_MAX_OUTPUT_SIZE);
        hmacText[loopCtrPos] = i;
        if( VOS_IS_STATUS_SUCCESS( vos_sha1_hmac_str(cryptHandle, hmacText, loopCtrPos + 1, key, keyLen, resultOffset) ) )
        {
            resultOffset += VOS_DIGEST_SHA1_SIZE;
            retVal = ANI_OK;
        }
        else
        {
            retVal = ANI_ERROR;
        }
    }

    vos_mem_free(hmacText);

    return retVal;
}

