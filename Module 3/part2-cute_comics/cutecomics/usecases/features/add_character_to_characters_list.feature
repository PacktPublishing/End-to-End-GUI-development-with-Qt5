Feature: Add character to characters list

    Scenario: No characters in characters list
        Given there are no characters in the characters list
        When I add a character with name "X" to the characters list
        Then there is a character with name "X" in the characters list
