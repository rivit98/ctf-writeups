# CursedNova, Mindblown, web 

## Description
Hey, hey - here! Do you want something good? I've got something nice, just look into your messages, the one from the Administrator. This will blow your mind!

## Solution

Message:

![msg](./img/msg.png)

This looks like brainfuck. Quick look at source and we see that there are html comments with parts of brainfuck code:

![source](./img/source.png)

By writing simple [script](./solve.py) we can extract the full brainfuck code from the message. Now all we have to do is run the following code (https://copy.sh/brainfuck/).

```
++++[++++>---<]>.>-[--->+<]>.---.+.[->+++++++<]>.-.++++++++++.+.+++++++.++[---->+++<]>-.---[->++<]>-.+[-->+<]>++++.---[----->+<]>-.[-->+<]>-----.---.+++[-->+++<]>.[----->+++<]>.++++++++++.+++.++++++++.---------.[--->+<]>+++.
```

Flag: `CURSEDNOVA{Br41Nblown}`
