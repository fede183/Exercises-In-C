
#ifndef CONFIG_HPP
#define CONFIG_HPP
namespace Config
{
    const int square_sixe = 25; 
    const int horizontal_squares = 10;
    const int vertical_squares = 27;
    const int invisible_squares = 3;
    const int header_squares = 2;
    const int side_block_width = 8;
    const int complete_vertical_squares = vertical_squares + invisible_squares;
    const int display_width = square_sixe*horizontal_squares; 
    const int display_side_block_width = square_sixe*side_block_width; 
    const int display_heigth = square_sixe*(vertical_squares + header_squares + invisible_squares);
    const int display_header = square_sixe*(header_squares + invisible_squares);
    

    const int next_piece_block_width = 6;
    const int next_piece_block_heigth = 7;
    const int display_next_piece_block_width = square_sixe*next_piece_block_width; 
    const int display_next_piece_block_heigth = square_sixe*next_piece_block_heigth; 
    const int next_piece_block_position_x = horizontal_squares + 1;
    const int next_piece_block_position_y = header_squares + invisible_squares + 3;
    const int display_next_piece_block_position_x = square_sixe*next_piece_block_position_x;
    const int display_next_piece_block_position_y = square_sixe*next_piece_block_position_y;

    const int scores[4] = {40, 100, 300, 1200};
    const float delays_for_level[4] = {0.48, 0.43, 0.38, 0.33};

    //------
    //|0|1|8|12|
    //|2|3|9|13|
    //|4|5|10|14|
    //|6|7|11|15|
    //------

    const int figures[7][4] = {
        0, 2, 4, 6, //I
        1, 2, 3, 4, //Z
        0, 2, 3, 5, //S
        0, 2, 4, 5, //L
        1, 2, 3, 5, //T
        0, 1, 2, 3, //O
        1, 3, 4, 5, //J
    };


};
#endif // CONFIG_HPP
