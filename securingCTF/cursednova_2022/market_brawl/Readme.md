# CursedNova, Market brawl, web 

## Description

Those Rexxan's knuckleheads are brawling at the Market area. Head over there and get that silly idea out of their empty heads.

## Solution

Looking at `includes\pages\game\ShowTraderPage.class.php` we see the following code:

```
    public function show()
    {
        global $LNG, $USER, $resource;

        $darkmatter_cost_trader = Config::get()->darkmatter_cost_trader;

        $this->assign(array(
            'tr_cost_dm_trader' => sprintf($LNG['tr_cost_dm_trader'], pretty_number($darkmatter_cost_trader), $LNG['tech'][921]),
            'charge' => self::$Charge,
            'resource' => $resource,
            'requiredDarkMatter' => $USER['darkmatter'] < $darkmatter_cost_trader ? sprintf($LNG['tr_not_enought'], $LNG['tech'][921]) : false,
        ));
        if ($_SERVER['REQUEST_METHOD'] === 'HEAD') {
            header('Secret: ' . $LNG['W19_BRAWL']);
        }
        $this->display("page.trader.default.tpl");
    }
```

so it is enough to do a HEAD request...

Flag: `CURSEDNOVA{Request_method_matters_tuyoh8Oh}`