/* file: implicit_als_predict_ratings_dense_default_kernel.h */
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

/*
//++
//  Declaration of structure containing kernels for implicit ALS
//  prediction.
//--
*/

#ifndef __IMPLICIT_ALS_PREDICT_RATINGS_DENSE_DEFAULT_KERNEL_H__
#define __IMPLICIT_ALS_PREDICT_RATINGS_DENSE_DEFAULT_KERNEL_H__

#include "implicit_als_predict_ratings_batch.h"
#include "implicit_als_predict_ratings_distributed.h"
#include "implicit_als_model.h"
#include "kernel.h"

#include "service_micro_table.h"

using namespace daal::data_management;

namespace daal
{
namespace algorithms
{
namespace implicit_als
{
namespace prediction
{
namespace ratings
{
namespace internal
{

template <typename algorithmFPType, CpuType cpu>
class ImplicitALSPredictKernel : public daal::algorithms::Kernel
{
public:
    ImplicitALSPredictKernel() {}
    virtual ~ImplicitALSPredictKernel() {}

    void compute(const NumericTable *usersFactorsTable, const NumericTable *itemsFactorsTable,
                NumericTable *ratingsTable, const Parameter *parameter);

protected:
    void getFactors(daal::internal::BlockMicroTable<algorithmFPType, readOnly, cpu> &mtFactors1,
                size_t nRows1, algorithmFPType **factors1,
                daal::internal::BlockMicroTable<algorithmFPType, readOnly, cpu> &mtFactors2,
                size_t nRows2, algorithmFPType **factors2);
};

}
}
}
}
}
}

#endif
