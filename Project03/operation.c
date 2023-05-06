#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

void print_matrix(MATRIX* matrix){
    if(matrix == NULL){
        printf("Invalid matrix null") ;
        exit(1) ;
    }

    for(int i=0 ; i<matrix->channel ; i++){
        printf("layer %d\n", i+1) ;
        for(int j=0 ; j<matrix->width ; j++){
            for(int k=0 ; k<matrix -> height ; k++){

                printf("%.f ", matrix -> elements[i][j][k]) ;
            }
            printf("\n") ;
        }
        printf("\n") ;
    }
}

MATRIX * create_matrix3D(int channel, int width, int height){
    if(channel<1 || width<1 || height<1){
        printf("invalid, cannot create matrix!") ;
        exit(1) ;
    }

    MATRIX* matrix = (MATRIX*) malloc(sizeof(MATRIX)) ;

    matrix -> channel = channel ;
    matrix -> width = width ;
    matrix -> height = height ;

    matrix -> elements = (float***) malloc(channel*sizeof(float**)) ;
    for(int i=0 ; i<channel ; i++){
        matrix -> elements[i] = (float**) malloc(width*sizeof(float*)) ;
        for(int j=0 ; j<width ; j++){
            matrix -> elements[i][j] =(float*) malloc(height*sizeof(float)) ;
        }
    }

    return matrix ;
}

MATRIX * convo_operation(MATRIX* image, MATRIX* filter, int strides) {
    if(image ->channel != filter -> channel){
        printf("can't do operation since image and filter have different number of channels\n") ;
        exit(1) ;
    }
    if(image == NULL || filter == NULL){
        printf("Invalid matrix\n") ;
        exit(1) ;
    }

    int img_width = image -> width ;
    int img_height = image -> height ;
    int channel = image -> channel ;

    int filter_width = filter -> width ;
    int filter_height = filter -> height ;

    int width = ((img_width-filter_width)/strides) + 1 ;
    int height = ((img_height-filter_height)/strides) + 1 ;

    MATRIX * result = create_matrix3D(channel, width, height) ;

    int x = 0.0f;
    int y = 0.0f ;

    for(int c=0 ; c<channel ; c++){
        for(int i=0 ; i<width ; i+=strides){
            for(int j=0 ; j<height ; j++){
                result->elements[c][i/strides][j/strides] = 0.0f ;
                for(int fi=0 ; fi<filter_width ; fi++){
                    for(int fj=0 ; fj<filter_height ; fj++){
                        for(int k=0 ; k<strides ; k++){
                            x = i + k + fi ;
                            y = j + k + fj ;
                            result->elements[c][i/strides][j/strides] += image->elements[c][x][y] * filter->elements[c][fi][fj] ;
                        }
                    }
                }
            }
        }
    }

    

   return result ;

}

MATRIX * padding(MATRIX* image, int channel, int width, int height, int pad_width, int pad_height){

    if(image == NULL){
        printf("Invalid matrix\n") ;
        exit(1) ;
    }

    if(pad_width==0 && pad_height==0){
        return image ;
    }

    int new_width = width + 2*pad_width ;
    int new_height = height + 2*pad_height ;

    MATRIX * new_padded_img = create_matrix3D(channel, new_width, new_height) ;

    // initialize to be zero
    for(int c=0 ; c<channel ; c++){
        for(int w=0 ; w<new_width ; w++){
            for(int h=0 ; h<new_height ; h++){

                new_padded_img -> elements[c][w][h] = 0.0f ;
            }
        }
    }

    for(int c=0 ; c<channel ; c++){
        for(int w=pad_width ; w<new_width-pad_width ; w++){
            for(int h=pad_height ; h<new_height-pad_height ; h++){

                new_padded_img -> elements[c][w][h] = image -> elements[c][w-pad_width][h-pad_height] ;
            }
        }
    }

    return new_padded_img ;

}

MATRIX * ReLU(MATRIX* image){
    if(image==NULL){
        printf("Invalid matrix");
        exit(1) ;
    }

    int channel = image -> channel ;
    int width = image -> width ;
    int height = image -> height ;

    MATRIX * after_ReLU_matrix = create_matrix3D(channel, width, height) ;

    for(int c=0 ; c<channel ; c++){
        for(int w=0 ; w<width ; w++){
            for(int h=0 ; h<height ; h++){
                
                if(image -> elements[c][w][h] < 0){
                    after_ReLU_matrix -> elements[c][w][h] = 0; 
                } else {
                    after_ReLU_matrix -> elements[c][w][h] = image -> elements[c][w][h] ;
                }

            }
        }
    }

    return after_ReLU_matrix ;
}

void free_matrix(MATRIX* matrix){
    for(int i=0 ; i<matrix->channel ; i++){
        for(int j=0 ; j<matrix->width ; j++){
            
            free(matrix->elements) ;
        }
        free(matrix->elements[i]);
    }

    free(matrix->elements) ;
    free(matrix) ;
    matrix = NULL ;
}
