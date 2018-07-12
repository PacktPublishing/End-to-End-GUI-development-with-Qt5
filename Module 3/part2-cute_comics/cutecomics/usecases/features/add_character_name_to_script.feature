Feature: Insert character name into script

    Scenario: No character names in script
        Given there is at least one character with name "X" in the characters list
        And there are no character names in the script
        When I insert character name "X" into the script
        Then a character name "X" appears in the script
