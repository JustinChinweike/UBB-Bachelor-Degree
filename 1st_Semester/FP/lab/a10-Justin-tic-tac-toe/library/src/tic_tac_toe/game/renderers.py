import abc

from library.src.tic_tac_toe.logic.models import GameState


class Renderer(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def render(self, game_state: GameState) -> None:
        """Render the current game state."""
