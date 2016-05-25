/* file: low_order_moments_csr_batch.cpp */
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
!  Content:
!    C++ example of computing low order moments in the batch processing mode.
!
!    Input matrix is stored in the compressed sparse row (CSR) format with
!    one-based indexing.
!******************************************************************************/

/**
 * <a name="DAAL-EXAMPLE-CPP-LOW_ORDER_MOMENTS_CSR_BATCH">
 * \example low_order_moments_csr_batch.cpp
 */

#include "daal.h"
#include "service.h"

using namespace std;
using namespace daal;
using namespace daal::algorithms;

typedef float  dataFPType;          /* Data floating-point type */
typedef double algorithmFPType;     /* Algorithm floating-point type */

/*
 * Input data set parameters
 * Input matrix is stored in the CSR format with one-based indexing
 */
const string datasetFileName = "../data/batch/covcormoments_csr.csv";

void printResults(const services::SharedPtr<low_order_moments::Result> &res);

int main(int argc, char *argv[])
{
    checkArguments(argc, argv, 1, &datasetFileName);

    /* Read datasetFileName from a file and create numeric tables to store the input data */
    CSRNumericTable *dataTable = createSparseTable<dataFPType>(datasetFileName);

    /* Create an algorithm to compute low order moments in the batch processing mode using the default method */
    low_order_moments::Batch<algorithmFPType, low_order_moments::fastCSR> algorithm;

    /* Set input objects for the algorithm */
    algorithm.input.set(low_order_moments::data, services::SharedPtr<CSRNumericTable>(dataTable));

    /* Compute low order moments */
    algorithm.compute();


    /* Get the computed low order moments */
    services::SharedPtr<low_order_moments::Result> res = algorithm.getResult();

    printResults(res);

    return 0;
}

void printResults(const services::SharedPtr<low_order_moments::Result> &res)
{
    printNumericTable(res->get(low_order_moments::minimum),              "Minimum:");
    printNumericTable(res->get(low_order_moments::maximum),              "Maximum:");
    printNumericTable(res->get(low_order_moments::sum),                  "Sum:");
    printNumericTable(res->get(low_order_moments::sumSquares),           "Sum of squares:");
    printNumericTable(res->get(low_order_moments::sumSquaresCentered),   "Sum of squared difference from the means:");
    printNumericTable(res->get(low_order_moments::mean),                 "Mean:");
    printNumericTable(res->get(low_order_moments::secondOrderRawMoment), "Second order raw moment:");
    printNumericTable(res->get(low_order_moments::variance),             "Variance:");
    printNumericTable(res->get(low_order_moments::standardDeviation),    "Standard deviation:");
    printNumericTable(res->get(low_order_moments::variation),            "Variation:");
}
