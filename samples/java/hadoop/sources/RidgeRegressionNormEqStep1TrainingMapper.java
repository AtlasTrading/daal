/* file: RidgeRegressionNormEqStep1TrainingMapper.java */
//==============================================================
//
// SAMPLE SOURCE CODE - SUBJECT TO THE TERMS OF SAMPLE CODE LICENSE AGREEMENT,
// http://software.intel.com/en-us/articles/intel-sample-source-code-license-agreement/
//
// Copyright 2017-2018 Intel Corporation
//
// THIS FILE IS PROVIDED "AS IS" WITH NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS.
//
// =============================================================

package DAAL;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.BufferedWriter;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.Arrays;

import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Mapper.Context;
import org.apache.hadoop.conf.Configuration;

import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.algorithms.ridge_regression.Model;
import com.intel.daal.algorithms.ridge_regression.training.*;
import com.intel.daal.data_management.data.*;
import com.intel.daal.services.*;

public class RidgeRegressionNormEqStep1TrainingMapper extends Mapper<Object, Text, IntWritable, WriteableData> {

    private static final int nDataFeatures   = 10;  /* Number of features in training and testing data sets */
    private static final int nLabelsFeatures = 2;   /* Number of dependent variables that correspond to each observation */
    private static final int nVectorsInBlock = 250;

    /* Index is supposed to be a sequence number for the split */
    private int index = 0;
    private int totalTasks = 0;

    @Override
    public void setup(Context context) {
        index = context.getTaskAttemptID().getTaskID().getId();
        Configuration conf = context.getConfiguration();
        totalTasks = conf.getInt("mapred.map.tasks", 0);
    }

    @Override
    public void map(Object key, Text value,
                    Context context) throws IOException, InterruptedException {

        /* Read a data set */
        String dataFilePath = "/Hadoop/RidgeRegressionNormEq/data/" + value + "_train.csv";
        String labelsFilePath = "/Hadoop/RidgeRegressionNormEq/data/" + value + "_train_labels.csv";

        double[] data = new double[nDataFeatures * nVectorsInBlock];
        double[] labels = new double[nLabelsFeatures * nVectorsInBlock];

        readData(dataFilePath, nDataFeatures, nVectorsInBlock, data);
        readData(labelsFilePath, nLabelsFeatures, nVectorsInBlock, labels);

        DaalContext daalContext = new DaalContext();

        HomogenNumericTable ntData = new HomogenNumericTable(daalContext, data, nDataFeatures, nVectorsInBlock);
        HomogenNumericTable ntLabels = new HomogenNumericTable(daalContext, labels, nLabelsFeatures, nVectorsInBlock);

        /* Create an algorithm object to train the ridge regression model with the normal equations method */
        TrainingDistributedStep1Local ridgeRegressionTraining = new TrainingDistributedStep1Local(daalContext,
                                                                                                  Double.class, TrainingMethod.normEqDense);
        /* Set the input data */
        ridgeRegressionTraining.input.set(TrainingInputId.data, ntData);
        ridgeRegressionTraining.input.set(TrainingInputId.dependentVariable, ntLabels);

        /* Build a partial ridge regression model */
        PartialResult pres = ridgeRegressionTraining.compute();

        /* Write the data prepended with a data set sequence number. Needed to know the position of the data set in the input data */
        context.write(new IntWritable(0), new WriteableData(index, pres));
        index += totalTasks;

        daalContext.dispose();
    }

    private static void readData(String dataset, int nFeatures, int nVectors, double[] data) {
        System.out.println("readData " + dataset);
        try {
            Path pt = new Path(dataset);
            FileSystem fs = FileSystem.get(new Configuration());
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(fs.open(pt)));

            int nLine = 0;
            for (String line; ((line = bufferedReader.readLine()) != null) && (nLine < nVectors); nLine++) {
                String[] elements = line.split(",");
                for (int j = 0; j < nFeatures; j++) {
                    data[nLine * nFeatures + j] = Double.parseDouble(elements[j]);
                }
            }
            bufferedReader.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
