/* file: batch_input.cpp */
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
#include "math/logistic/JInput.h"
#include "math/logistic/JInputId.h"
#include "math/logistic/JMethod.h"
#include "daal.h"
#include "common_helpers.h"

USING_COMMON_NAMESPACES()
using namespace daal::algorithms::math;

#define InputDataId        com_intel_daal_algorithms_math_logistic_InputId_dataId

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_math_logistic_Input_cSetInput
(JNIEnv *jenv, jobject thisObj, jlong inputAddr, jint id, jlong ntAddr)
{
    if(id == InputDataId)
    {
        jniInput<logistic::Input>::set<logistic::InputId, NumericTable>(inputAddr, logistic::data, ntAddr);
    }
}

JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_math_logistic_Input_cGetInputTable
(JNIEnv *jenv, jobject thisObj, jlong inputAddr, jint id)
{
    if(id == InputDataId)
    {
        return jniInput<logistic::Input>::get<logistic::InputId, NumericTable>(inputAddr, logistic::data);
    }

    return (jlong)0;
}
