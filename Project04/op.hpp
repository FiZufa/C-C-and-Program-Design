
//#pragma once
#include <tuple>
#include <iostream>
#include <algorithm>

template <typename T>
class Blob{

    private:
        int height ;
        int width ;
        int channel ;
        T* data ;

    public:

        // constructor
        Blob() ;
        Blob(int h, int w, int c, T* data) ;
        Blob(const Blob<T>& other);
        // destructor
        ~Blob() ;

        // get the members
        T* get_data() const;
        std::tuple<int,int,int> get_shape() const;
        int get_num_height() const;
        int get_num_width() const;
        int get_num_channel() const;
    
        //operator function
        Blob& operator=(const Blob<T>& other);
        bool operator==(const Blob<T>& other);
        Blob operator+(const Blob<T>& other);
        Blob operator-(const Blob<T>& other);
        Blob operator*(const Blob<T>& other);
        
} ;



// consructor
template <typename T>
Blob<T>::Blob() {
    height = 0 ;
    width = 0 ;
    channel = 0 ;
    data = nullptr ;
}

template <typename T>
Blob<T>::Blob(int height, int width, int channel, T* data){
    this->height = height ;
    this->width = width ;
    this->channel = channel ;
    this->data = data ;
}

template <typename T>
Blob<T>::Blob(const Blob<T>& other){ //copy constructor

    // parameter checking
    if(&other == this){
        return ;
    }

    this->height = other.height;
    this->width = other.width;
    this->channel = other.channel;
    this->data = other.data;

}

//destructor
template<typename T>
Blob<T>::~Blob(){
    delete[] data ;
}

// get the members

template <typename T>
int Blob<T>::get_num_width() const{
    return width ;
}

template <typename T>
int Blob<T>::get_num_height() const{
    return height ;
}

template <typename T>
int Blob<T>::get_num_channel() const{
    return channel ;
}

template <typename T>
std::tuple<int, int, int> Blob<T>::get_shape() const{
    return std::make_tuple(height, width, channel) ;
}

template <typename T>
T* Blob<T>::get_data() const {
    return data;
}

// operator function
template <typename T>
Blob<T>& Blob<T>::operator=(const Blob<T>& other){ // copy assignment

    if(this == &other){
        return *this;
    }

    height = other.height;
    width = other.width;
    channel = other.channel;

    if(data){
        delete[] data ; 
    }


    data = other.data ; 
    return *this ;

}

template <typename T>
bool Blob<T>::operator==(const Blob<T>& other){
    // parameter checking if nullptr
    if(data==nullptr || other.data==nullptr){
        throw std::invalid_argument("cannot compare since the data is null") ;
    }

    if(this->width != other.width || this->height != other.height || this->channel != other.channel || other.data == nullptr){
        return false ;
    }

    for(int i=0 ; i<width*height*channel ; i++){
        if(this->data[i] != other.data[i]){
            return false ;
        }
    }

    return true ;
}

template <typename T>
Blob<T> Blob<T>::operator+(const Blob<T>& other){
    //parameter checking size and if nullptr
    if(height != other.height || width != other.width || channel != other.channel){
        throw std::invalid_argument("Cannot do + operation since they have different size") ;
    }
    if(data == nullptr || other.data == nullptr){
        throw std::invalid_argument("Cannot do + operation since the data is null") ;
    }

    T * new_data = new T[height*width*channel];

    for(int i=0 ; i<width*height*channel ; i++){
        new_data[i] = data[i] + other.data[i] ;
    }

    return Blob<T>(height, width,channel,new_data) ;
}

template <typename T>
Blob<T> Blob<T>::operator-(const Blob<T>& other){

    //parameter checking size and if nullptr
    if(height != other.height || width != other.width || channel != other.channel){
        throw std::invalid_argument("Cannot do + operation since they have different size") ;
    }
    if(data == nullptr || other.data == nullptr){
        throw std::invalid_argument("Cannot do + operation since the data is null") ;
    }

    T* new_data = new T[height*width*channel] ;

    for(int i=0 ; i<height*width*channel ; i++){
        new_data[i] = data[i] - other.data[i] ;
    }


    return Blob<T>(height, width, channel, new_data) ;
}

template <typename T>
Blob<T> Blob<T>::operator*(const Blob<T>& other){
    //parameter checking
    if(data==nullptr || other.data == nullptr){
        throw std::invalid_argument("Cannot do * operation since the data is null") ;
    }
    if(width != other.height || channel != other.channel){
        throw std::invalid_argument("Cannot do * operation since they have different size") ;
    }

    int len = height*other.width*channel ;

    T* new_data = new T[len]{0} ;

    for(int c=0 ; c<channel ; c++){
        for(int i=0 ; i<height ; i++){
            for(int j=0 ; j<other.width ; j++){
                int sum = 0 ;
                for(int k=0 ; k<width ; k++){

                    sum += (data[c*i*width + k] + other.data[c*k*other.width + j]);

                }
                new_data[i*other.width + j] = sum ;

            }
            
    
        }
    }

    return Blob<T>(height,other.width,channel,new_data);

}






