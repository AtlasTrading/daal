/* file: ridge_regression_model.cpp */
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
//  Implementation of the class defining the ridge regression model
//--
*/

#include "algorithms/ridge_regression/ridge_regression_model.h"
#include "algorithms/ridge_regression/ridge_regression_ne_model.h"
#include "algorithms/ridge_regression/ridge_regression_types.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace ridge_regression
{
namespace interface1
{

Parameter::Parameter() : interceptFlag(true) {}

TrainParameter::TrainParameter()
        : Parameter(),
          ridgeParameters(new HomogenNumericTable<double>(1, 1, NumericTableIface::doAllocate, 1.0))
    {
    };

void TrainParameter::check() const
{
    if (!checkNumericTable(ridgeParameters.get(), _errors.get(), ridgeParametersStr(), packed_mask, 0, 0, 1))
    {
        return;
    }
}

/**
 * Constructs the ridge regression model
 * \param[in] beta  Numeric table that contains ridge regression coefficients
 * \param[in] par   ridge regression parameters
 */
Model::Model(NumericTablePtr &beta, const Parameter &par) : daal::algorithms::Model()
{
    _coefdim = beta->getNumberOfColumns();
    _nrhs = beta->getNumberOfRows();
    _interceptFlag = par.interceptFlag;
    _beta = beta;
}

/**
 * Initializes ridge regression coefficients of the ridge regression model
 */
void Model::initialize()
{
    BlockDescriptor<double> _betaArrayBlock;
    double *_betaArray = NULL;
    _beta->getBlockOfRows(0, _nrhs, writeOnly, _betaArrayBlock);
    _betaArray = _betaArrayBlock.getBlockPtr();
    for(size_t i = 0; i < _coefdim * _nrhs; i++)
    {
        _betaArray[i] = 0;
    }
    _beta->releaseBlockOfRows(_betaArrayBlock);
}

/**
 * Returns the number of regression coefficients
 * \return Number of regression coefficients
 */
size_t Model::getNumberOfBetas() const { return _coefdim; }

/**
 * Returns the number of features in the training data set
 * \return Number of features in the training data set
 */
size_t Model::getNumberOfFeatures() const { return _coefdim - 1; }

/**
 * Returns the number of responses in the training data set
 * \return Number of responses in the training data set
 */
size_t Model::getNumberOfResponses() const { return _nrhs; }

/**
 * Returns true if the ridge regression model contains the intercept term, and false otherwise
 * \return True if the ridge regression model contains the intercept term, and false otherwise
 */
bool Model::getInterceptFlag() const { return _interceptFlag; }

/**
 * Returns the numeric table that contains regression coefficients
 * \return Table that contains regression coefficients
 */
NumericTablePtr Model::getBeta() { return _beta; }

/**
 * Returns the numeric table that contains regression coefficients
 * \return Table that contains regression coefficients
 */
NumericTablePtr Model::getBeta() const { return _beta; }

void Model::setToZero(NumericTable *table)
{
    BlockDescriptor<double> block;
    double *tableArray;

    size_t nRows = table->getNumberOfRows();
    size_t nCols = table->getNumberOfColumns();

    table->getBlockOfRows(0, nRows, writeOnly, block);
    tableArray = block.getBlockPtr();

    for(size_t i = 0; i < nCols * nRows; i++)
    {
        tableArray[i] = 0;
    }

    table->releaseBlockOfRows(block);
}

} // namespace interface1
} // namespace ridge_regression
} // namespace algorithms
} // namespace daal

/**
 * Checks the correctness of ridge regression model
 * \param[in]  model             The model to check
 * \param[in]  par               The parameter of ridge regression algorithm
 * \param[out] errors            The collection of errors
 * \param[in]  coefdim           Required number of ridge regression coefficients
 * \param[in]  nrhs              Required number of responses on the training stage
 * \param[in]  method            Computation method
 */
void daal::algorithms::ridge_regression::checkModel(ridge_regression::Model* model, const daal::algorithms::Parameter *par, services::ErrorCollection *errors,
    const size_t coefdim, const size_t nrhs, int method)
{
    if(!model) { errors->add(ErrorNullModel); return; }

    const Parameter *parameter = static_cast<const Parameter *>(par);

    if(model->getInterceptFlag() != parameter->interceptFlag)
    {
        errors->add(services::Error::create(ErrorIncorrectParameter, ParameterName, interceptFlagStr()));
        return;
    }

    if(!checkNumericTable(model->getBeta().get(), errors, betaStr(), 0, 0, coefdim, nrhs)) { return; }

    size_t dimWithoutBeta = coefdim;
    if(!model->getInterceptFlag())
    {
        dimWithoutBeta--;
    }

    ridge_regression::ModelNormEq* modelNormEq = dynamic_cast<ridge_regression::ModelNormEq*>(model);
    if(!checkNumericTable(modelNormEq->getXTXTable().get(), errors, XTXTableStr(), 0, 0, dimWithoutBeta, dimWithoutBeta)) { return; }
    if(!checkNumericTable(modelNormEq->getXTYTable().get(), errors, XTYTableStr(), 0, 0, dimWithoutBeta, nrhs)) { return; }
}