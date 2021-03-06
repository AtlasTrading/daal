/* file: svm_train_kernel.h */
/*******************************************************************************
* Copyright 2014-2018 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Declaration of template structs that calculate SVM Training functions.
//--
*/

#ifndef __SVM_TRAIN_KERNEL_H__
#define __SVM_TRAIN_KERNEL_H__

#include "numeric_table.h"
#include "model.h"
#include "daal_defines.h"
#include "svm_train_types.h"
#include "kernel.h"
#include "service_numeric_table.h"

using namespace daal::data_management;
using namespace daal::internal;
using namespace daal::services;

#include "svm_train_boser_cache.i"

namespace daal
{
namespace algorithms
{
namespace svm
{
namespace training
{
namespace internal
{

enum SVMVectorStatus
{
    free    = 0x0,
    up      = 0x1,
    low     = 0x2,
    shrink  = 0x4
};

template <typename algorithmFPType, CpuType cpu>
struct SVMTrainTask
{
    static const size_t kernelFunctionBlockSize = 1024; /* Size of the block of kernel function elements */

    SVMTrainTask(size_t nVectors) : _cache(nullptr), _nVectors(nVectors){}

    Status setup(const Parameter& svmPar, const NumericTablePtr& xTable, NumericTable& yTable);

    /* Perform Sequential Minimum Optimization (SMO) algorithm to find optimal coefficients alpha */
    Status compute(const Parameter& svmPar);

    /* Write support vectors and classification coefficients into model */
    Status setResultsToModel(const NumericTable& xTable, Model& model, algorithmFPType C) const;

    ~SVMTrainTask();

protected:
    Status init(algorithmFPType C);

    inline void updateI(algorithmFPType C, size_t index);

    bool findMaximumViolatingPair(size_t nActiveVectors, algorithmFPType tau, int& Bi, int& Bj,
        algorithmFPType& delta, algorithmFPType& ma, algorithmFPType& Ma, algorithmFPType& curEps, Status& s) const;

    Status reconstructGradient(size_t& nActiveVectors);

    algorithmFPType WSSi(size_t nActiveVectors, int& Bi) const;

    Status WSSj(size_t nActiveVectors, algorithmFPType tau, int Bi, algorithmFPType GMax, int& Bj,
        algorithmFPType& delta, algorithmFPType& res) const;

    Status update(size_t nActiveVectors, algorithmFPType C, int Bi, int Bj, algorithmFPType delta);

    size_t updateShrinkingFlags(size_t nActiveVectors, algorithmFPType C, algorithmFPType ma, algorithmFPType Ma);

    /*** Methods used in shrinking ***/
    size_t doShrink(size_t nActiveVectors);

    /**
    * \brief Write support vectors and classification coefficients into output model
    */
    Status setSVCoefficients(size_t nSV, Model& model) const;
    Status setSVIndices(size_t nSV, Model& model) const;
    Status setSV_Dense(Model& model, const NumericTable& xTable, size_t nSV) const;
    Status setSV_CSR(Model& model, const NumericTable& xTable, size_t nSV) const;
    algorithmFPType calculateBias(algorithmFPType C) const;

    inline void updateAlpha(algorithmFPType C, int Bi, int Bj, algorithmFPType delta,
        algorithmFPType& newDeltai, algorithmFPType& newDeltaj);

protected:
    const size_t _nVectors; //Number of observations in the input data set
    TArray<algorithmFPType, cpu> _y; //Array of class labels
    TArray<algorithmFPType, cpu> _alpha; //Array of classification coefficients
    TArray<algorithmFPType, cpu> _grad; //Objective function gradient
    TArray<algorithmFPType, cpu> _kernelDiag; //diagonal elements of the matrix Q (kernel(x[i], x[i]))
    TArray<char, cpu> _I; // array of flags I_LOW and I_UP
    SVMCacheIface<algorithmFPType, cpu> *_cache; //caches matrix Q (kernel(x[i], x[j])) values
};

template <Method method, typename algorithmFPType, CpuType cpu>
struct SVMTrainImpl : public Kernel
{
    services::Status compute(const NumericTablePtr& xTable, NumericTable& yTable,
        daal::algorithms::Model *r, const daal::algorithms::Parameter *par);
};

} // namespace internal

} // namespace training

} // namespace svm

} // namespace algorithms

} // namespace daal

#endif
