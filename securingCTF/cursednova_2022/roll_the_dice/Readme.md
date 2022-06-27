# CursedNova, Roll the dice, web

## Description

Wise man once said "Fortune favours the brave". Can you beat the odds and roll the dice 100 times with all of them landing on 1? Hop in the chat and try your luck with the /roll command!

## Solution

Let's visit the chat subpage, we see the option to roll the dice.

[chat](./img/chat.png)

After clicking the "Roll dice" option, the message field is filled with the following command `/roll`. Grepping by this we find:

```
                // Rolling dice:
                case '/roll':
                    $this->insertParsedMessageRoll($textParts);
                    break;
```

```
    public function insertParsedMessageRoll($textParts)
    {
        if (count($textParts) == 1) {
            // default is one d6:
            $text = '/roll ' . $this->getUserName() . ' 1d6 ' . $this->rollDice(6);
        } else {
            $diceParts = explode('d', $textParts[1]);
            if (count($diceParts) == 2) {
                $number = (int) $diceParts[0];
                $sides = (int) $diceParts[1];

                // Dice number must be an integer between 1 and 100, else roll only one:
                $number = ($number > 0 && $number <= 100) ? $number : 1;

                // Sides must be an integer between 1 and 100, else take 6:
                $sides = ($sides > 0 && $sides <= 100) ? $sides : 6;

                $text = '/roll ' . $this->getUserName() . ' ' . $number . 'd' . $sides . ' ';
                $showFlag = true;
                for ($i = 0; $i < $number; $i++) {
                    if ($i != 0) {
                        $text .= ',';
                    }

                    $rolled_number = $this->rollDice($sides);
                    $text .= $rolled_number;
                    if ($rolled_number != 1) {
                        $showFlag = false;
                    }

                }

                // W5
                // Show flag if 100 dice rolls and all of them landed on 1.
                if ($showFlag == true && $number == 100) {
                    include_once 'language/en/FLAGS.php';
                    $text .= $LNG["W5_ROLL_THE_DICE"];
                }

            } else {
                // if dice syntax is invalid, roll one d6:
                $text = '/roll ' . $this->getUserName() . ' 1d6 ' . $this->rollDice(6);
            }
        }
        $this->insertChatBotMessage(
            $this->getPrivateMessageID(),
            $text
        );
    }
```

So we are controlling the number of dice sides - it is enough to use this command: `/roll 100d1`

Flag: `CURSEDNOVA{They_see_me_rollin_chunaeF6}`