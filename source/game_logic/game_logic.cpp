#include "game_logic.hpp"

#include <algorithm>
#include <array>
#include <iostream>

GameLogic::GameLogic() : _board(9, 9), _state(kPaused), _goal(50), _score(0) {
  ;
}

GameLogic::~GameLogic() { ; }

void GameLogic::mouse_click(float x, float y) {
  _board.drag_start({x, y});
  switch (_state) {
    case kPlaying: {
      break;
    }
    case kPaused: {
      _state = kPlaying;
      break;
    }
    case kLevelComplete: {
      _goal *= 1.5f;
      _board.create(_board.width() + 3, _board.height() + 3);
      _score = 0;
      _state = kPlaying;
      break;
    }
  }
}

void GameLogic::mouse_move(float x, float y) { _board.drag_move({x, y}); }

void GameLogic::mouse_release(float x, float y) {
  _score += _board.drag_release_and_check_move({x, y});
  if (_score >= _goal) {
    _board.clear();
    _state = kLevelComplete;
  }
}

const GameBoard &GameLogic::game_board() { return _board; }

int GameLogic::goal() { return _goal; }

int GameLogic::score() { return _score; }

GameLogic::GameState GameLogic::game_state() { return _state; }
