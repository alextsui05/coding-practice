#include <iostream>

#include <png++/png.hpp>

template < class TPixel >
void rotate_cw( png::image< TPixel >& M ) {
    const int N = M.get_height( ); // assume square
    for ( int i = 0; i < N / 2; ++i ) {
        for ( int k = 0; k < N - 2*i - 1; ++k ) {
            TPixel tmp = M[ i + k ][ i ];
            M[ i + k ][ i ] = M[ i ][ N - i - 1 - k ];
            M[ i ][ N - i - 1 - k ] = M[ N - i - 1 - k ][ N - i - 1 ];
            M[ N - i - 1 - k ][ N - i - 1 ] = M[ N - i - 1 ][ i + k ];
            M[ N - i - 1 ][ i + k ] = tmp;
        }
    }
}

int main(int argc, char* argv[])
{
    png::image< png::rgb_pixel > image( 128, 128 );
    for ( size_t y = 0; y < image.get_height( ); ++y ) {
        for ( size_t x = 0; x < image.get_width( ); ++x ) {
            image[ y ][ x ] = png::rgb_pixel( x, y, x + y );
        }
    }
    image.write( "rgb.png" );

    rotate_cw( image );

    image.write( "rgb.rotated.png" );
    return 0;
}
