#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include "Actor.class.hpp"

	class GameState {

		Vector2D 			_winDem;
		GameState::State	_curState;
		Actor				*_actors;

	public:

		enum				State {
							LOADING,
							PLAYING,
							GAMEOVER
		};

		GameState(void);
		GameState(Vector2D _winDem);
		GameState(GameState const &src);
		~GameState(void);

		GameState			&operator=(GameState const &rhs);

		Vector2D			getWinDem(void) const;
		Game::State			getCurState(void) const;
		Actors				*getAllActors(void) const;

	private:

	};

	// To print the game state info
	std::ostream      				&operator<<(std::ostream &o, GameState const &i);

#endif
