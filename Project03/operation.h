
typedef struct
{
    int width ;
    int height ;
    int channel ;
    float *** elements ;
} MATRIX;

MATRIX * create_matrix3D(int channel, int width, int height);
MATRIX * convo_operation(MATRIX* image, MATRIX* filter, int strides) ;
MATRIX * padding(MATRIX* image, int channel, int width, int height, int pad_width, int pad_height) ;
MATRIX * ReLU(MATRIX* image) ;
void print_matrix(MATRIX* matrix) ;
void free_matrix(MATRIX* matrix) ;
