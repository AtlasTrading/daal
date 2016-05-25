/* file: abs_layer_backward_kernel.h */
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

//++
//  Implementation of abs layer.
//--


#ifndef __ABS_LAYER_BACKWARD_KERNEL_H__
#define __ABS_LAYER_BACKWARD_KERNEL_H__

#include "neural_networks/layers/abs/abs_layer.h"
#include "neural_networks/layers/abs/abs_layer_types.h"
#include "kernel.h"
#include "tensor.h"
#include "threading.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace abs
{
namespace backward
{
namespace internal
{

/**
 *  \brief Kernel for abs calculation
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class AbsKernel : public Kernel
{
public:
    void compute(const abs::backward::Input *input, const daal::algorithms::Parameter *par,
                 abs::backward::Result *result);

private:
    const size_t _nRowsInBlock = 5000;

    inline void processBlock(SharedPtr<Tensor> inputTable,
                             SharedPtr<Tensor> forwardOutputTable,
                             size_t nProcessedRows, size_t nRowsInCurrentBlock,
                             SharedPtr<Tensor> resultTable);
};

} // internal
} // backward
} // abs
} // layers
} // neural_networks
} // algorithms
} // daal

#endif
