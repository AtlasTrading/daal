/* file: multiclassconfusionmatrixresult.cpp */
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
#include "daal.h"
#include "JComputeMode.h"
#include "classifier/quality_metric/multi_class_confusion_matrix/JMultiClassConfusionMatrixResult.h"
#include "classifier/quality_metric/multi_class_confusion_matrix/JMultiClassConfusionMatrixResultId.h"
#include "classifier/quality_metric/multi_class_confusion_matrix/JMultiClassConfusionMatrixMethod.h"

#include "common_helpers.h"

#define ConfMatrix com_intel_daal_algorithms_classifier_quality_metric_multi_class_confusion_matrix_MultiClassConfusionMatrixResultId_ConfusionMatrix
#define MCMetrics com_intel_daal_algorithms_classifier_quality_metric_multi_class_confusion_matrix_MultiClassConfusionMatrixResultId_MultiClassMetrics

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::classifier::quality_metric;
using namespace daal::algorithms::classifier::quality_metric::multiclass_confusion_matrix;

/*
 * Class:     com_intel_daal_algorithms_classifier_quality_metric_multi_class_confusion_matrix_MultiClassConfusionMatrixResult
 * Method:    cSetResultTable
 * Signature: (JIJ)V
 */
JNIEXPORT void
JNICALL Java_com_intel_daal_algorithms_classifier_quality_1metric_multi_1class_1confusion_1matrix_MultiClassConfusionMatrixResult_cSetResultTable
(JNIEnv *, jobject, jlong resAddr, jint id, jlong ntAddr)
{
    jniArgument<multiclass_confusion_matrix::Result>::set<multiclass_confusion_matrix::ResultId, NumericTable>(resAddr, id, ntAddr);
}

/*
 * Class:     com_intel_daal_algorithms_classifier_quality_metric_multi_class_confusion_matrix_MultiClassConfusionMatrixResult
 * Method:    cGetResultTable
 * Signature: (JI)J
 */
JNIEXPORT jlong
JNICALL Java_com_intel_daal_algorithms_classifier_quality_1metric_multi_1class_1confusion_1matrix_MultiClassConfusionMatrixResult_cGetResultTable
(JNIEnv *, jobject, jlong resAddr, jint id)
{
    if (id == ConfMatrix)
    {
        return jniArgument<multiclass_confusion_matrix::Result>::
            get<multiclass_confusion_matrix::ResultId, NumericTable>(resAddr, confusionMatrix);
    } else if (id == MCMetrics)
    {
        return jniArgument<multiclass_confusion_matrix::Result>::
            get<multiclass_confusion_matrix::ResultId, NumericTable>(resAddr, multiClassMetrics);
    }

    return (jlong)0;

}

JNIEXPORT jlong
JNICALL Java_com_intel_daal_algorithms_classifier_quality_1metric_multi_1class_1confusion_1matrix_MultiClassConfusionMatrixResult_cNewResult
(JNIEnv *, jobject)
{
    return jniArgument<multiclass_confusion_matrix::Result>::newObj();
}
