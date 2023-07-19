#include "op.hpp"
#include <iostream>

int main() {
    
    int* dataInt2x3 = new int[18] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    int* dataInt3x4 = new int[36] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
    float* dataFloat2x3 = new float[18] {1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f,16.0f,17.0f,18.0f};
    float* dataFloat3x4 = new float[36] {1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f,16.0f,17.0f,18.0f,19.0f,20.0f,21.0f,22.0f,23.0f,24.0f,25.0f,26.0f,27.0f,28.0f,29.0f,30.0f,31.0f,32.0f,33.0f,34.0f,35.0f,36.0f};

    Blob<int> blobInt2x3(2,3,3,dataInt2x3) ;
    Blob<int> blobInt3x4(3,4,3,dataInt3x4) ;
    Blob<int> blobIntCopy(blobInt2x3) ;
    Blob<float> blobFloat2x3(2,3,3,dataFloat2x3) ;
    Blob<float> blobFloat3x4(3,4,3,dataFloat3x4) ;

    // do operation
    //equals
    Blob<int> intEquals2x3 = blobInt2x3 ;
    Blob<float> floatEquals2x3 = blobFloat2x3 ;

    //plus
    Blob<int> plusInt2x3 = intEquals2x3 + blobInt2x3 ;
    Blob<float> plusFloat2x3 = floatEquals2x3 + blobFloat2x3 ;

    // minus
    Blob<int> minusInt2x3 = intEquals2x3 - blobInt2x3 ;
    Blob<float> minusFloat2x3 = floatEquals2x3 - blobFloat2x3 ;

    // multiply
    Blob<int> multiInt2x4 = blobInt2x3 * blobInt3x4 ;
    Blob<float> multiFloat2x4 = blobFloat2x3 * blobFloat3x4 ;

    // print the result ;
    
    std::tuple<int,int,int> shapeBlobInt2x3 = blobInt2x3.get_shape();
    std::tuple<int,int,int> shapeBlobInt3x4 = blobInt3x4.get_shape();

    std::tuple<int,int,int> shapeBlobFloat2x3 = blobInt2x3.get_shape();
    std::tuple<int,int,int> shapeBlobFloat3x4 = blobInt3x4.get_shape();

    std::tuple<int,int,int> shapeBlobIntCopy = blobIntCopy.get_shape();

    std::tuple<int,int,int> shapeIntEq2x3 = intEquals2x3.get_shape();
    std::tuple<int,int,int> shapeFloatEq2x3 = floatEquals2x3.get_shape();

    std::tuple<int,int,int> shapePlusInt2x3 = plusInt2x3.get_shape();
    std::tuple<int,int,int> shapePlusFloat2x3 = plusFloat2x3.get_shape();

    std::tuple<int,int,int> shapeMinusInt2x3 = minusInt2x3.get_shape();
    std::tuple<int,int,int> shapeMinusFloat2x3 = minusFloat2x3.get_shape();

    std::tuple<int,int,int> shapeMultiInt2x4 = multiInt2x4.get_shape();
    std::tuple<int,int,int> shapeBlobFloat2x4 = multiFloat2x4.get_shape();


    std::cout<< "Shape blobInt2x3x3: " << std::get<0>(shapeBlobInt2x3) << "x" << std::get<1>(shapeBlobInt2x3) << "x" << std::get<2>(shapeBlobInt2x3) << std::endl ;
    int*blob_data_1 = blobInt2x3.get_data();
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_1[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape blobInt3x4x3: " << std::get<0>(shapeBlobInt3x4) << "x" << std::get<1>(shapeBlobInt3x4) << "x" << std::get<2>(shapeBlobInt3x4) << std::endl ;
    int*blob_data_2 = blobInt3x4.get_data();
        for(int i=0 ; i<36 ; i++){
            std::cout<<blob_data_2[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape blobFloat2x3x3: " << std::get<0>(shapeBlobFloat2x3) << "x" << std::get<1>(shapeBlobFloat2x3) << "x" << std::get<2>(shapeBlobFloat2x3) << std::endl ;
    float*blob_data_3 = blobFloat2x3.get_data();
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_3[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape blobFloat3x4x3: " << std::get<0>(shapeBlobFloat3x4) << "x" << std::get<1>(shapeBlobFloat3x4) << "x" << std::get<2>(shapeBlobFloat3x4) << std::endl ;
    float*blob_data_4 = blobFloat3x4.get_data();
        for(int i=0 ; i<36 ; i++){
            std::cout<<blob_data_4[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape blobIntCopy: " << std::get<0>(shapeBlobIntCopy) << "x" << std::get<1>(shapeBlobIntCopy) << "x" << std::get<2>(shapeBlobInt2x3) << std::endl ;
    int*blob_data_5 = blobIntCopy.get_data() ;
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_5[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape intEq2x3: " << std::get<0>(shapeIntEq2x3) << "x" << std::get<1>(shapeIntEq2x3) << "x" << std::get<2>(shapeIntEq2x3) << std::endl ;
    int*blob_data_6 = intEquals2x3.get_data();
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_6[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape floatEq2x3: " << std::get<0>(shapeFloatEq2x3) << "x" << std::get<1>(shapeFloatEq2x3) << "x" << std::get<2>(shapeFloatEq2x3) << std::endl ;
    float*blob_data_7 = floatEquals2x3.get_data();
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_7[i]<<" ";
        }
        std::cout<<std::endl;


    std::cout<< "Shape intEquals2x3 + blobInt2x3 : " << std::get<0>(shapePlusInt2x3) << "x" << std::get<1>(shapePlusInt2x3) << "x" << std::get<2>(shapePlusInt2x3) << std::endl ;
    int*blob_data_8 = plusInt2x3.get_data();
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_8[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape floatEquals2x3 + blobFloat2x3: " << std::get<0>(shapePlusFloat2x3) << "x" << std::get<1>(shapePlusFloat2x3) << "x" << std::get<2>(shapePlusFloat2x3) << std::endl ;
    float*blob_data_9 = plusFloat2x3.get_data();
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_9[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape intEquals2x3 - blobInt2x3 : " << std::get<0>(shapeMinusInt2x3) << "x" << std::get<1>(shapeMinusInt2x3) << "x" << std::get<2>(shapeMinusInt2x3) << std::endl ;
    int*blob_data_10 = minusInt2x3.get_data() ;
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_10[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "Shape floatEquals2x3 - blobFloat2x3: " << std::get<0>(shapeMinusFloat2x3) << "x" << std::get<1>(shapeMinusFloat2x3) << "x" << std::get<2>(shapeMinusFloat2x3) << std::endl ;
    float*blob_data_11 = minusFloat2x3.get_data() ;
        for(int i=0 ; i<18 ; i++){
            std::cout<<blob_data_11[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<< "shape blobInt2x3 * blobInt3x4 : " << std::get<0>(shapeMultiInt2x4) << "x" << std::get<1>(shapeMultiInt2x4) << "x" << std::get<2>(shapeMultiInt2x4) << std::endl ;
    int*blob_data_12 = multiInt2x4.get_data();
        for(int i=0 ; i<24 ; i++){
            std::cout<<blob_data_12[i]<<" ";
        }
        std::cout<<std::endl;
        
    std::cout<< "shape blobFloat2x3 * blobFloat3x4 " << std::get<0>(shapeBlobFloat2x4) << "x" << std::get<1>(shapeBlobFloat2x4) << "x" << std::get<2>(shapeBlobFloat2x4) << std::endl ;
    float*blob_data_13 = multiFloat2x4.get_data();
        for(int i=0 ; i<24 ; i++){
            std::cout<<blob_data_13[i]<<" ";
        }
        std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<< "Is blobInt2x3 is same with blobInt3x4? " ;
    if(blobInt2x3==blobInt3x4){
        std::cout<<" YES."<<std::endl ;
    } else {
        std::cout<<" NO." <<std::endl ;
    }

    std::cout<<std::endl;
    std::cout<< "Is blobInt2x3 is same with intEquals2x3? " ;
    if(blobInt2x3==intEquals2x3){
        std::cout<<" YES."<<std::endl ;
    } else {
        std::cout<<" NO." <<std::endl ;
    }

    /*
    no need since already handled by destructor
    delete[] blob_data_1;
    delete[] blob_data_2;
    delete[] blob_data_3;
    delete[] blob_data_4;
    delete[] blob_data_5;
    delete[] blob_data_6;
    delete[] blob_data_7;
    delete[] blob_data_8;
    delete[] blob_data_10;
    delete[] blob_data_11;
    delete[] blob_data_12;
    delete[] blob_data_13;

    */


    return 0;
}