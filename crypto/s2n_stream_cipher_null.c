/*
 * Copyright 2014 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "error/s2n_errno.h"

#include "crypto/s2n_cipher.h"

#include "utils/s2n_safety.h"
#include "utils/s2n_blob.h"

int s2n_stream_cipher_null_endecrypt(struct s2n_session_key *key, struct s2n_blob *in, struct s2n_blob *out)
{
    if (out->data < in->data) {
        S2N_ERROR(S2N_ERR_SIZE_MISMATCH);
    }

    if (in->data != out->data) {
        memcpy_check(in->data, out->data, out->size);
    }
    return 0;
}

int s2n_stream_cipher_null_get_key(struct s2n_session_key *key, struct s2n_blob *in)
{
    return 0;
}

int s2n_stream_cipher_null_destroy_key(struct s2n_session_key *key)
{
    return 0;
}

struct s2n_cipher s2n_null_cipher = {
    .type = S2N_STREAM,
    .key_material_size = 0,
    .io.stream = {
                  .decrypt = s2n_stream_cipher_null_endecrypt,
                  .encrypt = s2n_stream_cipher_null_endecrypt},
    .get_encryption_key = s2n_stream_cipher_null_get_key,
    .get_decryption_key = s2n_stream_cipher_null_get_key,
    .destroy_key = s2n_stream_cipher_null_destroy_key,
};
