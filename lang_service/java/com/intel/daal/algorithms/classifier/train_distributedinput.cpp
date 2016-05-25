/* file: train_distributedinput.cpp */
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

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_intel_daal_algorithms_classifier_training_TrainingDistributedInput */

#include "daal.h"
#include "classifier/training/JTrainingDistributedInput.h"

#include "common_helpers.h"

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::classifier;
using namespace daal::algorithms::classifier::training;

JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_classifier_training_TrainingDistributedInput_cInit
(JNIEnv *env, jobject thisObj, jlong algAddr )
{
    classifier::training::DistributedInput *inputPtr = NULL;

    //    if(cmode == jBatch)
    //    {
    SharedPtr<Distributed> alg =
        staticPointerCast<Distributed, AlgorithmIface>
            (*(SharedPtr<AlgorithmIface> *)algAddr);
    inputPtr = &(alg->input);
    //    }

    return (jlong)inputPtr;
}

/*
 * Class:     com_intel_daal_algorithms_classifier_training_TrainingDistributedInput
 * Method:    cSetDataSet
 * Signature: (JIJ)I
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_classifier_training_TrainingDistributedInput_cAddInput
(JNIEnv *env, jobject thisObj, jlong inputAddr, jint id, jlong ntAddr )
{
    jniInput<classifier::training::DistributedInput>::
        add<classifier::training::Step2MasterInputId, classifier::training::PartialResult>(inputAddr, classifier::training::partialModels, ntAddr);
}
