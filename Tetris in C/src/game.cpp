#include "../classes/config.hpp"
#include "../classes/point.hpp"
#include "../classes/game.hpp"
#include "board.cpp"

Game::Game() {
    // Declare Board
    this->board = new Board(Config::complete_vertical_squares, Config::horizontal_squares);
    this->piece = new Piece();
    this->old_piece = new Piece();
    this->piece->copy(this->old_piece);
}
Game::~Game() {
    delete board;
    delete piece;
}
void Game::move_left() {
    dx = -1;
    dx_count -= dx_count == 0 ? 0 : 1;
    this->piece->move(-1);
    if (this->board->has_colitions_border_or_remains(this->piece)) 
        this->old_piece->copy(this->piece);
}

void Game::move_right() {
    dx = 1;
    dx_count += dx_count == Config::horizontal_squares ? 0 : 1;
    this->piece->move(1);
    if (this->board->has_colitions_border_or_remains(this->piece)) 
        this->old_piece->copy(this->piece);
}
void Game::descend() {
    this->dy = 1;
    this->dy_count += this->dy_count == Config::complete_vertical_squares ? 0 : 1;
    this->piece->descend(1);
}

void Game::rotate() {
    Point center_point = this->piece->get_center_point();
    for (int i = 0; i < 4; i++) {
        int rotate_x = this->piece->get_point(i).y - center_point.y;
        int rotate_y = this->piece->get_point(i).x - center_point.x;         
        this->piece->set_point(center_point.x - rotate_x, center_point.y + rotate_y, i);
    }
    if (this->dx_count == 0) {
        while (this->board->has_colitions_border_or_remains(this->piece)) {
            this->piece->move(1);
        }
        while (!this->piece->touching_zero_border()) {
            this->piece->move(-1);
        }
    }  
    if (this->dy_count == 0) {
        while (this->piece->has_colitions_top()) {
            this->piece->descend(1);
        }
        while (!this->piece->touching_zero_top()) {
            this->piece->descend(-1);
        }
    }        
}

bool Game::is_game_over() {
    return this->board->get_row_quantity() > Config::vertical_squares;
}
void Game::clean_for_cycle() {
    if (complete_lines > 10 && level < 4) {
        complete_lines -= 10;
        level += 1;
    } 
    dx = 0, dy = 0;
    this->piece->copy(this->old_piece);
}
int Game::get_score() {
    return score;
}
int Game::get_level() {
    return level;
}

void Game::check_state() {
    if (this->dx == 0 && this->board->has_colitions_bottom_or_remains(this->piece)) {
        this->old_piece->copy(this->piece);
        this->board->add_piece(this->piece);
        // Check Board for complete lines
        int complete_lines_quantity = this->board->delete_complete_lines();
        this->score += Config::scores[complete_lines_quantity - 1];
        this->complete_lines += complete_lines_quantity;
        this->piece = new Piece();
        this->piece->copy(this->old_piece);
        this->dx_count = 0;
        this->dy_count = 0;
    }
}

int Game::get_point_quantity() {
    int point_quantity = 0;
    int row_len = this->board->get_row_quantity();
    for (int j = 0; j < row_len; j++)
    {
        int column_len = this->board->get_column_quantity(j);
        point_quantity += column_len;
    }

    return point_quantity + 4;
}

Point* Game::get_all_points() {

    int** columns = this->board->get_columns();
    int row_len = this->board->get_row_quantity();
    int point_quantity = this->get_point_quantity();
    Point* points = (Point*) malloc(sizeof(Point) * point_quantity);

    int point_index = 0;
    for (int j = 0; j < row_len; j++)
    {
        int* column = columns[j];
        int column_len = this->board->get_column_quantity(j);
        for (int i = 0; i < column_len; i++)
        {
            int real_y = Config::complete_vertical_squares - 1 - j;
            int position_x = column[i];
            int position_y = real_y;
            Point point;
            point.x = position_x;
            point.y = position_y;
            points[point_index] = point;
            point_index++;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        points[i + point_index] = this->piece->get_point(i);
    }

    return points;
}