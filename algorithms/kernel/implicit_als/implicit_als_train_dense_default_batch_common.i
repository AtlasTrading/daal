/* file: implicit_als_train_dense_default_batch_common.i */
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
//  Implementation of common computational kernels of impicit ALS training algorithm
//--
*/

#ifndef __IMPLICIT_ALS_TRAIN_DENSE_DEFAULT_BATCH_COMMON_I__
#define __IMPLICIT_ALS_TRAIN_DENSE_DEFAULT_BATCH_COMMON_I__

#include "service_blas.h"

namespace daal
{
namespace algorithms
{
namespace implicit_als
{
namespace training
{
namespace internal
{
template <typename algorithmFPType, CpuType cpu>
void computeXtX(
    size_t *nRows, size_t *nCols, algorithmFPType *beta, algorithmFPType *x, size_t *ldx,
    algorithmFPType *xtx, size_t *ldxtx)
{
    /* SYRK parameters */
    char uplo = 'U';
    char trans = 'N';
    algorithmFPType alpha = 1.0;

    daal::internal::Blas<algorithmFPType, cpu>::xsyrk(&uplo, &trans, (DAAL_INT *)nCols, (DAAL_INT *)nRows, &alpha, x, (DAAL_INT *)ldx, beta,
                       xtx, (DAAL_INT *)ldxtx);
}

}
}
}
}
}

#endif
