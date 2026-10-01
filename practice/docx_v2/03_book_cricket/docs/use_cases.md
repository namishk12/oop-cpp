# Use Case Notes

## UC1 Evaluate Page

Primary actor: `Innings`

1. Receive a non-negative page number.
2. Ask `BookCricketRules` for the delivery result.
3. Update runs and legal-ball count.
4. End the innings if the result is out or the over limit is reached.

Exceptional variations: negative page number; a delivery submitted after the
innings is complete.

## UC2 Play Match

Primary actor: caller or future UI adapter

1. Construct two innings with the selected starting batsman.
2. Feed pages to the first innings until it ends.
3. Feed pages to the second innings until it ends.
4. Compare the two scores and report a winner or tie.

The unit tests use fixed page vectors. A separate application may generate
those vectors using the standard library random facilities.
