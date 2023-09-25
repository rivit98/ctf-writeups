# CursedNova, Dark matter, web 

## Description

There are great items for sell in the Dark Matter Shop! Check out the Officers tab.

## Solution

Looking at the code in `includes\pages\game\ShowOfficierPage.class.php` we see:


```
        $getFreeDarkMatter = HTTP::_GP('freeDarkMatter', '');

        if ($getFreeDarkMatter > 0 && $getFreeDarkMatter != 1) {
            if (strpos(strval($getFreeDarkMatter), ".")) {
                echo ("No chance!");
                exit;
            }

            $darkMatter = min(1 / $getFreeDarkMatter, 300);

            $this->setUserDarkMatter($USER['id'], $darkMatter);

            echo ("You now have " . $darkMatter . " Dark Matter.");

            exit;
        }
```

What is interesting here - `strpos`, normaly this should return the position of found character or value indicating that the value was not found at all (-1, NULL, ...).
So if we can make `strpos` return 0, `exit` function will not be executed. Knowing this, we set the first character as dot and the rest as fraction part - `.001`. The flag is ours!

Flag: `CURSEDNOVA{Deal_with_the_Devil_Oakai7az}`