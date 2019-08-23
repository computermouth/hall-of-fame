# week5 homework

1. Score
2. Countdown
3. Menu

## Score

* both players start at 0
* the number should be displayed somewhere on screen at all times
* when score reaches 10 call `ww_window_send_quit_event();`

## Countdown

* at start of game, display countdown 3... 2... 1... then ball starts moving
* countdown should be actual seconds, figure out the math, or checkout `man time`
* ^^Gonna have to google it

## Menu

* main menu has 2 options, play, quit
* quit calls `ww_window_send_quit_event();`
* play launches into Countdown
* When a player wins, it now brings you back to the menu

## Settings Menu

* increase ball speed
