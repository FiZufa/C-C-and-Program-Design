#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

int main(){
    
    int channel =  3 ;
    int img_width, img_height ;

    printf("Enter the width of the image : ") ;
    scanf("%d", &img_width) ;
    printf("Enter the height of the image : ") ;
    scanf("%d", &img_height) ;

    // 1) create the matrix for input RGB image
    MATRIX* image = create_matrix3D(channel, img_width, img_height) ; 

    for(int i=0 ; i<channel ; i++){
        printf("layer %d\n", i+1) ;
        for(int j=0 ; j<img_width ; j++){
            for(int k=0 ; k<img_height ; k++){

                float in ; 
                scanf("%f", &in) ;
                image -> elements[i][j][k] = in ;
            }
        }
    }

    //print_matrix(image) ;

    // determine the filter (kernel)
    int filter_width ;
    int filter_height ;

    printf("Filter (kernel) width : ") ;
    scanf("%d", &filter_width) ;
    printf("Filter (kernel) height : ") ;
    scanf("%d", &filter_height) ;

    MATRIX* filter = create_matrix3D(channel, filter_width, filter_height) ; 

    for(int i=0 ; i<filter->channel ; i++){
        printf("layer filter %d\n", i+1) ;
        for(int j=0 ; j<3 ; j++){
            for(int k=0 ; k<3 ; k++){

                float in ; 
                scanf("%f", &in) ;
                filter -> elements[i][j][k] = in ;

            }
        }
    }

    //print_matrix(filter);
    // determine stride size
    int stride ;
    printf("Input stride size : ") ;
    scanf("%d", &stride) ;

    printf("\n") ;

    // padding

   int pad_width ;
   int pad_height ;
   printf("Input padding width size : ") ;
   scanf("%d", &pad_width) ;
    printf("Input padding width size : ") ;
   scanf("%d", &pad_height) ;

   MATRIX * padding_matrix = padding(image, channel, img_width, img_height, pad_width, pad_height) ;

   printf("The matrix after padding is : \n") ;
   print_matrix(padding_matrix) ;

   printf("\n") ;

    // convolution matrix
   MATRIX* operated_matrix = convo_operation(padding_matrix, filter, stride) ;

   printf("Feature map matrix after convolution operation:  \n") ;
   
   print_matrix(operated_matrix) ;

   printf("\n") ;

    // do ReLU
    MATRIX * relu = ReLU(operated_matrix) ;

    printf("The matrix after ReLU performed : \n") ;

    print_matrix(relu) ;


    free_matrix(image) ;
    free_matrix(filter) ;
    free_matrix(operated_matrix) ;
    free_matrix(padding_matrix) ;
    free(relu) ;


    return 0 ;
    
}
