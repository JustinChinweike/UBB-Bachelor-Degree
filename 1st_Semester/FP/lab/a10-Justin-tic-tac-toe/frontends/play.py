from library.src.tic_tac_toe.game.engine import TicTacToe
from library.src.tic_tac_toe.game.players import RandomComputerPlayer, MinimaxComputerPlayer
from library.src.tic_tac_toe.logic.models import Mark

from console.console_players import ConsolePlayer
from console.console_renderers import ConsoleRenderer

player1 = ConsolePlayer(Mark("X"))
# player2 = RandomComputerPlayer(Mark("O"))
player2 = MinimaxComputerPlayer(Mark("O"))

TicTacToe(player1, player2, ConsoleRenderer()).play()
