Feature: Add element to composition

    Scenario: Zero to one elements
        Given a composition with zero elements in it
        When I add an element with element id "A" to the composition
        Then the composition contains exactly one element
        And the new contained element's id is "A"

    Scenario: one to two elements
        Given a composition with one element in it
        When I add an element with element id "B" to the composition
        Then the composition contains exactly two elements
        And the new contained element's id is "B"
