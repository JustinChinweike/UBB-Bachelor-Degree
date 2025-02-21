from functools import partial

from library.src.tic_tac_toe.logic.models import GameState, Mark, Move


def find_best_move(game_state: GameState) -> Move | None:
    maximizer: Mark = game_state.current_mark
    bound_minimax = partial(minimax, maximizer=maximizer)
    return max(game_state.possible_moves, key=bound_minimax)


def minimax(
        move: Move, maximizer: Mark, choose_highest_score: bool = False
) -> int:
    if move.after_state.game_over:
        return move.after_state.evaluate_score(maximizer)
    return (max if choose_highest_score else min)(
        minimax(next_move, maximizer, not choose_highest_score)
        for next_move in move.after_state.possible_moves
    )













# The minimax algorithm starts by recursively exploring the tree to look ahead
# and find all the possible game outcomes. Once those are found,
# it computes their scores and backtracks to the starting node.
# If it’s the maximizing player’s turn that leads to the next position,
# then the algorithm picks the maximum score at that level.
# Otherwise, it picks the minimum score, assuming the opponent will never make mistakes.
