# -*- coding: utf-8 -*-
class GameData:
    """GameData stores the data that needs to be shared
    When using multiple states in a game, you will find that
    some game data needs to be shared. In this instance GameData
    is used to share access to data that a the game and running
    states may need. You can think of this as a "blackboard" in
    UE terms.
    """

    def __init__(self) -> None:
        """Inits the shared fields"""
        self.background_audio = None
        self.fonts = {}
        self.background_volume = 0.5
        self.inputs = None
        self.font = None

        # scrolling backgrounds
        self.background = None
        self.parallax = []
