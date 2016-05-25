/* file: training_init_partial_result.cpp */
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

#include "daal.h"

#include "implicit_als/training/init/JInitPartialResult.h"

#include "implicit_als_init_defines.i"

#include "common_helpers.h"

USING_COMMON_NAMESPACES()
using namespace daal::algorithms::implicit_als::training::init;

/*
 * Class:     com_intel_daal_algorithms_implicit_als_training_init_InitPartialResult
 * Method:    cNewPartialResult
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_implicit_1als_training_init_InitPartialResult_cNewPartialResult
(JNIEnv *env, jobject thisObj)
{
    return jniArgument<implicit_als::training::init::PartialResult>::newObj();
}

/*
 * Class:     com_intel_daal_algorithms_implicit_als_training_init_InitPartialResult
 * Method:    cGetPartialResult
 * Signature: (JIII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_implicit_1als_training_init_InitPartialResult_cGetPartialResult
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method, jint cmode)
{
    if (cmode == jDistributed)
    {
        return jniDistributed<step1Local, implicit_als::training::init::Method, Distributed, fastCSR>::
            getPartialResult(prec, method, algAddr);
    }

    return (jlong)0;
}

/*
 * Class:     com_intel_daal_algorithms_implicit_als_training_init_InitPartialResult
 * Method:    cGetPartialResultModel
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_implicit_1als_training_init_InitPartialResult_cGetPartialResultModel
(JNIEnv *env, jobject thisObj, jlong partialResultAddr, jint id)
{
    return jniArgument<implicit_als::training::init::PartialResult>::
        get<PartialResultId, implicit_als::PartialModel>(partialResultAddr, partialModel);
}

/*
 * Class:     com_intel_daal_algorithms_implicit_als_training_init_InitPartialResult
 * Method:    cSetPartialResultModel
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_implicit_1als_training_init_InitPartialResult_cSetPartialResultModel
(JNIEnv *env, jobject thisObj, jlong resAddr, jint id, jlong mdlAddr)
{
    SharedPtr<SerializationIface> *res = (SharedPtr<SerializationIface> *)resAddr;
    SharedPtr<daal::algorithms::Model> *mdlShPtr = (SharedPtr<daal::algorithms::Model> *)mdlAddr;

    // daal::algorithms::implicit_als::training::PartialResultId cid;
    // if(id == initPartialModelId) {cid = daal::algorithms::implicit_als::training::PartialResultId::partialModel;}
    // else {return;}

    // daal::algorithms::implicit_als::training::PartialResult *partialResult =
    //      (daal::algorithms::implicit_als::training::PartialResult *)(res->get());
    // partialResult->set(cid, *mdlShPtr);
}
