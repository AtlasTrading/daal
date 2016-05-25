/* file: backward_batch.cpp */
/*******************************************************************************
* Copyright 2014-2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <jni.h>
#include "neural_networks/layers/average_pooling1d/JBackwardBatch.h"

#include "daal.h"

#include "common_helpers.h"

using namespace daal;
using namespace daal::algorithms::neural_networks::layers;

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_average_1pooling1d_BackwardBatch
 * Method:    cInit
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_BackwardBatch_cInit
(JNIEnv *env, jobject thisObj, jint prec, jint method, jlong nDim)
{
    return jniBatch<average_pooling1d::Method, average_pooling1d::backward::Batch, average_pooling1d::defaultDense>::
           newObj(prec, method, nDim);
}


/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_average_1pooling1d_BackwardBatch
 * Method:    cGetInput
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_BackwardBatch_cGetInput
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniBatch<average_pooling1d::Method, average_pooling1d::backward::Batch, average_pooling1d::defaultDense>::
           getInput(prec, method, algAddr);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_average_1pooling1d_BackwardBatch
 * Method:    cInitParameter
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_BackwardBatch_cInitParameter
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniBatch<average_pooling1d::Method, average_pooling1d::backward::Batch, average_pooling1d::defaultDense>::
           getParameter(prec, method, algAddr);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_average_1pooling1d_BackwardBatch
 * Method:    cGetResult
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_BackwardBatch_cGetResult
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniBatch<average_pooling1d::Method, average_pooling1d::backward::Batch, average_pooling1d::defaultDense>::
           getResult(prec, method, algAddr);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_average_1pooling1d_BackwardBatch
 * Method:    cSetResult
 * Signature: (JIIJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_BackwardBatch_cSetResult
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method, jlong resAddr)
{
    jniBatch<average_pooling1d::Method, average_pooling1d::backward::Batch, average_pooling1d::defaultDense>::
    setResult<average_pooling1d::backward::Result>(prec, method, algAddr, resAddr);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_average_1pooling1d_BackwardBatch
 * Method:    cClone
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_BackwardBatch_cClone
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniBatch<average_pooling1d::Method, average_pooling1d::backward::Batch, average_pooling1d::defaultDense>::
           getClone(prec, method, algAddr);
}
